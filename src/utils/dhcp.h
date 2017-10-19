/*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
 *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *  Dhcp                                   #################################
 *                                         ##########    ####       ########
 *  Functions decleration                  ########  ####  ##  ###  ########
 *                                         ########  ####  ##     ##########
 *  Or Nagar                               ########  ####  ##  ###  ########
 *  09-08-2017                             ##########    ####  ###  ######## 
 *  13:51:54                               #################################
 * 
 * Usage:
 *  Allocate a new address with DHCPAllocIp and free with DHCPFreeIp
 *
 * Service features:
 *  Allocates unique, valid ip addresses for a router
 * 
 *vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
#ifndef __DHCP_H__
#define __DHCP_H__

#define N_BYTES (4)

typedef struct ip
{
    unsigned char byte[N_BYTES];
} ip_t;

typedef struct dhcp dhcp_t;

typedef enum
{
    DHCP_OK = 0,
    DHCP_ADDR_TAKEN,
    DHCP_ADDR_ILLEGAL,
    DHCP_ALL_ADDR_TAKEN,
    DHCP_ADDR_NOT_EXIST,
    DHCP_ALLOC_ERROR
} dhcp_status_t;

/*
 * Create a DHCP management structure
 *
 *  subnet_addr expects a valid address for a given class.
 *          example: DHCPCreate({127, 0, 1, 0}, 24)
 *      if an extra byte has been sent in subnet_addr, no dhcp object is created
 *          example: DHCPCreate({127, 0, 1, 0}, 16)
 *                   too many bytes sent, will return NULL.
 *
 */
dhcp_t *DHCPCreate(ip_t subnet_addr, int static_bits);

/*
 * Destroys a dhcp object
 */
void DHCPDestroy(dhcp_t *dhcp);

/*
 * Allocates a ip_t addr to the user.
 *  -> result is a pointer to data managed by the user
 *  A successful request returns:           DHCP_OK
 *  If the address requested has been taken and a new one allocated to user,
 *      returns:                            DHCP_ADDR_TAKEN
 *  If there are no addresses left returns: DHCP_ALL_ADDR_TAKEN
 *  If the address passes is invalid given the subnet address,
 *      returns:                            DHCP_ADDR_INVALID
 */
dhcp_status_t DHCPAllocIp(dhcp_t *dhcp, ip_t request, ip_t *result);

/*
 * Frees address up for use by future users.
 *  Successful free returns:             DHCP_OK
 *  If the address is not found returns: DHCP_ADDR_NOT_EXIST
 */
dhcp_status_t DHCPFreeIp(dhcp_t *dhcp, ip_t addr);

#endif /* __DHCP_H__ */
