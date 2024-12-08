FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3.10 \
    python3-pip \
    curl \
    libgtest-dev \
    ninja-build

RUN curl -sSL https://install.python-poetry.org | python3 -
ENV PATH="/root/.local/bin:$PATH"

WORKDIR /app
COPY . .
RUN chmod +x scripts/*

CMD ["./scripts/build.sh"]
