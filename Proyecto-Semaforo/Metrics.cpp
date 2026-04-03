#include "Metrics.h"


Metrics::Metrics(int n) {
    comidas.resize(n, 0);
    inicioEspera.resize(n);
    tiemposDeEspera.resize(n);
}

void Metrics::iniciarEspera(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    inicioEspera[id] = std::chrono::steady_clock::now();
}

void Metrics::finalizarEspera(int id) {
    std::lock_guard<std::mutex> lock(mtx);

    auto fin = std::chrono::steady_clock::now();
    long long duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicioEspera[id]).count();

    tiemposDeEspera[id].push_back(duracion);
}

void Metrics::incrementarComida(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    comidas[id]++;
}

void Metrics::guardarCSV(const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "[Metrics] No se pudo abrir el archivo: " << filename << "\n";
        return;
    }

    std::cout << "[Metrics] Generando archivo: " << filename << "\n";

    file << "Filosofo,Comidas,PromedioEspera(ms),MaximoEspera(ms),DesviacionEstandar(ms)\n";

    for (int id = 0; id < comidas.size(); id++) {
        const auto& tiempos = tiemposDeEspera[id];

        double promedio = 0;
        long long maximo = 0;
        double desviacion = 0;

        if (!tiempos.empty()) {
            long long suma = 0;
            for (auto t : tiempos) {
                suma += t;
                if (t > maximo) maximo = t;
            }
            promedio = double(suma) / tiempos.size();

            double sumDif = 0;
            for (auto t : tiempos) {
                sumDif += (t - promedio) * (t - promedio);
            }
            desviacion = std::sqrt(sumDif / tiempos.size());
        }

        file << id << ","
            << comidas[id] << ","
            << promedio << ","
            << maximo << ","
            << desviacion << "\n";
    }

    file.close();
    std::cout << "[Metrics] Archivo cerrado correctamente.\n";
}
