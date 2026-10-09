#include <stdio.h>              // Funções de entrada e saída
#include <pthread.h>            // Threads e Mutex
#include <stdlib.h>              // Função _Exit()

#ifdef _WIN32   // Bibliotecas se for rodar no Sistema Windows.
    #include <windows.h>       
    #define SLEEP_MS(ms) Sleep(ms)
#else           // Bibliotecas se for rodar no Sistema Linux.
    #include <unistd.h>         // Biblioteca POSIX para Linux
    #include <signal.h>         // signal() e SIGALRM para Linux
    #define SLEEP_MS(ms) sleep((ms) / 1000)
#endif

/*-------------------------------------------------------------*/



pthread_mutex_t garfo[5];       // Cria um Mutex para cada garfo

void encerrar(){
    printf("Encerrando o programa intencionalmente\n");
    _Exit(0);
}

#ifdef _WIN32
void *encerrar_temporizado(void *arg) {
    Sleep(7000);                // Espera 7 segundos no Windows
    encerrar();
    return NULL;
}
#endif

void *filosofo(void *arg) {     // Função executada por cada filósofo
    int id = *(int *)arg;       // Obtém o número do filósofo

    int esquerdo = id;          // Define o garfo da esquerda
    int direito = (id + 1) % 5; // Define o garfo da direita

    pthread_mutex_lock(&garfo[esquerdo]); // Pega o primeiro garfo

    printf("Filosofo %d pegou o garfo %d\n", id, esquerdo);

    SLEEP_MS(3000);   // Pausa de 3 segundos

    pthread_mutex_lock(&garfo[direito]);  // Tenta pegar o segundo garfo

    printf("Filosofo %d esta comendo\n", id);

    pthread_mutex_unlock(&garfo[direito]); // Libera o segundo garfo
    pthread_mutex_unlock(&garfo[esquerdo]); // Libera o primeiro garfo

    return NULL;                // Finaliza a thread
}

int main() {
    pthread_t threads[5];       // Cria 5 threads
    int id[5];                  // Guarda o ID de cada filósofo

#ifdef _WIN32
    pthread_t timer_thread;
    pthread_create(&timer_thread, NULL, encerrar_temporizado, NULL); 
#else
    signal(SIGALRM, encerrar); 
    alarm(7);
#endif

    for (int i = 0; i < 5; i++)
        pthread_mutex_init(&garfo[i], NULL); // Inicializa os Mutexes

    for (int i = 0; i < 5; i++) {
        id[i] = i;              // Define o ID do filósofo
        pthread_create(&threads[i], NULL, filosofo, &id[i]); // Cria a thread
    }

    for (int i = 0; i < 5; i++)
        pthread_join(threads[i], NULL); // Espera cada filósofo terminar

    return 0;                   // Finaliza o programa
}