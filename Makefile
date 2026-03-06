
CC_CLANG := clang
CC_SDL2_FLAGS := $(shell sdl2-config --cflags --libs)
CC_SDL2_FLAGS_IMAGE := $(shell sdl2-config --cflags --libs) -lSDL2_image
BASICS_DIR := 01-basics
RENDER_DIR := 02-rendering-images
EVENTS_DIR := 03-events

hello: $(BASICS_DIR)/01-hello.c
	$(CC_CLANG) $< -o $(BASICS_DIR)/01-hello $(CC_SDL2_FLAGS)

renderimages: $(RENDER_DIR)/02-images.c
	$(CC_CLANG) $< -o $(RENDER_DIR)/02-images $(CC_SDL2_FLAGS_IMAGE)

events: $(EVENTS_DIR)/03-events.c
	$(CC_CLANG) $< -o $(EVENTS_DIR)/03-events $(CC_SDL2_FLAGS)

clean:
	rm -f $(BASICS_DIR)/01-hello $(RENDER_DIR)/03-events $(RENDER_DIR)/03-events