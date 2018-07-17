/*
** EPITECH PROJECT, 2018
** C socket API
** File description:
** shutdown
*/

#include "lblsocket.h"

int lsocket_shutdown(lsocket_t *socket)
{
	if (shutdown(socket->fd, SHUT_RDWR) == -1)
		return (-1);
	socket->is_connected = false;
	return (0);
}