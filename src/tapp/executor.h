#ifndef TAPP_EXECUTOR_H_
#define TAPP_EXECUTOR_H_

#include <stdint.h>

#include "attributes.h"
#include "error.h"
#include "handle.h"

typedef intptr_t TAPP_executor;

TAPP_error TAPP_create_executor(TAPP_handle handle, TAPP_attr attr);

TAPP_error TAPP_destroy_executor(TAPP_executor* exec);

#endif /* TAPP_HANDLE_H_ */
