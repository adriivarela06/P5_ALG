#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "camino_heroe.h"

using namespace std;

bool leer_entrada(const string& fichero, int& n, vector<vector<int>>& C, vector<int>& G) {
    ifstream f(fichero);
    if (!f.is_open()) {
        cerr << "Error: no se puede abrir el fichero '" << fichero << "'\n";
        return false;
    }

    f >> n;
    if (n <= 0) return false;

    C.assign(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int valor;
            f >> valor;
            C[i][j] = (valor < 0) ? INF : valor;
        }
    }

    G.assign(n, 0);
    for (int k = 0; k < n; ++k) {
        f >> G[k];
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <entrada.txt>\n";
        return 1;
    }

    int n;
    vector<vector<int>> C;
    vector<int> G;
    
    if (!leer_entrada(argv[1], n, C, G)) {
        return 1;
    }

    vector<vector<int>> D, P;

    // 1. Iniciamos el cronómetro
    auto inicio = chrono::high_resolution_clock::now();

    // 2. Ejecutamos el algoritmo
    el_camino_del_heroe(C, G, D, P);

    // 3. Paramos el cronómetro
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> tiempo = fin - inicio;

    // 4. Imprimimos el resultado
    cout << n << "\t" << tiempo.count() << "\n";

    return 0;
}