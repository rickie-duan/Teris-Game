CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -Wall -MMD
EXEC = biquadris
OBJECTS = starBlock.o main.o subject.o Level1.o Board.o Level3.o textdisplay.o TBlock.o SBlock.o OBlock.o JBlock.o IBlock.o ZBlock.o Window.o Level4.o Level0.o Block.o LBlock.o GameLevel.o Grid.o Level2.o graphicdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
