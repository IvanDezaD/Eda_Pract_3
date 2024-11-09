CXX = g++
CXXFLAGS1 = -Wall -Wextra -std=c++11 -I/usr/local/include -I./src 
CXXFLAGS2 = -Wall -Wextra -std=c++14 -I/usr/local/include -I./src 
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lpthread -lbenchmark

# Archivos de origen y ejecutables
SRCS = $(wildcard ./src/*.cpp)
OBJS = $(filter-out ./src/main.o, $(SRCS:.cpp=.o))

# Archivos de prueba y sus ejecutables
TEST_SRCS = ./tests/test_cola.cpp ./tests/test_informe.cpp ./tests/test_colec.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXECS = $(TEST_SRCS:.cpp=.out)

# Carpeta de destino
TARGET_DIR = target
EXEC = $(TARGET_DIR)/main

# Objetivo predeterminado: compila el programa principal sin ejecutar los tests
all: $(EXEC)

# Crear la carpeta de destino
$(TARGET_DIR):
	@mkdir -p $(TARGET_DIR)

# Compilar el programa principal
$(EXEC): ./src/main.o $(OBJS) | $(TARGET_DIR)
	@echo "Compilando el programa principal..."
	$(CXX) $(CXXFLAGS1) -o $@ $^ 

# Compilar y ejecutar las pruebas
.PHONY: tests

tests: $(TEST_EXECS)
	@echo "Ejecutando todas las pruebas..."
	@for exec in $(TEST_EXECS); do \
		./$$exec || exit 1; \
	done
	@echo "Pruebas exitosas, limpiando ejecutables de prueba..."
	rm -f $(TEST_EXECS)
	@$(MAKE) $(EXEC)

# Compilar cada prueba individual
./tests/test_cola.out: ./tests/test_cola.cpp $(OBJS)
	@echo "Compilando test_cola..."
	$(CXX) $(CXXFLAGS2) -o $@ $< $(OBJS) $(LDFLAGS)

./tests/test_informe.out: ./tests/test_informe.cpp $(OBJS)
	@echo "Compilando test_informe..."
	$(CXX) $(CXXFLAGS2) -o $@ $< $(OBJS) $(LDFLAGS)

./tests/test_colec.out: ./tests/test_colec.cpp $(OBJS)
	@echo "Compilando test_colec..."
	$(CXX) $(CXXFLAGS2) -o $@ $< $(OBJS) $(LDFLAGS)

# Compilar archivos .o a partir de .cpp en src
./src/%.o: ./src/%.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS1) -c $< -o $@

# Limpiar archivos generados
clean:
	@echo "Limpiando archivos generados..."
	rm -f $(OBJS) $(TEST_OBJS) $(EXEC) $(TEST_EXECS) ./src/main.o
	@rm -rf $(TARGET_DIR)

.PHONY: all clean

