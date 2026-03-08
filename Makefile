
CC_CLANG := clang
CC_SDL2_FLAGS := $(shell sdl2-config --cflags --libs)
CC_SDL2_FLAGS_IMAGE := $(shell sdl2-config --cflags --libs) -lSDL2_image
BUILD_DIR := build
BASICS_DIR := 01-basics
RENDER_DIR := 02-rendering-images
EVENTS_DIR := 03-events
KEYPRESS_DIR := 04-keypress
TEXTURE_DIR = 07-textures

basics: $(BASICS_DIR)/01-hello.c
	$(CC_CLANG) $< -o $(BUILD_DIR)/01-hello $(CC_SDL2_FLAGS)

renderimages: $(RENDER_DIR)/02-images.c
	$(CC_CLANG) $< -o $(BUILD_DIR)/02-images $(CC_SDL2_FLAGS_IMAGE)

events: $(EVENTS_DIR)/03-events.c
	$(CC_CLANG) $< -o $(BUILD_DIR)/03-events $(CC_SDL2_FLAGS)

keypress: $(KEYPRESS_DIR)/04-keypress.c
	$(CC_CLANG) $< -o $(BUILD_DIR)/04-keypress $(CC_SDL2_FLAGS_IMAGE)

texture: $(TEXTURE_DIR)/07-texture.c
	$(CC_CLANG) $< -o $(BUILD_DIR)/07-texture $(CC_SDL2_FLAGS_IMAGE)

clean:
	rm -f build/*