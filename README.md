TAPP: Tensor Algebra Processing Primitives
===
TAPP is a draft for a low-level standard tensor interface, similar to BLAS interface for matrices.

TAPP defines the interface itself and clarifies the related technicalities. A reference implementation is available [here.](https://github.com/TAPPorg/reference-implementation)

TAPP formulates the basic tensor contraction operation as
```
D(idx_D) = alpha A(idx_A) * B(idx_B) + beta C(idx_C),
```
where A,B,C and D are tensors and alpha, beta scalars. idx_* is an array of indices of the corresponding tensor using the Einstein summation convention, e.g. 
```
    int64_t idx_D[3] = {'a', 'd', 'e'};
    int64_t idx_A[3] = {'a', 'b', 'c'};
    int64_t idx_B[4] = {'c', 'd', 'e', 'b'};
    int64_t idx_C[3] = {'a', 'd', 'e'};
```
The function TAPP_create_tensor_product in src/tapp/product.h uses this information to create a contraction plan, which is then executed by TAPP_execute_product.


TAPP was devised following CECAM Workshop on Tensor Contraction Library Standardization which took place in Toulouse May 22-24, 2024. Since then, a working group is meeting regularly to maintain TAPP. 

[tensor.sciencesconf.org](https://tensor.sciencesconf.org/)

Please submit all technical questions, suggestions and queries to Issues.
For other inquiries, you can contact:
Devin Matthews damatthews at mail.smu.edu 
Paolo Bientinesi pauldj at cs.umu.se 
Jan Brandejs jbrandejs at irsamc.ups-tlse.fr 
