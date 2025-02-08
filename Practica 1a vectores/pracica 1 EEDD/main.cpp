#include <iostream>
#include "VDinamico.h"
#include <cstdlib>

/**
 * @author Carlota Calderón Suárez ccs00064@red.ujaen.es
 * @author Lucía Masats Aroza lma00072@red.ujaen.es
 */

int main() {
    try {

        srand(time(0)); // Para obtener una secuencia diferente de números aleatorios en cada ejecución:
        // Al inicializar la semilla con el tiempo actual (time(0)), la secuencia cambiará cada vez que ejecutes el programa.

        VDinamico<int> v(100000);

        //Genera numeros aleatorios entre 0 y 99999999 y los guarda en el vector
        for (int i = 0; i < 100000; ++i) {
            int random = rand() % 100000000;
            v[i] = random;
        }

        //std::cout << v[203893379736]; //Para probar la excepcion por fuera de rango

        std::cout<<std::endl<<"Estos son los doscientos primeros numeros generadoss aleatoriamente : "<<std::endl;
        for (int i = 0; i < 200; ++i) {
            std::cout << v[i] << ", ";
        }

        std::cout << std::endl<<std::endl<<"Ordenados de menor a mayor mediente sort : "<<std::endl;
        v.ordenar();
        for (int i = 0; i < 200; ++i) {
            std::cout << v[i] << ", ";
        }

        std::cout << std::endl<<std::endl<<"Ordenados de menor a mayor mediente el metodo burbuja : "<<std::endl;
        v.ordenaBurbuja();
        for (int i = 0; i < 200; ++i) {
            std::cout << v[i] << ", ";
        }
    } catch (const std::exception& e){
        std::cout << e.what();
    }
    return 0;
}

