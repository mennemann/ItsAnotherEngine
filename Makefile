CC = g++
CFLAGS = -g -Wall

IDIR1=./src/core src/core/*.cpp
IDIR2=./src/output src/output/*.cpp
IDIR3=./src/shapes
IDIR4=./src/types src/types/*.cpp
IDIR5=/usr/include/opencv4/

INC=-I$(IDIR1) -I$(IDIR2) -I$(IDIR3) -I$(IDIR4) -I$(IDIR5)


LIBS=opencv_core opencv_videoio opencv_highgui


MAIN=./src/main.cpp

main:
	#echo $(INC)
	$(CC) $(CFLAGS) $(INC) $(LIBS:%=-l%) $(MAIN)