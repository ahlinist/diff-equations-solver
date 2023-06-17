FROM alpine:3.18.2

RUN apk update && \
    apk add --no-cache g++

WORKDIR /app

COPY src/ ./src/

RUN g++ -o diff-eq-solver src/*.cpp src/*/*.cpp

ENTRYPOINT [ "/app/diff-eq-solver" ]
