#ifndef _NET_API_H_
# define _NET_API_H_

# include <stdint.h>
# include <stdbool.h>
# include <arpa/inet.h>
# include <linux/ip.h>

# include "lgtab.h"

typedef struct netapi_s {
  char *id;
  uint32_t ip_addr;
  uint8_t maclen;
  uint8_t mac_addr[8];
} netapi_t;

int netapi(gtab_t *tab) __THROW __nonnull((1));
netapi_t *netapi_first_connected(const gtab_t *interfaces) __THROW __nonnull((1));
const uint8_t *netapi_ip_addr(const netapi_t *iface) __THROW __nonnull((1));
bool netapi_is_connected(const netapi_t *iface) __THROW __nonnull((1));
void netapi_print(const netapi_t *iface) __THROW __nonnull((1));

bool is_connected(uint32_t ipaddr) __THROW;

#endif /* !_NET_API_H_ */