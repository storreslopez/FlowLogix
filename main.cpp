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

#define RESET "\033[0m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_BLUE "\033[94m"

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
            cout << BRIGHT_RED << "❌ Error: Ingrese un entero valido." << RESET << "\n" << endl;
        } else if (numeroEmpleados > 0) {
            numeroValido = true;
        } else {
            cout << BRIGHT_RED << "❌ Error: El numero de empleados debe ser mayor a 0." << RESET << "\n" << endl;
        }
    }
    system("clear || cls");

    long codigos[numeroEmpleados];
    string nombres[numeroEmpleados];
    char oficina[numeroEmpleados];
    vector<short> empleadosConTardanza;
    vector<short> empleadosPuntuales;

    double sumaHorasPorOficina[3] = {0.0, 0.0, 0.0};
    int puntualesPorOficina[3] = {0, 0, 0};

    float datosEmpleados[numeroEmpleados][NUMERO_DATOS];

    // ========== DUMMY DATA FOR TESTING - REMOVE WHEN DONE ==========
    if (numeroEmpleados >= 10) {
        codigos[0] = 1001; nombres[0] = "Juan Perez"; oficina[0] = 'C';
        datosEmpleados[0][0] = 40.0f; datosEmpleados[0][1] = 30.0f; datosEmpleados[0][2] = 25000.0f;
        datosEmpleados[0][3] = 39.5f; datosEmpleados[0][4] = 12500.0f; datosEmpleados[0][5] = 987500.0f;
        empleadosConTardanza.push_back(0);

        codigos[1] = 1002; nombres[1] = "Maria Garcia"; oficina[1] = 'S';
        datosEmpleados[1][0] = 35.0f; datosEmpleados[1][1] = 0.0f; datosEmpleados[1][2] = 30000.0f;
        datosEmpleados[1][3] = 35.0f; datosEmpleados[1][4] = 0.0f; datosEmpleados[1][5] = 1050000.0f;
        empleadosPuntuales.push_back(1);
        sumaHorasPorOficina[1] += 35.0f; puntualesPorOficina[1]++;

        codigos[2] = 1003; nombres[2] = "Carlos Rodriguez"; oficina[2] = 'L';
        datosEmpleados[2][0] = 42.0f; datosEmpleados[2][1] = 120.0f; datosEmpleados[2][2] = 22000.0f;
        datosEmpleados[2][3] = 40.0f; datosEmpleados[2][4] = 44000.0f; datosEmpleados[2][5] = 880000.0f;
        empleadosConTardanza.push_back(2);

        codigos[3] = 1004; nombres[3] = "Ana Martinez"; oficina[3] = 'C';
        datosEmpleados[3][0] = 38.0f; datosEmpleados[3][1] = 0.0f; datosEmpleados[3][2] = 28000.0f;
        datosEmpleados[3][3] = 38.0f; datosEmpleados[3][4] = 0.0f; datosEmpleados[3][5] = 1064000.0f;
        empleadosPuntuales.push_back(3);
        sumaHorasPorOficina[0] += 38.0f; puntualesPorOficina[0]++;

        codigos[4] = 1005; nombres[4] = "Luis Fernandez"; oficina[4] = 'S';
        datosEmpleados[4][0] = 40.0f; datosEmpleados[4][1] = 90.0f; datosEmpleados[4][2] = 32000.0f;
        datosEmpleados[4][3] = 38.5f; datosEmpleados[4][4] = 48000.0f; datosEmpleados[4][5] = 1232000.0f;
        empleadosConTardanza.push_back(4);

        codigos[5] = 1006; nombres[5] = "Sofia Lopez"; oficina[5] = 'L';
        datosEmpleados[5][0] = 36.0f; datosEmpleados[5][1] = 0.0f; datosEmpleados[5][2] = 24000.0f;
        datosEmpleados[5][3] = 36.0f; datosEmpleados[5][4] = 0.0f; datosEmpleados[5][5] = 864000.0f;
        empleadosPuntuales.push_back(5);
        sumaHorasPorOficina[2] += 36.0f; puntualesPorOficina[2]++;

        codigos[6] = 1007; nombres[6] = "Pedro Sanchez"; oficina[6] = 'C';
        datosEmpleados[6][0] = 39.0f; datosEmpleados[6][1] = 45.0f; datosEmpleados[6][2] = 26000.0f;
        datosEmpleados[6][3] = 38.25f; datosEmpleados[6][4] = 19500.0f; datosEmpleados[6][5] = 994500.0f;
        empleadosConTardanza.push_back(6);

        codigos[7] = 1008; nombres[7] = "Laura Torres"; oficina[7] = 'S';
        datosEmpleados[7][0] = 37.0f; datosEmpleados[7][1] = 0.0f; datosEmpleados[7][2] = 31000.0f;
        datosEmpleados[7][3] = 37.0f; datosEmpleados[7][4] = 0.0f; datosEmpleados[7][5] = 1147000.0f;
        empleadosPuntuales.push_back(7);
        sumaHorasPorOficina[1] += 37.0f; puntualesPorOficina[1]++;

        codigos[8] = 1009; nombres[8] = "Roberto Jimenez"; oficina[8] = 'L';
        datosEmpleados[8][0] = 41.0f; datosEmpleados[8][1] = 180.0f; datosEmpleados[8][2] = 23000.0f;
        datosEmpleados[8][3] = 38.0f; datosEmpleados[8][4] = 69000.0f; datosEmpleados[8][5] = 874000.0f;
        empleadosConTardanza.push_back(8);

        codigos[9] = 1010; nombres[9] = "Carmen Ruiz"; oficina[9] = 'C';
        datosEmpleados[9][0] = 35.5f; datosEmpleados[9][1] = 0.0f; datosEmpleados[9][2] = 27000.0f;
        datosEmpleados[9][3] = 35.5f; datosEmpleados[9][4] = 0.0f; datosEmpleados[9][5] = 958500.0f;
        empleadosPuntuales.push_back(9);
        sumaHorasPorOficina[0] += 35.5f; puntualesPorOficina[0]++;
    }
    // ========== END DUMMY DATA ==========

    bool continua = true;
    while (continua) {
        cout << endl;
        cout << BRIGHT_CYAN << setw(50) << right << "EMPRESA FLOWLOGIX" << RESET << endl;
        cout << setw(55) << right << "Puntualidad que impulsa tu empresa." << endl;
        cout << BRIGHT_CYAN << setw(50) << right << "REGISTRO DE TARDANZA" << RESET << endl;
        cout << endl;
        cout << string(60, '=') << endl;
        cout << BRIGHT_YELLOW << "1. " << RESET << "Registra informacion de empleados" << endl;
        cout << BRIGHT_YELLOW << "2. " << RESET << "Consultar empleado" << endl;
        cout << BRIGHT_YELLOW << "3. " << RESET << "Reportes" << endl;
        cout << setw(4) << "" << BRIGHT_YELLOW << "3.1 " << RESET << "Reporte de empleados con registro de tardanza" << endl;
        cout << setw(4) << "" << BRIGHT_YELLOW << "3.2 " << RESET << "Reporte de empleados puntuales" << endl;
        cout << setw(4) << "" << BRIGHT_YELLOW << "3.3 " << RESET << "Reporte descuento tiempo tardanza" << endl;
        cout << BRIGHT_YELLOW << "4. " << RESET << "Salir" << endl;
        cout << string(60, '=') << endl;
        cout << endl;

        short opcionMenu;
        bool opcionMenuValida = false;

        while (!opcionMenuValida) {
            cout << "► Ingrese una opcion (1-4): ";
            cin >> opcionMenu;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << BRIGHT_RED << "❌ Error: Ingrese un entero valido.\n" << RESET << endl;
            } else if (opcionMenu >= 1 && opcionMenu <= 4) {
                opcionMenuValida = true;
            } else {
                cout << BRIGHT_RED << "❌ Error: Ingrese una opcion valida [1-4]\n" << RESET << endl;
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
                            cout << BRIGHT_RED << "❌ Error: Ingrese un entero valido.\n" << RESET << endl;
                            continue;
                        }

                        if (codigoEmpleado < 1) {
                            cout << BRIGHT_RED << "❌ Error: El código debe ser mayor o igual a 1.\n" << RESET << endl;
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
                            cout << BRIGHT_RED << "❌ Error: Este codigo ya ha sido registrado.\n" << RESET << endl;
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
                            cout << BRIGHT_RED << "❌ Error: Ingrese un caracter valido.\n" << RESET << endl;
                            continue;
                        }

                        oficinaEmpleado = toupper(oficinaEmpleado);

                        if (oficinaEmpleado == 'C' || oficinaEmpleado == 'S' || oficinaEmpleado == 'L') {
                            oficinaValida = true;
                        } else {
                            cout << BRIGHT_RED << "❌ Error: Opción no válida. Ingrese C, S o L.\n" << RESET << endl;
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
                            cout << BRIGHT_RED << "❌ Error: Ingrese un float valido.\n" << RESET << endl;
                        } else if (horasSemanales > 0) {
                            horasValidas = true;
                        } else {
                            cout << BRIGHT_RED << "❌ Error: Ingrese un valor positivo.\n" << RESET << endl;
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
                            cout << BRIGHT_RED << "❌ Error: Ingrese un float valido.\n" << RESET << endl;
                        } else if (minutosTardanza >= 0) {
                            minutosValidos = true;
                        } else {
                            cout << BRIGHT_RED << "❌ Error: Ingrese un valor positivo.\n" << RESET << endl;
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
                            cout << BRIGHT_RED << "❌ Error: Ingrese un float valido.\n" << RESET << endl;
                        } else if (valorHora > 0) {
                            valorHoraValido = true;
                        } else {
                            cout << BRIGHT_RED << "❌ Error: Ingrese un valor positivo.\n" << RESET << endl;
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
                        cout << BRIGHT_RED << "❌ Error: Ingrese un entero valido.\n" << RESET << endl;
                        continue;
                    }

                    if (codigoEmpleado < 1) {
                        cout << BRIGHT_RED << "❌ Error: El código debe ser mayor o igual a 1.\n" << RESET << endl;
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

                    cout << "\n" << BRIGHT_CYAN << string(70, '=') << RESET << "\n";
                    cout << BRIGHT_CYAN << "|" << RESET << setw(35) << right << "INFORMACIÓN DETALLADA DEL EMPLEADO" << setw(33) << "" << BRIGHT_CYAN << "|" << RESET << "\n";
                    cout << BRIGHT_CYAN << string(70, '=') << RESET << "\n\n";

                    cout << BRIGHT_YELLOW << left << setw(30) << "  Código del empleado:" << RESET << right << setw(38) << codigoEmpleado << "\n";
                    cout << BRIGHT_YELLOW << left << setw(30) << "  Nombre completo:" << RESET << right << setw(38) << nombres[empleadoIndex] << "\n";
                    cout << BRIGHT_YELLOW << left << setw(30) << "  Oficina:" << RESET << right << setw(38) << oficinaEmpleado << "\n";

                    cout << "\n" << string(70, '-') << "\n";
                    cout << BRIGHT_YELLOW << "  INFORMACIÓN LABORAL" << RESET << "\n";
                    cout << string(70, '-') << "\n\n";

                    cout << BRIGHT_YELLOW << left << setw(30) << "  Valor por hora:" << RESET << right << setw(10) << "$" << setw(28) << datosEmpleados[empleadoIndex][2] << "\n";
                    cout << BRIGHT_YELLOW << left << setw(30) << "  Horas semanales trabajadas:" << RESET << right << setw(10) << datosEmpleados[empleadoIndex][0] << setw(28) << " hrs\n";
                    cout << BRIGHT_YELLOW << left << setw(30) << "  Minutos de tardanza semanal:" << RESET << right << setw(10) << datosEmpleados[empleadoIndex][1] << setw(28) << " min\n";

                    cout << "\n" << string(70, '-') << "\n";
                    cout << BRIGHT_YELLOW << "  CÁLCULOS SALARIALES" << RESET << "\n";
                    cout << string(70, '-') << "\n\n";

                    cout << BRIGHT_YELLOW << left << setw(30) << "  Horas descontadas:" << RESET << right << setw(10) << (datosEmpleados[empleadoIndex][1] / 60.0) << setw(28) << " hrs\n";
                    cout << BRIGHT_YELLOW << left << setw(30) << "  Horas netas de trabajo:" << RESET << right << setw(10) << datosEmpleados[empleadoIndex][3] << setw(28) << " hrs\n";
                    cout << BRIGHT_YELLOW << left << setw(30) << "  Valor descuento efectuado:" << RESET << right << setw(10) << "$" << setw(28) << datosEmpleados[empleadoIndex][4] << "\n";

                    cout << "\n" << string(70, '=') << "\n";
                    cout << BRIGHT_GREEN << left << setw(30) << "  SALARIO NETO A CANCELAR:" << RESET << right << setw(10) << "$" << setw(28) << datosEmpleados[empleadoIndex][5] << "\n";
                    cout << string(70, '=') << "\n\n";
                } else {
                    cout << BRIGHT_RED << "❌ Error: No hay ningun empleado con ese ID!\n" << RESET << endl;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nPresione ENTER para continuar...";
                cin.get();
                system("clear || cls");
                break;
            }
            case 3: {
                cout << BRIGHT_CYAN << string(60, '=') << RESET << "\n";
                cout << BRIGHT_CYAN << setw(30) << right << "MENÚ DE REPORTES" << RESET << "\n";
                cout << BRIGHT_CYAN << string(60, '=') << RESET << "\n";
                cout << BRIGHT_YELLOW << "1. " << RESET << "Reporte de empleados con registro de tardanza" << endl;
                cout << BRIGHT_YELLOW << "2. " << RESET << "Reporte de empleados puntuales" << endl;
                cout << BRIGHT_YELLOW << "3. " << RESET << "Reporte descuento tiempo tardanza" << endl;
                cout << BRIGHT_CYAN << string(60, '=') << RESET << "\n";

                short opcionSubMenu;
                bool opcionSubMenuValida = false;
                while (!opcionSubMenuValida) {
                    cout << "\n► Seleccione una opcion [1-3]: ";
                    cin >> opcionSubMenu;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << BRIGHT_RED << "❌ Error: Ingrese un entero valido.\n" << RESET << endl;
                    } else if (opcionSubMenu >= 1 && opcionSubMenu <= 3) {
                        opcionSubMenuValida = true;
                    } else {
                        cout << BRIGHT_RED << "❌ Error: Opcion fuera del rango (1-3).\n" << RESET << endl;
                    }
                }

                system("clear || cls");
                switch (opcionSubMenu) {
                    case 1: {
                        if (empleadosConTardanza.empty()) {
                            cout << "\n" << BRIGHT_RED << "⚠️ No hay empleados con tardanzas." << RESET << endl;
                            break;
                        }

                        short indiceConMayorTardanza = empleadosConTardanza[0];
                        short indiceConMenorTardanza = empleadosConTardanza[0];
                        double sumaTardanzas = 0.0;

                        cout << "\n" << BRIGHT_CYAN << string(100, '=') << RESET << "\n";
                        cout << BRIGHT_CYAN << setw(50) << right << "EMPLEADOS CON TARDANZA" << RESET << "\n";
                        cout << BRIGHT_CYAN << string(100, '=') << RESET << "\n\n";

                        cout << fixed << setprecision(2);
                        cout << BRIGHT_YELLOW << left << setw(12) << "CODIGO" << setw(25) << "NOMBRE" << setw(15) << "DEPENDENCIA" << right << setw(15) << "MIN. TARDANZA" << setw(18) << "HRS. TARDANZA" << RESET << "\n";
                        cout << string(100, '-') << "\n";

                        for (const short indiceEmpleado: empleadosConTardanza) {
                            const float tardanza = datosEmpleados[indiceEmpleado][1];
                            sumaTardanzas += tardanza;

                            if (tardanza > datosEmpleados[indiceConMayorTardanza][1]) {
                                indiceConMayorTardanza = indiceEmpleado;
                            }

                            if (tardanza < datosEmpleados[indiceConMenorTardanza][1]) {
                                indiceConMenorTardanza = indiceEmpleado;
                            }

                            string depStr;
                            switch (oficina[indiceEmpleado]) {
                                case 'C': depStr = "Contabilidad"; break;
                                case 'S': depStr = "Sistemas"; break;
                                case 'L': depStr = "Logistica"; break;
                            }

                            cout << left << setw(12) << codigos[indiceEmpleado] << setw(25) << nombres[indiceEmpleado] << setw(15) << depStr << right << setw(15) << tardanza << " mins" << setw(12) << (tardanza / 60.0f) << " hrs" << "\n";
                        }

                        if (!empleadosPuntuales.empty()) {
                            indiceConMenorTardanza = empleadosPuntuales[0];
                        }

                        const double promedioTardanza = sumaTardanzas / static_cast<double>(empleadosConTardanza.size());

                        cout << string(100, '-') << "\n";
                        cout << BRIGHT_CYAN << string(100, '=') << RESET << "\n";
                        cout << BRIGHT_CYAN << setw(50) << right << "RESUMEN ESTADÍSTICO" << RESET << "\n";
                        cout << BRIGHT_CYAN << string(100, '=') << RESET << "\n";
                        cout << BRIGHT_YELLOW << left << setw(40) << "  Empleado con MAYOR tardanza:" << RESET << nombres[indiceConMayorTardanza] << " (" << datosEmpleados[indiceConMayorTardanza][1] << " mins)\n";
                        cout << BRIGHT_YELLOW << left << setw(40) << "  Empleado con MENOR tardanza:" << RESET << nombres[indiceConMenorTardanza] << " (" << datosEmpleados[indiceConMenorTardanza][1] << " mins)\n";
                        cout << BRIGHT_YELLOW << left << setw(40) << "  Promedio de tardanzas:" << RESET << fixed << setprecision(2) << promedioTardanza << " mins\n";

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nPresione ENTER para continuar...";
                        cin.get();
                        break;
                    }
                    case 2: {
                        if (empleadosPuntuales.empty()) {
                            cout << "\n" << BRIGHT_RED << "⚠️ No hay empleados puntuales!\n" << RESET << endl;
                            break;
                        }

                        cout << "\n" << BRIGHT_CYAN << string(90, '=') << RESET << "\n";
                        cout << BRIGHT_CYAN << setw(45) << right << "EMPLEADOS PUNTUALES" << RESET << "\n";
                        cout << BRIGHT_CYAN << string(90, '=') << RESET << "\n\n";

                        cout << fixed << setprecision(2);
                        cout << BRIGHT_YELLOW << left << setw(12) << "CODIGO" << setw(25) << "NOMBRE" << setw(20) << "DEPENDENCIA" << right << setw(18) << "HORAS TRABAJADAS" << RESET << "\n";
                        cout << string(90, '-') << "\n";

                        for (const short indiceEmpleado: empleadosPuntuales) {
                            string depStr;
                            switch (oficina[indiceEmpleado]) {
                                case 'C': depStr = "Contabilidad"; break;
                                case 'S': depStr = "Sistemas"; break;
                                case 'L': depStr = "Logistica"; break;
                            }

                            cout << left << setw(12) << codigos[indiceEmpleado] << setw(25) << nombres[indiceEmpleado] << setw(20) << depStr << right << setw(15) << datosEmpleados[indiceEmpleado][0] << " hrs" << "\n";
                        }

                        cout << string(90, '-') << "\n";
                        cout << BRIGHT_CYAN << string(90, '=') << RESET << "\n";
                        cout << BRIGHT_CYAN << setw(45) << right << "PROMEDIOS POR OFICINA" << RESET << "\n";
                        cout << BRIGHT_CYAN << string(90, '=') << RESET << "\n";

                        if (puntualesPorOficina[0] > 0) {
                            const double promedio = sumaHorasPorOficina[0] / puntualesPorOficina[0];
                            cout << BRIGHT_YELLOW << left << setw(35) << "  Promedio de Contabilidad:" << RESET << right << setw(15) << fixed << setprecision(2) << promedio << " hrs (" << puntualesPorOficina[0] << " empleados puntuales)\n";
                        } else {
                            cout << BRIGHT_YELLOW << left << setw(35) << "  Promedio de Contabilidad:" << RESET << "No hay empleados puntuales\n";
                        }

                        if (puntualesPorOficina[1] > 0) {
                            const double promedio = sumaHorasPorOficina[1] / puntualesPorOficina[1];
                            cout << BRIGHT_YELLOW << left << setw(35) << "  Promedio de Sistemas:" << RESET << right << setw(15) << fixed << setprecision(2) << promedio << " hrs (" << puntualesPorOficina[1] << " empleados puntuales)\n";
                        } else {
                            cout << BRIGHT_YELLOW << left << setw(35) << "  Promedio de Sistemas:" << RESET << "No hay empleados puntuales\n";
                        }

                        if (puntualesPorOficina[2] > 0) {
                            const double promedio = sumaHorasPorOficina[2] / puntualesPorOficina[2];
                            cout << BRIGHT_YELLOW << left << setw(35) << "  Promedio de Logística:" << RESET << right << setw(16) << fixed << setprecision(2) << promedio << " hrs (" << puntualesPorOficina[2] << " empleados puntuales)\n";
                        } else {
                            cout << BRIGHT_YELLOW << left << setw(35) << "  Promedio de Logística:" << RESET << "No hay empleados puntuales\n";
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nPresione ENTER para continuar...";
                        cin.get();
                        break;
                    }
                    case 3: {
                        if (empleadosConTardanza.empty()) {
                            cout << "\n" << BRIGHT_RED << "⚠️ No hay empleados con tardanzas." << RESET << endl;
                            break;
                        }
                        double totalHorasDescontadas{};
                        double totalValorDescuentos{};
                        cout << "\n" << BRIGHT_CYAN << string(120, '=') << RESET << "\n";
                        cout << BRIGHT_CYAN << setw(60) << right << "REPORTE DESCUENTO TIEMPO TARDANZA" << RESET << "\n";
                        cout << BRIGHT_CYAN << string(120, '=') << RESET << "\n\n";

                        cout << fixed << setprecision(2);
                        cout << BRIGHT_YELLOW << left << setw(10) << "CODIGO" << setw(20) << "NOMBRE" << setw(13) << "DEPENDENCIA" << right << setw(11) << "VALOR/HR" << setw(11) << "HRS TRAB" << setw(11) << "MIN TARD" << setw(11) << "HRS DESC" << setw(11) << "HRS NETAS" << setw(11) << "VAL DESC" << setw(11) << "SAL NETO" << RESET << "\n";
                        cout << string(120, '-') << "\n";

                        for (const short indiceEmpleado: empleadosConTardanza) {
                            const float tardanza = datosEmpleados[indiceEmpleado][1];
                            totalHorasDescontadas += tardanza / 60.0f;
                            totalValorDescuentos += datosEmpleados[indiceEmpleado][4];

                            string depStr;
                            switch (oficina[indiceEmpleado]) {
                                case 'C': depStr = "Contabilidad"; break;
                                case 'S': depStr = "Sistemas"; break;
                                case 'L': depStr = "Logistica"; break;
                            }

                            cout << left << setw(10) << codigos[indiceEmpleado] << setw(20) << nombres[indiceEmpleado] << setw(13) << depStr << right << setw(1) << "$" << setw(10) << datosEmpleados[indiceEmpleado][2] << setw(11) << datosEmpleados[indiceEmpleado][0] << setw(11) << tardanza << setw(11) << (tardanza / 60.0f) << setw(11) << datosEmpleados[indiceEmpleado][3] << setw(1) << "$" << setw(10) << datosEmpleados[indiceEmpleado][4] << setw(1) << "$" << setw(10) << datosEmpleados[indiceEmpleado][5] << "\n";
                        }

                        cout << string(120, '-') << "\n";
                        cout << BRIGHT_CYAN << string(120, '=') << RESET << "\n";
                        cout << BRIGHT_CYAN << left << setw(43) << "" << right << setw(34) << "TOTALES" << RESET << "\n";
                        cout << BRIGHT_CYAN << string(120, '=') << RESET << "\n";
                        cout << BRIGHT_GREEN << left << setw(43) << "  Total Horas Descontadas:" << RESET << right << setw(33) << "" << fixed << setprecision(2) << totalHorasDescontadas << " hrs\n";
                        cout << BRIGHT_GREEN << left << setw(43) << "  Total Valor Descontado:" << RESET << right << setw(33) << "" << "$" << setw(10) << fixed << setprecision(2) << totalValorDescuentos << "\n";

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
