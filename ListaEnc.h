#define TRUE 1
#define FALSE 0

typedef struct {
    void* item;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
    int tamanhoDoItem;
    int tamanhoDaLista;
} ListaEnc;

ListaEnc* criarLista(int tam);
void insereNoInicio(void* i, ListaEnc *lista);
void insereNoFim(void* i, ListaEnc *lista);
int estahVazia(ListaEnc *lista);
void* removeDoInicio(ListaEnc* lista);
void* removeDoFim(ListaEnc* lista);
void liberarLista(ListaEnc* lista);
void* obterElemento(int index, ListaEnc* lista);
int obterTamanhoDaLista(ListaEnc* lista);
