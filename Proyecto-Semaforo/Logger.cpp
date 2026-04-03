#include "Logger.h"
#include <windows.h>

Logger::Logger() {
    startTime = std::chrono::steady_clock::now();
}

void Logger::log(int id, const std::string& action) {
    std::lock_guard<std::mutex> lock(mtx);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // tiempo relativo en ms desde que empezó el logger
    auto now = std::chrono::steady_clock::now();
    long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();

    // Asignar color según el estado
    if (action == "pensando")
        SetConsoleTextAttribute(hConsole, 13);  // fucsia
    else if (action == "programando")
        SetConsoleTextAttribute(hConsole, 3);   // azul
    else if (action == "hambriento")
        SetConsoleTextAttribute(hConsole, 12);  // rojo
    else if (action == "comiendo")
        SetConsoleTextAttribute(hConsole, 10);  // verde
    else
        SetConsoleTextAttribute(hConsole, 15);  // blanco

    std::cout << "[" << ms << "ms] Filosofo " << id << " esta " << action << std::endl;

    // Restaurar color por defecto
    SetConsoleTextAttribute(hConsole, 7);
}
