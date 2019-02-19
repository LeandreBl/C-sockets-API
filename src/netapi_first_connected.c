#include "netapi.h"

netapi_t *netapi_first_connected(const gtab_t *interfaces)
{
  for (size_t i = 0; i < interfaces->len; ++i)
    if (netapi_is_connected(interfaces->i[i]) == true)
      return (interfaces->i[i]);
  return (NULL);
}