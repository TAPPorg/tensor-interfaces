`XXX` is an appropiate namespace TBD.

```C
typedef int64_t XXX_extent;
typedef int64_t XXX_stride;
```
These types should almost certainly be signed. 64-bit seems like a fair assumption these days.

```C
typedef int32_t XXX_index;
```
This can probably be just about any integral type.

```C
typedef enum
{
    /* maybe these could be a bitfield, but are there enough bits??? */
    /* Reserved for standard 0x0 - 0x100 (for example) */
    XXX_TYPE_F32, // required
    XXX_TYPE_F64, // required
    XXX_TYPE_C32, // required
    XXX_TYPE_C64, // required
    XXX_TYPE_F16, // required?
    XXX_TYPE_BF16, // required?
    XXX_TYPE_F8,
    XXX_TYPE_BF8,
    XXX_TYPE_I32,
    XXX_TYPE_U32,
    XXX_TYPE_I16,
    XXX_TYPE_U16,
    XXX_TYPE_I8,
    XXX_TYPE_U8,
    /* Available for implementers 0x100 - 0x1000 (for example) */
    ...
} XXX_datatype;

typedef enum
{
    /* Implementations may use more precise computational type */
    /* Reserved for standard 0x2000 - 0x2100 (for example) */
    XXX_TYPE_F32_F32_ACCUM_F32 = XXX_TYPE_F32,
    XXX_TYPE_F64_F64_ACCUM_F64 = XXX_TYPE_F64,
    ...,
    XXX_TYPE_LOWER,    /* narrowest of input precisions */ /* should this be part of attr's */ /* should there be a truly neutral default (maybe HW dependent)? */
    XXX_TYPE_HIGHER,   /* widest of input precisions */
    /* Available for implementers 0x2100 - 0x3000 (for example) */
    ...
} XXX_comp_datatype;
```
Enumerations for the supported storage and computational datatypes. Not all combinations are required to be supported.

```C
typedef /* unspecified */ XXX_error; // Should be a trivial type, e.g. "int"

/*
 * Required errors:
 * - Invalid values (negative lengths, same extent for shared dimension)
 * - Null pointers (except 0-dimensional [or maybe 1+-dimensional is required?])
 * - If D == C (or XXX_IN_PLACE), stride_D_XXX are ignored (can be NULL)
 * - Invocation failure (generic failure)?
 *
 * Should some other information be available, e.g. out-of-memory so user could try again later.
 */

// The error explain function should not allocate the error string itself
// for security concerns.
// Adapted from the function MPI_Error_string
XXX_ERROR XXX_error_explain(XXX_ERROR err, char *error_string, int *error_size);

// Additionally one has to define as in MPI a MAX_ERROR_STRING
#define XXX_MAX_ERROR_STRING 512 /* implementation dependent */
```
Error handling --- implementation defined.

```C
typedef /* unspecified */ XXX_attr; // Requires initialization. E.g. "struct XXX_attr_internal*"
typedef int32_t XXX_key; // Some values should be reserved for standardization

/*
 * Potential keys:
 * - Execution plan (pointer to object)

XXX_error XXX_attr_init(XXX_attr* attr);

XXX_error XXX_attr_destroy(XXX_attr* attr);

XXX_error XXX_attr_set(XXX_attr* attr, XXX_key, void* value);

XXX_error XXX_attr_get(XXX_attr* attr, XXX_key, void** value);

XXX_error XXX_attr_clear(XXX_attr* attr, XXX_key);
```
Implementation defined (and maybe some standard) attributes, loosely based on MPI.

```C
// Unary and binary element-wise operations (transpose, scale, norm, reduction, etc.) should also be defined!

// Element-wise ops on A, B, and AB are very important for machine learning.
// Can this functionality be required in the interface without requiring JIT????

// Compute D_{idx_D} = alpha * A_{idx_A} * B_{idx_B} + beta * C_{idx_C}
// Here, plan creation is a required part of the API

typedef /* unspecified */ XXX_plan; // probably pointer to struct

XXX_error
XXX_contract_plan(
                   XXX_datatype      type_alpha,
                   XXX_datatype      type_A,
                   int               nmode_A,
             const XXX_extent*       shape_A,
             const XXX_stride*       stride_A,
             const XXX_index*        idx_A,
                   XXX_datatype      type_B,
                   int               nmode_B,
             const XXX_extent*       shape_B,
             const XXX_stride*       stride_B,
             const XXX_index*        idx_B,
                   XXX_datatype      type_beta,
                   XXX_datatype      type_C,
                   int               nmode_C,
             const XXX_extent*       shape_C,      
             const XXX_stride*       stride_C,     
             const XXX_index*        idx_C,        // users should specify C twice for in-place 
                   XXX_datatype      type_D,       // instead, could C or D be NULL?
             const XXX_stride*       stride_D,     // if C == D, do we also need nmode_D, shape_D, etc.?
                   XXX_comp_datatype type_comp,
                   XXX_plan          plan,
                   XXX_attr          attr);

XXX_error
XXX_contract_execute(
             const void*             alpha,
             const void*             A,
             const void*             B,
             const void*             beta,
             const void*             C,
                   void*             D,
                   XXX_plan          plan);

// Batched tensor contraction (TBD)

XXX_error
XXX_contract_batched(
                   int               batch_size,
                   int               nmode_M,
             const XXX_extent*       shape_M,
                   int               nmode_N,
             const XXX_extent*       shape_N,
                   int               nmode_K,
             const XXX_extent*       shape_K,
                   int               nmode_L,
             const XXX_extent*       shape_L,
             const void*             alpha,
                   XXX_datatype      type_alpha,
             const void**            A,
                   XXX_datatype      type_A,
             const XXX_stride*       stride_A_M,
             const XXX_stride*       stride_A_K,
             const XXX_stride*       stride_A_L,
             const void**            B,
                   XXX_datatype      type_B,
             const XXX_stride*       stride_B_K,
             const XXX_stride*       stride_B_N,
             const XXX_stride*       stride_B_L,
             const void*             beta,
                   XXX_datatype      type_beta,
             const void**            C,
                   XXX_datatype      type_C,
             const XXX_stride*       stride_C_M,
             const XXX_stride*       stride_C_N,
             const XXX_stride*       stride_C_L,
                   void**            D,            // users should specify C twice for in-place 
                   XXX_datatype      type_D,       // instead, could C or D be NULL?
             const XXX_stride*       stride_D_M,   // if C == D, do we also need nmode_D, shape_D, etc.?
             const XXX_stride*       stride_D_N,   // maybe XXX_IN_PLACE tag for C == D?
             const XXX_stride*       stride_D_L,
                   XXX_comp_datatype type_comp,
                   XXX_attr          attr);

/* See also cublasDgemmGroupedBatched for more complex batched interface */


```

