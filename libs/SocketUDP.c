#define _XOPEN_SOURCE 500
#include "SocketUDP.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int _initSockAddr(const char *address, int port, struct sockaddr_in *in) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;

    int s;
    struct addrinfo * info;
    char port2[10];
    snprintf(port2, 10, "%d", port);

    if ((s = getaddrinfo(address, port2, &hints, &info)) != 0) {
        return s;
    }
    in = memcpy(in, info->ai_addr, sizeof (struct sockaddr_in));
    freeaddrinfo(info);
    return 0;
}

int _fillSocketUDP(SocketUDP* s) {
    struct sockaddr_in in;
    socklen_t addr_len = sizeof (struct sockaddr_in);
    if (getsockname(s->socket, (struct sockaddr*) &in, &addr_len) == -1) {
        return -1;
    }

    char host[256];
    char serv[256];
    if (getnameinfo((struct sockaddr *) &in, sizeof (struct sockaddr_in),
            host, 256, serv, 256, NI_NUMERICSERV | NI_DGRAM) != 0) {
        return -1;
    }
    s->local.name = (char *) malloc(strlen(host) + 1);
    if (s->local.name == NULL) {
        return -1;
    }
    s->local.name[strlen(host)] = 0;
    strncpy(s->local.name, host, strlen(host));
    s->local.port = (int) atoi(serv);

    if (getnameinfo((struct sockaddr *) &in, sizeof (struct sockaddr_in),
            host, 256, NULL, 0, NI_NUMERICHOST | NI_DGRAM) != 0) {
        free(s->local.name);
        return -1;
    }
    s->local.ip = (char *) malloc(strlen(host) + 1);
    if (s->local.ip == NULL) {
        free(s->local.name);
        return -1;
    }
    s->local.ip[strlen(host)] = 0;
    strncpy(s->local.ip, host, strlen(host));
    return 0;
}

SocketUDP* creerSocketUDP(void) {
    SocketUDP* res = (SocketUDP*) malloc(sizeof (SocketUDP));
    if (res == NULL) {
        return NULL;
    }
    memset(res, 0, sizeof (SocketUDP));
    res->socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (res->socket == -1) {
        free(res);
        return NULL;
    }
    res->local.name = NULL;
    res->local.ip = NULL;
    res->local.port = -1;
    return res;
}

SocketUDP* creerSocketUDPAttachee(const char * address, int port) {
    SocketUDP* res = (SocketUDP*) malloc(sizeof (SocketUDP));
    if (res == NULL) {
        return NULL;
    }
    memset(res, 0, sizeof (SocketUDP));
    res->socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (res->socket == -1) {
        free(res);
        return NULL;
    }
    struct sockaddr_in in;
    _initSockAddr(address, port, &in);
    bind(res->socket, (struct sockaddr *) &in, sizeof (struct sockaddr_in));

    _fillSocketUDP(res);
    return res;
}

char * getLocalName(SocketUDP * s) {
    if (s == NULL) {
        return NULL;
    }
    return s->local.name;
}

char * getLocalIP(SocketUDP * s) {
    if (s == NULL) {
        return NULL;
    }
    return s->local.ip;
}

int getLocalPort(SocketUDP * s) {
    if (s == NULL) {
        return -1;
    }
    return s->local.port;
}

int writeToSocketUDP(SocketUDP* s, const char * addr, int port,
        const char * buf, int len) {
    struct sockaddr_in in;
    _initSockAddr(addr, port, &in);
    socklen_t addr_len = sizeof (struct sockaddr_in);
    int ret = sendto(s->socket, buf, len, 0, (struct sockaddr*) &in, addr_len);
    if (s->local.port == -1) {
        if (_fillSocketUDP(s) == -1) {
            return -1;
        }
    }
    return ret;
}

int readFromSocketUDP(SocketUDP* s, char *buffer, int length,
        char *address, int *port, int timeout) {
    struct sockaddr_in in;
    socklen_t addr_len = sizeof (struct sockaddr_in);
    char addr[256];

    struct timeval t;
    memset(&t, 0, sizeof (struct timeval));
    if (timeout > 0) {
        t.tv_sec = timeout;
    }
    setsockopt(s->socket, SOL_SOCKET,
            SO_RCVTIMEO, &t,
            sizeof (struct timeval));
    int ret = recvfrom(s->socket, buffer, length, 0,
            (struct sockaddr*) &in, &addr_len);

    *port = ntohs(in.sin_port);
    if (getnameinfo((struct sockaddr *) &in, sizeof (struct sockaddr_in),
            addr, 255, NULL, 0, NI_DGRAM) != 0) {
        return ret;
    }
    addr[strlen(addr)] = 0;
    strncpy(address, addr, 256);

    return ret;
}

int closeSocketUDP(SocketUDP* s) {
    if (s->local.name != NULL) {
        free(s->local.name);
    }

    if (s->local.ip != NULL) {
        free(s->local.ip);
    }

    if (close(s->socket) == -1) {
        return -1;
    }
    free(s);
    return 0;
}
