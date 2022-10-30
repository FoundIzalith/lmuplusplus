This is an implementation of the Legendre Memory Unit using C++.

The Legendre Memory Unit is a novel Recurrent Neural Network design capable of achieving very fast speeds using few resources. Unlike other RNNs, it is capable of being parallelized with some modifications. This allows us to perform complex analysis with neural networks using relatively few computational resources. 

**This project is currently unfinished and does not yet function.**

## Make 

This program can be built using **make**. 

Make targets:
* **lmu**  -            Compiles LMU code
* **client** -          Compile a standalone client with a terminal interface
* **jsbind** -          Compile with wrappers for JavaScript
* **pybind** -          Compile with wrappers for Python 
* **tests** -           Compile and run tests 
* **clean**  -          Removes all generated files

## Dependencies
[Armadillo](http://arma.sourceforge.net/) - a linear algebra and scientific computing library. Version 11.2.3


## References

Original implementation of the LMU: [nengo/keras-lmu](https://github.com/nengo/keras-lmu)

Implementation of the parallelized LMU: [hrshtv/pytorch-lmu](https://github.com/hrshtv/pytorch-lmu)

[1] Voelker, Kajic, Eliasmith. [Legendre Memory Units: Continuous-Time Representation in Recurrent Neural Networks](https://proceedings.neurips.cc/paper/2019/file/952285b9b7e7a1be5aa7849f32ffff05-Paper.pdf). Advances in Neural Information Processing Systems, Vol. 32, 2019. 

[2] Chilkuri, Narsimha & Eliasmith, Chris. [Parallelizing Legendre Memory Unit Training](https://www.researchgate.net/publication/349546847_Parallelizing_Legendre_Memory_Unit_Training). 2021. 

[3] Conrad Sanderson and Ryan Curtin. [Armadillo: a template-based C++ library for linear algebra](http://arma.sourceforge.net/armadillo_joss_2016.pdf). Journal of Open Source Software, Vol. 1, pp. 26, 2016.

[4] Conrad Sanderson and Ryan Curtin. [A User-Friendly Hybrid Sparse Matrix Class in C++](http://arma.sourceforge.net/armadillo_lncs_2018.pdf). Lecture Notes in Computer Science (LNCS), Vol. 10931, pp. 422-430, 2018.

[5] LeCun, Y.A., Bottou, L., Orr, G.B., Müller, KR. [Efficient BackProp](https://link.springer.com/chapter/10.1007/978-3-642-35289-8_3). Neural Networks: Tricks of the Trade. Lecture Notes in Computer Science, Vol. 7700, 2012. 

[6] Xavier Glorot, Yoshua Bengio. [Understanding the difficulty of training deep feedforward neural networks](http://proceedings.mlr.press/v9/glorot10a.html). Proceedings of the Thirteenth International Conference on Artificial Intelligence and Statistics, PMLR 9:249-256, 2010. 


