CXX = g++
CXXFLAGS = -std=c++20  -Wall -Werror -Wextra -Iheaders
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = main.cpp src/SimObject.cpp src/Circle.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = scppace

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LIBS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: build
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
