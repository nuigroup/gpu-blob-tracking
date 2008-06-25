CC=g++
INC=-I/usr/include/opencv
LIBS=-lcv -lhighgui -lglut -lGLEW

TINYXML = tinyxml.o tinystr.o tinyxmlparser.o tinyxmlerror.o
OBJECTS1=gpuTracker.o Camera.o ShaderProgram.o ImageFilter.o FilterChain.o FilterController.o
EXE1=gpuTracker


 

all: $(EXE1) 


$(EXE1): $(OBJECTS1) $(TINYXML)
	$(CC) $(LIBS) $(CFLAGS) $(OBJECTS1) $(TINYXML) -o $@


#.cpp.o:
%.o: src/%.cpp
	$(CC) $(INC) -c -Wall -o $@ $< 

#.c.o:
%.o: src/%.c

	$(CC) $(INC) -c -Wall -o $@ $< 

clean:
	rm -rf *o $(EXE1)




