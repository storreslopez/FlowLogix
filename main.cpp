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

    long codigos[numeroEmpleados];
    string nombres[numeroEmpleados];
    char oficina[numeroEmpleados];

    float datosNum[numeroEmpleados][NUMERO_DATOS];
    // datosNum[i][0] → horas trabajadas
    // datosNum[i][1] → minutos tardanza
    // datosNum[i][2] → valor hora
    // datosNum[i][3] → horas netas trabajadas
    // datosNum[i][4] → valor descontado
    // datosNum[i][5] → salario neto

    bool continua = true;
    while (continua) {
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

        system("clear || cls");

        switch (opcionMenu) {
            case 1: {
                for (size_t i = 0; i < numeroEmpleados; ++i) {
                    long codigoEmpleado;
                    bool codigoValido = false;
                    while (!codigoValido) {
                        cout << "► Ingrese el ID del empleado #" << i + 1 << ": ";
                        cin >> codigoEmpleado;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "❌ Error: Ingrese un entero valido.\n" << endl;
                            continue;
                        }

                        if (codigoEmpleado < 1) {
                            cout << "❌ Error: El código debe ser mayor o igual a 1.\n" << endl;
                            continue;
                        }

                        bool codigoExiste = false;
                        for (const long codigo: codigos) {
                            if (codigo == codigoEmpleado) {
                                codigoExiste = true;
                                break;
                            }
                        }

                        if (codigoExiste) {
                            cout << "❌ Error: Este codigo ya ha sido registrado.\n" << endl;
                            continue;
                        }

                        codigoValido = true;
                    }
                    codigos[i] = codigoEmpleado;

                    string nombre;
                    cout << "\n► Ingrese el nombre del empleado #" << i + 1 << ": ";
                    cin.ignore();
                    getline(cin, nombre);
                    nombres[i] = nombre;

                    char oficinaEmpleado;
                    bool oficinaValida = false;
                    while (!oficinaValida) {
                        cout << "\n► Ingrese la oficina en la que trabaja " << nombre
                                << " [(C)ontabilidad, (S)istemas, (L)ogística]: ";
                        cin >> oficinaEmpleado;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "❌ Error: Ingrese un caracter valido.\n" << endl;
                            continue;
                        }

                        oficinaEmpleado = toupper(oficinaEmpleado);

                        if (oficinaEmpleado == 'C' || oficinaEmpleado == 'S' || oficinaEmpleado == 'L') {
                            oficinaValida = true;
                        } else {
                            cout << "❌ Error: Opción no válida. Ingrese C, S o L.\n" << endl;
                        }
                    }
                    oficina[i] = oficinaEmpleado;

                    float horasSemanales;
                    bool horasValidas = false;
                    while (!horasValidas) {
                        cout << "\n► Ingrese el numero de horas semanales de " << nombre << ": ";
                        cin >> horasSemanales;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "❌ Error: Ingrese un float valido.\n" << endl;
                        } else if (horasSemanales > 0) {
                            horasValidas = true;
                        } else {
                            cout << "❌ Error: Ingrese un valor positivo.\n" << endl;
                        }
                    }
                    datosNum[i][0] = horasSemanales;

                    float minutosTardanza;
                    bool minutosValidos = false;
                    while (!minutosValidos) {
                        cout << "\n► Ingrese los minutos de tardanza de " << nombre << ": ";
                        cin >> minutosTardanza;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "❌ Error: Ingrese un float valido.\n" << endl;
                        } else if (minutosTardanza >= 0) {
                            minutosValidos = true;
                        } else {
                            cout << "❌ Error: Ingrese un valor positivo.\n" << endl;
                        }
                    }
                    datosNum[i][1] = minutosTardanza;

                    float valorHora;
                    bool valorHoraValido = false;
                    while (!valorHoraValido) {
                        cout << "\n► Ingrese el valor de la hora de " << nombre << ": ";
                        cin >> valorHora;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "❌ Error: Ingrese un float valido.\n" << endl;
                        } else if (valorHora > 0) {
                            valorHoraValido = true;
                        } else {
                            cout << "❌ Error: Ingrese un valor positivo.\n" << endl;
                        }
                    }
                    datosNum[i][2] = valorHora;

                    datosNum[i][3] = horasSemanales - (minutosTardanza / 60.0f);
                    datosNum[i][4] = (minutosTardanza / 60.0f) * valorHora;
                    datosNum[i][5] = datosNum[i][3] * valorHora;
                }
                break;
            }
            case 2: {
                long codigoEmpleado;
                bool codigoValido = false;
                while (!codigoValido) {
                    cout << "► Ingrese el ID del empleado a consultar: ";
                    cin >> codigoEmpleado;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "❌ Error: Ingrese un entero valido.\n" << endl;
                        continue;
                    }

                    if (codigoEmpleado < 1) {
                        cout << "❌ Error: El código debe ser mayor o igual a 1.\n" << endl;
                        continue;
                    }

                    codigoValido = true;
                }

                short empleadoIndex = -1;

                for (size_t i = 0; i < numeroEmpleados; ++i) {
                    if (codigos[i] == codigoEmpleado) {
                        empleadoIndex = i;
                        break;
                    }
                }

                if (empleadoIndex >= 0) {
                    cout << fixed << setprecision(2);

                    cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
                    cout << "║           INFORMACIÓN DETALLADA DEL EMPLEADO                   ║\n";
                    cout << "╚════════════════════════════════════════════════════════════════╝\n\n";

                    cout << left << setw(30) << "  Código del empleado:" << codigoEmpleado << "\n";
                    cout << left << setw(30) << "  Nombre completo:" << nombres[empleadoIndex] << "\n";
                    cout << left << setw(30) << "  Oficina:" << oficina[empleadoIndex] << "\n";

                    cout << "\n" << string(64, '-') << "\n";
                    cout << "  INFORMACIÓN LABORAL\n";
                    cout << string(64, '-') << "\n\n";

                    cout << left << setw(30) << "  Valor por hora:" << right << setw(10) << "$" << datosNum[empleadoIndex][2] << "\n";
                    cout << left << setw(30) << "  Horas semanales trabajadas:" << right << setw(10) << datosNum[empleadoIndex][0] << " hrs\n";
                    cout << left << setw(30) << "  Minutos de tardanza semanal:" << right << setw(10) << datosNum[empleadoIndex][1] << " min\n";

                    cout << "\n" << string(64, '-') << "\n";
                    cout << "  CÁLCULOS SALARIALES\n";
                    cout << string(64, '-') << "\n\n";

                    cout << left << setw(30) << "  Horas descontadas:" << right << setw(10) << (datosNum[empleadoIndex][1] / 60.0) << " hrs\n";
                    cout << left << setw(30) << "  Horas netas de trabajo:" << right << setw(10) << datosNum[empleadoIndex][3] << " hrs\n";
                    cout << left << setw(30) << "  Valor descuento efectuado:" << right << setw(10) << "$" << datosNum[empleadoIndex][4] << "\n";

                    cout << "\n" << string(64, '-') << "\n";
                    cout << left << setw(30) << "  SALARIO NETO A CANCELAR:" << right << setw(10) << "$" << datosNum[empleadoIndex][5] << "\n";
                    cout << string(64, '-') << "\n\n";
                } else {
                    cout << "❌ Error: No hay ningun empleado con ese ID!\n" << endl;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nPresione ENTER para continuar...";
                cin.get();
                system("clear || cls");
                break;
            }
            case 3: {
                break;
            }
            case 4:
                continua = false;
                break;
        }
    }


    return 0;
}