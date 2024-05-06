CC = gcc
CFLAGS = -I./libyara/include/ -I./include/
LDFLAGS = -static -L./libyara/lib
LIBS = -lyara -lm
TARGET = doYARkA
SRC = doyarka.c android.c connection.c yara_analyzer.c cJSON.c
OBJS=$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

OBJ_DIR = obj
BUILD_DIR = build

all: $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/rules

$(BUILD_DIR)/$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/rules: rules | $(BUILD_DIR)
	cp -r $^ $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f $(BUILD_DIR)/$(TARGET)
	rm -rf $(BUILD_DIR)/rules
	rm -rf $(OBJ_DIR)
