/*
 * circular_buffer.c
 *
 *  Created on: 17/ago/2015
 *      Author: Paolo Santinelli
 */


//--------------------------------------------------------------------------------------
#include <stdlib.h>
#include "circularBuffer.h"

/* Circular buffer */
//typedef struct {                                        /* Circular buffer struct */
//    int                 size;   /* maximum number of elements         */
//    int                 w_pos;  /* write index                        */
//    int                 r_pos;  /* read index			        */
//    int                 count;  /* number of items in the buffer      */
//    unsigned char       *buff;  /* vector of elements                 */
//} CircularBuffer;

/** 
 * Inizialize circular buffer 
 */
void cbInit(CircularBuffer *cb, uint size) 
{             
    cb->size  = size;
    cb->w_pos = 0;
    cb->r_pos = 0;
    cb->count = 0;
    cb->buff  = (byte*)malloc(cb->size * sizeof(byte));
}


/**
 * Free circular buffer 
 */
inline void cbFree(CircularBuffer *cb)
{                       
    free(cb->buff); /* OK if null */
}


/** 
 * Check circular buffer full condition 
 */
inline int cbIsFull(CircularBuffer *cb) 
{                      
    return cb->count == cb->size;
}


/** 
 * Check circular buffer empty condition 
 */
inline int cbIsEmpty(CircularBuffer *cb) 
{                     
    return cb->count == 0;
}


/** 
 * Write data in to circular buffer 
 */
bool cbWrite(CircularBuffer *cb, byte elem) 
{   
    if (cb->count >= cb->size)
        return false;

    cb->count++;
    cb->buff[cb->w_pos] = elem;

    // cb->w_pos = (cb->w_pos+1) % cb->size;
    cb->w_pos = 
        (++cb->w_pos < cb->size) 
        ? cb->w_pos 
        : 0; 
 
    return true;
}


/** 
 * Read data from circular buffer 
 */
bool cbRead(CircularBuffer *cb, byte *elem) 
{   
    if (cb->count <= 0)
        return false;
    
    cb->count--;
    *elem = cb->buff[cb->r_pos];

    // cb->r_pos = (cb->r_pos+1) % cb->size;
    cb->r_pos = 
        (++cb->r_pos < cb->size) 
        ? cb->r_pos
        : 0; 

    return true; 
}
//------------------------------------------------------------------------------------

