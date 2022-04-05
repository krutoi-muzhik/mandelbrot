TARGET = mandelbrot
CC = gcc
GLLIBS = -lopengl32 -lglfw3 -lgdi32 -lglew32

all: $(TARGET)

$(TARGET): $(TARGET).c $(TARGET).h
	$(CC) $(TARGET).c $(GLLIBS) -o $(TARGET).exe

run:
	./$(TARGET).exe

clean:
	del $(TARGET).exe