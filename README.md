# csdl2dump
Just a dump of SDL source code

## Development Platform
- Macbook Pro (late 2014 model)
- Clang compiler
- SDL2 library

### Compiling .c file using terminal
- clang [file.c] -o [output] $(sdl2-config --cflags --libs)
- clang [file.c] -o [output] $(sdl2-config --cflags --libs) -lSDL2_image --> for SDL2_Image dependency

### Notes
- Using Makefile to compile binaries
- Also create a build/ folder inside the csdl2dump main folder to store generated binaries (modular and clean code)

### Folder Structure
```
├── 01-basics
│   └── 01-hello.c
├── 02-rendering-images
│   ├── 02-images.c
│   ├── image.bmp
│   └── screenshot.png
├── 03-events
│   ├── 03-events
│   └── 03-events.c
├── 04-keypress
│   ├── 04-keypress.c
│   └── images
│       ├── down.bmp
│       ├── left.bmp
│       ├── press.bmp
│       ├── right.bmp
│       └── up.bmp
├── 60FPSCap.c
├── Makefile
├── README.md
└── build
```