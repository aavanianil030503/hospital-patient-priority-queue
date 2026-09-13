#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[20];
    int priority;
    int order;
} Patient;

Patient heap[MAX];
int size = 0;
int arrivalOrder = 0;

int isHigherPriority(Patient a, Patient b) {
    if (a.priority != b.priority)
        return a.priority < b.priority;
    return a.order < b.order;
}

void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void addPatient(char name[], int priority) {
    Patient p;
    strcpy(p.name, name);
    p.priority = priority;
    p.order = arrivalOrder++;

    int i = size;
    heap[size++] = p;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (isHigherPriority(heap[i], heap[parent])) {
            swap(&heap[i], &heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

void treatNext() {
    if (size == 0) {
        printf("No patients waiting.\n");
        return;
    }

    printf("Treating: %s (Priority %d)\n",
           heap[0].name, heap[0].priority);

    heap[0] = heap[size - 1];
    size--;

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size &&
            isHigherPriority(heap[left], heap[smallest]))
            smallest = left;

        if (right < size &&
            isHigherPriority(heap[right], heap[smallest]))
            smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

int main() {
    addPatient("P1", 3);
    addPatient("P2", 1);
    addPatient("P3", 2);
    addPatient("P4", 1);
    addPatient("P5", 3);
    addPatient("P6", 2);

    printf("First 3 patients:\n");

    treatNext();
    treatNext();
    treatNext();

    addPatient("P7", 1);

    printf("\nAfter P7 arrives:\n");

    while (size > 0)
        treatNext();

    return 0;
}
