#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <vector>
#include "ordena.h"
#include <cmath>

using namespace std;

// exemplo 1
int main()
{

  int tam_instancia = 10000;

  clock_t t;

  for (int i = 0; i < 20; i++)
  {
    FILE *arq;
    char filename[20];
    sprintf(filename, "%d.txt", i + 1);

    arq = fopen(filename, "w"); // Cria um arquivo texto para gravação
    int num;
    for (int j = 1; j <= tam_instancia; j++)
    {
      num = rand() % tam_instancia; /* gerando valores aleatórios entre zero e n */
      fprintf(arq, "%d", num);
      fprintf(arq, "\n");
    }
    if (arq != NULL)
    {
      fclose(arq);
    }
    else
    {
      perror(filename);
      exit(EXIT_FAILURE);
    }
  }
  FILE *arqres;
  char filenameres[50];
  
  arqres = fopen(filenameres, "w");
  sprintf(filenameres, "resultado %d.txt", tam_instancia);
  arqres = fopen(filenameres, "w"); // Cria um arquivo texto para gravação do resultado

  for (int i = 1; i <= 20; i++)
  {

    vector<int> instancias;

    char filename[20];
    sprintf(filename, "%d.txt", i);
    ifstream input(filename);

    if (!input.is_open())
    {
      cerr << "Arquivo nao encontrado.\n";
      exit(2);
    }
    int ler;
    while (input >> ler)
    {
      instancias.push_back(ler);
    }
    int *vet = &instancias[0];

    int nDig = 3;

    fprintf(arqres, "Arquivo: %d", i);
    fprintf(arqres, "\n");

    t = clock();
    insertionSort(vet, instancias.size());
    t = clock() - t;
    fprintf(arqres, "tempo insertionSort: %lu", t);
    fprintf(arqres, "\n");


    //cout << "tempo insertionSort:" << t << "ms" << endl
    //     << endl;

    t = clock();
    radixSort(vet, instancias.size(), nDig);
    t = clock() - t;
    fprintf(arqres, "tempo radixSort: %lu", t);
    fprintf(arqres, "\n");
    // cout << "tempo radixSort:" << t << "ms" << endl
    //      << endl;

    t = clock();
    chamaMerge(vet, instancias.size());
    t = clock() - t;
    fprintf(arqres, "tempo chamaMerge: %lu", t);
    fprintf(arqres, "\n");

    // for (int i = 0; i < instancias.size(); ++i)
    // {
    //  cout << vet[i] << " ";
    // }
  }
  fclose(arqres);
  return 0;
}

void chamaMerge(int *vet, long long int n)
{ // Função para chamada do merge recursivo

  mergeSortRecursivo(vet, 0, n - 1, n);
  //std::cout << "- - Merge Recursivo.: " << cp << " | " <<  movim << " | ";
  // codigo reaproveitado de Estrutura de Dados I - mostrando numero de comparações e de movimentações do codigo
}

void mergeSortRecursivo(int *vet, long long int posIni, long long int posFin, long long int n)
{ // Função do merge recursivo
  int meio;
  if (posIni < posFin)
  {
    meio = (posIni + posFin) / 2;
    mergeSortRecursivo(vet, posIni, meio, n);
    mergeSortRecursivo(vet, meio + 1, posFin, n);
    auxiliaMerge(vet, posIni, posFin, meio, n);
  }
}

void auxiliaMerge(int *vet, long long int posIni, long long int posFin, int meio, long long int n)
{ // Função para intercalar os valores do vetor no merge
  int posLivre, inVetor1, inVetor2, i;
  int aux[n];

  inVetor1 = posIni;
  inVetor2 = meio + 1;
  posLivre = posIni;

  while (inVetor1 <= meio && inVetor2 <= posFin)
  {
    //cp++;
    if (vet[inVetor1] <= vet[inVetor2])
    {
      aux[posLivre] = vet[inVetor1];
      //movim++;
      inVetor1++;
    }
    else
    {
      aux[posLivre] = vet[inVetor2];
      inVetor2++;
    }
    posLivre++;
  }

  for (int i = inVetor1; i <= meio; ++i)
  {
    aux[posLivre] = vet[i];
    posLivre++;
  }

  for (int i = inVetor2; i <= posFin; ++i)
  {
    aux[posLivre] = vet[i];
    posLivre++;
  }

  for (int i = posIni; i <= posFin; ++i)
  {
    vet[i] = aux[i];
  }
}

void insertionSort(int *vet, long long int n)
{ // Função do insertionSort
  long long int i, j, aux;
  for (i = n - 2; i >= 0; i--)
  {
    aux = vet[i];
    j = i + 1;
    while (aux > vet[j])
    {
      vet[j - 1] = vet[j];
      j++;
    }
    vet[j - 1] = aux;
  }
}

void radixSort(int *vet, int n, int d)
{ // Função do radixSort
  int movi = 0, cmp = 0;
  int *aux = new int[n];

  for (int div = 1; div < pow(10, d); div *= 10)
  {                  // O radix usa um metodo de ordenação estável como suporte para realizar a ordenação de um vetor
    int c[10] = {0}; // vetor para utilização do coutingSort

    for (int i = 0; i < n; i++)
    {
      c[(vet[i] / div) % 10]++;
    }

    for (int i = 1; i < 10; i++)
    {
      c[i] = c[i] + c[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
      aux[c[(vet[i] / div) % 10] - 1] = vet[i];
      c[(vet[i] / div) % 10]--;
    }

    for (int i = 0; i < n; i++)
    {
      vet[i] = aux[i];
    }
  }

  delete[] aux;
}