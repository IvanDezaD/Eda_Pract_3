#include <gtest/gtest.h>
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

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int test_result = RUN_ALL_TESTS();

    return test_result;
}
