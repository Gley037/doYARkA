CC = gcc
CFLAGS = -I./libyara/include/ -I./include/
LDFLAGS = -static -L./libyara/lib
LIBS = -lyara -lm
TARGET = doYARkA
SRC = doyarka.c android.c connection.c yara_analyzer.c cJSON.c
OBJS=$(addprefix $(BUILD_DIR)/, $(SRC:%.c=%.o))

BUILD_DIR = build

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(BUILD_DIR)/$(TARGET)
