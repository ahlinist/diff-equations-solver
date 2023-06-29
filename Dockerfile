FROM alpine:3.18.2 AS builder

RUN apk update && \
    apk add --no-cache g++ make cmake gtest-dev gmock 

WORKDIR /app

COPY src /app/src
COPY tests /app/tests
COPY CMakeLists.txt /app/CMakeLists.txt

RUN cmake -B build && \
    cd build && \
    make 

RUN ./build/tests/DifferentialEquationsSolverTests

# Start a new stage for the final image
#FROM alpine:3.18.2

FROM scratch

#RUN apk update && \
#    apk add --no-cache libstdc++

# Copy only the executable from the build stage
COPY --from=builder /app/build/src/DifferentialEquationsSolver /app/DifferentialEquationsSolver

ENTRYPOINT ["/app/DifferentialEquationsSolver"]

#TODO: check smaller base images
#TODO: fix compiler and gtest versions
