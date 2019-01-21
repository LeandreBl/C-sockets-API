/*
** EPITECH PROJECT, 2018
** C socket API
** File description:
** connect
*/

#include "internal.h"

int lsocket_connect32(lsocket_t *lsocket, uint32_t ip, uint16_t port)
{
  if (__lsocket_create(lsocket) == -1)
    return (-1);
  lsocket->saddr.sin_addr.s_addr = ip;
  lsocket->saddr.sin_port = htons(port);
  lsocket->saddr.sin_family = AF_INET;
  if (connect(lsocket->fd, (struct sockaddr *)&lsocket->saddr, sizeof(lsocket->saddr)) == -1)
    return (-1);
  lsocket->is_connected = true;
  lsocket->port = htons(lsocket->saddr.sin_port);
  return (0);
}

int lsocket_connect(lsocket_t *lsocket, const char *addr, uint16_t port)
{
  uint32_t ip_addr;
  struct hostent *info;

  info = gethostbyname(addr);
  if (info == NULL)
    return (-1);
  ip_addr = ((struct in_addr *)info->h_addr)->s_addr;
  return (lsocket_connect32(lsocket, ip_addr, port));
}
