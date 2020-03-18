#include <stdlib.h>
#include "Lista.h"

Lista * lista_cria(void)
{
    return NULL;
}

Lista * lista_insere(Lista *lst, int x)
{
    Lista *novo = (Lista*)malloc(sizeof(Lista));
    novo->num = x;
    novo->prox = lst;
    return novo;
}

int lista_busca(Lista *lst, int x)
{
    Lista *p;

    for(p=lst; p!=NULL; p=p->prox)
        if(p->num==x)
            return 1;
    return 0;
}

void lista_imprime(Lista *lst)
{
    Lista *p;

    for(p=lst; p!=NULL; p=p->prox)
        printf("%d ", p->num);
}

Lista * lista_remove_primeiro(Lista *lst, int *x)
{
    Lista *p = lst;
    Lista *rlst = lst;

    *x = lst->num;

    rlst = p->prox;
    free(p);

    return rlst;
}

int lista_vazia(Lista *lst)
{
    return lst == NULL;
}
