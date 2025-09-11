
CXX = g++
INCLUDE_DIRS = -I./EcnrLib -I./WavFileHandler -I./AudioChannel -I./FIRFilter -I./Logging -I./
CXXFLAGS = -std=c++17 -Wall -DLOG_ENABLE $(INCLUDE_DIRS) -g
LDFLAGS =

OUT_DIR = out

# Shared library for EcnrLib
EcnrLib_OBJS = $(OUT_DIR)/EcnrLib.o $(OUT_DIR)/FIRFilter.o

EcnrLib_TARGET = $(OUT_DIR)/libEcnrLib.so

# Test app
TEST_OBJS = $(OUT_DIR)/main.o $(OUT_DIR)/WavFileHandler.o $(OUT_DIR)/AudioChannel.o $(OUT_DIR)/EcnrLib.o $(OUT_DIR)/FIRFilter.o

TEST_TARGET = $(OUT_DIR)/test_app

all: $(OUT_DIR) $(TEST_TARGET) $(EcnrLib_TARGET)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/FIRFilter.o: FIRFilter/FIRFilter.cpp FIRFilter/FIRFilter.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EcnrLib_TARGET): $(EcnrLib_OBJS)
	$(CXX) -shared -o $@ $^

$(TEST_TARGET): $(TEST_OBJS) $(EcnrLib_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS) -L$(OUT_DIR)

$(OUT_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/AudioChannel.o: AudioChannel/AudioChannel.cpp AudioChannel/AudioChannel.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/WavFileHandler.o: WavFileHandler/WavFileHandler.cpp WavFileHandler/WavFileHandler.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/EcnrLib.o: EcnrLib/EcnrLib.cpp EcnrLib/EcnrLib.h
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

clean:
	rm -rf $(OUT_DIR)/*
