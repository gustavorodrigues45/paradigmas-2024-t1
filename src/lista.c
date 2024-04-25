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
} Lista;

// Funcao para criar uma nova lista
void Lista_new(Lista* lista, int data_size, void (*free_data)(void*)) {
    lista->data_size = data_size;
    lista->free_data = free_data;
    lista->head = NULL;
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

// Exemplo de funcao para liberar a memoria de um valor do tipo int*
void free_int(void *valor) {
    free(valor);
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

    // Verifica o tamanho da lista
    printf("Tamanho da lista: %d\n", Lista_size(&lista));

    // Deleta a lista e libera a memoria
    Lista_delete(&lista);

    return 0;
}
