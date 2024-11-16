#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "threads.h"

#define NUM_LEBRES 2
#define NUM_TARTARUGAS 2

int main() {
    srand(time(NULL));

    int total_competidores = NUM_LEBRES + NUM_TARTARUGAS;
    Competidor competidores[total_competidores];
    pthread_t threads[total_competidores];

    // Inicializa lebres
    for (int i = 0; i < NUM_LEBRES; i++) {
        competidores[i].tipo = "Lebre";
        competidores[i].id = i + 1;
        competidores[i].posicao = 0;
        competidores[i].velocidade = 3;
        competidores[i].chance_descanso = 50; 
    }

    // Inicializa tartarugas
    for (int i = 0; i < NUM_TARTARUGAS; i++) {
        competidores[NUM_LEBRES + i].tipo = "Tartaruga";
        competidores[NUM_LEBRES + i].id = i + 1;
        competidores[NUM_LEBRES + i].posicao = 0;
        competidores[NUM_LEBRES + i].velocidade = 1;
        competidores[NUM_LEBRES + i].chance_descanso = 0; 
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
