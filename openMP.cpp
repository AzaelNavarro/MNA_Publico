#include <omp.h>
#include <iostream>

using namespace std;

// Número total de elementos
#define N 1000

// Cantidad de valores a mostrar
#define MOSTRAR 10

void imprimirArreglo(float* arr, const char* nombre);

int main() {
    cout << "=== Suma de Arreglos en Paralelo con OpenMP ===\n\n";

    float A[N], B[N], R[N];

    // Inicialización de los arreglos
    for (int i = 0; i < N; i++) {
        A[i] = i + 1;          // 1, 2, 3, ...
        B[i] = (i + 1) * 2;    // 2, 4, 6, ...
    }

    // Definimos explícitamente 2 hilos (como el ejemplo gráfico)
    omp_set_num_threads(2);

    // FOR paralelo
    #pragma omp parallel for shared(A, B, R)
    for (int i = 0; i < N; i++) {
        int hilo = omp_get_thread_num();
        R[i] = A[i] + B[i];

        // Mostrar qué hilo procesa qué índices (solo algunos para no saturar)
        if (i < 5 || (i >= N/2 && i < N/2 + 5)) {
            #pragma omp critical
            cout << "Hilo " << hilo << " sumando indice " << i << endl;
        }
    }

    cout << "\n--- Resultados (primeros valores) ---\n";
    imprimirArreglo(A, "Arreglo A");
    imprimirArreglo(B, "Arreglo B");
    imprimirArreglo(R, "Arreglo R (A + B)");

    return 0;
}

void imprimirArreglo(float* arr, const char* nombre) {
    cout << nombre << ": ";
    for (int i = 0; i < MOSTRAR; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
