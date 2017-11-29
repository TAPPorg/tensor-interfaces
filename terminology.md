# Terminology

## Tensor

A **dense tensor** is a multi-dimensional array of (usually) arithmetic values. A tensor has a non-negative [positive? are scalars OK?] number of **dimensions** [or **modes**, **ways**, etc.?]. Each **dimension** has a non-negative [positive?] **length**. As an example, consider a 4-dimensional tensor *A* with real elements and dimension lengths 4, 5, 9, and 3:

![](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BA%7D%20%5Cin%20%5Cmathbb%7BR%7D%5E%7B4%20%5Cotimes%205%20%5Cotimes%209%20%5Cotimes%203%7D)

In a programming language such as C, this would correspond to:

```C
double A[4][5][9][3];
```

(or `float`, etc.).

## Indexing

Individual tensor elements are referred to by **indexing**. A *d*-dimensional tensor is indexed by *d* [not necessarily distinct?] **symbols**. Each symbol may take on a definite integral value in the range `[0,n)` [can we agree on 0-based indexing?], where *n* is the length of the dimension being indexed. If a symbol appears multiple times then it takes on the same value in each case. For example, we may refer to elements of the tensor *A* above using symbols *i*, *j*, *k*, and *l*:

![](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BA%7D_%7Bijkl%7D%20%5Cin%20%5Cmathbb%7BR%7D)

In this case it must be that `0 <= i < 4`, `0 <= j < 5`, `0 <= k < 9`, and `0 <= l < 3`.

## Shape

A tensor **shape** is an ordered set of non-negative integers. The *i*th entry, `shape[i]`, gives the length of the *i*th dimension of the tensor. The shape of a particular tensor *A* is denoted `shape_A`. Dimension *i* in tensor *A* is **compatible** with dimension *j* in tensor *B* if `shape_A[i] == shape_B[j]`. *Only compatible dimensions may share the same indexing symbol* [is this always necessary?].

## Layout

When the values of a tensor are placed in a linear storage medium (e.g. main memory), additional information is necessary to map values referred to by indices to linear locations. A tensor **layout** is such a map from *d* indices to a linear location [should the layout only be defined on the ranges of the tensor dimensions?]:

![](https://latex.codecogs.com/gif.latex?%5Cmathrm%7Blayout%7D%20%5C%2C%5Ccolon%20%5Cmathbb%7BN%7D%5Ed%20%5Cto%20%5Cmathbb%7BN%7D)

The most useful layout for dense tensors is the **general stride** layout:

![](https://latex.codecogs.com/gif.latex?%5Cmathrm%7Blayout%7D%20%5C%2C%5Ccolon%20%28i_0%2C%5Cldots%2Ci_%7Bd-1%7D%29%20%5Cmapsto%20%5Csum_%7Bk%3D0%7D%5E%7Bd-l%7D%20s_k%20%5Ccdot%20i_k)

The ordered set of *s* values is the **stride** of the tensor, denoted for soe tensor *A* by `stride_A`. There are two special cases of the general stride layout of importance: the **column-major** layout and the **row-major** layout. These are defined by:

![](https://latex.codecogs.com/gif.latex?%5Cbegin%7Balign*%7D%20%5Cmathrm%7Blayout_%7Bcol%7D%7D%20%5C%2C%5Ccolon%20%28i_0%2C%5Cldots%2Ci_%7Bd-1%7D%29%20%5Cmapsto%20%26%20%5Csum_%7Bk%3D0%7D%20i_k%20%5Cprod_%7Bl%3D0%7D%5E%7Bk-1%7D%20n_l%20%5C%5C%20%5Cmathrm%7Blayout_%7Brow%7D%7D%20%5C%2C%5Ccolon%20%28i_0%2C%5Cldots%2Ci_%7Bd-1%7D%29%20%5Cmapsto%20%26%20%5Csum_%7Bk%3D0%7D%20i_k%20%5Cprod_%7Bl%3Dk&plus;1%7D%5E%7Bd-1%7D%20n_l%20%5Cend%7Balign*%7D)

where *n* are the dimension lengths of the tensor. Since these layouts depend only on the tensor shape, an additional stride vector is not required.

## Tensor Specification

A tensor *A* is fully specified by:

1. Its dimensionality `ndim_A`.
2. Its shape `shape_A`.
3. Its layout (restricting ourselves to general stride layouts) `stride_A`, or an assumption of column- or row-major storage.
4. A pointer to the origin element `A`.
5. Its data type (real, complex, precision, etc.), unless assumed from the context.

## Other Terms

The **size** of a tensor is the number of elements, given by the product of the dimension lengths. The **span** of a tensor is the difference between the lowest and highest linear location over all elements, plus one. In a general stride layout this is given by: 

![](https://latex.codecogs.com/gif.latex?%5Cmathrm%7Bspan%7D%20%3D%201&plus;%5Csum_%7Bi%3D0%7D%5E%7Bd-1%7D%20%28n_i-1%29%5Ccdot%20%7Cs_i%7C)

A tensor is **contiguous** if its span is equal to its size. Two dimensions *i* and *j* are **sequentially contiguous** if `stride[j] == stride[i]*shape[i]` (note this requires `stride[j] >= stride[i]` and means that sequential contiguity is not commutative). An ordered set of dimensions are sequentially contiguous if each consecutive pair of dimensions is sequentially contiguous.

A sequentially contiguous set of dimensions may be replaced (**folded**) by a single dimension whose length is equal to the product of the lengths of the original dimensions, and whose stride is equal to the smallest stride of the original dimensions. The tensor formed from folding contains the same elements at the same linear locations as the original. A contiguous tensor may always be folded to a vector (or in general to a tensor of any lower dimensionality).

### Issues

- Do strides have to be positive? Can they be 0?
- Even if strides can't be 0 or negative, do elements have to be unique? Does it depend on whether you're writing or reading?
- Is the origin element the (0,...,0) element or the "bottom-left" (lowest-address) element if strides can be negative?
- Does anyone care about layouts other than general stride?
- What about complex: do we need an "imaginary stride"?
- Do strides need to be in units of the data type size? Esp. what about complex?
- Ditto for types like double-double.
- Other structures beyond dense.
