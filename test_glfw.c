#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep
#include <signal.h>

typedef struct {
    int xposmw;
    int yposmw;
    pthread_mutex_t data_mutex; // Mutex for protecting shared data
    int running; // Flag to indicate if threads should continue running
} t_sz;

typedef struct {
    t_sz *map_data;
    int pipe_index;
} t_pipe_thread_data;

void *pipe_writer(void *arg) {
    t_pipe_thread_data *data = (t_pipe_thread_data *)arg;

    while (data->map_data->running) {
        // Lock the mutex to read the shared data
        pthread_mutex_lock(&data->map_data->data_mutex);

        // Simulate reading from the map_data (replace this with your actual logic)
        int xpos = data->map_data->xposmw;
        int ypos = data->map_data->yposmw;

        // Unlock the mutex after reading
        pthread_mutex_unlock(&data->map_data->data_mutex);

        // Simulate some work
        printf("Pipe %d: Reading position (%d, %d)\n", data->pipe_index, xpos, ypos);
        sleep(1); // Simulate work by sleeping
    }

    return NULL;
}

void cleanup_threads(t_sz *map_data) {
    // Signal the threads to stop
    pthread_mutex_lock(&map_data->data_mutex);
    map_data->running = 0; // Set the running flag to false
    pthread_mutex_unlock(&map_data->data_mutex);
}

int pipe_data_multithreaded(t_sz *map_data) {
    pthread_t threads[4];
    t_pipe_thread_data *thread_data;
    int i;

    // Initialize the mutex for the shared data
    pthread_mutex_init(&map_data->data_mutex, NULL);
    map_data->running = 1; // Set the running flag to true

    thread_data = malloc(sizeof(t_pipe_thread_data) * 4);
    if (!thread_data) {
        perror("Failed to allocate memory for thread data");
        return EXIT_FAILURE;
    }

    for (i = 0; i < 4; i++) {
        thread_data[i].map_data = map_data;
        thread_data[i].pipe_index = i;
        if (pthread_create(&threads[i], NULL, pipe_writer, &thread_data[i]) != 0) {
            perror("Failed to create thread");
            free(thread_data);
            return EXIT_FAILURE;
        }

        // Detach the thread to run independently
        pthread_detach(threads[i]);
    }

    // Main thread can perform other tasks here without blocking
    // Example: Simulate changing values in map_data
    for (int j = 0; j < 10; j++) {
        // Lock the mutex to modify the shared data
        pthread_mutex_lock(&map_data->data_mutex);

        // Simulate modifying the shared data
        map_data->xposmw += 1; // Example modification
        map_data->yposmw += 1;

        // Unlock the mutex after modifying
        pthread_mutex_unlock(&map_data->data_mutex);

        // Simulate doing other work in the main thread
        printf("Main thread: Modified position to (%d, %d)\n", map_data->xposmw, map_data->yposmw);
        sleep(1); // Simulate work by sleeping
    }

    // Cleanup before exiting
    cleanup_threads(map_data); // Signal the threads to stop

    // Free allocated memory
    free(thread_data);
    pthread_mutex_destroy(&map_data->data_mutex);
    return EXIT_SUCCESS;
}

int main() {
    t_sz map_data;
    return pipe_data_multithreaded(&map_data);
}
