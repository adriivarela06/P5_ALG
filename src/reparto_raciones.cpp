#include <iostream>
#include <vector>
#include <map>
#include <cstdlib> 
#include <ctime>   
#include <algorithm>

using namespace std;

const int INF = 100000000;

struct Estado {
    int indice_caja;
    int peso_restante;

    Estado(int i, int p) : indice_caja(i), peso_restante(p) {}

    bool operator<(const Estado& otro) const {
        if (indice_caja != otro.indice_caja)
            return indice_caja < otro.indice_caja;
        return peso_restante < otro.peso_restante;
    }
};

struct Solucion {
    int n_cajas; 
    vector<int> desglose_cajas; // desglose_cajas[i] = cuántas cajas del tipo i usamos

    // Por defecto, el estado es imposible (-INF)
    Solucion() : n_cajas(-INF) {} 
    
    // Constructor para soluciones válidas
    Solucion(int num_cajas, vector<int> desglose) : n_cajas(num_cajas), desglose_cajas(desglose) {}
};

// Pasamos 'cajas' por referencia constante (&) para no copiar el vector en cada llamada recursiva (Eficiencia)
Solucion reparto(int i, int capacidad, const vector<pair<int, int>> &cajas, map<Estado, Solucion> &m) {

    // CASO BASE 1: Éxito. Devolvemos un vector vacío de tamaño N (inicializado a 0 cajas usadas)
    if (capacidad == 0) {
        return Solucion(0, vector<int>(cajas.size(), 0));
    }

    // CASO BASE 2: Fracaso.
    if (capacidad < 0 || i < 0) return Solucion(-INF, vector<int>());
    
    Estado estado_actual(i, capacidad);
    
    if (m.find(estado_actual) != m.end()){
        return m[estado_actual];
    }

    int peso_caja = cajas[i].first;

    Solucion mejor_solucion; // Empieza siendo -INF por defecto

    for (int k = 0; capacidad - k * peso_caja >= 0; ++k) {
            Solucion sol_subproblema = reparto(i - 1, capacidad - k * peso_caja, cajas, m);
            
        if (sol_subproblema.n_cajas != -INF) {
            int candidata_cajas = k + sol_subproblema.n_cajas;
            
            // Si encontramos un camino que usa MÁS cajas que el mejor actual, actualizamos todo
            if (candidata_cajas > mejor_solucion.n_cajas) {
                mejor_solucion.n_cajas = candidata_cajas;
                
                // Copiamos el desglose que venía de los tipos anteriores (i-1, i-2...)
                mejor_solucion.desglose_cajas = sol_subproblema.desglose_cajas;
                
                // Anotamos que en este tipo 'i', decidimos usar 'k' cajas
                mejor_solucion.desglose_cajas[i] = k;                
            }
        }
    }

    m[estado_actual] = mejor_solucion;
    return m[estado_actual];
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Error: Modo de uso correcto: " << argv[0] << " <kilogramos>\n";
        cout << "Ejemplo: " << argv[0] << " 14\n";
        return 1; 
    }

    int M = stoi(argv[1]); 

    srand(time(NULL));

    // Forzamos que num_tipos sea entre 2 y 5 para asegurar variedad
    int num_tipos = (rand() % 4) + 2; 
    vector<pair<int, int>> cajas;


    for (int i = 1; i < num_tipos; ++i) {
        int peso = (rand() % 9) + 2; // Pesos entre 2 y 10 kg
        int cantidad = (rand() % 5) + 1;
        cajas.push_back({peso, cantidad});
    }

    cout << "Cajas Disponibles en el Almacen \n";
    for (int i = 0; i < cajas.size(); ++i) {
        cout << "Tipo " << i << " -> Peso: " << cajas[i].first << " kg | Cantidad: " << cajas[i].second << "\n";
    }
    cout << "---------------------------------------\n\n";

    map<Estado, Solucion> m;
    int n = cajas.size();

    Solucion resultado = reparto(n - 1, M, cajas, m);

    cout << "Resultado para " << M << " kg \n";
    if (resultado.n_cajas < 0) {
        cout << "No es posible entregar exactamente " << M << " kg.\n";
    } else {
        cout << "El maximo numero de cajas es: " << resultado.n_cajas << "\n";
        cout << "Detalle del reparto óptimo:\n";
        
        for (int i = 0; i < n; ++i) {
            int cantidad_usada = resultado.desglose_cajas[i];
            if (cantidad_usada > 0) {
                cout << "- Del Tipo " << i << " (Peso: " << cajas[i].first 
                     << " kg) se utilizaron: " << cantidad_usada << " cajas.\n";
            }
        }
    }

    return 0;
}