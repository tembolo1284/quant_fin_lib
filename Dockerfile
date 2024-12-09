FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Add the command to ignore release date validation completely
RUN echo 'Acquire::Check-Valid-Until "0";' > /etc/apt/apt.conf.d/99verify-peer.conf && \
    echo 'Acquire::Check-Date "0";' >> /etc/apt/apt.conf.d/99verify-peer.conf

# Update without checking timestamps
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
    ninja-build

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

CMD ["./scripts/build.sh"]
