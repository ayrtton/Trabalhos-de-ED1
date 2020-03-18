#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct lista
{
    int num;
    struct lista *prox;
}Lista;

Lista * lista_cria(void);
Lista * lista_insere(Lista *lst, int x);
int lista_busca(Lista *lst, int x);
void lista_imprime(Lista *lst);
Lista * lista_remove_primeiro(Lista *lst, int *x);
int lista_vazia(Lista *lst);

#endif // LISTA_H_INCLUDED
