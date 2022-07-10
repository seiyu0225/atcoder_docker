FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential python3 pip
RUN pip install numpy networkx joblib cython scipy llvmlite numba
WORKDIR /work