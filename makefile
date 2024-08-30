CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g $(shell pkg-config --cflags thrift)
LDFLAGS = -lbenchmark -lflatbuffers -lprotobuf -pthread $(shell pkg-config --libs thrift)

# Source files
SRCS = main.cc data_generator.cc ./serial_func/serializers.cc ./serial_func/data_generator_string.cc  

# Object files
OBJS = $(SRCS:.cc=.o)

# Target executable
TARGET = benchmark_test

all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) gen-cpp/struct_types.cpp ./schema/ProtoData.pb.cc -o $(TARGET) $(LDFLAGS) 

# Compile source files to object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
