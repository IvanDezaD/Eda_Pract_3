# Variables de compilación
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lpthread

# Archivos de origen y ejecutables
SRCS = main.cpp lista_enlazada.cpp
TEST_SRCS = test_LE.cpp
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
EXEC = my_program
TEST_EXEC = test_program

# Objetivo principal: solo compila el programa principal si pasan las pruebas
all: test $(EXEC)

# Compilar el programa principal
$(EXEC): $(OBJS)
	@echo "Compilando el programa principal..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar el programa de prueba
$(TEST_EXEC): $(OBJS) $(TEST_OBJS)
	@echo "Compilando el ejecutable de pruebas..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Ejecutar las pruebas y detener en caso de error
test: $(TEST_EXEC)
	@echo "Ejecutando pruebas..."
	./$(TEST_EXEC)

# Este objetivo solo se ejecuta si `test` pasa (usado por `all`)
$(EXEC): test

# Compilar archivos .o a partir de .cpp
%.o: %.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	@echo "Limpiando archivos generados..."
	rm -f $(OBJS) $(TEST_OBJS) $(EXEC) $(TEST_EXEC)

.PHONY: all test clean

