[![Release job](https://github.com/ahlinist/diff-equations-solver/actions/workflows/release.yml/badge.svg)](https://github.com/ahlinist/diff-equations-solver/actions/workflows/release.yml)

# diff-equations-solver

# Run the image from dockerhub

docker run --pull=always -i -p 8080:8080 antonhlinisty/diff-eq-solver  

# Build and Run 

## docker

docker build -f Dockerfile_local -t diff-eq-solver-local . && docker run -i -p 8080:8080 diff-eq-solver-local  

## cmake

cmake -B build && cd build && make && ./src/DifferentialEquationsSolver  

# Test 

## docker

docker build -f Dockerfile_tests -t diff-eq-solver-tests . && docker run diff-eq-solver-tests   

## cmake

cmake -B build && cd build && make && make test  

# Use

http://localhost:8080/solution?a=1&b=2&c=3&initial_x=1&initial_x_prime=3  