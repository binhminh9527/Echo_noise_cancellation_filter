CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./WavFileHandler -I./EcnrLib
LDFLAGS =

# Shared library for EcnrLib
EcnrLib_OBJS = EcnrLib/EcnrLib.o
EcnrLib_TARGET = libEcnrLib.so

# Test app
TEST_OBJS = main.o WavFileHandler/WavFileHandler.o
TEST_TARGET = test_app

all: $(TEST_TARGET) $(EcnrLib_TARGET)

$(EcnrLib_TARGET): $(EcnrLib_OBJS)
	$(CXX) -shared -o $@ $^

$(TEST_TARGET): $(TEST_OBJS) $(EcnrLib_TARGET)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L. -lEcnrLib

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

WavFileHandler/WavFileHandler.o: WavFileHandler/WavFileHandler.cpp WavFileHandler/WavFileHandler.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

EcnrLib/EcnrLib.o: EcnrLib/EcnrLib.cpp EcnrLib/EcnrLib.h
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(TEST_TARGET) $(EcnrLib_TARGET) *.o WavFileHandler/*.o EcnrLib/*.o
