#ifndef PILHA__H_INCLUDED
#define PILHA__H_INCLUDED

typedef struct pilha
{
    int tam;
    Lista *prim;
}Pilha;

Pilha * pilha_cria(void);
int pilha_vazia(Pilha *p);
void pilha_push(Pilha *p, int x);
int pilha_pop(Pilha *p);
void pilha_libera(Pilha *p);
void pilha_imprime(Pilha *p);

#endif // PILHA__H_INCLUDED
