CC = clang
CFLAGS = -Wall -Wextra -std=c11 -O2
INCLUDES = -I./raylib-5.5_macos/include
LDFLAGS = -L./raylib-5.5_macos/lib
LDLIBS = -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

DYLD_FLAGS = -Wl,-rpath,@executable_path/raylib-5.5_macos/lib

TARGET = game_of_life

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

# linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LDLIBS) $(DYLD_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# generate compile_commands.json for clangd
compile_commands:
	bear -- make

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run compile_commands

cleanrun: clean all run

.PHONY: all clean run compile_commands cleanrun
