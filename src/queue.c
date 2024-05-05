#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
        /* TODO: put a new process to queue [q] */
        if (q == NULL || proc == NULL || q->size == MAX_QUEUE_SIZE) {
        // Handle invalid input or full queue
        return;
    }

    // Add the new process to the end of the queue
    q->proc[q->size] = proc;
    q->size++;
}

struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
         if (q == NULL || q->size == 0) {
        // Handle empty queue or invalid input
        return NULL;
    }

    // Get the process from the front of the queue
    struct pcb_t *proc = q->proc[0];

    // Shift all elements to the left
    for (int i = 0; i < q->size - 1; i++) {
        q->proc[i] = q->proc[i + 1];
    }

    // Decrease the size of the queue
    q->size--;

    return proc;
	// return NULL;
}

