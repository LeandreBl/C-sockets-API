#ifndef _NET_API_H_
# define _NET_API_H_

# include <stdint.h>
# include <stdbool.h>
# include <lvector.h>

# include <lgtab.h>
# include <lstr.h>

typedef struct netapi_s {
  lstr_t id;
  uint32_t ip_addr;
  lvector(uint8_t) mac;
} netapi_t;

int netapi(gtab_t *tab) __THROW __nonnull((1));
netapi_t *netapi_first_connected(const gtab_t *interfaces) __THROW __nonnull((1));
const uint8_t *netapi_ip_addr(const netapi_t *iface) __THROW __nonnull((1));
bool netapi_is_connected(const netapi_t *iface) __THROW __nonnull((1));
void netapi_print(const netapi_t *iface) __THROW __nonnull((1));

bool is_connected(uint32_t ipaddr) __THROW;

#endif /* !_NET_API_H_ */