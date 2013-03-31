/* 
 * File:   packets.h
 * Author: shifty
 *
 * Created on 31 mars 2013, 21:54
 */

#ifndef PACKETS_H
#define	PACKETS_H
#include <sys/types.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef int opType_t;
    
    struct packet {
        opType_t type;
        char * datas;
    };
    
    /**
     * Type defining a request from the client to the server
     * that he would like his state to change.
     */
    typedef struct packet Request_t;
    
    /**
     * Type defining a message from the server that
     * Something happened.
     */
    typedef struct packet Message_t;
    
    /**
     * Type defining an update of something in the server
     * that must change in the client.
     */
    typedef struct packet Update_t;


#ifdef	__cplusplus
}
#endif

#endif	/* PACKETS_H */

