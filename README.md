![example workflow] (https://github.com/ahlinist/diff-equations-solver/actions/workflows/release.yml/badge.svg)

# diff-equations-solver

# Run 

docker build -t diff-eq-solver . && docker run -i diff-eq-solver  

# Test 

docker build -f Dockerfile_tests -t diff-eq-solver-tests . && docker run diff-eq-solver-tests   
