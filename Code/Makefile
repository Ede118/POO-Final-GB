CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -MMD -MP -ICode/include -ICode/include/XML -pthread
LDFLAGS :=
LDLIBS := -pthread

SRC_DIR := Code/src
BUILD_DIR := Code/build
BIN_DIR := Code

XML_SOURCES := $(wildcard $(SRC_DIR)/XML/*.cpp)
XML_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(XML_SOURCES))

SERVER_OBJECTS := \
	$(XML_OBJECTS) \
	$(BUILD_DIR)/app/AuthService.o \
	$(BUILD_DIR)/app/RPCAuthLogin.o \
	$(BUILD_DIR)/app/server.o

CLIENT_OBJECTS := \
	$(XML_OBJECTS) \
	$(BUILD_DIR)/app/clientcmd.o

SERVER_BIN := $(BIN_DIR)/server
CLIENT_BIN := $(BIN_DIR)/client

.PHONY: all clean server client

all: $(SERVER_BIN) $(CLIENT_BIN)

server: $(SERVER_BIN)

client: $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(CLIENT_BIN): $(CLIENT_OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(SERVER_BIN) $(CLIENT_BIN)

-include $(SERVER_OBJECTS:.o=.d) $(CLIENT_OBJECTS:.o=.d)
