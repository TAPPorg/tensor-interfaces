# Interface Issues

- Integer size:
  - Fixed at 32-bit, 64-bit or configurable?
  - Same for lengths and strides?
  - Signed or unsigned?
- Type for index string:
  - char or integral (char allows string literals in C/C++).
- Pointers or pass by values for scalars?
- Return values (norm, dot, etc.) or parameters?
- Does reduce (idamax, etc.) return the index, the value, or both?
- Dedicated reductions (max, min, norm2, etc.) or a single function with operation tag?
- For a mixed-precision interface:
  - Separate functions?
  - Type tags?
  - What is the type of alpha and beta?
  - Internal computation type?
  - Accumulation type?
- Storage format for complex:
  - Separate real/complex storage nice for some applications.
- High-level vs. low-level interfaces:
  - Low-level interface *must* be in ANSI C.
    - Structs are probably a no-no
    - Language compatibility (esp with Fortran?)
    - Doesn't necessarily need to be concise and intuitive
    - 1st concern
  - High-level interfaces
    - Can be tuned to language and/or usage
    - Use existing interfaces as well (Eigen, MATLAB, Numpy, etc.)
    - 2nd concern
- Error checking:
  - When does it happen?
  - How much?
  - Can it be turned off?
  - What happens on error?
- Hardware:
  - CPU only?
  - Separate interface for GPU or combined? Heterogeneous?
  - Out-of-core
  - Threading
  - Distributed parallelism (maybe)?
  
## "Plans"
  
Paul Springer incorporates the notion of a "plan" in [HPTT](https://github.com/springer13/hptt), similar to how it is used in e.g. FFTW. The basic idea is that instead of just calling an interface function, one creates an object for the operation. This object can then be executed (possibly more than once) and maniuplated to change the operation parameters.
  
Examples of why this is helpful:
  - Reducing overhead by calling the object multiple times with different pointers
    - This also can increase the amount of allowable overhead, opening up new analysis/optimization opportunities
  - Passing around operations for task scheduling, etc. (Lambdas work for this too).
  - Creating an isolated execution environment
    - E.g. specifying threading, precision, algorithm, etc. without being affected by global changes
