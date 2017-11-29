# Classifying and Specifying Tensor Operations

- *n*-ary operations
    - Do we count all tensors (operands, maybe including lone scalars?) on the RHS? Just tensors being "multiplied"? All but the LHS?
    - How are `norm`, `reduce`, and `dot` classified?
    - Is it enough to consider just "binary" operations?
- Existing methods for specifying operations (contraction at least):
    1. Reduction to canonical form. Example: specify input permutation of A and B and always contract last *k* indices of A and first *k* indices of B, then permute output into C.
    
        ```C[abcd] = A[afce]*B[edbf] -> perm_A = [0,2,3,1], perm_B = [0,3,2,1], perm_C = [0,2,1,3]```
        
        (Note that the permutations are not unique)
        
    2. Pick dimensions by position. Example: specify which dimensions are contracted listing their position in A and B. Dimensions of C are all those left over (some interfaces have no way to choose the ordering in C!). E.g. Tensor Toolbox and Eigen.
    
        ```C[abcd] = A[afce]*B[edbf] -> ctr_A = [3,1], ctr_B = [0,3], + explicit permutation of C```
        
    3. Pick dimensions using Einstein summation. Example: specify index strings for each operand. Repeated indices in A and B are contracted. Relative positions determine necessary permutations. I think this is everybody's current favorite.
    
        ```C[abcd] = A[afce]*B[edbf] -> idx_A = "afce", idx_B = "edbf", idx_C = "abcd"```
        
    4. Specify the shape of the operation not the shape of the operands. Example: generalize GEMM interface by specifying multiple *m*, *n*, and *k* dimensions and shapes, with two stride vectors for each operand. This is actually highly useful for the implementation!
    
        ```C++
        contract(ndim_M, shape_M, ndim_N, shape_N, ndim_K, shape_K,
                 alpha, A, stride_A_M, stride_A_K,
                        B, stride_B_K, stride_B_N,
                  beta, C, stride_C_M, stride_C_N);
        ```
- Permutations: "comes-from" or "goes-to" notation?
- Beyond contraction:
  - Generalized Einstein summation: sum over all indices that don't appear on the LHS. Allows: batched operations (weighting), single-index trace, extended contraction (CP decomposition etc.).
  - What are these operations called? Possibility:
    - Appears in only A or B but not both: trace.
    - Appears in A and B but not C: contract.
    - Appears in A or B (not both) and in C: free.
    - Appears in only C: replicate (or broadcast).
    - Appears in all 3: weight.
    - More than 3 operands: who knows?
- "Batched" operations:
  - When batch operands are regularly strided in memory, it can be encoded as a higher-dimensional non-batched operation. True for batched matrix operations as well but it doesn't fit in the matrix-based interface.
  - Otherwise (batch operands are randomly located), is it better to have a batched interface or more complicated tensor layouts? E.g. [TBLIS](https://github.com/devinamatthews/tblis) can do operations over tensors and matrices without regular strides (I call it a scatter layout).
  - Why do we want batched operations?
    - Block sparsity!
    - Others?
- Threading: should this be explicit in the interface
- Mixed/extended/reduced precision and mixed-domain. Integers too.
  - Internal computation in single precision may significant speed many things up without changing the calling program.
  - Good complex/mixed domain support very important in many calculations.
- Notation:
    - free vs. uncontracted vs. external and bound vs. contracted vs. internal
    - permutation vs. transpose vs. shuffle vs. etc.
    - contraction vs. multiplication (should multiplication be something more general?)
