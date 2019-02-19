#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ifaddrs.h>
#include <linux/if_packet.h>

#include "netapi.h"

static void set_mac(netapi_t *netapi, const struct ifaddrs *node)
{
  struct sockaddr_ll *p = (struct sockaddr_ll *)node->ifa_addr;

  netapi->maclen = p->sll_halen;
  memcpy(netapi->mac_addr, p->sll_addr, p->sll_halen * sizeof(uint8_t));
}

static void set_ipaddr(netapi_t *netapi, const struct ifaddrs *node)
{
  struct sockaddr_in *soin = (struct sockaddr_in *)node->ifa_addr;

  netapi->ip_addr = soin->sin_addr.s_addr;
}

static netapi_t *netapi_create(const struct ifaddrs *node)
{
  netapi_t *obj = calloc(1, sizeof(*obj));

  if (obj == NULL)
    return (NULL);
  obj->id = strdup(node->ifa_name);
  if (obj->id == NULL) {
    free(obj);
    return (NULL);
  }
  if (node->ifa_addr->sa_family == AF_INET)
    set_ipaddr(obj, node);
  else if (node->ifa_addr->sa_family == AF_PACKET)
    set_mac(obj, node);
  return (obj);
}

static void inet_destroy(netapi_t *interface)
{
  free(interface->id);
  free(interface);
}

static int add_interface(gtab_t *tab, struct ifaddrs *node)
{
  netapi_t *p;
  netapi_t *new_inet;

  for (size_t i = 0; i < tab->len; ++i) {
    p = tab->i[i];
    if (strcmp(p->id, node->ifa_name) == 0) {
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

  if (gtab_create(tab, 3, (void (*)(void *))inet_destroy) == -1 || getifaddrs(&list) == -1) {
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

