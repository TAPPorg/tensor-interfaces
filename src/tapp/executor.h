#ifndef TAPP_EXECUTOR_H_
#define TAPP_EXECUTOR_H_

#include <stdint.h>

#include "error.h"

typedef intptr_t TAPP_executor;

/*
 * TODO: implementation-defined creation of executors or "wrapper" to get all implementations and select one?
 *       devices probably can't be enumerated until you have a handle....
 */

TAPP_error TAPP_destroy_executor(TAPP_executor exec);

#endif /* TAPP_HANDLE_H_ */
