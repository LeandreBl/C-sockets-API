/*
** EPITECH PROJECT, 2018
** C socket API
** File description:
** header
*/

#ifndef _LBLSOCKET_H
# define _LBLSOCKET_H

# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/cdefs.h>

typedef struct lsocket_s {
	struct sockaddr_in saddr;
	int fd;
	int backlog;
	uint16_t port;
	bool is_connected;
} lsocket_t;

int lsocket_destroy(lsocket_t *socket) __THROW __nonnull((1));

int lsocket_server(lsocket_t *socket, uint16_t port, int backlog) __THROW __nonnull((1));
int lsocket_accept(lsocket_t *server, lsocket_t *client) __THROW __nonnull((1, 2));

int lsocket_connect(lsocket_t *socket, const char *addr, uint16_t port) __THROW __nonnull((1, 2));
int lsocket_connect32(lsocket_t *socket, uint32_t ip, uint16_t port) __THROW __nonnull((1));

int lsocket_shutdown(lsocket_t *socket) __THROW __nonnull((1));

#endif /* !_LBLSOCKET_H */
