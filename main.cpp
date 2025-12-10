#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else
#error "Este programa requiere Windows para funcionar."
#endif


using namespace std;

int main() {
    constexpr short NUMERO_DATOS = 6;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("clear || cls");

    short numeroEmpleados;
    bool numeroValido = false;

    while (!numeroValido) {
        cout << "► Ingrese el numero de empleados: ";
        cin >> numeroEmpleados;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Error: Ingrese un entero valido." << "\n" << endl;
        } else if (numeroEmpleados > 0) {
            numeroValido = true;
        } else {
            cout << "❌ Error: El numero de empleados debe ser mayor a 0." << "\n" << endl;
        }
    }
    system("clear || cls");

    long codigo[numeroEmpleados];
    string nombre[numeroEmpleados];
    char oficina[numeroEmpleados];

    float datosNum[numeroEmpleados][NUMERO_DATOS];
    // datosNum[i][0] → horas trabajadas
    // datosNum[i][1] → minutos tardanza
    // datosNum[i][2] → valor hora
    // datosNum[i][3] → horas netas trabajadas
    // datosNum[i][4] → valor descontado
    // datosNum[i][5] → salario neto

    while (true) {
        cout << endl;
        cout << setw(50) << right << "EMPRESA FLOWLOGIX" << endl;
        cout << setw(55) << right << "Puntualidad que impulsa tu empresa." << endl;
        cout << setw(50) << right << "REGISTRO DE TARDANZA" << endl;
        cout << endl;

        cout << "1. " << "Registra informacion de empleados" << endl;
        cout << "2. " << "Consultar empleado" << endl;
        cout << "3. " << "Reportes" << endl;
        cout << setw(4) << "" << "3.1 Reporte de empleados con registro de tardanza" << endl;
        cout << setw(4) << "" << "3.2 Reporte de empleados puntuales" << endl;
        cout << setw(4) << "" << "3.3 Reporte descuento tiempo tardanza" << endl;
        cout << "4. " << "Salir" << endl;
        cout << endl;

        short opcionMenu;
        bool opcionMenuValida = false;

        while (!opcionMenuValida) {
            cout << "► Ingrese una opcion (1-4): ";
            cin >> opcionMenu;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "❌ Error: Ingrese un entero valido.\n" << endl;
            } else if (opcionMenu >= 1 && opcionMenu <= 4) {
                opcionMenuValida = true;
            } else {
                cout << "❌ Error: Ingrese una opcion valida [1-4]\n" << endl;
            }
        }

    }

    
    return 0;
}