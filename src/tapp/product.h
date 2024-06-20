#ifndef TAPP_PRODUCT_H_
#define TAPP_PRODUCT_H_

#include <stdint.h>

#include "error.h"
#include "handle.h"
#include "executor.h"
#include "datatype.h"
#include "status.h"
#include "tensor.h"

//TODO: where should this go?
typedef int TAPP_element_op;

enum
{
    TAPP_IDENTITY = 0,
    TAPP_CONJUGATE = 1,
};

//TODO: where should this go?
#define TAPP_IN_PLACE NULL

/*
 * TODO: what are the required error conditions?
 *
 * TODO: must C and D info be the same? (should they just be the same variable?)
 *  JB: Can this be implemented efficiently with different data types of C and D? 
 *      Let’s say D is complex and C real. Then it should be possible with a different "stride".
 *      In such cases we might want to support different C and D info. If D info is null, they 
 *      are assumed identical. 
 */

typedef intptr_t TAPP_tensor_product;

// D_{idx_D} = alpha * A_{idx_A} * B_{idx_B} + beta * C_{idx_C}
// each idx is an array of einsum style index "characters", e.g. {'a', 'b', 'i', 'j'}
TAPP_error TAPP_create_tensor_product(TAPP_tensor_product* plan,
                                      TAPP_handle handle,
                                      TAPP_element_op op_A,
                                      TAPP_tensor_info A,
                                      const int64_t* idx_A,
                                      TAPP_element_op op_B,
                                      TAPP_tensor_info B,
                                      const int64_t* idx_B,
                                      TAPP_element_op op_C,
                                      TAPP_tensor_info C,
                                      const int64_t* idx_C,
                                      TAPP_element_op op_D,
                                      TAPP_tensor_info D,
                                      const int64_t* idx_D,
                                      TAPP_prectype prec);

TAPP_error TAPP_destory_tensor_product(TAPP_tensor_product plan);

//TODO: in-place operation: set C = NULL or TAPP_IN_PLACE?

TAPP_error TAPP_execute_product(TAPP_tensor_product plan,
                                TAPP_executor exec,
                                TAPP_status* status,
                                const void* alpha,
                                const void* A,
                                const void* B,
                                const void* beta,
                                const void* C,
                                      void* D);

//TODO: is it always OK to pass NULL for exec?
//TODO: can C be NULL/TAPP_IN_PLACE (in addition to array entries being NULL)?

TAPP_error TAPP_execute_batched_product(TAPP_tensor_product plan,
                                        TAPP_executor exec,
                                        TAPP_status* status,
                                        int num_batches,
                                        const void* alpha,
                                        const void** A,
                                        const void** B,
                                        const void* beta,
                                        const void** C,
                                              void** D);

//JB: TODO: variable sized batching (DM suggests plan of plans)

#endif /* TAPP_PRODUCT_H_ */
