#include <stdlib.h>
#include "Lista.h"
#include "Pilha.h"

Pilha * pilha_cria(void)
{
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->prim = NULL;
    p->tam = 0;
    return p;
}

int pilha_vazia(Pilha *p)
{
    if(p->prim == NULL)
        return 1;
    return 0;
}

void pilha_push(Pilha *p, int x)
{
    Lista *novo = (Lista*)malloc(sizeof(Lista));
    novo->num = x;
    novo->prox = p->prim;
    p->prim = novo;
    p->tam++;
}

int pilha_pop(Pilha *p)
{
    Lista *t;
    int x;

    if(pilha_vazia(p))
        return -1;

    t = p->prim;
    x = t->num;
    p->prim = t->prox;
    p->tam--;

    free(t);
    return x;
}

void pilha_libera(Pilha *p)
{
    Lista *t, *q = p->prim;

    while(q!=NULL)
    {
        t = q->prox;
        free(q);
        q = t;
    }
    free(p);
}

void pilha_imprime(Pilha *p)
{
    Lista *q;

    for(q=p->prim; q!=NULL; q=q->prox)
        printf("%d ", q->num);
}
