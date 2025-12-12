#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

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
    short empleadosConTardanza[numeroEmpleados];
    short numEmpleadosConTardanza = 0;
    short empleadosPuntuales[numeroEmpleados];
    short numEmpleadosPuntuales = 0;

    double sumaHorasPorOficina[3] = {0.0, 0.0, 0.0};
    int puntualesPorOficina[3] = {0, 0, 0};

    float datosEmpleados[numeroEmpleados][NUMERO_DATOS];
    bool yaRegistroEmpleados = false;

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
                if (yaRegistroEmpleados) {
                    cout << "\n" << BRIGHT_RED << "⚠️ Ya has registrado los empleados." << RESET << endl;
                    break;
                }
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

                    if (minutosTardanza == 0) empleadosPuntuales[numEmpleadosPuntuales++] = i;
                    if (minutosTardanza > 0) empleadosConTardanza[numEmpleadosConTardanza++] = i;

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
                yaRegistroEmpleados = true;
                break;
            }
            case 2: {
                if (!yaRegistroEmpleados) {
                    cout << "\n" << BRIGHT_RED << "⚠️ Aun no has registrado ningun empleado." << RESET << endl;
                    break;
                }
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
                if (!yaRegistroEmpleados) {
                    cout << "\n" << BRIGHT_RED << "⚠️ Aun no has registrado ningun empleado." << RESET << endl;
                    break;
                }
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
                        if (numEmpleadosConTardanza == 0) {
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

                        for (short j = 0; j < numEmpleadosConTardanza; ++j) {
                            const short indiceEmpleado = empleadosConTardanza[j];
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

                        if (numEmpleadosPuntuales > 0) {
                            indiceConMenorTardanza = empleadosPuntuales[0];
                        }

                        const double promedioTardanza = sumaTardanzas / static_cast<double>(numEmpleadosConTardanza);

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
                        if (numEmpleadosPuntuales == 0) {
                            cout << "\n" << BRIGHT_RED << "⚠️ No hay empleados puntuales!\n" << RESET << endl;
                            break;
                        }

                        cout << "\n" << BRIGHT_CYAN << string(90, '=') << RESET << "\n";
                        cout << BRIGHT_CYAN << setw(45) << right << "EMPLEADOS PUNTUALES" << RESET << "\n";
                        cout << BRIGHT_CYAN << string(90, '=') << RESET << "\n\n";

                        cout << fixed << setprecision(2);
                        cout << BRIGHT_YELLOW << left << setw(12) << "CODIGO" << setw(25) << "NOMBRE" << setw(20) << "DEPENDENCIA" << right << setw(18) << "HORAS TRABAJADAS" << RESET << "\n";
                        cout << string(90, '-') << "\n";

                        for (short j = 0; j < numEmpleadosPuntuales; ++j) {
                            const short indiceEmpleado = empleadosPuntuales[j];
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
                        if (numEmpleadosConTardanza == 0) {
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

                        for (short j = 0; j < numEmpleadosConTardanza; ++j) {
                            const short indiceEmpleado = empleadosConTardanza[j];
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
    cout << BRIGHT_BLUE << "🤗 Gracias por usar nuestro programa!" << RESET << endl;
    return 0;
}
