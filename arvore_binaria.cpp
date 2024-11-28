#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da estrutura de um nó da árvore binária
struct NoArvore {
    int info;
    struct NoArvore *esq;
    struct NoArvore *dir;
};

// Definição da estrutura da árvore
struct Arvore {
    struct NoArvore *raiz;
};

// Função para criar a árvore
struct Arvore* Criar() {
    struct Arvore *arvore = (struct Arvore *)malloc(sizeof(struct Arvore));
    arvore->raiz = NULL;
    return arvore;
}

// Função para inserir um elemento na árvore
struct NoArvore* InserirNo(struct NoArvore *no, int valor) {
    if (no == NULL) {
        struct NoArvore *novoNo = (struct NoArvore *)malloc(sizeof(struct NoArvore));
        novoNo->info = valor;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        return novoNo;
    }
    if (valor < no->info) {
        no->esq = InserirNo(no->esq, valor);
    } else if (valor > no->info) {
        no->dir = InserirNo(no->dir, valor);
    }
    return no;
}

void Inserir(struct Arvore *arvore, int valor) {
    arvore->raiz = InserirNo(arvore->raiz, valor);
}

// Função para imprimir a árvore em ordem com indentação
void ImprimirNo(struct NoArvore *no, int nivel) {
    if (no != NULL) {
        for (int i = 0; i < nivel; i++) {
            printf("..");
        }
        printf("%d\n", no->info);
        ImprimirNo(no->esq, nivel + 1);
        ImprimirNo(no->dir, nivel + 1);
    }
}

void Imprimir(struct Arvore *arvore) {
    ImprimirNo(arvore->raiz, 0);
}

// Função para verificar se a árvore está vazia
bool EstaVazia(struct Arvore *arvore) {
    return arvore->raiz == NULL;
}

// Função para buscar um elemento na árvore
bool BuscarNo(struct NoArvore *no, int valor) {
    if (no == NULL) {
        return false;
    }
    if (no->info == valor) {
        return true;
    } else if (valor < no->info) {
        return BuscarNo(no->esq, valor);
    } else {
        return BuscarNo(no->dir, valor);
    }
}

bool Buscar(struct Arvore *arvore, int valor) {
    return BuscarNo(arvore->raiz, valor);
}

// Função para remover um elemento da árvore
struct NoArvore* RemoverNo(struct NoArvore *no, int valor) {
    if (no == NULL) {
        return NULL;
    }
    if (valor < no->info) {
        no->esq = RemoverNo(no->esq, valor);
    } else if (valor > no->info) {
        no->dir = RemoverNo(no->dir, valor);
    } else {
        if (no->esq == NULL) {
            struct NoArvore *temp = no->dir;
            free(no);
            return temp;
        } else if (no->dir == NULL) {
            struct NoArvore *temp = no->esq;
            free(no);
            return temp;
        }
        struct NoArvore *temp = no->dir;
        while (temp->esq != NULL) {
            temp = temp->esq;
        }
        no->info = temp->info;
        no->dir = RemoverNo(no->dir, temp->info);
    }
    return no;
}

void Remover(struct Arvore *arvore, int valor) {
    arvore->raiz = RemoverNo(arvore->raiz, valor);
}

// Função para liberar a memória da árvore
void LiberarNo(struct NoArvore *no) {
    if (no != NULL) {
        LiberarNo(no->esq);
        LiberarNo(no->dir);
        free(no);
    }
}

void Liberar(struct Arvore *arvore) {
    LiberarNo(arvore->raiz);
    free(arvore);
}

// Função principal
int main() {
    struct Arvore *minhaArvore = Criar();

    // Inserindo novos valores na árvore
    Inserir(minhaArvore, 10);
    Inserir(minhaArvore, 5);
    Inserir(minhaArvore, 15);
    Inserir(minhaArvore, 3);
    Inserir(minhaArvore, 7);
    Inserir(minhaArvore, 12);
    Inserir(minhaArvore, 18);
    Inserir(minhaArvore, 1);
    Inserir(minhaArvore, 6);

    // Imprimindo elementos da árvore
    printf("Elementos da árvore:\n");
    Imprimir(minhaArvore);

    // Verificando se a árvore está vazia
    printf("\nA árvore está vazia? %s\n", EstaVazia(minhaArvore) ? "Sim" : "Não");

    // Buscando um elemento
    printf("Buscar 7: %s\n", Buscar(minhaArvore, 7) ? "Encontrado" : "Não encontrado");

    // Removendo um elemento
    printf("\nApós remover 5:\n");
    Remover(minhaArvore, 5);
    Imprimir(minhaArvore);

    // Liberando memória
    Liberar(minhaArvore);
    return 0;
}
