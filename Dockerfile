FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Add the command to ignore release date validation completely
RUN echo 'Acquire::Check-Valid-Until "0";' > /etc/apt/apt.conf.d/99verify-peer.conf && \
    echo 'Acquire::Check-Date "0";' >> /etc/apt/apt.conf.d/99verify-peer.conf

# Update without checking timestamps and install base dependencies
RUN apt-get -o Acquire::Check-Valid-Until=false update && \
    apt-get -o Acquire::Check-Valid-Until=false install -y \
    build-essential \
    cmake \
    python3.10 \
    python3-pip \
    python3-dev \
    libffi-dev \
    curl \
    libgtest-dev \
    ninja-build \
    pkg-config \
    git \
    # API dependencies
    libspdlog-dev \
    libjsoncpp-dev \
    uuid-dev \
    openssl \
    libssl-dev \
    zlib1g-dev \
    postgresql-server-dev-all \
    libc-ares-dev \
    libcurl4-openssl-dev \
    libboost-all-dev

# Install Drogon framework
RUN git clone https://github.com/drogonframework/drogon && \
    cd drogon && \
    git checkout v1.8.7 && \
    git submodule update --init && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make && \
    make install && \
    cd / && \
    rm -rf drogon

# Install Python Poetry
RUN curl -sSL https://install.python-poetry.org | python3 -
ENV PATH="/root/.local/bin:$PATH"

WORKDIR /app
COPY . .
RUN chmod +x scripts/*

# Install Python dependencies explicitly
RUN pip3 install cffi pytest

# Make sure poetry uses the virtualenv in the container
ENV POETRY_VIRTUALENVS_IN_PROJECT=true
ENV POETRY_VIRTUALENVS_CREATE=true

# Install poetry dependencies
RUN cd /app && poetry install

# Update library cache
RUN ldconfig

CMD ["./scripts/build.sh"]
