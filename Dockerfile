FROM python:3.10.6

RUN apt-get update && apt-get install -y \
    wget \
    build-essential \
    cmake \
    libfreetype6-dev \
    pkg-config \
    libfontconfig-dev \
    libjpeg-dev \
    libopenjp2-7-dev 

WORKDIR /app

# Install Python dependencies
COPY requirements.txt .
RUN pip install -r requirements.txt

# Install Poppler
RUN wget https://poppler.freedesktop.org/poppler-data-0.4.9.tar.gz \
    && tar -xf poppler-data-0.4.9.tar.gz \
    && cd poppler-data-0.4.9 \
    && make install \
    && cd .. \
    && wget https://poppler.freedesktop.org/poppler-20.08.0.tar.xz \
    && tar -xf poppler-20.08.0.tar.xz \
    && cd poppler-20.08.0 \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install \
    && ldconfig

# Copy application code
COPY . .

# Start the application
CMD ["python", "app.py"]
