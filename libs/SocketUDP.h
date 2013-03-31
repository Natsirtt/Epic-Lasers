#ifndef _SOCKET_UDP_H
#define _SOCKET_UDP_H

typedef struct {
    char* name;
    char* ip;
    int port;
} id;

typedef struct {
    int socket;
    id local;
} SocketUDP;

/**
 * Crée et retourne un pointeur sur une nouvelle SocketUDP
 * @return un pointeur sur la SocketUDP nouvellement créée
 */
SocketUDP* creerSocketUDP();

/**
 * Crée et retourne un pointeur sur une nouvelle SocketUDP attachée
 * à l'adresse <b>address</b> sur le port <b>port</b>.
 * @param address
 * @param port
 * @return un pointeur sur la SocketUDP nouvellement créée
 */
SocketUDP* creerSocketUDPAttachee(const char * address, int port);

/**
 * Indique le nom de la machine locale enregistrée sur la SocketUDP
 * pointée par <b>s</b>
 * @param s
 * @return La chaine de caractère décrivant le nom de la machine locale.
 */
char * getLocalName(SocketUDP * s);

/**
 * Indique l'ip de la machine locale sous forme pointée.
 * @param s
 * @return La chaine de caractères décrivant l'ip de la machine locale.
 */
char * getLocalIP(SocketUDP * s);

/**
 * Indique le numéro de port utilisé par la SocketUDP pointée par <b>s</b>.
 * @param s
 * @return Le numéro de port attribué à la SocketUDP pointée par <b>s</b>
 */
int getLocalPort(SocketUDP * s);

/**
 * Écrit <b>len</b> octets de <b>buf</b> dans la SocketUDP pointée par
 * <b>s</b> pour la machine à l'adresse <b>addr</b> sur le port <b>port</b>.
 * @param s
 * @param addr
 * @param port
 * @param buf
 * @param len
 * @return Le nombre d'octets écrits sur la socket ou -1 en cas d'erreur.
 */
int writeToSocketUDP(SocketUDP* s, const char * addr, int port,
        const char * buf, int len);

/**
 * Lit depuis un
 * @param s
 * @param addr
 * @param port
 * @param buf
 * @param len
 * @param timeout
 * @return 
 */
int readFromSocketUDP(SocketUDP *socket, char *buffer, int length,
        char *address, int *port, int timeout);

/**
 * Libère les ressources occupée par la SocketUDP pointée par <b>s</b>.
 * @param s
 * @return 
 */
int closeSocketUDP(SocketUDP * s);

#endif
