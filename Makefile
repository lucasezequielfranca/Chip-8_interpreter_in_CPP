CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra 

TARGET = chip8

all:
	$(CXX) $(CXXFLAGS) *.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
