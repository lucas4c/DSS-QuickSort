#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Feito por Lucas Lopes do Nascimento 20/02/2022

int swapCounter, recursionCounter; //Variáveis globais para contar as recursões e swaps das funções. (Inicializar ambas em zero antes de realizar qualquer quicksort

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int randomNumber(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

int partitionMedianLomuto (int vector[], int low, int high) {
    int media=floor(high/2);
    int x=vector[low], y=vector[media], z=vector[high];
    int pivot = z;
    if (y>x && y<z || y>z && y<x) {
            pivot=y;
            swap(&vector[media], &vector[high]);
            swapCounter++;
    }
    else if (z>x && z<y || z>y && z<x) {
            pivot=z;
            swap(&vector[high], &vector[low]);
            swapCounter++;
    }
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (vector[j] < pivot) {
            i++;
            swap(&vector[i], &vector[j]);
            swapCounter++;
        }
    }
    swap(&vector[i + 1], &vector[high]);
    swapCounter++;
    return (i+1);
}

void quickSortMedianLomuto(int vector[], int low, int high) {
    if(low<high){
        recursionCounter++;
        int part = partitionMedianLomuto(vector, low, high);
        quickSortMedianLomuto(vector, low, part - 1);
        quickSortMedianLomuto(vector, part + 1, high);

    }
}

int partitionRandomLomuto (int vector[], int low, int high) {
    int randomIndex = randomNumber(low, high);
    int pivot = vector[randomIndex];

    swap(&vector[randomIndex], &vector[high]);
    swapCounter++;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (vector[j] < pivot) {
            i++;
            swap(&vector[i], &vector[j]);
            swapCounter++;
        }
    }
    swap(&vector[i + 1], &vector[high]);
    swapCounter++;
    return (i+1);
}

void quickSortRandomLomuto(int vector[], int low, int high) {
    if(low<high){
        recursionCounter++;
        int part = partitionRandomLomuto(vector, low, high);
        quickSortRandomLomuto(vector, low, part - 1);
        quickSortRandomLomuto(vector, part + 1, high);

    }
}

int partitionMedianHoare(int vector[], int low, int  high) {
    int media=floor(high/2);
    int x=vector[low], y=vector[media], z=vector[high];
    int pivot = x;
    if (y>x && y<z || y>z && y<x) pivot=y;
    else if (z>x && z<y || z>y && z<x) pivot=z;

    int i = low -1, j = high + 1;

    while(1) {
        do {
            i++;
        } while (vector[i] < pivot);
        do {
            j--;
        } while (vector[j] > pivot);

        if (i>=j)
            return j;
        swap(&vector[i], &vector[j]);
        swapCounter++;
    }
}

void quickSortMedianHoare(int vector[], int low, int high) {
    if(low<high) {
        recursionCounter++;
        int part = partitionMedianHoare(vector, low, high);
        quickSortMedianHoare(vector, low, part);
        quickSortMedianHoare(vector, part+1, high);
    }
}

int partitionRandomHoare(int vector[], int low, int  high) {

    int randomIndex = randomNumber(low, high);
    int pivot = vector[randomIndex];

    int i = low -1, j = high + 1;

    while(1) {
        do {
            i++;
        } while (vector[i] < pivot);
        do {
            j--;
        } while (vector[j] > pivot);

        if (i>=j)
            return j;
        swap(&vector[i], &vector[j]);
        swapCounter++;
    }
}

void quickSortRandomHoare(int vector[], int low, int high) {
    if(low<high) {
        recursionCounter++;
        int part = partitionRandomHoare(vector, low, high);
        quickSortRandomHoare(vector, low, part);
        quickSortRandomHoare(vector, part+1, high);
    }
}

void printArray(int vector[], int size) {
    int i;
    for (i=0; i<size; i++)
        printf("%d ", vector[i]);
    printf("\n");
}

int main() {
    srand(time(0));
    clock_t start, end;
    float executionTime;

    FILE *input;
    FILE *medianHoareOutput;
    FILE *medianLomutoOutput;
    FILE *randomHoareOutput;
    FILE *randomLomutoOutput;
    char *line = (char*) malloc(sizeof(char)*10000000);

    int *array1 = (int*) malloc(sizeof(int)*1000000);
    int *array2 = (int*) malloc(sizeof(int)*1000000);
    int *array3 = (int*) malloc(sizeof(int)*1000000);
    int *array4 = (int*) malloc(sizeof(int)*1000000);

    int arrayCounter, arrayNumber, arraySize;

    input = fopen("entrada2.txt", "r");
    medianHoareOutput = fopen("stats-mediana-hoare.txt", "w");
    medianLomutoOutput = fopen("stats-mediana-lomuto.txt", "w");
    randomHoareOutput = fopen("stats-aleatorio-hoare.txt", "w");
    randomLomutoOutput = fopen("stats-aleatorio-lomuto.txt", "w");

    while(fgets(line, 10000000, input)) {
        arrayNumber = strtok(line, " ");
        arraySize = atoi(arrayNumber);
        arrayCounter = 0;
        arrayNumber = strtok(NULL, " ");
        while(arrayNumber) {
            array1[arrayCounter] = atoi(arrayNumber);
            array2[arrayCounter] = atoi(arrayNumber);
            array3[arrayCounter] = atoi(arrayNumber);
            array4[arrayCounter] = atoi(arrayNumber);
            arrayCounter++;
            arrayNumber = strtok(NULL, " ");
        }
        swapCounter=0;
        recursionCounter=0;
        start = clock();
        quickSortMedianHoare(array1, 0, arraySize);
        end = clock();
        executionTime = (float) (end-start) / CLOCKS_PER_SEC;
        fprintf(medianHoareOutput, "TAMANHO ENTRADA %d\nSWAPS %d\nRECURSOES %d\nTEMPO %.8f EM SEGUNDOS\n", arraySize, swapCounter, recursionCounter, executionTime);

        swapCounter=0;
        recursionCounter=0;
        start = clock();
        quickSortMedianLomuto(array2, 0, arraySize);
        end = clock();
        executionTime = (float) (end-start) / CLOCKS_PER_SEC;
        fprintf(medianLomutoOutput, "TAMANHO ENTRADA %d\nSWAPS %d\nRECURSOES %d\nTEMPO %.8f EM SEGUNDOS\n", arraySize, swapCounter, recursionCounter, executionTime);

        swapCounter=0;
        recursionCounter=0;
        start = clock();
        quickSortRandomHoare(array3, 0, arraySize);
        end = clock();
        executionTime = (float) (end-start) / CLOCKS_PER_SEC;
        fprintf(randomHoareOutput, "TAMANHO ENTRADA %d\nSWAPS %d\nRECURSOES %d\nTEMPO %.8f EM SEGUNDOS\n", arraySize, swapCounter, recursionCounter, executionTime);

        swapCounter=0;
        recursionCounter=0;
        start = clock();
        quickSortRandomLomuto(array4, 0, arraySize);
        end = clock();
        executionTime = (float) (end-start) / CLOCKS_PER_SEC;
        fprintf(randomLomutoOutput, "TAMANHO ENTRADA %d\nSWAPS %d\nRECURSOES %d\nTEMPO %.8f EM SEGUNDOS\n", arraySize, swapCounter, recursionCounter, executionTime);
    }

    fclose(input);
    fclose(medianHoareOutput);
    fclose(medianLomutoOutput);
    fclose(randomHoareOutput);
    fclose(randomLomutoOutput);


}

