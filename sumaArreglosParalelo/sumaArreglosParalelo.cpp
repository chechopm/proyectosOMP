// sumaArreglosParalelo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

#define N 50000
#define chunk 200
#define show 10

void printArray(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo.\n";
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 4;
        b[i] = (N - i) * (0.001 * i);
    }
    
    #pragma omp parallel for \
    shared(a, b, c, chunk) private(i) \
    schedule(static, chunk) \

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
        #pragma omp atomic
         std::cout << "El thread " << omp_get_thread_num() << " esta en marcha " << std::endl;

    
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo a: " << std::endl;
    printArray(a);
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo b: " << std::endl;
    printArray(b);
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo c: " << std::endl;
    printArray(c);
}

void printArray(float* d)
{
    for (int x = 0; x < show; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
