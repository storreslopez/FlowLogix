#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>

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
    vector<short> empleadosConTardanza;
    vector<short> empleadosPuntuales;

    // Declaramos para evitar nullptr
    double sumaHorasPorOficina[3] = {0.0, 0.0, 0.0};
    int puntualesPorOficina[3] = {0, 0, 0};

    float datosEmpleados[numeroEmpleados][NUMERO_DATOS];
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
                    datosEmpleados[i][0] = horasSemanales;


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
                    datosEmpleados[i][1] = minutosTardanza;

                    if (minutosTardanza == 0) empleadosPuntuales.push_back(i);
                    if (minutosTardanza > 0) empleadosConTardanza.push_back(i);

                    const float horasNetasTrabajadas = horasSemanales - (minutosTardanza / 60.0f);

                    if (minutosTardanza == 0) {
                        int oficinaIndex;
                        switch (oficinaEmpleado) {
                            case 'C':
                                oficinaIndex = 0;
                                break;
                            case 'S':
                                oficinaIndex = 1;
                                break;
                            case 'L':
                                oficinaIndex = 2;
                                break;
                        }

                        sumaHorasPorOficina[oficinaIndex] += horasNetasTrabajadas;
                        puntualesPorOficina[oficinaIndex]++;
                    }

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
                    datosEmpleados[i][2] = valorHora;

                    datosEmpleados[i][3] = horasNetasTrabajadas;
                    datosEmpleados[i][4] = (minutosTardanza / 60.0f) * valorHora;
                    datosEmpleados[i][5] = datosEmpleados[i][3] * valorHora;
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
                    string oficinaEmpleado;

                    switch (oficina[empleadoIndex]) {
                        case 'C':
                            oficinaEmpleado = "Contabilidad";
                            break;
                        case 'S':
                            oficinaEmpleado = "Sistemas";
                            break;
                        case 'L':
                            oficinaEmpleado = "Logistica";
                            break;
                    }

                    cout << fixed << setprecision(2);

                    cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
                    cout << "║           INFORMACIÓN DETALLADA DEL EMPLEADO                   ║\n";
                    cout << "╚════════════════════════════════════════════════════════════════╝\n\n";

                    cout << left << setw(30) << "  Código del empleado:" << codigoEmpleado << "\n";
                    cout << left << setw(30) << "  Nombre completo:" << nombres[empleadoIndex] << "\n";
                    cout << left << setw(30) << "  Oficina:" << oficinaEmpleado << "\n";

                    cout << "\n" << string(64, '-') << "\n";
                    cout << "  INFORMACIÓN LABORAL\n";
                    cout << string(64, '-') << "\n\n";

                    cout << left << setw(30) << "  Valor por hora:" << right << setw(10) << "$" << datosEmpleados[
                        empleadoIndex][2] << "\n";
                    cout << left << setw(30) << "  Horas semanales trabajadas:" << right << setw(10) << datosEmpleados[
                        empleadoIndex][0] << " hrs\n";
                    cout << left << setw(30) << "  Minutos de tardanza semanal:" << right << setw(10) << datosEmpleados[
                        empleadoIndex][1] << " min\n";

                    cout << "\n" << string(64, '-') << "\n";
                    cout << "  CÁLCULOS SALARIALES\n";
                    cout << string(64, '-') << "\n\n";

                    cout << left << setw(30) << "  Horas descontadas:" << right << setw(10) << (
                        datosEmpleados[empleadoIndex][1] / 60.0) << " hrs\n";
                    cout << left << setw(30) << "  Horas netas de trabajo:" << right << setw(10) << datosEmpleados[
                        empleadoIndex][3] << " hrs\n";
                    cout << left << setw(30) << "  Valor descuento efectuado:" << right << setw(10) << "$" <<
                            datosEmpleados[
                                empleadoIndex][4] << "\n";

                    cout << "\n" << string(64, '-') << "\n";
                    cout << left << setw(30) << "  SALARIO NETO A CANCELAR:" << right << setw(10) << "$" <<
                            datosEmpleados[
                                empleadoIndex][5] << "\n";
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
                cout << "1 Reporte de empleados con registro de tardanza" << endl;
                cout << "2 Reporte de empleados puntuales" << endl;
                cout << "3 Reporte descuento tiempo tardanza" << endl;

                short opcionSubMenu;
                bool opcionSubMenuValida = false;
                while (!opcionSubMenuValida) {
                    cout << "\n► Seleccione una opcion [1-3]: ";
                    cin >> opcionSubMenu;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "❌ Error: Ingrese un entero valido.\n" << endl;
                    } else if (opcionSubMenu >= 1 && opcionSubMenu <= 3) {
                        opcionSubMenuValida = true;
                    } else {
                        cout << "❌ Error: Opcion fuera del rango (1-3).\n" << endl;
                    }
                }

                system("clear || cls");
                switch (opcionSubMenu) {
                    case 1: {
                        if (empleadosConTardanza.empty()) {
                            cout << "\n⚠️ No hay empleados con tardanzas." << endl;
                            break;
                        }

                        short indiceConMayorTardanza = empleadosConTardanza[0];
                        short indiceConMenorTardanza = empleadosConTardanza[0];
                        double sumaTardanzas = 0.0;

                        cout << "\n=== EMPLEADOS CON TARDANZA ===\n";
                        cout << fixed << setprecision(2);

                        for (const short indiceEmpleado: empleadosConTardanza) {
                            const float tardanza = datosEmpleados[indiceEmpleado][1];
                            sumaTardanzas += tardanza;

                            if (tardanza > datosEmpleados[indiceConMayorTardanza][1]) {
                                indiceConMayorTardanza = indiceEmpleado;
                            }

                            if (tardanza < datosEmpleados[indiceConMenorTardanza][1]) {
                                indiceConMenorTardanza = indiceEmpleado;
                            }

                            cout << "\nCodigo: " << codigos[indiceEmpleado] << endl;
                            cout << "Nombre: " << nombres[indiceEmpleado] << endl;
                            cout << "Dependencia: " << oficina[indiceEmpleado] << endl;
                            cout << "Minutos de Tardanza: " << tardanza << " mins" << endl;
                            cout << "Horas de Tardanza: " << (tardanza / 60.0f) << " hrs" << endl;
                        }

                        if (!empleadosPuntuales.empty()) {
                            indiceConMenorTardanza = empleadosPuntuales[0];
                        }

                        const double promedioTardanza =
                                sumaTardanzas / static_cast<double>(empleadosConTardanza.size());

                        cout << "\n=== RESUMEN ===\n";
                        cout << "Empleado con MAYOR tardanza: " << nombres[indiceConMayorTardanza]
                                << " (" << datosEmpleados[indiceConMayorTardanza][1] << " mins)\n";
                        cout << "Empleado con MENOR tardanza: " << nombres[indiceConMenorTardanza]
                                << " (" << datosEmpleados[indiceConMenorTardanza][1] << " mins)\n";
                        cout << "Promedio de tardanzas: " << promedioTardanza << " mins\n";

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nPresione ENTER para continuar...";
                        cin.get();
                        break;
                    }
                    case 2: {
                        if (empleadosPuntuales.empty()) {
                            cout << "\n⚠️ No hay empleados puntuales!\n" << endl;
                            break;
                        }

                        cout << "\n=== EMPLEADOS PUNTUALES ===\n";
                        cout << fixed << setprecision(2);

                        for (const short indiceEmpleado: empleadosPuntuales) {
                            cout << "\nCodigo: " << codigos[indiceEmpleado] << endl;
                            cout << "Nombre: " << nombres[indiceEmpleado] << endl;
                            cout << "Dependencia: " << oficina[indiceEmpleado] << endl;
                            cout << "Horas Trabajadas: " << datosEmpleados[indiceEmpleado][2] << " hrs" << endl;
                        }

                        if (puntualesPorOficina[0] > 0) {
                            const double promedio = sumaHorasPorOficina[0] / puntualesPorOficina[0];
                            cout << "Promedio de Contabilidad: " << promedio << " hrs ("
                                    << puntualesPorOficina[0] << " empleados puntuales)\n";
                        } else {
                            cout << "Promedio de Contabilidad: No hay empleados puntuales\n";
                        }

                        if (puntualesPorOficina[1] > 0) {
                            const double promedio = sumaHorasPorOficina[1] / puntualesPorOficina[1];
                            cout << "Promedio de Sistemas: " << promedio << " hrs ("
                                    << puntualesPorOficina[1] << " empleados puntuales)\n";
                        } else {
                            cout << "Promedio de Sistemas: No hay empleados puntuales\n";
                        }

                        if (puntualesPorOficina[2] > 0) {
                            const double promedio = sumaHorasPorOficina[2] / puntualesPorOficina[2];
                            cout << "Promedio de Logística: " << promedio << " hrs ("
                                    << puntualesPorOficina[2] << " empleados puntuales)\n";
                        } else {
                            cout << "Promedio de Logística: No hay empleados puntuales\n";
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nPresione ENTER para continuar...";
                        cin.get();
                        break;
                    }
                    case 3: {
                        if (empleadosConTardanza.empty()) {
                            cout << "\n⚠️ No hay empleados con tardanzas." << endl;
                            break;
                        }
                        double totalHorasDescontadas{};
                        double totalValorDescuentos{};
                        cout << "\n=== REPORTE DE TARDANZA ===\n";
                        cout << fixed << setprecision(2);

                        for (const short indiceEmpleado: empleadosConTardanza) {
                            const float tardanza = datosEmpleados[indiceEmpleado][1];
                            totalHorasDescontadas += tardanza / 60.0f;
                            totalValorDescuentos += datosEmpleados[indiceEmpleado][4];

                            cout << "\nCodigo: " << codigos[indiceEmpleado] << endl;
                            cout << "Nombre: " << nombres[indiceEmpleado] << endl;
                            cout << "Dependencia: " << oficina[indiceEmpleado] << endl;
                            cout << "Valor Salarial: $" << datosEmpleados[indiceEmpleado][2] << "/hr" << endl;
                            cout << "Horas Totales: " << datosEmpleados[indiceEmpleado][0] << endl;
                            cout << "Minutos de Tardanza: " << tardanza << " mins" << endl;
                            cout << "Horas descontadas: " << (tardanza / 60.0f) << " hrs" << endl;
                            cout << "Horas netas de Trabajo: " << datosEmpleados[indiceEmpleado][3] << endl;
                            cout << "Valor descuento afectado: $" << datosEmpleados[indiceEmpleado][4] << endl;
                            cout << "Salario Neto a Cancelar: $" << datosEmpleados[indiceEmpleado][5] << endl;
                        }

                        cout << "\n=== TOTAL DESCUENTOS ===\n";
                        cout << fixed << setprecision(2);
                        cout << "Total Horas Descontadas: " << totalHorasDescontadas << endl;
                        cout << "Total Valor Descontado: $" << totalValorDescuentos << endl;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nPresione ENTER para continuar...";
                        cin.get();
                        break;
                    }
                }
                break;
            }
            case 4:
                continua = false;
                break;
        }
    }


    return 0;
}
