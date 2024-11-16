#include "threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int corrida_terminada = 0;

void *correr(void *arg) {
    Competidor *competidor = (Competidor *)arg;

    while (!corrida_terminada) {
        pthread_mutex_lock(&mutex);

        if (corrida_terminada) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        if (rand() % 100 >= competidor->chance_descanso) {
            competidor->distancia += competidor->velocidade;
            printf("%s %d correu para %d metros\n", competidor->tipo, competidor->id, competidor->distancia);
        } else {
            printf("%s %d está descansando\n", competidor->tipo, competidor->id);
        }

        if (competidor->distancia >= DISTANCIA_TOTAL) {
            corrida_terminada = 1;
            printf("\n%s %d venceu a corrida!\n", competidor->tipo, competidor->id);
        }

        pthread_mutex_unlock(&mutex);
        usleep(50000); // Simula o tempo entre os ciclos
    }

    return NULL;
}

