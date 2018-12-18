/*
** EPITECH PROJECT, 2018
** C socket API
** File description:
** server
*/

#include "lsocket.h"

int lsocket_server(lsocket_t *lsocket, uint16_t port, int backlog)
{
    struct sockaddr *p = (struct sockaddr *)&lsocket->saddr;
    socklen_t len = sizeof(*p);

    if (__lsocket_create(lsocket) == -1)
        return (-1);
    lsocket->backlog = backlog;
    lsocket->saddr.sin_addr.s_addr = INADDR_ANY;
    lsocket->saddr.sin_family = AF_INET;
    lsocket->saddr.sin_port = htons(port);
    if (bind(lsocket->fd, p, sizeof(lsocket->saddr)) == -1)
        return (-1);
    if ((port == 0 && getsockname(lsocket->fd, p, &len) == -1)
        || listen(lsocket->fd, backlog) == -1)
        return (-1);
    lsocket->port = htons(lsocket->saddr.sin_port);
    return (0);
}
