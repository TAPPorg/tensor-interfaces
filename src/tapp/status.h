#ifndef TAPP_STATUS_H_
#define TAPP_STATUS_H_

#include <stdint.h>

#include "error.h"

typedef intptr_t TAPP_status;

/*
 * Status objects are created by execution functions (e.g. TAPP_execute_product).
 *
 * TODO: how to get data out? using attributes or separate standardized interface? implementation-defined?
 */

TAPP_error TAPP_destroy_status(TAPP_status status);

#endif /* TAPP_STATUS_H_ */
