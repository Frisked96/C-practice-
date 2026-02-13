CXX = clang++
# -MMD generates .d files for dependency tracking
CXXFLAGS = -std=c++17 -Wall -Wextra -I/home/frisked/vcpkg/installed/x64-linux/include -MMD -MP

SRCS = main.cpp game_map.cpp engine.cpp render.cpp actions.cpp input_handler.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
TARGET = rof

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# This rule compiles .cpp to .o and also generates the .d file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include the generated dependency files
-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
