# c-3dviewer — C/C++ OpenGL 3D Model Viewer

A desktop application that loads, parses, and renders Wavefront `.obj` models using modern OpenGL and a Qt6-based GUI. Developed as a coursework project to practice cross-language integration (C/C++), matrix mathematics, file parsing, and UI development.

## Features

- **OBJ Loader**: Parses vertices, normals, texture coordinates, and faces  
- **Rendering**: Modern OpenGL pipeline with vertex & fragment shaders  
- **Camera Controls**: Orbit, pan, and zoom via mouse & keyboard  
- **Affine Transformations**: Manual implementation of translate, rotate, scale  
- **Demo Models**: Included sample `.obj` files for quick testing  

## Prerequisites

- **Compiler**: GCC or Clang (C11/C++11 compatible)  
- **Libraries**:  
  - Qt6 (QtWidgets, QtGui, QtCore)  
  - OpenGL loader (GLEW or GLAD)  
- **Build tools**: QMake (`qmake`), GNU Make, `pkg-config`  
- **Utilities**: LaTeX (for PDF documentation), optional Check or custom test harness  
- **Platform**: Unix-like (Linux/macOS)

## Build & Run

1. **Generate Makefile & build**  
    ```bash
    cd src/my3dViewer
    qmake
    make
    ```
2. **Launch viewer**  
    ```bash
    ./my3dViewer path/to/model.obj
    ```
3. **Run unit tests**  
    ```bash
    make test
    ```
4. **Generate PDF documentation**  
    ```bash
    make pdf   # produces my3dViewer.pdf
    ```
5. **Clean build artifacts**  
    ```bash
    make clean
    ```

## Controls

- **Rotate**: Click-and-drag  
- **Zoom**: Mouse wheel  
- **Pan**: Shift + click-and-drag  

## Notes

- Core math & parsing in C (C11), GUI & rendering loop in C++ (C++11) with Qt6  
- Affine transformations implemented from scratch (no external math libraries)  
- OBJ parser supports triangles & quads; extendable for materials/textures  
- UI layout editable via `mainwindow.ui`; shaders under `src/my3dViewer/shaders/`  
