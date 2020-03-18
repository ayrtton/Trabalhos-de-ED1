#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Lista.h"
#include "Pilha.h"

Lista * inicia_entrada(Lista *entrada, int *N);
Pilha ** inicia_trilhos(Pilha **trilho, int *K, int *T);
void imprime_vagoes(Lista *entrada, Pilha **trilho, Lista *saida, int n);

int main()
{
    setlocale(LC_ALL, "");

    Lista *entrada = lista_cria();;
    Lista *saida = lista_cria();
    Pilha **trilho = NULL;

    int numero_de_trilhos, numero_de_vagoes, tamanho_dos_trilhos, numero_de_etapas;
    int x, vagao, botao, i, flag;

    entrada = inicia_entrada(entrada, &numero_de_vagoes);
    trilho = inicia_trilhos(trilho, &numero_de_trilhos, &tamanho_dos_trilhos);
    imprime_vagoes(entrada, trilho, saida, numero_de_trilhos);

    vagao = 1;                                                          //Vagão procurado.
    i = 0;
    numero_de_etapas = 0;
    while(1)
    {
        printf("\nEntre com [1] para continuar: ");
        scanf("%d", &botao);
        if(botao!=1)
            break;

        flag = 0;
        if(entrada != NULL && entrada->num == vagao)                    //Procura vagão na frente da entrada.
        {
            entrada = lista_remove_primeiro(entrada, &x);
            saida = lista_insere(saida, x);
            vagao++;
            flag = 1;                                                   //Sinal que encontrou.
        }
        if(flag==0)
        {
            for(i=0; i<numero_de_trilhos; i++)
            {
                if(trilho[i]->tam > 0 && trilho[i]->prim->num == vagao)  //Procura nos trilhos, se já estiverem ocupados.
                {
                    x = pilha_pop(trilho[i]);
                    saida = lista_insere(saida, x);
                    vagao++;
                    flag = 1;
                    break;
                }
            }
        }
        if(flag == 0)                                                   //Não encontrou nos trilhos nem na frente da entrada,
        {                                                               //desempilha entrada.
            entrada = lista_remove_primeiro(entrada, &x);
            for(i=0; i<numero_de_trilhos; i++)
            {
                if((trilho[i]->tam < tamanho_dos_trilhos) && (trilho[i]->tam == 0 || trilho[i]->prim->num > x))
                {
                    pilha_push(trilho[i], x);
                    flag = 1;                                           //Sinal que há espaço para empilhar.
                    break;
                }
            }
            if(flag==0)                                                 //Aloca novo trilho, caso não haja espaço.
            {
                numero_de_trilhos++;
                trilho = (Pilha**)(realloc(trilho, numero_de_trilhos * sizeof(Pilha*)));
                trilho[numero_de_trilhos-1] = pilha_cria();
                pilha_push(trilho[numero_de_trilhos-1], x);
            }
        }
        imprime_vagoes(entrada, trilho, saida, numero_de_trilhos);

        if(vagao == numero_de_vagoes+1)
            break;

        numero_de_etapas++;
    }

    printf("Fim | %d trilhos de espera utilizados | %d etapas\n", numero_de_trilhos, numero_de_etapas);
}

Lista * inicia_entrada(Lista *entrada, int *N)
{
    int x, i;

    printf("Número de vagões: ");
    scanf("%d", N);

    srand(time(0));
    for(i=0; i<*N; i++)
    {
        x = rand() % *N + 1;
        while(lista_busca(entrada, x))
            x = rand() % *N + 1;;
        entrada = lista_insere(entrada, x);
    }

    return entrada;
}

Pilha ** inicia_trilhos(Pilha **trilho, int *K, int *T)
{
    int i;

    printf("Quantidade de trilhos: ");
    scanf("%d", K);
    printf("Tamanho máximo dos trilhos: ");
    scanf("%d", T);

    trilho = (Pilha**)malloc(*K * sizeof(Pilha*));
    for(i=0; i<*K; i++)
        trilho[i] = pilha_cria();

    return trilho;
}

void imprime_vagoes(Lista *entrada, Pilha **trilho, Lista *saida, int K)
{
    int i;

    printf("\nEntrada: ");
    lista_imprime(entrada);
    putchar('\n');
    for(i=0; i<K; i++)
    {
        printf("Trilho %d: ", i+1);
        if(trilho[i]->tam > 0)
        {
            pilha_imprime(trilho[i]);
            printf(" Tamanho: %d", trilho[i]->tam);
        }
        putchar('\n');
    }
    printf("Saída: ");
    lista_imprime(saida);
    putchar('\n');
}
