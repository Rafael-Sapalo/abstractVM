FROM ubuntu:latest

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

CMD ["/bin/bash"]
