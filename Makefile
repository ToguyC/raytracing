# see https://yuukidach.github.io/2019/08/05/makefile-learning/
# Variable setup
CC:=g++
CFLAGS:=-Wall -Wextra -g
LIBS:=-lm
VPATH:=

BIN:=build
RENDER_PATH:=image.ppm

# Get source and object
SRCS := $(shell find . -type f -name '*.cpp')
OBJS = $(addprefix $(BIN)/, $(SRCS:.cpp=.o))

# Create the target
main: $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LIBS)

run:
	./$(BIN)/main > $(RENDER_PATH) && feh --force-aliasing $(RENDER_PATH)

# Convert the source in object, but before all, run `$(BIN)` aka mkdir
$(BIN)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

# Echo the source and object values
help:
	@echo "src: $(SRCS)"
	@echo "obj: $(OBJS)"

clean:
	rm -rf $(BIN)

.PHONY: help clean main
.SILENT: run