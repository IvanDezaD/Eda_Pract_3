# Variables de compilación
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I/usr/local/include -I./src 
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lpthread -lbenchmark

# Archivos de origen y ejecutables
SRCS = $(wildcard ./src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Archivos de prueba y sus ejecutables
TEST_SRCS = ./tests/test_cola.cpp ./tests/test_informe.cpp ./tests/test_colec.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXECS = $(TEST_SRCS:.cpp=.out)

# Ejecutable principal
EXEC = main

# Objetivo principal: compila el programa principal solo si pasan las pruebas
all: test $(EXEC)

# Compilar el programa principal
$(EXEC): $(OBJS)
	@echo "Compilando el programa principal..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar y ejecutar las pruebas
test: $(TEST_EXECS)
	@echo "Ejecutando todas las pruebas..."
	@for exec in $(TEST_EXECS); do ./$$exec || exit 1; done

# Compilar cada prueba individual
./tests/test_cola.out: ./tests/test_cola.cpp $(OBJS)
	@echo "Compilando test_cola..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

./tests/test_informe.out: ./tests/test_informe.cpp $(OBJS)
	@echo "Compilando test_informe..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

./tests/test_colec.out: ./tests/test_colec.cpp $(OBJS)
	@echo "Compilando test_colec..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar archivos .o a partir de .cpp en src
./src/%.o: ./src/%.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	@echo "Limpiando archivos generados..."
	rm -f $(OBJS) $(TEST_OBJS) $(EXEC) $(TEST_EXECS)

.PHONY: all test clean

