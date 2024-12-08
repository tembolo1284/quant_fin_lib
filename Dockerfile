FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3.10 \
    python3-pip \
    curl

RUN curl -sSL https://install.python-poetry.org | python3 -

WORKDIR /app
COPY . .

# Make scripts executable
RUN chmod +x scripts/*

CMD ["./scripts/build.sh"]
