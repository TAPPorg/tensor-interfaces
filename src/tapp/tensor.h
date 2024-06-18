#ifndef TAPP_TENSOR_H_
#define TAPP_TENSOR_H_

#include <stdint.h>

#include "error.h"
#include "datatype.h"

typedef intptr_t TAPP_tensor_info;

/*
 * TODO: what are the required error conditions? What is explicitly allowed (esp. regarding strides)?
 */

TAPP_error TAPP_create_tensor_info(TAPP_tensor_info* info,
                                   TAPP_datatype type,
                                   int nmode,
                                   const int64_t* extents,
                                   const int64_t* strides);

TAPP_error TAPP_destory_tensor_info(TAPP_tensor_info info);

int TAPP_get_nmodes(TAPP_tensor_info info);

TAPP_error TAPP_set_nmodes(TAPP_tensor_info info,
                           int nmodes);

void TAPP_get_extents(TAPP_tensor_info info,
                      int64_t* extents);

TAPP_error TAPP_set_extents(TAPP_tensor_info info,
                            const int64_t* extents);

void TAPP_get_strides(TAPP_tensor_info info,
                      int64_t* strides);

TAPP_error TAPP_set_strides(TAPP_tensor_info info,
                            const int64_t* strides);

#endif /* TAPP_TENSOR_H_ */
