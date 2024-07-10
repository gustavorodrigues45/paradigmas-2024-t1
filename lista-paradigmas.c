#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um no da lista
typedef struct _lista_nodo {
    void *valor; // Ponteiro para os dados
    struct _lista_nodo *next; // Ponteiro para o proximo no
} ListaNodo;

// Estrutura da lista encadeada generica
typedef struct {
    int data_size; // Tamanho dos dados a serem armazenados
    void (*free_data)(void*); // Funcao para liberar a memoria dos dados
    ListaNodo *head; // Ponteiro para o primeiro no da lista
    ListaNodo *current; // Ponteiro para o no atual da lista
} Lista;

// Funcao para criar uma nova lista
void Lista_new(Lista* lista, int data_size, void (*free_data)(void*)) {
    lista->data_size = data_size;
    lista->free_data = free_data;
    lista->head = NULL;
    lista->current = NULL;
}

// Funcao para deletar uma lista
void Lista_delete(Lista* lista) {
    ListaNodo *current = lista->head;
    while (current != NULL) {
        ListaNodo *temp = current;
        current = current->next;
        if (lista->free_data) {
            lista->free_data(temp->valor); // Libera a memoria dos dados
        }
        free(temp); // Libera a memoria do no
    }
    lista->head = NULL;
    lista->current = NULL;
}

// Funcao para verificar se a lista esta vazia
int Lista_isEmpty(Lista* lista) {
    return lista->head == NULL;
}

// Funcao para retornar o tamanho da lista
int Lista_size(Lista* lista) {
    int size = 0;
    ListaNodo *current = lista->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

// Funcao para inserir um elemento no iniicio da lista
void Lista_pushFront(Lista* lista, void* valor) {
    ListaNodo *new_node = (ListaNodo*)malloc(sizeof(ListaNodo));
    if (new_node == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o novo nó.\n");
        exit(EXIT_FAILURE);
    }
    new_node->valor = malloc(lista->data_size);
    if (new_node->valor == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para os dados.\n");
        free(new_node);
        exit(EXIT_FAILURE);
    }
    // Copia os dados para o novo no
    memcpy(new_node->valor, valor, lista->data_size);
    new_node->next = lista->head;
    lista->head = new_node;
}

// Funcao para obter o valor atual
void Lista_current(Lista* lista, void* dest) {
    if (lista->current != NULL) {
        memcpy(dest, lista->current->valor, lista->data_size);
    } else {
        fprintf(stderr, "Erro: No atual é NULL.\n");
        exit(EXIT_FAILURE);
    }
}

// Funcao para remover um no pela chave
void Lista_remove(Lista* lista, void* chave, int (*cmp)(void*, void*)) {
    ListaNodo *current = lista->head;
    ListaNodo *previous = NULL;
    while (current != NULL) {
        if (cmp(current->valor, chave) == 0) {
            if (previous == NULL) { // Remover o primeiro nó
                lista->head = current->next;
            } else {
                previous->next = current->next;
            }
            if (lista->free_data) {
                lista->free_data(current->valor);
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Funcao para inserir um elemento apos o no atual
void Lista_insertAfter(Lista* lista, void* dado) {
    if (lista->current == NULL) {
        fprintf(stderr, "Erro: No atual é NULL.\n");
        exit(EXIT_FAILURE);
    }

    ListaNodo *new_node = (ListaNodo*)malloc(sizeof(ListaNodo));
    if (new_node == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o novo nó.\n");
        exit(EXIT_FAILURE);
    }
    new_node->valor = malloc(lista->data_size);
    if (new_node->valor == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para os dados.\n");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    memcpy(new_node->valor, dado, lista->data_size);
    new_node->next = lista->current->next;
    lista->current->next = new_node;
}

// Exemplo de funcao para liberar a memoria de um valor do tipo int*
void free_int(void *valor) {
    free(valor);
}

// Exemplo de funcao de comparacao para int*
int cmp_int(void* a, void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    return (int_a > int_b) - (int_a < int_b);
}

int main() {

    Lista lista;
    Lista_new(&lista, sizeof(int), free_int);

    // Adiciona elementos na lista
    int *valor1 = (int*)malloc(sizeof(int));
    *valor1 = 10;
    Lista_pushFront(&lista, valor1);

    int *valor2 = (int*)malloc(sizeof(int));
    *valor2 = 20;
    Lista_pushFront(&lista, valor2);

    // Configura o ponteiro atual
    lista.current = lista.head;

    // Testa Lista_current
    int current_value;
    Lista_current(&lista, &current_value);
    printf("Valor atual: %d\n", current_value);

    // Testa Lista_remove
    int chave = 10;
    Lista_remove(&lista, &chave, cmp_int);
    printf("Tamanho da lista apos remocao: %d\n", Lista_size(&lista));

    // Testa Lista_insertAfter
    int valor3 = 30;
    Lista_insertAfter(&lista, &valor3);

    // Verifica o tamanho da lista
    printf("Tamanho da lista: %d\n", Lista_size(&lista));

    // Deleta a lista e libera a memoria
    Lista_delete(&lista);

    return 0;
}
