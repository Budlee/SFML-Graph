CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lpthread
SOURCES=main.cpp GraphLines.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=graph

all: build run

build: $(SOURCES) $(EXECUTABLE)

    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	./$(EXECUTABLE)

clean: 
	rm -f *.o
	rm -f $(EXECUTABLE)
