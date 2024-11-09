#include "../src/informe.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace std;

class InformeTest : public ::testing::Test {
protected:
    informe i;

    // Configuración antes de cada prueba
    void SetUp() override {
        crearInforme("Informe inicial", i);  // Crea un informe con una descripción inicial
    }
};

// Prueba para verificar la creación y descripción del informe
TEST_F(InformeTest, CrearInforme) {
    EXPECT_EQ(descripcion(i), "Informe inicial");  // Verifica que la descripción inicial es correcta
}

// Prueba para verificar el cambio de descripción
TEST_F(InformeTest, CambiarDescripcion) {
    cambiarDescripcion("Nuevo informe", i);
    EXPECT_EQ(descripcion(i), "Nuevo informe");  // Verifica que la descripción ha sido cambiada
}

// Prueba para verificar el registro de comentarios
TEST_F(InformeTest, RegistrarComentario) {
    registrarComentario("Comentario 1", i);
    registrarComentario("Comentario 2", i);

    EXPECT_EQ(comentariosRegistrados(i), 2);  // Verifica que hay dos comentarios registrados
}

// Prueba para verificar la concatenación de los comentarios registrados
TEST_F(InformeTest, ConcatenarComentarios) {
    registrarComentario("Comentario 1", i);
    registrarComentario("Comentario 2", i);
    registrarComentario("Comentario 3", i);

    string expected = "[ 1 --> Comentario 1 ---];;[ 2 --> Comentario 2 ---];;[ 3 --> Comentario 3 ---];;";
    EXPECT_EQ(comentarios(i), expected);  // Verifica que los comentarios se concatenan correctamente
}

// Prueba para verificar el comportamiento cuando no hay comentarios
TEST_F(InformeTest, SinComentarios) {
    EXPECT_EQ(comentarios(i), "");  // Verifica que la salida es vacía cuando no hay comentarios
    EXPECT_EQ(comentariosRegistrados(i), 0);  // Verifica que no se registran comentarios
}


int main(int argc, char **argv) {
    printf("Corriendo tests del informe\n");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
