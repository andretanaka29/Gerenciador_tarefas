/*
 * tarefa.h
 *
 *  Created on: Dec 03, 2018
 *      Author: Renan Augusto Starke
 */

#ifndef TAREFAS_TAREFA_H_
#define TAREFAS_TAREFA_H_

#include "lista_enc.h"

typedef struct tarefas tarefa_t;

void vetor_para_lista(lista_enc_t *lista, tarefa_t **vetor);
tarefa_t **lista_para_vetor(lista_enc_t *lista, int n);

void imprimir_vetor(tarefa_t **vetor, int tam);
//------------------------------------

lista_enc_t * importar_csv_linkedList(char *nome);

tarefa_t *cria_tarefa(int id, int C, int T);

int tarefa_obter_id (tarefa_t *tarefa);
int tarefa_obter_C (tarefa_t *tarefa);
int tarefa_obter_T (tarefa_t *tarefa);
float tarefa_obter_U (tarefa_t *tarefa);

void libera_lista_tarefas(lista_enc_t *lista);
void imprimir_lista_tarefas(lista_enc_t *lista);

#endif /* TAREFAS_TAREFA_H_ */
