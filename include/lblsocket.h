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

typedef struct lsocket_s {
	struct sockaddr_in saddr;
	int fd;
	int backlog;
	uint16_t port;
	bool is_connected;
} lsocket_t;

int __lsocket_create(lsocket_t *socket);
int lsocket_destroy(lsocket_t *socket);

int lsocket_server(lsocket_t *socket, uint16_t port, int backlog);
int lsocket_accept(lsocket_t *server, lsocket_t *client);

int lsocket_connect(lsocket_t *socket, const char *addr, uint16_t port);
int lsocket_connect32(lsocket_t *socket, uint32_t ip, uint16_t port);

int lsocket_shutdown(lsocket_t *socket);

#endif /* !_LBLSOCKET_H */
