#include "netapi.h"

static const uint32_t LOCALHOST = 0x100007f;

bool is_connected(uint32_t ipaddr)
{
	return (ipaddr != 0 && ipaddr != LOCALHOST);
}

bool netapi_is_connected(const netapi_t *iface)
{
	return is_connected(iface->ip_addr);
}