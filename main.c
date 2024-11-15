#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DISTANCIA_TOTAL 100
#define NUM_COELHOS 2
#define NUM_TARTARUGAS 2

pthread_mutex_t mutex;
int corrida_terminada = 0;

typedef struct {
    char *tipo;
    int id;
    int distancia;
    int velocidade;
    int descanso;
} Competidor;

void *correr(void *arg) {
    Competidor *competidor = (Competidor *)arg;

    while (!corrida_terminada) {
        pthread_mutex_lock(&mutex);

        if (corrida_terminada) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        if (rand() % 100 >= competidor->descanso) {
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
