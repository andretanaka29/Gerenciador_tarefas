#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

typedef struct heap heap_t;

heap_t * cria_heap(int n);
void add_heap(heap_t *h, void * ptr);
void retira_heap(heap_t *h, int tam);
void imprimir_heap(heap_t *h, int tam);
void max_heapfy(heap_t *h, int i, int k);
void build_heap(heap_t *h, int n);
int obter_total_heap(heap_t *h);
int obter_tamanho_heap(heap_t *h);

#endif // HEAP_H_INCLUDED
