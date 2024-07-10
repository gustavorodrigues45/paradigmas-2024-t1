////////////////////////////////////// Patrícia Caselani ////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da lista
typedef struct _lista_nodo {
    void *valor;              // Ponteiro para os dados
    struct _lista_nodo *next; // Ponteiro para o próximo nó
} ListaNodo;

// Estrutura da lista encadeada genérica
typedef struct {
    int data_size;             // Tamanho dos dados a serem armazenados
    void (*free_data)(void *); // Função para liberar a memória dos dados
    ListaNodo *head;           // Ponteiro para o primeiro nó da lista
} Lista;

// Função que inicializa a lista
void Lista_new(Lista *lista, int data_size, void (*free_data)(void *)) {
    lista->data_size = data_size;
    lista->free_data = free_data;
    lista->head = NULL;
}

// Função que insere um elemento no início da lista
void Lista_pushFront(Lista *lista, void *valor) {
    ListaNodo *new_node = (ListaNodo *)malloc(sizeof(ListaNodo));
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
    memcpy(new_node->valor, valor, lista->data_size);
    new_node->next = lista->head;
    lista->head = new_node;
}

// Função que insere um elemento no final da lista
void Lista_pushBack(Lista *lista, void *valor) {
    ListaNodo *new_node = (ListaNodo *)malloc(sizeof(ListaNodo));
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
    memcpy(new_node->valor, valor, lista->data_size);
    new_node->next = NULL;

    if (lista->head == NULL) {
        lista->head = new_node;
    } else {
        ListaNodo *temp = lista->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Função que busca um elemento na lista
int Lista_search(Lista *lista, void *chave, void *dest, int (*cmp)(void *, void *)) {
    ListaNodo *current = lista->head;
    while (current != NULL) {
        if (cmp(chave, current->valor) == 0) {
            memcpy(dest, current->valor, lista->data_size);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Função para liberar a memória de um valor do tipo int*
void free_int(void *valor) {
    free(valor);
}

// Função que retorna o primeiro elemento da lista
void *Lista_first(Lista *lista) {
    if (lista->head == NULL) {
        fprintf(stderr, "Erro: A lista está vazia.\n");
        return NULL;
    }
    return lista->head->valor;
}

// Função que retorna o último elemento da lista
void *Lista_last(Lista *lista) {
    if (lista->head == NULL) {
        fprintf(stderr, "Erro: A lista está vazia.\n");
        return NULL;
    }
    ListaNodo *current = lista->head;
    while (current->next != NULL) {
        current = current->next;
    }
    return current->valor;
}

// Função que compara dois inteiros
int compare_int(void *a, void *b) {
    int *x = (int *)a;
    int *y = (int *)b;
    return *x - *y;
}

// Função que retorna o tamanho da lista
int Lista_size(Lista *lista) {
    int size = 0;
    ListaNodo *current = lista->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

int main() {
    Lista lista;
    Lista_new(&lista, sizeof(int), free_int);

    // Adiciona elementos na lista
    int *valor1 = (int *)malloc(sizeof(int));
    *valor1 = 20;
    Lista_pushFront(&lista, valor1);

    int *valor2 = (int *)malloc(sizeof(int));
    *valor2 = 10;
    Lista_pushFront(&lista, valor2);

    int valor3 = 15;
    Lista_pushBack(&lista, &valor3);

    int valor4 = 23;
    Lista_pushBack(&lista, &valor4);

    // Verifica o tamanho da lista
    printf("Tamanho da lista: %d\n", Lista_size(&lista));

    // Mostra o primeiro e o último elemento da lista
    int *first = (int *)Lista_first(&lista);
    printf("Primeiro elemento: %d\n", *first);

    int *last = (int *)Lista_last(&lista);
    printf("Último elemento: %d\n", *last);

    // Busca um elemento na lista
    int chave1 = 10;
    int *dest1 = (int *)malloc(sizeof(int));
    if (Lista_search(&lista, &chave1, dest1, compare_int)) {
        printf("Elemento encontrado: %d\n", *dest1);
    } else {
        printf("Elemento não encontrado.\n");
    }
    free(dest1);

    // Busca outro elemento na lista
    int chave2 = 15;
    int find_value;
    int found = Lista_search(&lista, &chave2, &find_value, compare_int);

    if (found) {
        printf("Elemento %d encontrado: %d\n", chave2, find_value);
    } else {
        printf("Elemento %d não encontrado.\n", chave2);
    }

    return 0;
}

////////////////////////////////////// Patrícia Caselani ////////////////////////////////////////////