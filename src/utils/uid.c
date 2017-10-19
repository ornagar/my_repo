
/*******************************************************************************
 *  Author: Or Nagar.
 *  Creation date: 25.06.17
 *  Last modified: 25.06.17
 *  Implementation of UID generator.
 *  Functions definition, C. file.
 ******************************************************************************/

#include <unistd.h>
#include <sys/time.h>

#include "uid.h"

rd33_uid_t UidCreate(void)
{
	static size_t index_counter = 1;
	rd33_uid_t uid = {0};
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	
	uid.index      = index_counter++;
	uid.millis     = tv.tv_usec;
	uid.process_id = getpid();
	
	return(uid);
}

rd33_uid_t UidCreateBadId(void)
{
	rd33_uid_t uid = {0, 0, -1};
	
    return(uid);
}

int UidIsSameId(rd33_uid_t id1, rd33_uid_t id2)
{
	return(id1.index == id2.index && 
		   id1.millis == id2.millis &&
		   id1.process_id == id2.process_id);
}

int UidIsBadId(rd33_uid_t id)
{
	return(id.index == 0 && id.millis == 0 && id.process_id == -1);
}
