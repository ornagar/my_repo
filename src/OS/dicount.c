/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Dicount                                #################################
 *                                         ##########    ####       ########
 *  Functions definition                   ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  21-08-2017                             ##########    ####  ###  ######## 
 *  17:48:56                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */
#include <assert.h>					 /* assert()					  */
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

#include "../utils/utils.h"			 /* Or's functions                */

#define ASCII_NUM  	(256)
enum
{
	SUCCESS,
	FAILURE
};

typedef struct
{
	unsigned char *address;
	size_t size;
	size_t ascii[ASCII_NUM];
} map_addr_t;

void *DictCounter(void *arg);

int main(int argc, char *argv[])
{
	unsigned char	*file			= NULL;
	struct stat 	s				= {0};
	map_addr_t 	  	*addr			= NULL;
	pthread_t 		*threads		= NULL;
	size_t 			thread_chunk	= 0;
	char			*dictionary		= "/home/super29/svn/Proj/src/OS/words";
	char			*letter_file	= "/home/super29/svn/Proj/src/OS/new_file";
	char 		 	*in_file		= NULL;
	int 			num_of_threads  = 3;
	int 			fd				= 0;
	int 		  	status			= 0;
	int 			i				= 0;
	int 			j				= 0;
	
	/* Number of threads to create, if no argument given default is three */ 
	if (1 < argc)
	{
		num_of_threads = atoi(argv[1]);
	}
	
	/* Allocate threads */
	threads = malloc(sizeof(threads) * num_of_threads);
	if (NULL == threads)
	{
		PRINT_ERROR("malloc error");
		return (FAILURE);
	}
	
	/* Open dictonary */
	fd = open(dictionary, O_RDWR);
	if (-1 == fd)
	{
		PRINT_ERROR("open error");
		free(threads);
		return (FAILURE);
	}
	
	status = fstat(fd, &s);
	if (-1 == status)
	{
		PRINT_ERROR("fstat error");
		free(threads);
		close(fd);
		return (FAILURE);
	}
	
	/* Map file to VM */
	file = mmap(NULL, s.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (MAP_FAILED == file)
	{
		PRINT_ERROR("mmap error");
		free(threads);
		close(fd);
		return (FAILURE);
	}
	
	/* Size of dictionary for each thread */
	thread_chunk = s.st_size / num_of_threads;
	
	/* Allocate struct for each thread  and assign them values*/
	addr = calloc(sizeof(map_addr_t), num_of_threads);
	if (NULL == addr)
	{
		PRINT_ERROR("malloc error");
		free(threads);
		close(fd);
		return (FAILURE);
	}
	for (i = 0; i < num_of_threads; ++i)
	{
		addr[i].address = file + i * thread_chunk;
		addr[i].size = thread_chunk;
	}
	addr[i - 1].size += s.st_size % num_of_threads;
	
	/* Create threads and send them to work */
	for (i = 0; i < num_of_threads; ++i)
	{
		status = pthread_create(&threads[i], NULL, DictCounter, &addr[i]);
		if (0 != status)
		{
			PRINT_ERROR("pthread_create error");
			free(threads);
			free(addr);
			close(fd);
			for (j = 0; j < i; ++j)
			{
				pthread_cancel(threads[j]);
			}
			return (1);
		}
	}
		
	
	/* Wait for threads and collect them */
	for (i = 0; i < num_of_threads; ++i)
	{
		pthread_join(threads[i], NULL);
		if (0 != status)
		{
			PRINT_ERROR("pthread_join error");
			free(threads);
			free(addr);
			close(fd);
			return (1);
		}
	}
	
	/* Collect all histogram into the first one */
	for (i = 1; i < num_of_threads; ++i)
	{
		for (j = 0; j < ASCII_NUM; ++j)
		{
			addr[0].ascii[j] += addr[i].ascii[j];
		}
	}
	
	/* Close the file */
	munmap(file, s.st_size);
	close(fd);

	/* Open or create file for letters */
	fd = open(letter_file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (-1 == fd)
	{
		PRINT_ERROR("open error");
		free(threads);
		return (FAILURE);
	}
	
	/* Use lseek and write to add a character to the end of file (for mmap) */
	errno = 0;
	if (-1 == lseek(fd, s.st_size - 1, SEEK_SET))
    {
        PRINT_ERROR("lseek error");
		close(fd);
		free(threads);
		free(addr);
        return (EXIT_FAILURE);
	}
	
	if (-1 == write(fd, "", 1))
    {
        PRINT_ERROR("write error");
		close(fd);
		free(threads);
		free(addr);
        return (EXIT_FAILURE);
	}
	
	in_file = mmap(NULL, s.st_size,
								PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == in_file)
	{
		printf("%d\n", errno);
		PRINT_ERROR("mmap error");
		free(threads);
		close(fd);
		close(fd);
		return (FAILURE);
	}
	
	/* For each letter in abc and ABC write it to the new file addr[0].ascii[i]
	 * times
	 */
	for (i = 'A'; i <= 'Z'; ++i)
	{
		memset(in_file, i, addr[0].ascii[i]);
		in_file += addr[0].ascii[i];
		*in_file = '\n';
		++in_file;
	}
	
	for (i = 'a'; i <= 'z'; ++i)
	{
		memset(in_file, i, addr[0].ascii[i]);
		in_file += addr[0].ascii[i];
		*in_file = '\n';
		++in_file;
	}
	
	/* Free resources */
	munmap(file, s.st_size);
	free(threads);
	free(addr);
	close(fd);

	return (EXIT_SUCCESS);
}

void *DictCounter(void *arg)
{
	map_addr_t *addr = arg;
	int i = 0;

	for (i = 0; i < addr->size; ++i)
	{
		addr->ascii[*addr->address] += 1;
		addr->address += 1;
	}
	
	return (NULL);
}
