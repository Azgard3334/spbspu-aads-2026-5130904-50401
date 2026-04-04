TARGET = main
SRC = main.cpp

all: run clean

$(TARGET): $(SRC)
	g++ $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm $(TARGET)
