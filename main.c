#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "threads.h"

#define NUM_COELHOS 2
#define NUM_TARTARUGAS 2

int main() {
    srand(time(NULL));

    int total_competidores = NUM_COELHOS + NUM_TARTARUGAS;
    Competidor competidores[total_competidores];
    pthread_t threads[total_competidores];

    // Inicializa coelhos
    for (int i = 0; i < NUM_COELHOS; i++) {
        competidores[i] = (Competidor){"Coelho", i + 1, 0, 3, 50}; // 50% chance de descansar
    }

    // Inicializa tartarugas
    for (int i = 0; i < NUM_TARTARUGAS; i++) {
        competidores[NUM_COELHOS + i] = (Competidor){"Tartaruga", i + 1, 0, 1, 0}; // Nunca descansa
    }

    // Cria threads
    for (int i = 0; i < total_competidores; i++) {
        pthread_create(&threads[i], NULL, correr, &competidores[i]);
    }

    // Aguarda todas as threads finalizarem
    for (int i = 0; i < total_competidores; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
