This is an implementation of the Legendre Memory Unit using C++.

The Legendre Memory Unit is a novel Recurrent Neural Network design capable of achieving very fast speeds using few resources. It utilizes a sliding window of time, onto which the continuous time history of the network is orthogonally mapped. 

**This project is currently unfinished and does not function.**

## Make 

This program can be built using **make**. 

Make targets:
* **lmu**  -            Compiles LMU code
* **client** -          Compile a standalone client with a terminal interface
* **embedded** -        Compile with wrappers for JavaScript, for use in larger applications 
* **tests** -           Compile and run tests 
* **clean**  -          Removes all generated files

## Dependencies
Armadillo - a linear algebra and scientific computing library. Version 11.2.3

## Bibliography

Voelker, Kajic, Eliasmith. [Legendre Memory Units: Continuous-Time Representation in Recurrent Neural Networks](https://proceedings.neurips.cc/paper/2019/file/952285b9b7e7a1be5aa7849f32ffff05-Paper.pdf). Advances in Neural Information Processing Systems, Vol. 32, 2019. 

Chilkuri, Narsimha & Eliasmith, Chris. [Parallelizing Legendre Memory Unit Training](https://www.researchgate.net/publication/349546847_Parallelizing_Legendre_Memory_Unit_Training). 2021. 

Conrad Sanderson and Ryan Curtin. [Armadillo: a template-based C++ library for linear algebra](http://arma.sourceforge.net/armadillo_joss_2016.pdf). Journal of Open Source Software, Vol. 1, pp. 26, 2016.

Conrad Sanderson and Ryan Curtin. [A User-Friendly Hybrid Sparse Matrix Class in C++](http://arma.sourceforge.net/armadillo_lncs_2018.pdf). Lecture Notes in Computer Science (LNCS), Vol. 10931, pp. 422-430, 2018.

LeCun, Y.A., Bottou, L., Orr, G.B., Müller, KR. [Efficient BackProp](https://link.springer.com/chapter/10.1007/978-3-642-35289-8_3). Neural Networks: Tricks of the Trade. Lecture Notes in Computer Science, vol 7700, 2012. 