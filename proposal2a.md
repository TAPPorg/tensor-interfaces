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

typedef enum
{
    XXX_TYPE_F32_F32_ACCUM_F32 = XXX_TYPE_F32,
    ...
} XXX_comp_datatype;
```
Enumerations for the supported storage and computational datatypes. Not all combinations are required to be supported.

```C
typedef /* unspecified */ XXX_error; // Should be a trivial type

int XXX_error_check(XXX_error err); // return non-zero on error

const char* XXX_error_explain(XXX_error err);

void XXX_error_clear(XXX_error err);
```
Error handling --- implementation defined.

```C
typedef /* unspecified */ XXX_attr; // Requires initialization
typedef int32_t XXX_key; // Some values should be reserved for standardization

XXX_error XXX_attr_init(XXX_attr* attr);

XXX_error XXX_attr_destroy(XXX_attr* attr);

XXX_error XXX_attr_set(XXX_attr* attr, XXX_key, void* value);

XXX_error XXX_attr_get(XXX_attr* attr, XXX_key, void** value);

XXX_error XXX_attr_clear(XXX_attr* attr, XXX_key);
```
Implementation defined (and maybe some standard) attributes, loosely based on MPI.

```C
// Unary and binary element-wise operations (transpose, scale, norm, reduction, etc.) should also be defined!

// Compute D_{idx_D} = alpha * A_{idx_A} * B_{idx_B} + beta * C_{idx_C}

XXX_error
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
                   XXX_comp_datatype comp_type,
                   XXX_attr          attr);
```

