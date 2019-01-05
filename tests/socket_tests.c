#include <criterion/criterion.h>
#include "lsocket.h"

Test(server, localhost)
{
  lsocket_t server;
  lsocket_t client;

  cr_assert(lsocket_server(&server, 1234, 5) == 0);
  system("sleep 1 && nc 127.0.0.1 1234&");
  cr_assert(lsocket_accept(&server, &client) == 0);
  cr_assert(lsocket_shutdown(&server) == 0);
  cr_assert(lsocket_destroy(&server) == 0);
}

Test(connect, localhost)
{
  lsocket_t client;
  if (system("nc -l 1235&") == -1) {
    cr_log_error("Could not start netcat on port 1235");
    return;
  }
  cr_assert(lsocket_connect(&client, "127.0.0.1", 1235) == 0);
  cr_assert(lsocket_shutdown(&client) == 0);
  cr_assert(lsocket_destroy(&client) == 0);
}

Test(connect32, localhost)
{
  lsocket_t client;
  if (system("nc -l 1236&") == -1) {
    cr_log_error("Could not start netcat on port 1236");
    return;
  }
  cr_assert(lsocket_connect32(&client, 0, 1236) == 0);
  cr_assert(lsocket_shutdown(&client) == 0);
  cr_assert(lsocket_destroy(&client) == 0);
}