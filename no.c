#include <stdio.h>
#include <stdlib.h>

#include "no.h"

struct nos{
    void* dados;     /*!< Referência do dado respectiva ao nó da lista encadeada. */
    no_t *proximo;   /*!< Referência do próximo elemento da lista encadeada. */
    no_t *anterior;  /*!< Referência do elemento anterior da lista encadeada. */
};

/**
  * @brief  Cria um novo nó de lista encadeada.
  * @param	dado: ponteiro genérico para qualquer tipo de dado.
  *
  * @retval no_t: ponteiro do tipo nó contendo a referência do dado.
  */
no_t *cria_no(void *dado)
{
    no_t *p = malloc(sizeof(no_t));

    if (p == NULL){
        perror("cria_no:");
        exit(EXIT_FAILURE);
    }

    p->dados = dado;
    p->proximo = NULL;
    p->anterior = NULL;

    return p;
}

/**
  * @brief  Faz o encadeamento entre dois nós de encadeados.
  * @param	fonte: ponteiro da fonte entre a ligação.
  *         destino: ponteiro do destino entre a ligação.
  *
  * @retval Nenhum.
  */
void liga_nos (no_t *fonte, no_t *destino)
{
    if (fonte == NULL || destino == NULL){
        fprintf(stderr,"liga_nos: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    fonte->proximo = destino;
    destino->anterior = fonte;
}

/**
  * @brief  Remove encadeamento um nó encadeado.
  * @param	no: nó de lista que se deseja remover ligação.
  *
  * @retval Nenhum.
  */
void desliga_no (no_t *no)
{
    if (no == NULL) {
        fprintf(stderr,"liga_nos: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    no->proximo = NULL;
    no->anterior = NULL;
}

/**
  * @brief  Remove encadeamento "anterior" de um nó encadeado.
  * @param	no: nó de lista que se deseja remover ligação.
  *
  * @retval Nenhum.
  */
void desliga_no_anterior (no_t *no)
{
    if (no == NULL) {
        fprintf(stderr,"liga_nos: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    no->anterior = NULL;
}

/**
  * @brief  Remove encadeamento "próximo" de um nó encadeado.
  * @param	no: nó de lista que se deseja remover ligação.
  *
  * @retval Nenhum.
  */
void desliga_no_proximo (no_t *no)
{
    if (no == NULL) {
        fprintf(stderr,"liga_nos: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    no->proximo = NULL;
}

/**
  * @brief  Obtém a referência do dado pertencente ao nó de lista encadeada.
  * @param	no: nó de lista que se deseja obter o dado.
  *
  * @retval void *: dado referenciado pelo nó encadeado.
  */
void *obter_dado (no_t *no)
{
    if (no == NULL) {
        fprintf(stderr,"liga_nos: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    return no->dados;
}

/**
  * @brief  Obtém a próxima referência encadeada.
  * @param	no: nó de lista que se deseja obter o próximo elemento.
  *
  * @retval no_t *: ponteiro do próximo elemento da lista. NULL se final de lista.
  */
no_t *obter_proximo (no_t *no)
{
    if (no == NULL) {
        fprintf(stderr,"liga_nos: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    return no->proximo;
}

/**
  * @brief  Obtém a referência anterior encadeada.
  * @param	no: nó de lista que se deseja obter o próximo elemento.
  *
  * @retval no_t *: ponteiro do próximo elemento da lista. NULL se final de lista.
  */
no_t *obtem_anterior (no_t *no)
{
    if (no == NULL) {
        fprintf(stderr,"liga_nos: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    return no->anterior;
}

/**
  * @brief  Atualiza os dados de um nó
  * @param	no: nó de lista que se deseja alterar
  *         dados: ponteiro de um novo dado
  * @retval Nehum
  */
void alterar_dados(no_t *no, void *dados){
	no->dados = dados;
}
