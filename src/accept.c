/*
** EPITECH PROJECT, 2018
** C socket API
** File description:
** accept
*/

#include <string.h>

#include "lblsocket.h"

int lsocket_accept(lsocket_t *server, lsocket_t *dest)
{
	socklen_t len = sizeof(dest->saddr);

	memset(dest, 0, sizeof(*dest));
	dest->fd = accept(server->fd, (struct sockaddr *)&dest->saddr, &len);
	if (dest->fd == -1)
		return (-1);
	dest->is_connected = true;
	dest->port = server->port;
	return (0);
}
