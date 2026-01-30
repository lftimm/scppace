CXX = g++
CXXFLAGS = -std=c++20 -O3 -Wall -Werror -Wextra -Iheaders -isystem libs -fopenmp
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -fopenmp
SRC = main.cpp src/Planet.cpp src/PlanetGenerator.cpp src/Scenes.cpp 
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
