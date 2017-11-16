# tensor-interfaces
A place to store information for the tensor discussions and possible specifications.

# Proposal 1

This is an initial proposal for a mixed-precision tensor contraction interface:

    /**
     * \brief This routine computes the tensor contraction C = alpha * A * B + beta * C
     *
     * \f[ \mathcal{C}_{\text{modes}_\mathcal{C}} \gets \alpha * \mathcal{A}_{\text{modes}_\mathcal{A}} B_{\text{modes}_\mathcal{B}} + \beta \mathcal{C}_{\text{modes}_\mathcal{C}}. \f]
    
     * \param[in] alpha Scaling for A*B (dataType is determined by 'typeA')
     * \param[in] A Pointer to the data corresponding to A (data type is determined by 'typeA')
     * \param[in] typeA Datatype of A. This values could be TYPE_SINGLE, TYPE_DOUBLE, TYPE_COMPLEX, or TYPE_DOUBLE_COMPLEX
     * \param[in] orderA Order of A
     * \param[in] sizeA Array with 'orderA' values that represents the size of A (e.g., sizeA[] = {4,8,12} represents an order-3 tensor of size 4x8x12).
     * \param[in] strideA Array with 'orderA' values that represents the strides of
     *            A with respect to each mode. While the following inequality must be obeyed: 
     *            strideA[i] >= strideA[i-1]*sizeA[i], if i > 0; else stride[0] > 0.
     *            This argument is optional and may be NULL; in this case a compact
     *            tensor is assumed.
     * \param[in] modeA Array with 'orderA' values that represent the modes of A.
     * \param[in] B Pointer to the data corresponding to B (data type is determined by 'typeB')
     * \param[in] typeB Datatype of B (see typeA)
     * \param[in] orderB Order of B
     * \param[in] sizeB Array with 'orderB' values that represents the size of B.
     * \param[in] strideB Array with 'orderB' values that represents the strides of B with respect to each mode (see strideA).
     * \param[in] beta Scaling for C (dataType is determined by 'typeC')
     * \param[in,out] C Pointer to the data corresponding to C (data type is determined by 'typeC')
     * \param[in] typeC Datatype of C (see typeA)
     * \param[in] orderC Order of C
     * \param[in] sizeC Array with 'orderC' values that represents the size of C.
     * \param[in] strideC Array with 'orderC' values that represents the strides of C with respect to each mode (see strideA).
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
     * long sizeC[] = {I0,I1,I2,I3};
     * long sizeA[] = {I1,I4,I3,I5};
     * long sizeB[] = {I5,I4,I0,I2};
     * long strideC[] = {1,I0,I0*I1,I0*I1*I2}; //optional
     * long strideA[] = {1,I1,I1*I4,I1*I4*I3}; //optional
     * long strideB[] = {1,I5,I5*I4,I5*I4*I0}; //optional
     * int modeC[] = {0,1,2,3};
     * int modeA[] = {1,4,3,5};
     * int modeB[] = {5,4,0,2};
     * int orderA = 4;
     * int orderB = 4;
     * int orderC = 4;
     * DataType typeA = TYPE_DOUBLE;
     * DataType typeB = TYPE_DOUBLE;
     * DataType typeC = TYPE_DOUBLE;
     *
     * tensorMult(&alpha, A, typeA, orderA, sizeA, NULL, modeA, 
     *                    B, typeB, orderB, sizeB, NULL, modeB, 
     *            &beta,  C, typeC, orderC, sizeC, NULL, modeC);
     *
     */
    void tensorMult(const void* alpha, const void *A, dataType typeA, int orderA, const long *sizeA, const long *strideA, const int* modeA,
                                       const void *B, dataType typeB, int orderB, const long *sizeB, const long *strideB, const int* modeB,
                    const void* beta,        void *C, dataType typeC, int orderC, const long *sizeC, const long *strideC, const int* modeC);
