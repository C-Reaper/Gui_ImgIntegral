# Image Integrals & Object Tracking (C)

## Overview

This project implements core computer vision and image processing techniques in C with a focus on:

* **Integral Images (Summed Area Tables)**
* **Object Tracking**
* Efficient grayscale image analysis
* Foundations for real-time image processing systems

The goal of this project is to provide fast, modular, and understandable implementations of image analysis and object tracking algorithms.

---

## Features

### Integral Images

* Generation of integral images from input frames
* Fast area and pixel sum calculations
* Optimized processing for large image datasets
* Support for grayscale image formats

### Object Tracking

* Object tracking between image frames
* Bounding box detection
* Centroid calculation
* Motion analysis
* Extendable tracking logic

### General

* Pure C implementation
* Modular architecture
* Cross-platform compatibility
* Minimal external dependencies
* Focus on performance and memory efficiency

---

## Project Structure

```text
├── src/
│   ├── Main.c
│
├── build/
│   ├── Main(.exe)
│
├── Makefile.linux
├── Makefile.windows
├── Makefile.wine
├── Makefile.web
└── LICENSE
└── README.md
```

---

## Requirements

### Compiler

* GCC
* Clang
* MSVC (optional)

### Supported Platforms

* Linux (X11)
* Emscripten (Browser)
* Windows

---

## Build Instructions and Running the Project

### Linux

```bash
make -f Makefile.linux all
make -f Makefile.linux exe
```

### Windows (MinGW)

```bash
mingw32-make -f Makefile.windows all
mingw32-make -f Makefile.windows exe
```

---

## Running the Project

```bash

```

Example output:

```text
[INFO] Image loaded
[INFO] Integral image generated
[INFO] Object detected
[INFO] Tracking completed
```

---

## Integral Image Example

An integral image stores, at each position, the sum of all pixels located above and to the left of the current pixel.

### Formula

```text
I(x, y) = img(x, y)
        + I(x-1, y)
        + I(x, y-1)
        - I(x-1, y-1)
```

### Advantages

* O(1) area sum calculations
* Faster image filtering
* Foundation for Haar-like features
* Suitable for real-time applications

---

## Object Tracking Example

The tracking pipeline is based on:

1. Motion detection
2. Segmentation
3. Centroid calculation
4. Object association between frames

---

## Performance

This project is designed with performance in mind:

* Cache-friendly memory access
* Low allocation overhead
* Linear runtime for image traversal
* Suitable for embedded systems

---

## Future Improvements

* OpenCV integration
* Multi-object tracking
* GPU acceleration
* SIMD optimizations
* Color and depth image support
* Kalman filters
* Optical flow tracking

---

## Debugging

### Linux

```bash
make -f Makefile.linux alldebug
make -f Makefile.linux debug
```

### Windows (MinGW)

```bash
mingw32-make -f Makefile.windows alldebug
mingw32-make -f Makefile.windows debug
```

---

## License

This project is licensed under the GPL 3 License.

---

## About

Developed for research and educational purposes in the fields of:

* Computer Vision
* Image Processing
* Object Tracking
* Real-Time Systems

