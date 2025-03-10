# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -g

# Source Files
SRCS = main.cpp file1.cpp file2.cpp

# Object Files
OBJS = $(SRCS:.cpp=.o)

# Executable Name
TARGET = myprogram

# Build Executable
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Build Files
clean:
	rm -f $(OBJS) $(TARGET)
