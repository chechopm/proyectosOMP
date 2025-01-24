// sumaArreglosParalelo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

// importación de librerías
#include <iostream>

// Se realiza una validación para corroborar si se utiliza omp
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

// Se definen las 3 variables que se podrían cambiar para precensiar diferentes escenarios
#define N 10000          // Hace referencia a la cantidad de ekementos en cada array 
#define chunk 1000      // Es el tamaño de los pedazos de arreglo que procesará cada hilo
#define show 10          // Es el número de registros que se imprimirán por arreglo

// Declaración de función que permitirá la impresión de <<show>> número de elementos de
// cada arreglo 
void printArray(float* d);

// Función principal que permite sumar dos arreglos por medio de paralelismo, mediante omp
// se ejecutan una cantidad de hilos que procesará (sumará) una candidad determinada de 
// elementos en paralelo.
int main()
{
    // Primero se establecen los arreglos que se quieren sumar
    std::cout << "Sumando Arreglos en Paralelo.\n";
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 4;
        b[i] = (N - i) * (0.001 * i);
    }

    int chunk_omp = chunk;

    // Se imprime un mensaje cuando el OMP este disponible
    # ifdef _OPENMP
        std::cout << "OMP disponible y funcionando" << std::endl;
    # endif
    
    // Se instancia el for paralelo para sumar los dos arreglos y colocar el resultado en
    // un arreglo C
    #pragma omp parallel for \
    shared(a, b, c, chunk_omp) private(i) \
    schedule(static, chunk_omp) \

    // El for que se ejecutará en paralelo.
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    
    // Finalmente se imprimen los 3 arreglos, sólo se imprimen <<show>> cantidad de registros.
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo a: " << std::endl;
    printArray(a);
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo b: " << std::endl;
    printArray(b);
    std::cout << "Imprimiendo los primeros " << show << " valores del arreglo c: " << std::endl;
    printArray(c);
}

// Función que permite realizar la impresión de <<show>> números de registros
// Se crea está función debido a que es un proceso repetitivo.
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
