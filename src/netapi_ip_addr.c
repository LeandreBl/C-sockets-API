#include "netapi.h"

const uint8_t *netapi_ip_addr(const netapi_t *iface)
{
	return ((uint8_t *)&iface->ip_addr);
}