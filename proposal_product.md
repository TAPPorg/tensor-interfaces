```c
/// C := alpha A * B + beta C
void product(
   type typeA, int RankA,  int[] ExtA,  int[] StrideA,  void *A,  int[]
idxA,
   type typeB, int RankB,  int[] ExtB,  int[] StrideB,  void *B,  int[]
idxB,
   type typeC, int RankC,  int[] ExtC,  int[] StrideC,  void *C,  int[]
idxC,
   type type_alpha, void *alpha,
   type type_beta,  void *beta,
   void *context,  void *INOUT
);
```

*NOTES*
- all arrays are const, except from *C
- type compute -> context
   default: compute type = typeC
- all int's are int64
- aliasing?!

refinement with explicit compute type
```c
void product_vPaul(
   type typeA, int RankA,  int[] ExtA,  int[] StrideA,  void *A,  int[]
idxA,
   type typeB, int RankB,  int[] ExtB,  int[] StrideB,  void *B,  int[]
idxB,
   type typeC, int RankC,  int[] ExtC,  int[] StrideC,  void *C,  int[]
idxC,
   type type_alpha, void *alpha,
   type type_beta,  void *beta,
   compute_type type,
   const void *infoIN,  void *infoOUT
);
```

