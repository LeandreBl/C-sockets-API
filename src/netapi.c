#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ifaddrs.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>

#include "netapi.h"

static void set_mac(netapi_t *netapi, const struct ifaddrs *node)
{
  struct sockaddr_ll *ptr = (struct sockaddr_ll *)node->ifa_addr;

  lvector_reserve(netapi->mac, ptr->sll_halen);
  netapi->mac.len = ptr->sll_halen;
  memcpy(netapi->mac.arr, ptr->sll_addr, ptr->sll_halen * sizeof(uint8_t));
}

static void set_ipaddr(netapi_t *netapi, const struct ifaddrs *node)
{
  struct sockaddr_in *soin = (struct sockaddr_in *)node->ifa_addr;

  netapi->ip_addr = soin->sin_addr.s_addr;
}

netapi_t *netapi_create(const struct ifaddrs *node)
{
  netapi_t *obj = calloc(1, sizeof(*obj));

  if (obj == NULL)
    return (NULL);
  if (lstr_create(&obj->id, node->ifa_name) == -1)
    return (NULL);
  if (node->ifa_addr->sa_family == AF_INET)
    set_ipaddr(obj, node);
  else if (node->ifa_addr->sa_family == AF_PACKET)
    set_mac(obj, node);
  return (obj);
}

void netapi_destroy(netapi_t *interface)
{
  lstr_destroy(&interface->id);
  lvector_destroy(interface->mac);
  free(interface);
}

static int add_interface(gtab_t *tab, struct ifaddrs *node)
{
  netapi_t *p;
  netapi_t *new_inet;

  for (size_t i = 0; i < tab->len; ++i) {
    p = tab->i[i];
    if (strcmp(p->id.i, node->ifa_name) == 0) {
      if (node->ifa_addr->sa_family == AF_PACKET)
        set_mac(p, node);
      else if (node->ifa_addr->sa_family == AF_INET)
        set_ipaddr(p, node);
      return (0);
    }
  }
  new_inet = netapi_create(node);
  if (new_inet == NULL)
    return (-1);
  return (gtab_append(tab, new_inet));
}

int netapi(gtab_t *tab)
{
  struct ifaddrs *list;
  struct ifaddrs *node;
  struct sockaddr_in *saddr;

  if (gtab_create(tab, 3, (void (*)(void *))netapi_destroy) == -1 || getifaddrs(&list) == -1) {
    fprintf(stderr, "Error: netapi: %s\n", strerror(errno));
    return (-1);
  }
  for (node = list; node != NULL; node = node->ifa_next) {
    if (node->ifa_addr != 0) {
      saddr = (struct sockaddr_in *)node->ifa_addr;
      if (is_connected(saddr->sin_addr.s_addr) == true && add_interface(tab, node) == -1)
        return (-1);
    }
  }
  freeifaddrs(list);
  return (0);
}

bool is_connected(uint32_t ipaddr) __THROW;