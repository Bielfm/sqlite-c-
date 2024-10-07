#include <iostream>
#include <sqlite3.h>

// CALLBACK MOSTRAR DATOS
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

int main() {
    sqlite3* DB;
    char* errorMessage;

    // ABRIR Y CREAR BASE DE DATOS
    int exit = sqlite3_open("mi_base_datos.db", &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(DB) << std::endl;
        return -1;
    }
    else {
        std::cout << "Conexión exitosa a la base de datos" << std::endl;
    }

    // CREAR TABLA
    std::string sql = "CREATE TABLE IF NOT EXISTS EMPLEADO("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "NOMBRE TEXT NOT NULL, "
        "SALARIO INT NOT NULL);";

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error al crear la tabla: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }

    // INSERT DATOS
    sql = "INSERT INTO EMPLEADO (NOMBRE, SALARIO) VALUES ('Carlos', 3500);"
        "INSERT INTO EMPLEADO (NOMBRE, SALARIO) VALUES ('Marta', 4200);";

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error al insertar datos: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }

    // CONSULTAR DATOS 
    sql = "SELECT * FROM EMPLEADO;";
    exit = sqlite3_exec(DB, sql.c_str(), callback, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error al consultar datos: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }

    // CERRAR  BASE DATOS
    sqlite3_close(DB);

    return 0;
}
