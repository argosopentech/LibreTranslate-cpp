CC = g++

TARGET = libretranslate

all:
	$(CC) -o $(TARGET) main.cpp -pthread

clean:
	$(RM) $(TARGET)
