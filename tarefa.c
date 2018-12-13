/*
 * tarefa.c
 *
 *  Created on: Dec 03, 2018
 *      Author: Renan Augusto Starke
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tarefa.h"
#include "lista_enc.h"
#include "no.h"

#define CUTOFF 2

struct tarefas {
	int id;     /*!< Identificador numérico da tarefa. */
	int C;      /*!< Tempo de computação da tarefa. */
	int T;      /*!< Período da tarefa. */
	float U;    /*!< Utilização, razão C/T, da tarefa. */
};


/**
  * @brief  Cria um vetor de ponteiros do tipo tarefa baseando-se nos dados de uma lista encadeada.
  * @param	lista: referência de uma lista encadeada.
  * @param	n: tamanho do vetor.
  *
  * @retval tarefa_t**: vetor de ponteiros com todas as tarefas contidas na lista.
  */
tarefa_t **lista_para_vetor(lista_enc_t *lista, int n){
    int i;
    no_t *no;

    tarefa_t **vetor = malloc(sizeof(tarefa_t *) * n);

    if (!vetor)
    {
    	perror("vetor:");
    	exit(EXIT_FAILURE);
    }

    no = obter_cabeca(lista);

    for(i=0; i<n; i++)
    {
        vetor[i]= obter_dado(no);
        no = obter_proximo(no);
    }

    return vetor;
}

/**
  * @brief  Substitui as referências dos dados da lista para os do vetor.
  * @param	lista: referência de uma lista encadeada.
  * @param  vetor: vetor com as referência dos novos dados.
  *
  * @retval Nenhum.
  */
void vetor_para_lista(lista_enc_t *lista, tarefa_t **vetor){

    int i = 0;
    no_t *no;

    no = obter_cabeca(lista);

    while(!no)
    {
        alterar_dados(no, vetor[i++]);
        obter_proximo(no);
    }
}

/*************************************************************/



/**
  * @brief  Importa os dados de um arquivo CSV.
  * @param	nome_arquivo: nome do arquivo para importar.
  *
  * @retval lista_enc_t *: lista encadeada com todas as tarefas do arquivo.
  */
lista_enc_t * importar_csv_linkedList(char *nome_arquivo){

	char buffer[32];
	FILE *fp = fopen(nome_arquivo, "r");
	int id, C, T;
	int linha = 2;

	if (!fp){
		perror("importar_csv");
		exit(-1);
	}

	lista_enc_t *lista_tarefas = cria_lista_enc();

	if (!lista_tarefas){
		perror("importar_csv");
		fclose(fp);
		exit(-1);
	}

	/* Ignora linha da cabecalho */
	fgets(buffer, 32, fp);

	while (fgets(buffer, 32, fp) != NULL){

		int ret = sscanf(buffer, "T%d;%d;%d", &id, &C, &T);

		if (ret != 3){
			fprintf(stderr, "Erro lendo %s em linha %d\n", nome_arquivo, linha);
		}

#ifdef DEBUG
		printf("id: %d\n", id);
#endif

		tarefa_t *tarefa = cria_tarefa(id,C,T);
		no_t *no = cria_no(tarefa);

		add_cauda(lista_tarefas, no);
		linha++;
	}

	fclose(fp);

	return lista_tarefas;
}

/**
  * @brief  Cria uma nova tarefa.
  * @param	id: identificador.
  * @param  C: tempo de computação.
  * @param  T: período
  *
  * @retval tarefa_t *: nova tarefa criada dinamicamente.
  */
tarefa_t *cria_tarefa(int id, int C, int T){

	tarefa_t *tarefa = malloc(sizeof(tarefa_t));

	if (!tarefa){
		perror("cria_tarefa");
		exit(-1);
	}

	tarefa->id  = id;
	tarefa->C = C;
	tarefa->T = T;
	tarefa->U = (float)C/T;

	return tarefa;
}

/**
  * @brief  Retorna o identificador da tarefa.
  * @param	tarefa: referência da tarefa em questão.

  * @retval int: identificador.
  */
int tarefa_obter_id (tarefa_t *tarefa){
	return tarefa->id;
}

/**
  * @brief  Retorna o tempo de computação da tarefa.
  * @param	tarefa: referência da tarefa em questão.

  * @retval int: tempo de computação.
  */
int tarefa_obter_C (tarefa_t *tarefa){
	return tarefa->C;
}

/**
  * @brief  Retorna o período da tarefa.
  * @param	tarefa: referência da tarefa em questão.

  * @retval int: período.
  */
int tarefa_obter_T (tarefa_t *tarefa){
	return tarefa->T;
}

/**
  * @brief  Retorna a utilização da tarefa.
  * @param	tarefa: referência da tarefa em questão.

  * @retval float: utilização.
  */
float tarefa_obter_U (tarefa_t *tarefa){
	return tarefa->U;
}

/**
  * @brief  Libera uma lista encadeada de tarefas.
  * @param	lista: referência da lista de tarefas.

  * @retval Nenhum.
  */
void libera_lista_tarefas(lista_enc_t *lista){

	no_t *no = obter_cabeca(lista);

	while (no){
		tarefa_t *tarefa = obter_dado(no);
		free(tarefa);

		no_t *prox = obter_proximo(no);
		free(no);

		no = prox;
	}
	free(lista);
}

/**
  * @brief  Imprime os dados das tarefas em uma lista encadeada.
  * @param	lista: referência da lista de tarefas.

  * @retval Nenhum.
  */
void imprimir_lista_tarefas(lista_enc_t *lista){

	no_t *no;
	puts("----- lista enc -----------");
	printf("[id]\t[C]\t[T]\t[U]\n");

	no= obter_cabeca(lista);
	while (no){

		tarefa_t *tarefa = obter_dado(no);

		printf("%d\t%d\t%d\t%f\n", tarefa_obter_id(tarefa),
				tarefa_obter_C(tarefa), tarefa_obter_T(tarefa),
				tarefa_obter_U(tarefa));


		no = obter_proximo(no);
	}
	puts("-----------------");
}

/**
  * @brief  Imprime os dados das tarefas contidos em um vetor.
  * @param	vetor: referência do vetor de tarefas.
  * @param  tam: tamnho do vetor.
  *
  * @retval Nenhum.
  */
void imprimir_vetor(tarefa_t **vetor, int tam) {
	int i;

	puts("----- vetor -----------");
	printf("Tarefas no vetor de ponteiros: %d\n[id]\t[C]\t[T]\t[U]\n", tam);
	for (i=0; i < tam; i++)
		printf("%d\t%d\t%d\t%f\n", tarefa_obter_id(vetor[i]),
				tarefa_obter_C(vetor[i]),
				tarefa_obter_T(vetor[i]),
				tarefa_obter_U(vetor[i]));
	puts("----------------");
}
