CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++17 -fPIC -Iinclude -Ilib -fopenmp  -I C:\msys64\mingw64\include -IGLAD/include

SRCDIR = lib
OUTDIR = build

SOURCES = $(wildcard $(SRCDIR)/**/*.cpp) GLAD/src/glad.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OUTDIR)/%.o)

TARGET = ItsAnotherEngine.dll
TEST_EXE = main.exe


all: $(TARGET)

#Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ -L C:\msys64\mingw64\lib -lglfw3 -lopengl32 -fopenmp

#Compiling
$(OUTDIR)/%.o: $(SRCDIR)/%.cpp
	$(shell if not exist "$(dir $@)" mkdir "$(dir $@)")
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	if exist $(OUTDIR) rd /s /q $(OUTDIR)
	if exist $(TARGET) del $(TARGET)
	if exist $(TEST_EXE) del $(TEST_EXE)


test: tests/main.cpp $(TARGET)
	g++ -Iinclude -o $(TEST_EXE) $< -L. -lItsAnotherEngine

run: test
	main.exe