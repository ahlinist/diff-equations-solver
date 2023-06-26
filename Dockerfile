FROM alpine:3.18.2 AS builder

RUN apk update && \
    apk add --no-cache g++ make cmake

WORKDIR /app

COPY src /app/src
COPY tests /app/tests
COPY CMakeLists.txt /app/CMakeLists.txt

RUN cmake -B build && \
    cd build && \
    make 

# Start a new stage for the final image
FROM alpine:3.18.2

# Copy only the executable from the build stage
COPY --from=builder /app/build/src/DifferentialEquationsSolver /app/DifferentialEquationsSolver

ENTRYPOINT ["/app/DifferentialEquationsSolver"]

#TODO: check smaller base images
#TODO: fix compiler and gtest versions
