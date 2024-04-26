CC = gcc
CFLAGS = -I./libyara/include/
LDFLAGS = -static -L./libyara/lib
LIBS = -lyara -lm
TARGET = yara_module
SRC = yara_module.c

BUILD_DIR = build

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(BUILD_DIR)/$@ $(LIBS)

clean:
	rm -f $(TARGET)
