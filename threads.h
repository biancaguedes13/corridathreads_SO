#ifndef THREADS_H
#define THREADS_H

#define DISTANCIA_TOTAL 100

typedef struct {
    char *tipo;
    int id;
    int distancia;
    int velocidade;
    int chance_descanso;
} Competidor;

void *correr(void *arg);

#endif

