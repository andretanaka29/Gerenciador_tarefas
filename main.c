/*
 * main.c
 *
 *  Created on: Dec 03, 2018
 *      Author: Renan Augusto Starke
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "lista_enc.h"
#include "no.h"
#include "tarefa.h"
#include "heap.h"


int main(){

	int n_tarefas, i=0, n, x;
	lista_enc_t *lista_tarefas;
	tarefa_t **vetor;
	heap_t *heap;

	lista_tarefas = importar_csv_linkedList("dados.csv");
	imprimir_lista_tarefas(lista_tarefas);
    n_tarefas = obter_tamanho(lista_tarefas);
    vetor = lista_para_vetor(lista_tarefas, n_tarefas);
    heap = cria_heap(n_tarefas);

    for(x=0; x<10; x++)
    {
        srand(getpid() ^ time(NULL));
        for(n=0; n<5; n++)
        {
            i = rand() % n_tarefas;
            add_heap(heap, vetor[i]);
        }

        n = obter_tamanho_heap(heap);
        //imprimir_heap(heap, n);

        build_heap(heap, n);
        imprimir_heap(heap, n);
        sleep(2);

        retira_heap(heap, n);
        n = obter_tamanho_heap(heap);
        imprimir_heap(heap, n);
        sleep(3);

    }


    while(n!=0)
    {
        retira_heap(heap, n);
        n = obter_tamanho_heap(heap);
        imprimir_heap(heap, n);
        sleep(2);
    }

    retira_heap(heap, n);

	/* Liberação de memória */
    libera_lista_tarefas(lista_tarefas);
    free(vetor);
    free(heap);


	return 0;
}
