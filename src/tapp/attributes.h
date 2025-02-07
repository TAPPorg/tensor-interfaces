#ifndef TAPP_ATTRIBUTES_H_
#define TAPP_ATTRIBUTES_H_

#include <stdint.h>

#include "error.h"

typedef intptr_t TAPP_attr;
typedef int TAPP_key;

//TODO: predefined attributes? error conditions?

TAPP_error TAPP_attr_set(TAPP_attr attr, TAPP_key key, void* value);

TAPP_error TAPP_attr_get(TAPP_attr attr, TAPP_key key, void** value);

TAPP_error TAPP_attr_clear(TAPP_attr attr, TAPP_key key);

#endif /* TAPP_ATTRIBUTES_H_ */
