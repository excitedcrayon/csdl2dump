# csdl2dump
Just a dump of SDL source code

## Development Platform
- Macbook Pro (late 2014 model)
- Clang compiler
- SDL2 library

### Compiling .c file using terminal
- clang [file.c] -o [output] $(sdl2-config --cflags --libs)
- clang [file.c] -o [output] $(sdl2-config --cflags --libs) -lSDL2_image --> for SDL2_Image dependency
