# SRasterizer
Here is our CPU Software Rasterizer project made during our first Computer Graphics year.

## Installation
```shell
git clone git@github.com:SakurayYuzuru/Rasterizer.git
git submodule update --init --recursive --depth=1
```

## Compilation
If you plan to build our project, you should have :
- [SDL2](#Installation)
- CMake
- Make or other IDE  
And then you could build it with these code in your terminal.
```shell
mkdir build && cd build
cmake ..
make -j${nproc}
./SRasterizer
```

## Features
Basic components of a rasterizer were implemented along with the following extensions:
- Bresen Ham's algorithm
- Z-buffer
- Color Blending
- MVP Transformation

## Screen Shots
### Bresen Ham's algorithm
![Bresen Ham's algorithm](/ScreenShot/Bresen-ham.png)

### Color Blending
![Color Blending](/ScreenShot/Color%20Blending.png)