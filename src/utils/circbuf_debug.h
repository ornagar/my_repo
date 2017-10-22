/*****************************************************************************
 *  Or Nagar.
 *  Circular Buffer library.  
 *  Print CircBuffer Function definition.
 *  12/06/17
 ****************************************************************************/
#ifndef __CIRCBUF_DEBUG_H__
#define __CIRCBUF_DEBUG_H__

#ifdef _DEBUG
/*
 * Prints the current data in the circular buffer.
 */
void CircBufPrint(const circbuf_t *cb);
#endif		/* _DEBUG				*/
#endif 		/* __CIRCBUF_DEBUG_H__	*/
