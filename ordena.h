#ifndef ORDENA_H_
#define ORDENA_H_

// Funcão do InsertionSort
void insertionSort(int *vet, long long int n);
// Função para chamar o merge recursivo
void chamaMerge(int *vet, long long int n);
// Função para intercalar o merge
void auxiliaMerge(int *vet, long long int posIni, long long int posFin, int meio, long long int n);
// Função do merge recursivo
void mergeSortRecursivo(int *vet, long long int posIni, long long int posFin, long long int n);
// Função do merge iterativo
// Função do RadixSort
void radixSort(int *a, int n, int d);

#endif