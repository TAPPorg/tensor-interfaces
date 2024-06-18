#ifndef TAPP_HANDLE_H_
#define TAPP_HANDLE_H_

#include <stdint.h>

#include "error.h"

typedef intptr_t TAPP_handle;

/*
 * TODO: implementation-defined creation of handles or "wrapper" to get all implementations and select one?
 *       devices probably can't be enumerated until you have a handle....
 */

 //TODO: get string describing implementation?

 //TODO: API versioning and query

 //TODO: optional APIs with feature test macros

TAPP_error TAPP_destroy_handle(TAPP_handle handle);

#endif /* TAPP_HANDLE_H_ */
