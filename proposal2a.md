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
void contract_<type_name>(<type> alpha, nmode_type nmode_A,
                                        const <type>* A,
                                        const extent_type* shape_A,
                                        const stride_type* stride_A,
                                        const index_type* idx_A,
                                        nmode_type nmode_B,
                                        const <type>* B,
                                        const extent_type* shape_B,
                                        const stride_type* stride_B,
                                        const index_type* idx_B,
                           <type> beta, nmode_type nmode_C,
                                        <type>* C,
                                        const extent_type* shape_C,
                                        const stride_type* stride_C,
                                        const index_type* idx_C);
```
Here `<type_name>` is `f32`, `f64`, `i32`, etc. and `<type>` is correspondingly `float`, `double`, etc.
