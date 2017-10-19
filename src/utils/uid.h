/*******************************************************************************
 *  Author: Or Nagar.
 *  Creation date: 25.06.17
 *  Last modified: 25.06.17
 *  Implementation of UID generator.
 *  Functions declaration, H. file.
 ******************************************************************************/
#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h>

typedef struct uid 
{
    size_t index;
    int millis;
    pid_t process_id;
    
}rd33_uid_t;

/*
 * Create an UID.
 */
rd33_uid_t UidCreate(void);

/*
 * Create an invalid UID.
 */
rd33_uid_t UidCreateBadId(void);

/* Check whether two ids are the same.
 */
int UidIsSameId(rd33_uid_t id1, rd33_uid_t id2);

/* Check whether a created id is valid.
 */
int UidIsBadId(rd33_uid_t id);

#endif /* __UID_H__ */

