#include<stdlib.h>
#include "ListaEnc.h"

ListaEnc* criarLista(int tam) {
    ListaEnc* lista = (ListaEnc*) malloc(sizeof(ListaEnc));
    lista->inicio = NULL;
    lista->tamanhoDoItem = tam;
    lista->tamanhoDaLista = 0;
    return lista;
}

void insereNoInicio(void* i, ListaEnc *lista) {
    No *novoNo = (No*) malloc(sizeof(No));
    novoNo->item = i;
    novoNo->proximo = lista->inicio;
    lista->inicio =novoNo;
    lista->tamanhoDaLista++;
}

void insereNoFim(void* i, ListaEnc *lista) {
    if (estahVazia(lista)) insereNoInicio(i, lista);
    else {
        No *novoNo = (No*) malloc(sizeof(No));
        novoNo->item = i;
        novoNo->proximo = NULL;
        No *noAux = lista->inicio;
        while(noAux->proximo != NULL) {
            noAux = noAux->proximo;
        }
        noAux->proximo = novoNo;
        lista->tamanhoDaLista++;
    }
}

int estahVazia(ListaEnc *lista) {
    if (lista->inicio == NULL) return TRUE;
    else return FALSE;
}

void* removeDoInicio(ListaEnc* lista) {
    if (!estahVazia(lista)) {
        No* noAux = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        void* iRemovido = malloc(sizeof(lista->tamanhoDoItem));
        memcpy(iRemovido, noAux->item, lista->tamanhoDoItem);
        free(noAux->item);
        free(noAux);
        lista->tamanhoDaLista--;
        return iRemovido;
    } else NULL;
}

void* obterElemento(int index, ListaEnc* lista) {
    if (index < lista->tamanhoDaLista) {
        No* noAux = lista->inicio;
        int i;
        for(i = 0; i < index; i++) {
            noAux = noAux->proximo;
        }
        return noAux->item;
    } return NULL;
}

int obterTamanhoDaLista(ListaEnc* lista) {
    return lista->tamanhoDaLista;
}

void* removeDoFim(ListaEnc* lista) {
    if (!estahVazia(lista)) {
        No* noAnt = NULL;
        No* noAux = lista->inicio;
        while(noAux->proximo != NULL) {
            noAnt = noAux;
            noAux = noAux->proximo;
        }
        if (noAnt == NULL) return removeDoInicio(lista);
        else {
            noAnt->proximo = NULL;
            void* iRemovido = malloc(lista->tamanhoDoItem);
            memcpy(iRemovido, noAux->item, lista->tamanhoDoItem);
            free(noAux->item);
            free(noAux);
            lista->tamanhoDaLista--;
        }
    } else NULL;
}



void liberarLista(ListaEnc* lista) {
	while(!estahVazia(lista)) removeDoInicio(lista);
	free(lista);
}

