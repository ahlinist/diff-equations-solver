FROM alpine:3.18.2 AS builder

RUN apk update && \
    apk add --no-cache g++ make cmake gtest-dev gmock 

WORKDIR /app

COPY . /app

RUN cmake -B build && \
    cd build && \
     make -j8 

RUN ./build/tests/DifferentialEquationsSolverTests

# Start a new stage for the final image
FROM alpine:3.18.2

RUN apk update && \
    apk add --no-cache libstdc++

COPY --from=builder /app/build/src/DifferentialEquationsSolver /app/DifferentialEquationsSolver
COPY --from=builder /app/static/ /static/

ENTRYPOINT [ "/app/DifferentialEquationsSolver" ]

#TODO: fix compiler and gtest versions
