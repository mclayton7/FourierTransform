# Makefile for FFT
# Mac Clayton, 2012
%.o:	%.cc
	@echo Compiling $*	
	@rm -f $*.o
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(EXTRA_INCLUDES) -c $*.cc


.SILENT:
CXX = g++
CXXFLAGS = -g -Wall

fft::	fft.o complex.o 
	@echo Linking fft
	$(CXX) -g -o fft fft.o complex.o

complex.o:	complex.cc complex.h

clean:
	@rm -f *.o fft
