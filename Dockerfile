FROM alpine:3.18.2

RUN apk update && \
    apk add --no-cache g++ make cmake

WORKDIR /app

COPY build/src/DifferentialEquationsSolver /app/DifferentialEquationsSolver

ENTRYPOINT [ "/app/DifferentialEquationsSolver" ]

#TODO: check smaller base images
#TODO: fix compiler and gtest versions
