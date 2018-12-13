#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "tarefa.h"


struct heap {
	void **vetor;
	int total;
	int tam;
};

/**
  * @brief  Cria a estrutura de heap.
  * @param	n: tamanho do vetor de tarefas.
  *
  * @retval Estrutura de heap.
  */
heap_t * cria_heap(int n){

    heap_t *h = malloc (sizeof(heap_t));

    if (!h)
    {
    	perror("heap:");
    	exit(EXIT_FAILURE);
    }

    h->total = n;
    h->tam = 0;
    h->vetor = malloc(sizeof(void *)*n);

    return h;
}

/**
  * @brief  Adiciona um ponteiro de tarefa ao heap.
  * @param	heap: estrutura de heap.
  * @param  ptr: endereço da tarefa adicionada.
  *
  * @retval Nenhum.
  */
void add_heap(heap_t *h, void * ptr){

    int tamanho = h->tam;
    int max = h->total;

    if(tamanho+1 == max)
    {
        max = max*2;
        h->vetor = realloc(h->vetor, sizeof(void *)*max);
        h->total = max;
    }
    if (tamanho < max){
        h->vetor[h->tam] = ptr;
        h->tam++;
    }
}

/**
  * @brief  retira o primeiro item do heap.
  * @param	heap: estrutura de heap.
  * @param  tam: tamanho do heap.
  *
  * @retval Nenhum.
  */
void retira_heap(heap_t *h, int tam)
{
    int max = h->total;

    if(tam == 0)
    {
        fprintf(stderr, "\n\tNao ha tarefas no heap!\n");
    }

    if(tam == max/2)
    {
        h->vetor = realloc(h->vetor, sizeof(void *)*tam);
        h->total = tam;
    }

    printf("\nTarefa %d executada: U = %f\n\n", tarefa_obter_id(h->vetor[0]), tarefa_obter_U(h->vetor[0]));
    h->vetor[0] = h->vetor[tam-1];
    h->tam--;
    tam = h->tam;
    build_heap(h, tam);
}

/**
  * @brief  Imprime os dados das tarefas contidos no heap.
  * @param	heap: estrutura de heap.
  * @param  tam: tamanho do heap.
  *
  * @retval Nenhum.
  */
void imprimir_heap(heap_t *h, int tam){

	int i;

	puts("----- heap -----------");
	printf("Tarefas no heap de ponteiros: %d\n[id]\t[C]\t[T]\t[U]\n", tam);
	for (i=0; i < tam; i++)
		printf("%d\t%d\t%d\t%f\n", tarefa_obter_id(h->vetor[i]),
				tarefa_obter_C(h->vetor[i]),
				tarefa_obter_T(h->vetor[i]),
				tarefa_obter_U(h->vetor[i]));
	puts("----------------");
}

/**
  * @brief  Faz a comparação das tarefas para achar a de maior valor.
  * @param	heap: estrutura de heap.
  * @param  i: inicio do vetor.
  * @param  k: tamanho do vetor.
  *
  * @retval Nenhum.
  */
void max_heapfy(heap_t *h, int i, int k)
{
    tarefa_t *aux;
    int j = i*2+1;

    aux = h->vetor[i];

    while (j <= k)
    {
        if(j < k)
        {
            if(tarefa_obter_U(h->vetor[j]) < tarefa_obter_U(h->vetor[j+1]))
                j++;
        }
        if(tarefa_obter_U(h->vetor[i]) < tarefa_obter_U(h->vetor[j]))
        {
            h -> vetor[i] = h -> vetor[j];
            i = j;
            j = 2*i +1;
        }
        else
            j = k+1;
        h -> vetor[i] = aux;
    }
}

/**
  * @brief  Organiza o vetor de tarefas em forma de heap.
  * @param	heap: estrutura de heap.
  * @param  tam: tamanho do heap.
  *
  * @retval Nenhum.
  */
void build_heap(heap_t *h, int n)
{
    int i = 0;

    for(i = (n-1)/2; i>=0; i--)
    {
        max_heapfy(h, i, n-1);
    }
}

/**
  * @brief  Obtém o valor máximo d alocado para o vetor.
  * @param	heap: estrutura de heap.
  *
  * @retval Valor máximo do vetor no heap.
  */
int obter_total_heap(heap_t *h)
{
    return h->total;
}

/**
  * @brief  Obtém o tamanho atual do vetor.
  * @param	heap: estrutura de heap.
  *
  * @retval Tamanho do vetor no heap.
  */
int obter_tamanho_heap(heap_t *h)
{
    return h->tam;
}
