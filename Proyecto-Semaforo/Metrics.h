#pragma once
#include <vector>
#include <mutex>
#include <chrono>
#include <string>
#include "Metrics.h"
#include <iostream>    t
#include <fstream>      
#include <cmath>       


class Metrics {
private:
    std::vector<int> comidas;
    std::vector<std::chrono::steady_clock::time_point> inicioEspera;
    std::vector<std::vector<long long>> tiemposDeEspera;

    std::mutex mtx;

public:
    Metrics(int n);

    void iniciarEspera(int id);
    void finalizarEspera(int id);
    void incrementarComida(int id);

    void guardarCSV(const std::string& filename);
};
