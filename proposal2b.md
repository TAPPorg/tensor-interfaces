See [Proposal 1a](proposal1a.md) for definitions of basic types. This "very-low-level" interface and Proposal 1a could coexist.

```C
// Compute D_{MNL} = alpha * \sum_K A_{MKL} B_{KNL} + beta * C_{MNL}

XXX_error
XXX_contract(      int               nmode_M,
             const XXX_extent*       shape_M,
                   int               nmode_N,
             const XXX_extent*       shape_N,
                   int               nmode_K,
             const XXX_extent*       shape_K,
                   int               nmode_L,
             const XXX_extent*       shape_L,
             const void*             alpha,
                   XXX_datatype      type_alpha,
             const void*             A,
                   XXX_datatype      type_A,
             const XXX_stride*       stride_A_M,
             const XXX_stride*       stride_A_K,
             const XXX_stride*       stride_A_L,
             const void*             B,
                   XXX_datatype      type_B,
             const XXX_stride*       stride_B_K,
             const XXX_stride*       stride_B_N,
             const XXX_stride*       stride_B_L,
             const void*             beta,
                   XXX_datatype      type_beta,
             const void*             C,
                   XXX_datatype      type_C,
             const XXX_stride*       stride_C_M,
             const XXX_stride*       stride_C_N,
             const XXX_stride*       stride_C_L,
                   void*             D,
                   XXX_datatype      type_D,
             const XXX_stride*       stride_D_M,
             const XXX_stride*       stride_D_N,
             const XXX_stride*       stride_D_L,
                   XXX_comp_datatype type_comp,
                   XXX_attr          attr);

// Batched tensor contraction (TBD)

XXX_error
XXX_contract_batch(  ????  );
```
