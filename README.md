[![Release job](https://github.com/ahlinist/diff-equations-solver/actions/workflows/release.yml/badge.svg)](https://github.com/ahlinist/diff-equations-solver/actions/workflows/release.yml)

# diff-equations-solver

# Run the image from dockerhub

docker run -i antonhlinisty/diff-eq-solver  

# Build and Run 

## docker

docker build -t diff-eq-solver . && docker run -i diff-eq-solver  

## cmake

cmake -B build && cd build && make && ./DifferentialEquationsSolver  

# Test 

## docker

docker build -f Dockerfile_tests -t diff-eq-solver-tests . && docker run diff-eq-solver-tests   

## cmake

cd tests && cmake -B build && cd build && cmake .. && make && ./DifferentialEquationsSolverTests  
