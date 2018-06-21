This is an initial proposal for a mixed-precision tensor contraction interface:

```C++
typedef uint32_t mode_type
typedef uint32_t nmode_type;
typedef int64_t stride_type
typedef int64_t extent_type
```

```C++
enum error_t
{
   SUCCESS,
   INVALID_ARGUMENTS,
   INTERNAL_ERROR,
   ...
}
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
}
```

```C++
/**
 * \brief This routine computes the tensor contraction C = alpha * op(A) * op(B) + beta * op(C)
 *
 * \f[ \mathcal{C}_{\text{modes}_\mathcal{C}} \gets \alpha * op(\mathcal{A}_{\text{modes}_\mathcal{A}}) op(B_{\text{modes}_\mathcal{B}}) + \beta op(\mathcal{C}_{\text{modes}_\mathcal{C}}), \f]
 * where op(X) = X or op(X) = complex conjugate(X).
 *
 *
 * \param[in] alpha Scaling for A*B (data_type_t is determined by 'typeA')
 * \param[in] A Pointer to the data corresponding to A (data type is determined by 'typeA')
 * \param[in] typeA Datatype of A. This values could be TYPE_SINGLE, TYPE_DOUBLE, TYPE_COMPLEX, or TYPE_DOUBLE_COMPLEX
 * \param[in] conjA Indicates if the entries of A should be conjucated (only applies to complex types)
 * \param[in] nmodeA Number of modes of A
 * \param[in] extentA Array with 'nmodeA' values that represents the extent of A (e.g., extentA[] = {4,8,12} represents an order-3 tensor of size 4x8x12).
 * \param[in] strideA Array with 'nmodeA' values that represents the strides of
 *            A with respect to each mode. While the following inequality must be obeyed: 
 *               (strideA[i] >= strideA[i-1]*extentA[i], if i > 0) or (strideA[i] == 0), stride[i] >= 0.
 *            strideA[i] == 0 indicates that this dimension will be broadcasted.
 *
 *            This argument is optional and may be NULL; in this case a compact
 *            tensor is assumed.
 * \param[in] modeA Array with 'nmodeA' values that represent the modes of A.
 * \param[in] B Pointer to the data corresponding to B (data type is determined by 'typeB')
 * \param[in] typeB Datatype of B (see typeA)
 * \param[in] conjB Indicates if the entries of B should be conjucated (only applies to complex types)
 * \param[in] nmodeB Number of modes of B
 * \param[in] extentB Array with 'nmodeB' values that represents the extent of B.
 * \param[in] strideB Array with 'nmodeB' values that represents the strides of B with respect to each mode (see strideA).
 * \param[in] beta Scaling for C (data_type_t is determined by 'typeC')
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
 * The tensor contraction C[i0,i1,i2,i3] = 1.3 * A[i1,i4,i3,i5] * B[i5,i4,i0,i2], 
 * where C, A, and B respectively are double-precision tensors of size I0xI1xI2xI3, I1xI4xI3xI5,
 * and I5xI4xI0xI2 can be computed as follows:
 *
 * double alpha = 1.3;
 * double beta = 0.0;
 * extent_type extentC[] = {I0,I1,I2,I3};
 * extent_type extentA[] = {I1,I4,I3,I5};
 * extent_type extentB[] = {I5,I4,I0,I2};
 * stride_type strideC[] = {1,I0,I0*I1,I0*I1*I2}; //optional
 * stride_type strideA[] = {1,I1,I1*I4,I1*I4*I3}; //optional
 * stride_type strideB[] = {1,I5,I5*I4,I5*I4*I0}; //optional
 * mode_type modeC[] = {0,1,2,3};
 * mode_type modeA[] = {1,4,3,5};
 * mode_type modeB[] = {5,4,0,2};
 * nmode_type nmodeA = 4;
 * nmode_type nmodeB = 4;
 * nmode_type nmodeC = 4;
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
error_t tensorMult(const void* alpha, const void *A, data_type_t typeA, bool conjA, nmode_type nmodeA, const extent_type *extentA, const stride_type *strideA, const mode_type* modeA,
                                      const void *B, data_type_t typeB, bool conjB, nmode_type nmodeB, const extent_type *extentB, const stride_type *strideB, const mode_type* modeB,
                   const void* beta,        void *C, data_type_t typeC, bool conjC, nmode_type nmodeC, const extent_type *extentC, const stride_type *strideC, const mode_type* modeC, data_type_t typeCompute);
```
