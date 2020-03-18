#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Mapa.h"

void le_arquivo(Mapa *mp);
void mostra_menu(Mapa *mp);

int main()
{
    unsigned int cp = 1252;
    unsigned int cpin  = GetConsoleCP();
    unsigned int cpout = GetConsoleOutputCP();

    SetConsoleCP(cp);
    SetConsoleOutputCP(cp);

    Mapa *mapa;

    le_arquivo(&mapa);
    mostra_menu(&mapa);

    SetConsoleCP(cpin);
    SetConsoleOutputCP(cpout);
}

void le_arquivo(Mapa *mp)
{
    FILE *fp;
    int i, tam;
    char arquivo[12];
    char *texto;
    char *quebra;

    while(1)
    {
        printf("Arquivo: "); //Deve estar na mesma pasta, em formato .txt.
        gets(arquivo);
        if((fp = fopen(arquivo, "r"))==NULL)
            printf("Impossível abrir!\n");
        else
            break;
    }

    fseek(fp, 0, SEEK_END);
    tam = ftell(fp);
    rewind(fp);

    texto = (char*)malloc((tam + 1) * sizeof(char));
    fread(texto, tam, 1, fp);

    inicia_mapa(mp);
    quebra = strtok(texto, " 1 2 3 4 5 6 7 8 9 0 ' ! @ # $ % & * ( ) - _ + = § ¬ ¢ £ ³ ² ¹ / ? ° ¨ ´ ` ^ ~ º ª [ ] { } . , < > ; : \ | \n");
    while(quebra!= NULL)
    {
        insere_termo(mp, quebra);
        quebra = strtok(NULL, "1 2 3 4 5 6 7 8 9 0 ' ! @ # $ % & * ( ) - _ + = § ¬ ¢ £ ³ ² ¹ / ? ° ¨ ´ ` ^ ~ º ª [ ] { } . , < > ; : \ | \n");
    }

    free(texto);
    fclose(fp);
}

void mostra_menu(Mapa *mp)
{
    int opcao_menu, contador, indice;
    char *palavra = (char*)malloc(50 * sizeof(char));
    int *cont;

    while(1)
    {
        printf("\nMenu:\n1 - Ver mapa\n2 - Escrever contador\n3 - Ver contador\n4 - Remover termo\n5 - Ver tamanho do mapa\n6 - Ver palavra e contador\n7 - Ver lista\n0 - Liberar mapa e sair\n");
        scanf("%d", &opcao_menu);

        switch(opcao_menu)
        {
            case 1:
                imprime_mapa(mp);
                break;

            case 2:
                printf("Contador: ");
                scanf("%d", &contador);
                if(contador<1)
                {
                    printf("Contador inválido!\n");
                    break;
                }

                printf("Palavra: ");
                scanf("%s", palavra);
                if(escreve_cont(mp, palavra, contador))
                    printf("Palavra não encontrada!\n");
                break;

            case 3:
                printf("Palavra: ");
                scanf("%s", palavra);
                if(!le_contador(mp, palavra))
                    printf("Palavra não encontrada!\n");
                else
                    printf("%s |%d pontos\n", palavra, le_contador(mp, palavra));
                break;

            case 4:
                printf("Palavra: ");
                scanf("%s", palavra);
                remove_termo(mp, palavra);
                break;

            case 5:
                printf("%d itens\n", tamanho_mapa(mp));
                break;

            case 6:
                printf("Índice: ");
                scanf("%d", &indice);
                if(le_termo(mp, indice-1, palavra, &cont))
                    printf("\nPalavra: %s| Pontuação: %d\n", palavra, cont);
                else
                    printf("Índice inválido!\n");
                break;

            case 7:
                imprime_lista(mp);
                break;

            case 0:
                libera_mapa(mp);
                return;
        }
    }
}
