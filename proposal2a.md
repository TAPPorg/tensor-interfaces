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
    XXX_TYPE_F32,
    XXX_TYPE_F64,
    XXX_TYPE_C32,
    XXX_TYPE_C64,
    ...
} XXX_datatype;

```


```C
enum XXX_ERROR {
  XXX_SUCCESS,
  XXX_FAIL,
  // ... more to come
}

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

XXX_ERROR XXX_attr_init(XXX_attr *attr);

XXX_ERROR XXX_attr_destroy(XXX_attr *attr);

XXX_ERROR XXX_attr_set(XXX_attr *attr, XXX_key key, void *value);

XXX_ERROR XXX_attr_get(XXX_attr *attr, XXX_key key, void **value);

XXX_ERROR XXX_attr_clear(XXX_attr *attr, XXX_key key);
```


Implementation defined (and maybe some standard) attributes, loosely based on MPI.

## Contract operation

- The datatype of the $\alpha$ might be different than the one of the tensor A
  to allow for mixed precision algorithms, or complex-real products.
  
- Example:
```C
  A["abcd"] = B["ab"] * C["cd"]
  int nmode_A = 4;
  XXX_entent idx_A[4] = {'a', 'b', 'c', 'd'};
```

1. When `C` is `NULL`, the standard specifies that it should not do the sum.
2. Allow for aliasing of `C` and `D` pointers **if** `idx_C` and `idx_D` are equal.
3. Allow for `A` and `B` **at the same time** to be `NULL`, provided `C` is not `NULL`.
   In this case, the operation should be interpreted as a scaling of `C`.
   In particular, the transpose operation is also implementable like this.

  Example:
  ```C++
  // Scaling
  D["ijij"] = 2 * C["ijij"]

  // transposition (C → D)
  D["ij"] = C["ji"]
  ```

```C
// Unary and binary element-wise operations (transpose, scale, norm, reduction, etc.) should also be defined!

// Compute D_{idx_D} = alpha * A_{idx_A} * B_{idx_B} + beta * C_{idx_C}

XXX_ERROR
XXX_contract(const void*             alpha,
                   XXX_datatype      type_alpha,
             const void*             A,
                   XXX_datatype      type_A,
                   int               nmode_A,
             const XXX_extent*       shape_A,
             const XXX_stride*       stride_A,
             const XXX_index*        idx_A,
             const void*             B,
                   XXX_datatype      type_B,
                   int               nmode_B,
             const XXX_extent*       shape_B,
             const XXX_stride*       stride_B,
             const XXX_index*        idx_B,
             const void*             beta,
                   XXX_datatype      type_beta,
             const void*             C,
                   XXX_datatype      type_C,
                   int               nmode_C,
             const XXX_extent*       shape_C,
             const XXX_stride*       stride_C,
             const XXX_index*        idx_C,
                   void*             D,
                   XXX_datatype      type_D,
                   int               nmode_D,
             const XXX_extent*       shape_D,
             const XXX_stride*       stride_D,
             const XXX_index*        idx_D,
                   XXX_datatype      comp_type,
                   XXX_attr*         attr);
```

