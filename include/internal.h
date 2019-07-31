#ifndef INTERNAL_H_
#define INTERNAL_H_

#include "lsocket.h"

__attribute__((visibility("hidden"))) int lsocket_create(lsocket_t *socket) __THROW __nonnull((1));

#endif /* !INTERNAL_H_ */