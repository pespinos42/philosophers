#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int variable_compartida = 100;

void* hilo_incremento(void* arg) {
    int i;
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        variable_compartida++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* hilo_decremento(void* arg) {
    int i;
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        variable_compartida--;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    int i;
    pthread_t hilos[4];

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < 4; i++) {
		if (i % 2 == 0)
        	pthread_create(&hilos[i], NULL, hilo_incremento, NULL);
		else
			pthread_create(&hilos[i], NULL, hilo_decremento, NULL);
    }

    for (i = 0; i < 4; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("El valor de la variable compartida es %d\n", variable_compartida);

    pthread_mutex_destroy(&mutex);

    return 0;
}