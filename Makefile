
CXX = g++
INCLUDE_DIRS = -I./EcnrLib -I./WavFileHandler -I./AudioChannel
CXXFLAGS = -std=c++17 -Wall $(INCLUDE_DIRS)
LDFLAGS =

OUT_DIR = out

# Shared library for EcnrLib
EcnrLib_OBJS = $(OUT_DIR)/EcnrLib.o
EcnrLib_TARGET = $(OUT_DIR)/libEcnrLib.so

# Test app
TEST_OBJS = $(OUT_DIR)/main.o $(OUT_DIR)/WavFileHandler.o
TEST_TARGET = $(OUT_DIR)/test_app

all: $(OUT_DIR) $(TEST_TARGET) $(EcnrLib_TARGET)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(EcnrLib_TARGET): $(EcnrLib_OBJS)
	$(CXX) -shared -o $@ $^

$(TEST_TARGET): $(TEST_OBJS) $(EcnrLib_TARGET)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(OUT_DIR) -lEcnrLib

$(OUT_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/WavFileHandler.o: WavFileHandler/WavFileHandler.cpp WavFileHandler/WavFileHandler.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/EcnrLib.o: EcnrLib/EcnrLib.cpp EcnrLib/EcnrLib.h
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

clean:
	rm -rf $(OUT_DIR)/*
