CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
VLFLAGS = --leak-check=full --log-file="logfile.out" --show-leak-kinds=all -v
OBJECTS = control.o game.o view.o main.o Tview.o Gview.o
TARGET = snake

all: ${TARGET}

${TARGET}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJECTS} ${LDFLAGS}

run:
	./${TARGET}

clean:
	${RM} ${OBJECTS} ${TARGET}

valgrind:
	valgrind ${VLFLAGS} ./${TARGET}

depend:
	${CXX} ${CXXFLAGS} ${OBJECTS:.o=.cpp} -MM >.depend

-include .depend
