#include <stdio.h>              // Funções de entrada e saída
#include <pthread.h>            // Threads e Mutex

#ifdef _WIN32                   // Biblioteca para rodar no Windows
    #include <windows.h>        
    #define SLEEP_MS(ms) Sleep(ms)
#else                           // Biblioteca para rodar no Linux
    #include <unistd.h>         
    #define SLEEP_MS(ms) sleep((ms) / 1000)
#endif

pthread_mutex_t garfo[5];       // Um Mutex para cada garfo

void *filosofo(void *arg) {     // Função executada por cada filósofo
    int id = *(int *)arg;       // Obtém o número do filósofo

    int a = id;                 // Primeiro garfo
    int b = (id + 1) % 5;       // Segundo garfo

    if (a > b) {                // Verifica qual garfo possui menor número
        int temp = a;            // Guarda temporariamente o primeiro
        a = b;                  // Coloca o menor em a
        b = temp;               // Coloca o maior em b
    }

    pthread_mutex_lock(&garfo[a]); // Pega primeiro o menor garfo
    pthread_mutex_lock(&garfo[b]); // Depois pega o maior garfo

    printf("Filosofo %d esta comendo\n", id);

    SLEEP_MS(1000);  // Simula o tempo de 1 segundo para as threads pegas os "garfos".

    pthread_mutex_unlock(&garfo[b]); // Libera o maior garfo
    pthread_mutex_unlock(&garfo[a]); // Libera o menor garfo

    return NULL;                // Finaliza a thread
}

int main() {
    pthread_t threads[5];       // Cria 5 threads
    int id[5];                  // IDs dos filósofos

    for (int i = 0; i < 5; i++)
        pthread_mutex_init(&garfo[i], NULL); // Inicializa os Mutexes

    for(int i = 0; i < 5; i++) { // Quantidade de Rodadas  

        printf("\nRodada %d\n \n", i + 1); // Rodada atual

        for (int j = 0; j < 5; j++) {
            id[j] = j;              // Define o ID dos filósofos
            pthread_create(&threads[j], NULL, filosofo, &id[j]); // Cria thread
        }
        
        for (int j = 0; j < 5; j++) {
            pthread_join(threads[j], NULL); // Espera as threads terminarem
        }
            
    }

    return 0;                   // Finaliza o programa
}
