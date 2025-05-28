#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Shared data
int buffer = 0;
int ready = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

// Producer thread - produces data
void* producer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sleep(1); // Simulate work
        
        pthread_mutex_lock(&mutex);
        
        buffer = i * 10;
        ready = 1;
        printf("Producer: Created item %d\n", buffer);
        
        // Signal waiting consumer
        pthread_cond_signal(&condition);
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Consumer thread - consumes data
void* consumer(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        
        // Wait until data is ready
        while (!ready) {
            printf("Consumer: Waiting for data...\n");
            pthread_cond_wait(&condition, &mutex);
        }
        
        printf("Consumer: Got item %d\n", buffer);
        ready = 0; // Mark as consumed
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Simple example showing the basic pattern
void simple_example() {
    printf("=== Simple Producer-Consumer Example ===\n");
    
    pthread_t prod_thread, cons_thread;
    
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_create(&prod_thread, NULL, producer, NULL);
    
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
}

// Example 2: Multiple waiters
int counter = 0;
int target = 10;

void* waiter(void* arg) {
    int id = *(int*)arg;
    
    pthread_mutex_lock(&mutex);
    
    while (counter < target) {
        printf("Waiter %d: Counter is %d, waiting for %d...\n", 
               id, counter, target);
        pthread_cond_wait(&condition, &mutex);
    }
    
    printf("Waiter %d: Target reached! Counter = %d\n", id, counter);
    
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* incrementer(void* arg) {
    for (int i = 0; i < 15; i++) {
        usleep(500000); // 0.5 seconds
        
        pthread_mutex_lock(&mutex);
        counter++;
        printf("Incrementer: Counter = %d\n", counter);
        
        if (counter >= target) {
            printf("Incrementer: Broadcasting to all waiters!\n");
            pthread_cond_broadcast(&condition); // Wake ALL waiters
        }
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void multiple_waiters_example() {
    printf("\n=== Multiple Waiters Example ===\n");
    
    counter = 0; // Reset counter
    pthread_t waiters[3], inc_thread;
    int ids[] = {1, 2, 3};
    
    // Create multiple waiting threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&waiters[i], NULL, waiter, &ids[i]);
    }
    
    // Create incrementer thread
    pthread_create(&inc_thread, NULL, incrementer, NULL);
    
    // Wait for all threads
    for (int i = 0; i < 3; i++) {
        pthread_join(waiters[i], NULL);
    }
    pthread_join(inc_thread, NULL);
}

int main() {
    printf("CONDITION VARIABLES EXPLAINED:\n");
    printf("- Allow threads to wait for specific conditions\n");
    printf("- Must be used with a mutex\n");
    printf("- pthread_cond_wait() releases mutex and waits\n");
    printf("- pthread_cond_signal() wakes one waiting thread\n");
    printf("- pthread_cond_broadcast() wakes ALL waiting threads\n\n");
    
    simple_example();
    multiple_waiters_example();
    
    printf("\nKEY POINTS:\n");
    printf("1. Always use while loop, not if, when checking condition\n");
    printf("2. Condition variables prevent busy waiting (polling)\n");
    printf("3. Much more efficient than checking flags in loops\n");
    
    return 0;
}