/*
 * circular_buffer.h
 *
 *  Created on: 17/ago/2015
 *      Author: Paolo Santinelli
 */

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include "utility.h"

/** 
 * Circular buffer struct 
 */
typedef struct {
    uint           size;    // maximum number of elements   
    uint           w_pos;   // write index                  
    uint           r_pos;   // read index				    
    uint           count;   // number of items in the buffer
    unsigned char *buff;    // vector of elements       
} CircularBuffer;

void cbFree   (CircularBuffer *cb);
int  cbIsFull (CircularBuffer *cb);
int  cbIsEmpty(CircularBuffer *cb);
void cbInit   (CircularBuffer *cb, uint  size);
bool cbWrite  (CircularBuffer *cb, byte  elem);
bool cbRead   (CircularBuffer *cb, byte *elem);

#endif /* CIRCULAR_BUFFER_H_ */
