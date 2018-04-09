# Terminology

## Tensor

A **dense tensor** is a multi-dimensional array of arithmetic values. A tensor has a positive number, *n*, of **modes**  (i.e. it is an *n*-mode tensor).<sup>[1](#foot1)</sup> Each **mode** has a non-negative **extent**<sup>[2](#foot2)</sup>, which is the number of distinct values that the mode can have. As an example, consider a 4-mode tensor *A* with real elements and extents of 4, 5, 9, and 3:

![](https://latex.codecogs.com/gif.latex?\mathcal{A}\in{}\mathbb{R}^{4\otimes{}5\otimes9{}\otimes{}3})

In a programming language such as C, this would correspond to:

```C
double A[4][5][9][3];
```

(or `float`, etc.).

<a name="foot1">1</a>) Also: *n*-dimensional, *n*-way, order-*n*, *n*-ary, rank-*n*, *n*-adic, *n*-fold, *n*-index, *n* subspaces.

<a name="foot2">2</a>) Also: length, dimension, size.

## Indexing

Individual tensor elements are referred to by **indexing**. A *d*-mode tensor is indexed by *d* **indices**.<sup>[3](#foot3)</sup> Each index may take on a definite integral value in the range `[0,n)`,<sup>[4](#foot4)</sup> where *n* is the extent of the mode being indexed. If an index appears multiple times then it takes on the same value in each case. For example, we may refer to elements of the tensor *A* above using symbols *i*, *j*, *k*, and *l*:

![](https://latex.codecogs.com/gif.latex?\mathcal{A}_{ijkl}\in{}\mathbb{R})

In this case it must be that `0 <= i < 4`, `0 <= j < 5`, `0 <= k < 9`, and `0 <= l < 3`.

<a name="foot3">3</a>) Also: labels, symbols.

<a name="foot4">4</a>) 0-based (C-style) indexing is used here, but 1-based index (Fortran- or Matlab-style) is also possible. The distinction between the two is only relevant when referencing a single element of sub-range of elements. Operations such as tensor contraction do not generally need to explicitly depend on any indexing method.

## Shape

A tensor **shape**<sup>[5](#foot5)</sup> is an ordered set of non-negative integers. The *i*th entry, `shape[i]`, gives the extent of the *i*th mode of the tensor. The shape of a particular tensor *A* is denoted `shape_A`. Mode *i* in tensor *A* is **compatible** with mode *j* in tensor *B* if `shape_A[i] == shape_B[j]`. Only compatible dimensions may share the same index.

<a name="foot5">5</a>) Also: size, structure.

## Layout

When the values of a tensor are placed in a linear storage medium (e.g. main memory), additional information is necessary to map values referred to by indices to linear locations. A tensor **layout** for a *d*-mode tensor is such a map from *d* indices to a linear location:

![](https://latex.codecogs.com/gif.latex?\mathrm{layout}\\,\colon\mathbb{N}^d\to\mathbb{N})

The most useful layout for dense tensors is the **general stride** layout:

![](https://latex.codecogs.com/gif.latex?\mathrm{layout}\\,\colon(i_0,\ldots,i_{d-1})\mapsto\sum_{k=0}^{d-1}i_k\cdot{s_k})

The ordered set of *s* values is the **stride**<sup>[6](#foot6)</sup> of the tensor, denoted for some tensor *A* by `stride_A`. In general a stride value may be negative, but the strides must obey the condition that no two elements with distinct indices share the same linear location. There are two special cases of the general stride layout of importance: the **column-major** layout and the **row-major** layout. These are defined by:

![](https://latex.codecogs.com/gif.latex?\begin{align*}\mathrm{layout_{col}}\\,\colon(i_0,\ldots,i_{d-1})\mapsto{}&\sum_{k=0}^{d-1}i_k\prod_{l=0}^{k-1}n_l\\\\{}\mathrm{layout_{row}}\\,\colon(i_0,\ldots,i_{d-1})\mapsto{}&\sum_{k=0}^{d-1}i_k\prod_{l=k+1}^{d-1}n_l\end{align*})

where *n* are the extents of the tensor. Since these layouts depend only on the tensor shape, an additional stride vector is not required.

<a name="foot6">6</a>) Also: shape, leading dimension (similar but not identical idea).

## Tensor Specification

A tensor *A* is fully specified by:

1. Its number of modes `nmode_A`.
2. Its shape `shape_A`.
3. Its layout (restricting ourselves to general stride layouts) `stride_A`, or an assumption of column- or row-major storage.
4. A pointer to the origin element `A`. This is the location of ![](https://latex.codecogs.com/gif.latex?\mathcal{A}_{0\ldots{}0}).
5. Its data type (real, complex, precision, etc.), unless assumed from the context.

## Other Terms

The **size**<sup>[7](#foot7)</sup> of a tensor is the number of elements, given by the product of the extents. The **span**<sup>[8](#foot8)</sup> of a tensor is the difference between the lowest and highest linear location over all elements, plus one. In a general stride layout this is given by: 

![](https://latex.codecogs.com/gif.latex?\mathrm{span}=1+\sum_{i=0}^{d-1}(n_i-1)\cdot|s_i|)

A tensor is **contiguous** if its span is equal to its size. The *i*th and *j*th modes are **sequentially contiguous** if `stride[j] == stride[i]*shape[i]` (note this requires `stride[j] >= stride[i]` and means that sequential contiguity is not commutative). An ordered set of modes is sequentially contiguous if each consecutive pair of modes is sequentially contiguous.

A sequentially contiguous set of modes may be replaced (**folded**<sup>[9](#foot9)</sup>) by a single mode whose extent is equal to the product of the extents of the original modes, and whose stride is equal to the smallest stride of the original modes. The tensor formed from folding contains the same elements at the same linear locations as the original. A contiguous tensor may always be folded to a vector (or in general to a tensor with any fewer number of modes).

<a name="foot7">7</a>) Also: length.

<a name="foot8">8</a>) Also: extent.

<a name="foot9">9</a>) Also: linearized, unfolded (confusingly).
