FROM alpine:3.18.2

RUN apk update && \
    apk add --no-cache g++ make cmake

WORKDIR /app

COPY src/ ./src/
COPY CMakeLists.txt .

RUN cmake -B build && cd build && make

ENTRYPOINT [ "/app/build/DifferentialEquationsSolver" ]

#TODO: check smaller base images
#TODO: fix compiler and gtest versions
