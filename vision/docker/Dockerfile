# Base this on ResinIO's rpi-raspbian image.
FROM arm32v7/debian:stretch-slim

# Allow overriding the OpenCV version to build.
ARG opencv_version=4.1.0

# Install dependencies and clean-up apt sources.
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gfortran \
    libatlas-base-dev \
    libavcodec-dev \
    libavformat-dev \
    libavresample-dev \
    libcanberra-gtk* \
    libgtk2.0-dev \
    libgtk-3-dev \
    libjpeg-dev \
    libpng-dev \
    libswscale-dev \
    libtiff5-dev \
    libv4l-dev \
    libxvidcore-dev \
    libx264-dev \
    pkg-config \
    python \
    python2.7-dev \
    python3-dev \
    unzip \
    wget \
	apt-file \
  && rm -rf /var/lib/apt/lists/*

# Download OpenCV sources to /opt folder
WORKDIR /opt
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/${opencv_version}.zip \
    && unzip opencv.zip
RUN wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/${opencv_version}.zip \
    && unzip opencv_contrib.zip

# Install pip and numpy for both Python 2 and 3.
RUN wget https://bootstrap.pypa.io/get-pip.py
RUN python3 get-pip.py \
    && pip3 install numpy
RUN python get-pip.py \
    && pip2 install numpy

# Run OpenCV's cmake and configure it with ARM optimizations.
WORKDIR /opt/opencv-${opencv_version}/build
RUN cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib-${opencv_version}/modules \
    -D ENABLE_NEON=ON \
    -D ENABLE_VFPV3=ON \
    -D BUILD_TESTS=OFF \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
	-D OPENCV_GENERATE_PKGCONFIG=ON \
    -D BUILD_EXAMPLES=OFF ..

# Run main compile with 4 processes (best for the Pi 3).
RUN make -j8 \
    && make install \
    && make clean