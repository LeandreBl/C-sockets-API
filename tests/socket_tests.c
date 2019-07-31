#include <criterion/criterion.h>
#include <time.h>
#include "lsocket.h"

Test(server, localhost)
{
	lsocket_t server;
	lsocket_t client;
	char *cmd;

	cr_assert(lsocket_server(&server, 0, 5) == 0);
	cr_asprintf(&cmd, "sleep 1 && nc 127.0.0.1 %d&", server.port);
	system(cmd);
	free(cmd);
	cr_assert(lsocket_accept(&server, &client) == 0);
	cr_assert(lsocket_shutdown(&server) == 0);
	cr_assert(lsocket_destroy(&server) == 0);
}

Test(connect, localhost)
{
	lsocket_t client;
	char *cmd;
	uint16_t port = 2000 + rand() % 20000;

	srand(time(NULL));
	cr_asprintf(&cmd, "nc -l %u&", port);
	if (system(cmd) == -1) {
		cr_log_error("Could not start netcat on port %u\n", port);
		return;
	}
	free(cmd);
	cr_assert(lsocket_connect(&client, "127.0.0.1", port) == 0);
	cr_assert(lsocket_shutdown(&client) == 0);
	cr_assert(lsocket_destroy(&client) == 0);
}

Test(connect32, localhost)
{
	lsocket_t client;
	char *cmd;
	uint16_t port = 2000 + rand() % 20000;

	srand(time(NULL));
	cr_asprintf(&cmd, "nc -l %u&", port);
	if (system(cmd) == -1) {
		cr_log_error("Could not start netcat on port %u\n", port);
		return;
	}
	free(cmd);
	cr_assert(lsocket_connect32(&client, 0, port) == 0);
	cr_assert(lsocket_shutdown(&client) == 0);
	cr_assert(lsocket_destroy(&client) == 0);
}