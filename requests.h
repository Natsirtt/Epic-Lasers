#ifndef REQUESTS_H
#define	REQUESTS_H
#include "packets.h"
#include "libs/SocketUDP.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     * Fill the request pointed by req as a log request.
     */
    void rq_fillLogRequest(Request_t * req, char * nickname);

    /**
     * Extract the logs from the request pointed by req.
     */
    void rq_readLogRequest(Request_t * req, char * nickname);

    /**
     * Fill the request pointed by req with a move request
     * of a translation on (x, y, z) vector.
     */
    void rq_fillMoveRequest(Request_t * req, float x, float y, float z);

    /**
     * Extract the movement from the request pointed by req.
     */
    void rq_readMoveRequest(Request_t * req, float * x, float * y, float * z);

    /**
     * Fill the request pointed by req with a fire request from the client
     * in the direction (x,y,z).
     */
    void rq_fillFireRequest(Request_t * req, float x, float y, float z);

    /**
     * Extract the fire direction from the request pointedb y req
     */
    void rq_readFireRequest(Request_t * req, float * x, float * y, float * z);

    /**
     * Fill the request pointed by req with a respawn request from the client.
     */
    void rq_fillRespawnRequest(Request_t * req);
    
    /**
     * Indicates the type of the request pointed by req.
     * @return the type of request.
     */
    opType_t rq_getType(Request_t * req);

    /**
     * Send the request pointed by req to the server at addr:port
     */
    void rq_sendRequest(SocketUDP * socket, Request_t * req, const char * addr,
            int port);

    /**
     * Wait during timeout seconds for a request on the SocketUDP pointed by
     * socket. The received request will be pointed by req. the emmitter is
     * addr:port.
     */
    void rq_recvRequest(SocketUDP * socket, Request_t * req, char * addr,
            int * port, int timeout);

#ifdef	__cplusplus
}
#endif

#endif	/* REQUESTS_H */

