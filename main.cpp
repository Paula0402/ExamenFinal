#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Función para eliminar tildes de una cadena
string eliminarTildes(const string& str) {
    string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] == 'á' || result[i] == 'Á') result[i] = 'a';
        if (result[i] == 'é' || result[i] == 'É') result[i] = 'e';
        if (result[i] == 'í' || result[i] == 'Í') result[i] = 'i';
        if (result[i] == 'ó' || result[i] == 'Ó') result[i] = 'o';
        if (result[i] == 'ú' || result[i] == 'Ú') result[i] = 'u';
        if (result[i] == 'ü' || result[i] == 'Ü') result[i] = 'u';
    }
    return result;
}

// Estructura para un empleado
struct Empleado {
    string carnet;
    string nombre;
    string fechaNacimiento;
    string categoria;
    double salario;
    string direccion;
    string telefono;
    string correo;
    int edad;

    // Constructor
    Empleado(const string& carnet, const string& nombre, const string& fechaNacimiento, const string& categoria,
             double salario, const string& direccion, const string& telefono, const string& correo, int edad) {
        this->carnet = carnet;
        this->nombre = nombre;
        this->fechaNacimiento = fechaNacimiento;
        this->categoria = categoria;
        this->direccion = direccion;
        this->telefono = telefono;
        this->correo = correo;
        this->edad = edad;

        // Validaciones
        if (edad < 18) {
            cout << "Error: El empleado debe ser mayor de edad. No se registró al empleado.\n";
            return;
        }
        if (salario < 250000 || salario > 500000) {
            this->salario = 250000; // Asignar salario por defecto
        } else {
            this->salario = salario;
        }
        if (categoria != "administrador" && categoria != "operario" && categoria != "peon") {
            cout << "Error: Categoría inválida. No se registró al empleado.\n";
            return;
        }
    }

    // Método para mostrar información completa
    void mostrarInformacion() const {
        cout << "Carnet: " << carnet << "\n"
             << "Nombre: " << nombre << "\n"
             << "Fecha de nacimiento: " << fechaNacimiento << "\n"
             << "Categoría: " << categoria << "\n"
             << "Salario: " << salario << "\n"
             << "Dirección: " << direccion << "\n"
             << "Teléfono: " << telefono << "\n"
             << "Correo: " << correo << "\n"
             << "Edad: " << edad << "\n";
    }
};

// Estructura para un proyecto
struct Proyecto {
    string codigo;
    string nombre;
    string fechaInicio;
    string fechaFin;

    // Constructor
    Proyecto(const string& codigo, const string& nombre, const string& fechaInicio, const string& fechaFin) {
        this->codigo = codigo;
        this->nombre = nombre;
        this->fechaInicio = fechaInicio;
        this->fechaFin = fechaFin;
    }

    // Método para mostrar información completa
    void mostrarInformacion() const {
        cout << "Código: " << codigo << "\n"
             << "Nombre: " << nombre << "\n"
             << "Fecha de inicio: " << fechaInicio << "\n"
             << "Fecha de fin: " << fechaFin << "\n";
    }
};

// Sistema de gestión
class SistemaGestion {
private:
    vector<Empleado> empleados;
    vector<Proyecto> proyectos;

public:
    // Gestión de empleados
    void registrarEmpleado() {
        string carnet, nombre, fechaNacimiento, categoria, direccion, correo, telefono;
        double salario;
        int edad;

        // Validación de carnet único
        cout << "Ingrese el carnet: ";
        while (cin >> carnet && carnet.empty()) {
            cout << "Error: El carnet no puede estar vacío. Intente nuevamente: ";
        }

        // Comprobar si ya existe un empleado con el mismo carnet
        for (int i = 0; i < empleados.size(); ++i) {
            if (empleados[i].carnet == carnet) {
                cout << "Error: Ya existe un empleado con este carnet. No se puede registrar.\n";
                return;
            }
        }

        cout << "Ingrese el nombre: ";
        cin.ignore();  // Para evitar problemas con getline después de cin
        while (getline(cin, nombre) && nombre.empty()) {
            cout << "Error: El nombre no puede estar vacío. Intente nuevamente: ";
        }

        cout << "Ingrese la fecha de nacimiento (YYYY-MM-DD): ";
        while (cin >> fechaNacimiento && fechaNacimiento.empty()) {
            cout << "Error: La fecha de nacimiento no puede estar vacía. Intente nuevamente: ";
        }

        cout << "Ingrese la categoría (Administrador, Operario, Peon): ";
        cin >> categoria;
        transform(categoria.begin(), categoria.end(), categoria.begin(), ::tolower);
        categoria = eliminarTildes(categoria);  // Eliminar tildes

        while (categoria != "administrador" && categoria != "operario" && categoria != "peon") {
            cout << "Error: Categoría inválida. Debe ser Administrador, Operario o Peon. Intente de nuevo: ";
            cin >> categoria;
            transform(categoria.begin(), categoria.end(), categoria.begin(), ::tolower);
            categoria = eliminarTildes(categoria);  // Eliminar tildes
        }

        cout << "Ingrese el salario: ";
        while (!(cin >> salario) || salario < 250000 || salario > 500000) {
            cout << "Error: El salario debe estar entre 250,000 y 500,000. Intente nuevamente: ";
            cin.clear();  // Limpiar el estado de error
            cin.ignore(10000, '\n');  // Ignorar caracteres no válidos
        }

        cout << "Ingrese la dirección (opcional): ";
        cin.ignore();  // Para evitar problemas con getline después de cin
        getline(cin, direccion);

        // Si la dirección está vacía, asignar "San José"
        if (direccion.empty()) {
            direccion = "San José";
        }

        // **Correo obligatorio**
        cout << "Ingrese el correo (obligatorio): ";
        while (true) {
            getline(cin, correo);  // Usar getline para permitir espacios en el correo
            if (correo.empty()) {
                cout << "Error: El correo no puede estar vacío. Intente nuevamente: ";
            } else {
                break;
            }
        }

        // **Edad**: solo pedimos la edad una vez
        cout << "Ingrese la edad del empleado: ";
        cin >> edad;

        // Crear un nuevo objeto Empleado
        Empleado nuevoEmpleado(carnet, nombre, fechaNacimiento, categoria, salario, direccion, telefono, correo, edad);
        if (nuevoEmpleado.carnet != "") { // Solo agregar si los datos son válidos
            empleados.push_back(nuevoEmpleado);
            cout << "Empleado registrado exitosamente.\n";
        }
    }

    void consultarEmpleados() {
        string nombreBusqueda;
        cout << "Ingrese el nombre del empleado a consultar: ";
        cin.ignore(); // Para evitar problemas con getline después de cin
        getline(cin, nombreBusqueda);

        // Convertir nombre ingresado a minúsculas
        transform(nombreBusqueda.begin(), nombreBusqueda.end(), nombreBusqueda.begin(), ::tolower);
        nombreBusqueda = eliminarTildes(nombreBusqueda);  // Eliminar tildes

        bool encontrado = false;
        for (int i = 0; i < empleados.size(); ++i) {
            string nombreEmpleado = empleados[i].nombre;
            // Convertir el nombre del empleado a minúsculas para la comparación
            transform(nombreEmpleado.begin(), nombreEmpleado.end(), nombreEmpleado.begin(), ::tolower);
            nombreEmpleado = eliminarTildes(nombreEmpleado);  // Eliminar tildes

            if (nombreEmpleado == nombreBusqueda) {
                empleados[i].mostrarInformacion();
                cout << "------------------------\n";
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "Empleado no encontrado.\n";
        }
    }

    void modificarEmpleado() {
        string carnet;
        cout << "Ingrese el carnet del empleado a modificar: ";
        cin >> carnet;

        for (int i = 0; i < empleados.size(); ++i) {
            if (empleados[i].carnet == carnet) {
                cout << "Empleado encontrado: \n";
                empleados[i].mostrarInformacion();
                cout << "Ingrese nuevo nombre (dejar en blanco para no modificar): ";
                cin.ignore();
                string nuevoNombre;
                getline(cin, nuevoNombre);
                if (!nuevoNombre.empty()) {
                    empleados[i].nombre = nuevoNombre;
                }

                cout << "Ingrese nueva dirección (dejar en blanco para no modificar): ";
                string nuevaDireccion;
                getline(cin, nuevaDireccion);
                if (!nuevaDireccion.empty()) {
                    empleados[i].direccion = nuevaDireccion;
                }

                cout << "Empleado modificado exitosamente.\n";
                return;
            }
        }

        cout << "Empleado no encontrado.\n";
    }

    // Gestión de proyectos
    void agregarProyecto() {
        string codigo, nombre, fechaInicio, fechaFin;
        cout << "Ingrese el código del proyecto: ";
        cin >> codigo;

        cout << "Ingrese el nombre del proyecto: ";
        cin.ignore(); // Para evitar problemas con getline después de cin
        getline(cin, nombre);

        cout << "Ingrese la fecha de inicio del proyecto (YYYY-MM-DD): ";
        cin >> fechaInicio;

        cout << "Ingrese la fecha de fin del proyecto (YYYY-MM-DD): ";
        cin >> fechaFin;

        Proyecto nuevoProyecto(codigo, nombre, fechaInicio, fechaFin);
        proyectos.push_back(nuevoProyecto);
        cout << "Proyecto agregado exitosamente.\n";
    }

    void consultarProyectos() {
        string codigoBusqueda;
        cout << "Ingrese el código del proyecto a consultar: ";
        cin >> codigoBusqueda;

        bool encontrado = false;
        for (int i = 0; i < proyectos.size(); ++i) {
            if (proyectos[i].codigo == codigoBusqueda) {
                proyectos[i].mostrarInformacion();
                cout << "------------------------\n";
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "Proyecto no encontrado.\n";
        }
    }

    void modificarProyecto() {
        string codigo;
        cout << "Ingrese el código del proyecto a modificar: ";
        cin >> codigo;

        for (int i = 0; i < proyectos.size(); ++i) {
            if (proyectos[i].codigo == codigo) {
                cout << "Proyecto encontrado: \n";
                proyectos[i].mostrarInformacion();

                cout << "Ingrese nuevo nombre (dejar en blanco para no modificar): ";
                cin.ignore();
                string nuevoNombre;
                getline(cin, nuevoNombre);
                if (!nuevoNombre.empty()) {
                    proyectos[i].nombre = nuevoNombre;
                }

                cout << "Ingrese nueva fecha de fin (dejar en blanco para no modificar): ";
                string nuevaFechaFin;
                getline(cin, nuevaFechaFin);
                if (!nuevaFechaFin.empty()) {
                    proyectos[i].fechaFin = nuevaFechaFin;
                }

                cout << "Proyecto modificado exitosamente.\n";
                return;
            }
        }

        cout << "Proyecto no encontrado.\n";
    }
};

// Menú principal
int main() {
    SistemaGestion sistema;
    int opcion;

    do {
        cout << "\n--- Menú Principal ---\n";
        cout << "1. Gestión de Empleados\n";
        cout << "2. Gestión de Proyectos\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int opcionEmpleado;
                do {
                    cout << "\n--- Menú de Gestión de Empleados ---\n";
                    cout << "1. Registrar Empleado\n";
                    cout << "2. Consultar Empleado\n";
                    cout << "3. Modificar Empleado\n";
                    cout << "4. Volver\n";
                    cout << "Seleccione una opción: ";
                    cin >> opcionEmpleado;

                    switch (opcionEmpleado) {
                        case 1:
                            sistema.registrarEmpleado();
                            break;
                        case 2:
                            sistema.consultarEmpleados();
                            break;
                        case 3:
                            sistema.modificarEmpleado();
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Opción inválida. Intente nuevamente.\n";
                    }
                } while (opcionEmpleado != 4);
                break;
            }
            case 2: {
                int opcionProyecto;
                do {
                    cout << "\n--- Menú de Gestión de Proyectos ---\n";
                    cout << "1. Agregar Proyecto\n";
                    cout << "2. Consultar Proyecto\n";
                    cout << "3. Modificar Proyecto\n";
                    cout << "4. Volver\n";
                    cout << "Seleccione una opción: ";
                    cin >> opcionProyecto;

                    switch (opcionProyecto) {
                        case 1:
                            sistema.agregarProyecto();
                            break;
                        case 2:
                            sistema.consultarProyectos();
                            break;
                        case 3:
                            sistema.modificarProyecto();
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Opción inválida. Intente nuevamente.\n";
                    }
                } while (opcionProyecto != 4);
                break;
            }
            case 3:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 3);

    return 0;
}

