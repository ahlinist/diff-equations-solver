# diff-equations-solver

# Run

g++ -o diff-eq-solver src/*.cpp src/*/*.cpp && ./diff-eq-solver

# Test

g++ -o diff-eq-solver-tests tests/*.cpp src/*/*.cpp -lgtest -lgtest_main -pthread && ./diff-eq-solver-tests
