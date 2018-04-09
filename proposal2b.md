```C
typedef uint32_t nmode_type;
```
I prefer unsigned for this. 32 bits is plenty, could also just be `unsigned`.

```C
typedef int64_t extent_type;
typedef int64_t stride_type;
```
These types should almost certainly be signed. 64-bit seems like a fair assumption these days.

```C
typedef int32_t index_type;
```
This can probably be just about any integral type.

```C
void contract_<type_name>(nmode_type nmode_M, const extent_type* shape_M,
                          nmode_type nmode_N, const extent_type* shape_N,
                          nmode_type nmode_K, const extent_type* shape_K,
                          <type> alpha, const <type>* A,
                                        const stride_type* stride_A_M,
                                        const stride_type* stride_A_K,
                                        const <type>* B,
                                        const stride_type* stride_B_K,
                                        const stride_type* stride_B_N,
                           <type> beta, <type>* C,
                                        const stride_type* stride_C_M,
                                        const stride_type* stride_C_N);
```
Here `<type_name>` is `f32`, `f64`, `i32`, etc. and `<type>` is correspondingly `float`, `double`, etc.
