# GSoC 2022 Acts vectorized Linear Algebra 
Repository for the [Acts](https://github.com/acts-project/acts) Linear Algebra vectorization project: It contains infrastructure to develop, test and becnhmark linear algebra operations based on different backends. A reference implemenation is given using the [Eigen](http://eigen.tuxfamily.org) library. The [Vc](https://vcdevel.github.io/Vc-1.4.2/) library has been setup as an example for an explicitely vectorized implementation. Testing and benchmarking are done with [google test](https://google.github.io/googletest/) and [google benchmark](https://github.com/google/benchmark/blob/main/docs/user_guide.md).

## Build the Project

To build the project do:

```sh
git clone https://github.com/niermann999/Acts_vectorized_LA_backend.git
mkdir Acts_vectorized_LA_backend/build
cd Acts_vectorized_LA_backend/build
```
Run cmake, e.g.
```sh
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
```

All dependencies should build automatically.

You can find the executables in the ```build/src``` folder after running [CMake](https://cmake.org).


## Repository organization

The repository contains code to set up data for testing and benchmarking, the implementation of different matrix/vector operations, as well as dedicated unittest and benchmarks for every single operation:

-   `externals/` contains external dependencies like Eigen and Vc etc.
-   `data/` contains `fixtures` that set up test and benchmark data which can be reused across multiple test/benchmark instances. The test data defines input matrices/vectors and results for every operation. The benchmark data fills a number of input matrices/vectors with random values.
-   `definitions/` provides definitions for matrix and vector types, depending on which library/linear algebra implementation should be used. You are free to add your own.
-   `benchmarks/` contains a benchmarking suit that runs every LA operation on random data multiple times and outputs the statistics of the performance.
-   `tests/` contains automated unit tests for every LA operation. Note, that the Vc based multiplication test fails, since there is no implemention for that, yet.

## Evaluation Task

Please have a look at the ```include/matrix_operations.hpp``` file. You will find there a number of example implementations of very simple ```matrix x matrix``` operations. The Addition of two matrices is provided using both Eigen and Vc. The multiplication is only given in Eigen, as the vectorized multiplication operation should be implemented by you. You can use the Vc infrastructure ([Vc documentation](https://vcdevel.github.io/Vc-1.4.2/)) that is already provided in e.g. ```include/definitions/types.hpp```, but you are also welcome to use a different library or your own types. Please keep portability in mind though, since the Acts project will be deployed across a number of different computing setups.

You can test your solution by running the predefined unittests and benchmarks. The ```vectorized``` multiplication function is already integrated using the default data fixtures. If in your solution you want to use a different data layout, please add your own fixtures for unittesting and benchmarking. You can use the existing implementation as a guide.

## Hand in you solution

Hand in your solution by email to me (joana.niermann@cern.ch ). Please do not make a public pull request to this repository, as it can be viewed by anyone!

VERY IMPORTANT: Also hand in implementations that do not show an improved or a very bad performance! The first goal should be correctness

If you have any questions regarding the code/repository, the evaluation task or otherwise, please do not hesitate to contact me at joana.niermann@cern.ch !