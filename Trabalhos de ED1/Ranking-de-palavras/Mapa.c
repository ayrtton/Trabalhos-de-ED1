#include "Mapa.h"
#include <string.h>

struct _mapa
{
    int total;
    int blocos;
    Item **lista;
};

struct _item
{
    int conta;
    char *termo;
};

void inicia_mapa(Mapa *mp)
{
    mp->total = 0;
    mp->blocos = 1;
    mp->lista = (Item**)malloc(10 * sizeof(Item*));
}

void insere_termo(Mapa *mp, char *s)
{
    int i, j, tmp, x;

    if(mp->total>=mp->blocos*10)
    {
        mp->lista = (Item**)realloc(mp->lista, (mp->total+10) * sizeof(Item*));
        mp->blocos++;
    }

    strlwr(s);

    i = mp->total;

    j = i;
    while(j>0)
    {
        if(strcmp(s, mp->lista[j-1]->termo)==0)
        {
            incrementa(mp, mp->lista[j-1]->termo);
            ordena_para_cima(mp, j-1);
            return;
        }
        j--;
    }

    mp->lista[i] = (Item*)malloc(sizeof(Item));
    mp->lista[i]->termo = (char*)malloc(strlen(s) * sizeof(char));
    strcpy(mp->lista[i]->termo, s);
    mp->lista[i]->conta = 1;
    mp->total++;
}

int incrementa(Mapa *mp, char *s)
{
    int i;

    for(i=0; i<mp->total; i++)
    {
        if(strcmp(s, mp->lista[i]->termo)==0)
        {
            mp->lista[i]->conta++;
            return 0;
        }
    }

    return 1;
}

int escreve_cont(Mapa *mp, char *s, int c)
{
    int i;

    for(i=0; i<mp->total; i++)
    {
        if(strcmp(s, mp->lista[i]->termo)==0)
        {
            if(c > mp->lista[i]->conta)
            {
                mp->lista[i]->conta = c;
                ordena_para_cima(mp, i);
            }

            if(c < mp->lista[i]->conta)
            {
                mp->lista[i]->conta = c;
                ordena_para_baixo(mp, i);
            }
            return 0;
        }
    }

    return 1;
}

int le_contador(Mapa *mp, char *s)
{
    int i;

    for(i=0; i<mp->total; i++)
    {
        if(strcmp(s, mp->lista[i]->termo)==0)
            return mp->lista[i]->conta;
    }
    return 0;
}

void remove_termo(Mapa *mp, char *s)
{
    int i, j;

    strlwr(s);

    for(i=0; i<mp->total; i++)
    {
        if(strcmp(s, mp->lista[i]->termo)==0)
        {
            for(j=i; j<mp->total-1; j++)
                mp->lista[j] = mp->lista[j+1];
            mp->total--;
            free(mp->lista[mp->total+1]);

            if(mp->total<=mp->blocos*10-10)
            {
                mp->lista = (Item**)realloc(mp->lista, (mp->blocos*10-10) * sizeof(Item*));
                mp->blocos--;
            }

            if(mp->total==0)
            {
                printf("Mapa vazio!\n");
                libera_mapa(mp);
                exit(1);
            }

            return;
        }
    }

    printf("Palavra não encontrada!");
}

void libera_mapa(Mapa *mp)
{
    int i;

    for(i=0; i<mp->total; i++)
    {
        free(mp->lista[i]->termo);
        free(mp->lista[i]);
    }

    free(mp->lista);
    mp->blocos = 0;
    mp->total = 0;
}

int tamanho_mapa(Mapa *mp)
{
    return mp->total;
}

int le_termo(Mapa *mp, int i, char *t, int *c)
{
    if(i>=0 && i<mp->total)
    {
        strcpy(t, mp->lista[i]->termo);
        *c = mp->lista[i]->conta;
        return 1;
    }
    else
        return 0;
}

void imprime_mapa(Mapa *mp)
{
    int i, j;

    for(i=0; i<mp->total; i++)
    {
        printf("\n%2d° lugar: %s", i+1, mp->lista[i]->termo);
        printf(" -> %d ponto(s).",  mp->lista[i]->conta);
    }
    putchar('\n');
}

void ordena_para_cima(Mapa *mp, int i)
{
    int x = i, tmp;

    while(x!=0 && mp->lista[x]->conta > mp->lista[x-1]->conta)
    {
        tmp = mp->lista[x];
        mp->lista[x] = mp->lista[x-1];
        mp->lista[x-1] = tmp;
        x--;
    }
}

void ordena_para_baixo(Mapa* mp, int i)
{
    int x = i, tmp;

    while(x!=mp->total && mp->lista[x]->conta < mp->lista[x+1]->conta)
    {
        tmp = mp->lista[x];
        mp->lista[x] = mp->lista[x+1];
        mp->lista[x+1] = tmp;
        x++;
    }
}

void imprime_lista(Mapa *mp)
{
    int i;

    for(i=0; i<mp->total; i++)
        printf("%d -> %s\n", i+1, mp->lista[i]->termo);
}
