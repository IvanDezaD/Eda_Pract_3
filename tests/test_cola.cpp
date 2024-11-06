#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include "../src/colaGenerica.hpp"

//En los 3 primeros tests se prueban las funciones encolar, desencolar, longitud y primero
TEST(crear, CreaCorrectamenteVacia){
  cola<int> c;
  crear(c);
  EXPECT_TRUE(esVacia(c));
  EXPECT_EQ(longitud(c), 0);
}

TEST(encolar, encolaCorrectamente){
  cola<int> c;
  int dato1 = 0;
  int dato2 = 1;
  int datoRes1;
  int datoRes2;
  crear(c);
  encolar(c, dato1);
  EXPECT_EQ(longitud(c), 1);
  primero(c, datoRes1);
  EXPECT_EQ(datoRes1, 0);
  encolar(c, dato2);
  EXPECT_EQ(longitud(c), 2);
}

TEST(desencolar, desencolaCorrectamente){
  cola<int> c;
  int dato1 = 0;
  int dato2 = 1;
  int datoRes1;
  int datoRes2;
  crear(c);
  encolar(c, dato1);
  encolar(c, dato2);
  EXPECT_EQ(longitud(c), 2);
  desenencolar(c);
  EXPECT_EQ(longitud(c), 1);
  primero(c, datoRes1);
  EXPECT_EQ(datoRes1, 1);
  desenencolar(c);
  EXPECT_TRUE(esVacia(c));
}

//Tests de las funciones del iterador
TEST(iterador, funcionaCorrectamente){
  cola<int> c;
  int dato1 = 0;
  int dato2 = 1;
  int dato3 = 2;
  int datoRes1;
  int datoRes2;
  int datoRes3;
  crear(c);
  encolar(c, dato1);
  encolar(c, dato2);
  encolar(c, dato3);
  iniciarIterador(c);
  siguiente(c, datoRes1);
  EXPECT_EQ(datoRes1, 1);
  avanza(c);
  siguiente(c, datoRes2);
  EXPECT_EQ(datoRes2, 2);
  avanza(c);
  EXPECT_FALSE(existeSiguiente(c));
  iniciarIterador(c);
  primero(c, datoRes3);
  EXPECT_EQ(datoRes3, 0);
}

TEST(liberar, liberaCorrectamente){
  cola<int> c;
  int dato1 = 0;
  int dato2 = 0;
  crear(c);
  encolar(c, dato1);
  encolar(c, dato2);
  liberar(c);
  EXPECT_TRUE(esVacia(c));
  EXPECT_EQ(longitud(c), 0);
}

//Funcion de benchmark para probar el rendimiento de la implementacion.
static void BM_ColaEncolarDesenencolar(benchmark::State& state) {
    cola<int> c;
    crear(c);

    int num_elements = state.range(0); // Número de elementos que añadiremos y eliminaremos en la cola

    // Benchmark para encolar y desencolar elementos
    for (auto _ : state) {
        // Encolar elementos
        for (int i = 0; i < num_elements; ++i) {
            encolar(c, i);
        }

        // Desencolar elementos
        while (!esVacia(c)) {
            desenencolar(c);
        }
    }

    // Reporte del contador de elementos procesados
    state.SetItemsProcessed(state.iterations() * num_elements * 2); // x2 por encolar y desencolar
}

static void BM_ColaEncolarLiberar(benchmark::State& state) {
    cola<int> c;
    crear(c);

    int num_elements = state.range(0); // Número de elementos que añadiremos y eliminaremos en la cola

    // Benchmark para encolar y desencolar elementos
    for (auto _ : state) {
        // Encolar elementos
        for (int i = 0; i < num_elements; ++i) {
            encolar(c, i);
        }

        // liberar la memoria
        liberar(c);
    }

    // Reporte del contador de elementos procesados
    state.SetItemsProcessed(state.iterations() * num_elements * 2); // x2 por encolar y desencolar
}


// Registramos el benchmark para probar con diferentes tamaños de cola
BENCHMARK(BM_ColaEncolarDesenencolar)->Arg(1000)->Arg(5000)->Arg(10000)->Arg(100000);
BENCHMARK(BM_ColaEncolarLiberar)->Arg(1000)->Arg(5000)->Arg(10000)->Arg(100000);


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int test_result = RUN_ALL_TESTS();

  printf("\n\n\n\n\n\n");
  printf("\033[1;34mEjecutando Benchmarks de las Funciones Principales\033[0m\n");

  ::benchmark::Initialize(&argc, argv);
  if(::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
  ::benchmark::RunSpecifiedBenchmarks();


    return test_result;
}
