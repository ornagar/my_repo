/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Dhcp                                   #################################
 *                                         ##########    ####       ########
 *  Tester                                 ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  09-08-2017                             ##########    ####  ###  ######## 
 *  13:51:54                               #################################
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#include <stdio.h>                   /* printf()                      */
#include <stdlib.h>					 /* system(), EXIT_SUCCESS		  */

#include "dhcp.h"					 /* all functions declerations	  */
#include "utils.h"					 /* Or's functions                */

static int TestDhcpTrie(void);

int main(void)
{
	int err_sum = TestDhcpTrie();
	
	if (err_sum)
	{
		printf("Failure, found %d bugs in DHCP program", err_sum);
		return (EXIT_FAILURE);
	}
	else
	{
		puts("Succes: DHCP works as expected!");
		return (EXIT_SUCCESS);
	}
}

static int TestDhcpTrie(void)
{
	int count_errs = 0;
	dhcp_t *trie = NULL;
	ip_t result = {{190, 1, 0, 0}};
	ip_t new = {{190, 1, 0, 25}};
	ip_t new2 = {{190, 1, 0, 1}};
	ip_t new3 = {{191, 1, 0, 43}};
	int counter = 0;
	
	trie = DHCPCreate(result, 16);
	
	if (DHCP_OK != DHCPAllocIp(trie, new, &result))
	{
		puts("fail");
		++count_errs;
	}
	
	if (DHCP_OK != DHCPAllocIp(trie, new2, &result))
	{
		puts("fail");
		++count_errs;
	}
	
	if (DHCP_ADDR_ILLEGAL != DHCPAllocIp(trie, new3, &result))
	{
		puts("fail");
		++count_errs;
	}
	
	while (DHCP_ALL_ADDR_TAKEN != DHCPAllocIp(trie, new2, &result))
	{
		++counter;
	}
	if (65530 != counter)
	{
		puts("fail");
		++count_errs;
	}
	
	DHCPFreeIp(trie, new2);
	
	if (DHCP_OK != DHCPAllocIp(trie, new2, &result))
	{
		puts("fail");
		++count_errs;
	}
	
	DHCPDestroy(trie);
	
	return(count_errs);
}


