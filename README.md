[![Release job](https://github.com/ahlinist/diff-equations-solver/actions/workflows/release.yml/badge.svg)](https://github.com/ahlinist/diff-equations-solver/actions/workflows/release.yml)

# diff-equations-solver

# Run the image from dockerhub

docker run -i antonhlinisty/diff-eq-solver

# Build and Run 

docker build -t diff-eq-solver . && docker run -i diff-eq-solver  

# Test 

docker build -f Dockerfile_tests -t diff-eq-solver-tests . && docker run diff-eq-solver-tests   
