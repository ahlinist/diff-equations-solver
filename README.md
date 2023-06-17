# diff-equations-solver

# Run

g++ -o diff-eq-solver src/*.cpp src/*/*.cpp && ./diff-eq-solver  

or  

docker build -t diff-eq-solver .  

and  

sudo docker run -i diff-eq-solver  

# Test

g++ -o diff-eq-solver-tests tests/main.cpp tests/*/*.cpp src/*/*.cpp -lgtest -lgtest_main -pthread && ./diff-eq-solver-tests  

or  

sudo docker build -f Dockerfile_tests -t diff-eq-solver-tests .  

and  

sudo docker run diff-eq-solver-tests  
