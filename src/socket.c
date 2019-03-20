/*
** EPITECH PROJECT, 2018
** C socket API
** File description:
** socket
*/

#include <string.h>
#include <unistd.h>

#include "lsocket.h"

__attribute__ ((visibility ("hidden"))) int lsocket_create(lsocket_t *lsocket)
{
  memset(lsocket, 0, sizeof(*lsocket));
  lsocket->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (lsocket->fd == -1)
    return (-1);
  return (0);
}

int lsocket_destroy(lsocket_t *lsocket)
{
  if (close(lsocket->fd) == -1)
    return (-1);
  memset(lsocket, 0, sizeof(*lsocket));
  return (0);
}
