This is an initial proposal for a mixed-precision tensor contraction interface:

```C++
typedef char mode_type;
typedef int64_t stride_type;
typedef int64_t extent_type;
```

```C++
enum error_t
{
   SUCCESS,
   INVALID_ARGUMENTS,
   INTERNAL_ERROR,
   NOT_SUPPORTED
};
```

```C++
enum data_type_t
{
   TYPE_FP16,
   TYPE_FP32,
   TYPE_FP64,
   TYPE_INT16,
   TYPE_INT32,
   TYPE_INT64,
   TYPE_FCOMPLEX,
   TYPE_DCOMPLEX
};
```

```C++
/**
 * \brief This routine computes the tensor contraction C = alpha * op(A) * op(B) + beta * op(C)
 *
 * \f[ \mathcal{C}_{\text{modes}_\mathcal{C}} \gets \alpha * op(\mathcal{A}_{\text{modes}_\mathcal{A}}) op(B_{\text{modes}_\mathcal{B}}) + \beta op(\mathcal{C}_{\text{modes}_\mathcal{C}}), \f]
 * where op(X) = X or op(X) = complex conjugate(X).
 *
 *
 * \param[in] alpha Scaling for A*B (data_type_t is determined by 'typeCompute')
 * \param[in] A Pointer to the data corresponding to A (data type is determined by 'typeA')
 * \param[in] typeA Datatype of A. This values could be TYPE_SINGLE, TYPE_DOUBLE, TYPE_COMPLEX, or TYPE_DOUBLE_COMPLEX
 * \param[in] conjA Indicates if the entries of A should be conjucated (only applies to complex types)
 * \param[in] nmodeA Number of modes of A
 * \param[in] extentA Array with 'nmodeA' values that represents the extent of A (e.g., extentA[] = {4,8,12} represents an order-3 tensor of size 4x8x12).
 * \param[in] strideA Array with 'nmodeA' values that represents the strides of
 *            A with respect to each mode. While the following inequality must be obeyed: 
 *               (strideA[i] == 0) or (strideA[i] >= s * extentA[i-1], if i > 0, where s
 *               represents the last strideA[j] that is larger than 0, with j < i) .
 *            strideA[i] == 0 indicates that this dimension will be broadcasted.
 *
 *            This argument is optional and may be NULL; in this case a compact
 *            tensor is assumed.
 * \param[in] modeA Array with 'nmodeA' values that represent the modes of A.
 * \param[in] B Pointer to the data corresponding to B (data type is determined by 'typeB')
 * \param[in] typeB Datatype of B (see typeA)
 * \param[in] conjB Indicates if the entries of B should be conjugated (only applies to complex types)
 * \param[in] nmodeB Number of modes of B
 * \param[in] extentB Array with 'nmodeB' values that represents the extent of B.
 * \param[in] strideB Array with 'nmodeB' values that represents the strides of B with respect to each mode (see strideA).
 * \param[in] beta Scaling for C (data_type_t is determined by 'typeCompute')
 * \param[in,out] C Pointer to the data corresponding to C (data type is determined by 'typeC')
 * \param[in] typeC Datatype of C (see typeA)
 * \param[in] conjC Indicates if the initial entries of C should be conjucated (only applies to complex types)
 * \param[in] nmodeC Number of modes of C
 * \param[in] extentC Array with 'nmodeC' values that represents the extent of C.
 * \param[in] strideC Array with 'nmodeC' values that represents the strides of C with respect to each mode (see strideA).
 * \param[in] typeCompute Datatype of for the intermediate computation of typeCompute T = A * B
 *
 *
 * Example:
 *
 * The tensor contraction C[a,b,c,d] = 1.3 * A[b,e,d,f] * B[f,e,a,c], 
 * where C, A, and B respectively are double-precision tensors of size E_a x E_b x E_c x E_d,
 * E_b x E_e x E_d x E_f, and E_f x E_e x E_a x E_c can be computed as follows:
 *
 * double alpha = 1.3;
 * double beta = 0.0;
 * extent_type extentC[] = {E_a, E_b, E_c, E_d};
 * extent_type extentA[] = {E_b, E_e, E_d, E_f};
 * extent_type extentB[] = {E_f, E_e, E_a, E_c};
 * stride_type strideC[] = {1, E_a, E_a*E_b, E_a*E_b*E_c}; //optional
 * stride_type strideA[] = {1, E_b, E_b*E_e, E_b*E_e*E_d}; //optional
 * stride_type strideB[] = {1, E_f, E_f*E_e, E_f*E_e*E_a}; //optional
 * mode_type modeC[] = {'a','b','c','d'};
 * mode_type modeA[] = {'b','e','d','f'};
 * mode_type modeB[] = {'f','e','a','c'};
 * int nmodeA = 4;
 * int nmodeB = 4;
 * int nmodeC = 4;
 * data_type_t typeA = TYPE_FP64;
 * data_type_t typeB = TYPE_FP64;
 * data_type_t typeC = TYPE_FP64;
 * data_type_t typeCompute = TYPE_FP64;
 *
 * error_t error = tensorMult(&alpha, A, typeA, false, nmodeA, extentA, NULL, modeA, 
 *                             B, typeB, false, nmodeB, extentB, NULL, modeB, 
 *                     &beta,  C, typeC, false, nmodeC, extentC, NULL, modeC, typeCompute);
 *
 */
error_t tensorMult(const void* alpha, const void *A, data_type_t typeA, bool conjA, int nmodeA, const extent_type *extentA, const stride_type *strideA, const mode_type* modeA,
                                      const void *B, data_type_t typeB, bool conjB, int nmodeB, const extent_type *extentB, const stride_type *strideB, const mode_type* modeB,
                   const void* beta,        void *C, data_type_t typeC, bool conjC, int nmodeC, const extent_type *extentC, const stride_type *strideC, const mode_type* modeC, data_type_t typeCompute);
```
