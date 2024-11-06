#include "../src/coleccionMon.hpp"  // Incluye tu código principal aquí
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>

// Define el tipo para el identificador (por ejemplo, `long`) y el valor (`int` en este caso).
using Identificador = long;
using Valor = int;

class ColeccionMonTest : public ::testing::Test {
protected:
    coleccionMon<Identificador, Valor> m;

    // Esta función se ejecuta antes de cada prueba
    void SetUp() override {
        crear(m);  // Inicializamos la colección antes de cada prueba
    }
};

// Prueba para verificar que la colección está vacía después de ser creada
TEST_F(ColeccionMonTest, EsVaciaDespuesDeCrear) {
    EXPECT_TRUE(esVacia(m));
    EXPECT_EQ(tamaño(m), 0);
}

// Prueba para añadir un elemento y verificar el tamaño
TEST_F(ColeccionMonTest, AnyadirElemento) {
    long int iden = 1;
    anyadir(m, iden, 100);
    EXPECT_FALSE(esVacia(m));
    EXPECT_EQ(tamaño(m), 1);
    EXPECT_TRUE(esta(m, iden));
}

// Prueba para evitar duplicados
TEST_F(ColeccionMonTest, NoDuplicarElementos) {
  long int iden = 1;
    anyadir(m, iden, 100);
    anyadir(m, iden, 200);  // Intento de duplicado
    EXPECT_EQ(tamaño(m), 1);  // El tamaño debe seguir siendo 1
    Valor val;
    obtenerVal(m, iden, val);
    EXPECT_EQ(val, 100);  // El valor original debe mantenerse
}

// Prueba para verificar la actualización de un elemento
TEST_F(ColeccionMonTest, ActualizarElemento) {
    Identificador iden = 100;
    anyadir(m, iden, 100);
    EXPECT_TRUE(actualizar(m, iden, 200));
    Valor val;
    EXPECT_TRUE(obtenerVal(m, iden, val));
    EXPECT_EQ(val, 200);
}

// Prueba para verificar obtenerNumActu
TEST_F(ColeccionMonTest, ObtenerNumeroDeActualizaciones) {
    Identificador iden = 1;
    anyadir(m, iden, 100);
    EXPECT_EQ(obtenerNumActu(m, iden), 0);  // Sin actualizaciones todavía
    actualizar(m, iden, 200);
    EXPECT_EQ(obtenerNumActu(m, iden), 1);  // Se ha actualizado una vez
    actualizar(m, iden, 300);
    EXPECT_EQ(obtenerNumActu(m, iden), 2);  // Dos actualizaciones
}

// Prueba para verificar obtenerNumCons
TEST_F(ColeccionMonTest, ObtenerNumeroDeConsultas) {
    Identificador iden = 1;
    anyadir(m, iden, 100);
    EXPECT_EQ(obtenerNumCons(m, iden), 0);  // Ninguna consulta aún
    Valor val;
    registrarConsulta(m, iden);
    EXPECT_EQ(obtenerNumCons(m, iden), 1);  // Después de una consulta
    registrarConsulta(m, iden);
    EXPECT_EQ(obtenerNumCons(m, iden), 2);  // Después de dos consultas
}

// Prueba para verificar que obtenerVal funciona correctamente
TEST_F(ColeccionMonTest, ObtenerVal) {
    Identificador iden = 1;
    Identificador iden2 = 2;
    anyadir(m, iden, 100);
    Valor val;
    EXPECT_TRUE(obtenerVal(m, iden, val));
    EXPECT_EQ(val, 100);
    EXPECT_FALSE(obtenerVal(m, iden2, val));  // El iden=2 no está en la colección
}

// Prueba para verificar que 'esta' funciona correctamente
TEST_F(ColeccionMonTest, Esta) {
    Identificador iden = 1;
    Identificador iden2 = 2;
    EXPECT_FALSE(esta(m, iden));  // Al inicio, no hay elementos
    anyadir(m, iden, 100);
    EXPECT_TRUE(esta(m, iden));   // Después de añadir el iden=1
    EXPECT_FALSE(esta(m, iden2));  // El iden=2 no está
}

static void BenchmarkAnyadir(benchmark::State& state) {
    coleccionMon<Identificador, Valor> m;
    crear(m);
    Identificador iden = 1;
    for (auto _ : state) {
        for (Identificador i = 0; i < state.range(0); ++i) {
            anyadir(m, i, (int)i * 10);  // Añadir elementos
        }
    }
}
//BENCHMARK(BenchmarkAnyadir)->Arg(1000)->Arg(5000)->Arg(10000)->Iterations(10); // Prueba con diferentes tamaños

// Benchmark para actualizar elementos en la colección
static void BenchmarkActualizar(benchmark::State& state) {
    coleccionMon<Identificador, Valor> m;
    crear(m);
    // Prepara la colección con `n` elementos
    for (Identificador i = 0; i < state.range(0); ++i) {
        anyadir(m, i, (int)i * 10);
    }

    for (auto _ : state) {
        for (Identificador i = 0; i < state.range(0); ++i) {
            actualizar(m, i, (int)i * 20);  // Actualiza cada elemento
        }
    }
}
//BENCHMARK(BenchmarkActualizar)->Arg(1000)->Arg(5000)->Arg(10000)->Iterations(10);

// Benchmark para buscar elementos en la colección
static void BenchmarkEsta(benchmark::State& state) {
    coleccionMon<Identificador, Valor> m;
    crear(m);
    // Prepara la colección con `n` elementos
    for (Identificador i = 0; i < state.range(0); ++i) {
        anyadir(m, i, (int)i * 10);
    }

    for (auto _ : state) {
        for (Identificador i = 0; i < state.range(0); ++i) {
            benchmark::DoNotOptimize(esta(m, i));  // Buscar cada elemento
        }
    }
}
BENCHMARK(BenchmarkEsta)->Arg(2)->Arg(5)->Arg(10)->Iterations(1);

// Benchmark para obtener el valor de un elemento en la colección
static void BenchmarkObtenerVal(benchmark::State& state) {
    coleccionMon<Identificador, Valor> m;
    crear(m);
    // Prepara la colección con `n` elementos
    for (Identificador i = 0; i < state.range(0); ++i) {
        anyadir(m, i, (int)i * 10);
    }

    Valor val;
    for (auto _ : state) {
        for (Identificador i = 0; i < state.range(0); ++i) {
            benchmark::DoNotOptimize(obtenerVal(m, i, val));  // Obtener valor de cada elemento
        }
    }
}
BENCHMARK(BenchmarkObtenerVal)->Arg(1)->Arg(5)->Arg(10)->Iterations(1);


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int test_result = RUN_ALL_TESTS();
  
  ::benchmark::Initialize(&argc, argv);  // Inicializa Google Benchmark
  if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
  ::benchmark::RunSpecifiedBenchmarks();
  
  return test_result;
}
