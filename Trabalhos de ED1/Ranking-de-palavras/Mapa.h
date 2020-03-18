#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

typedef struct _mapa Mapa;
typedef struct _item Item;

void inicia_mapa(Mapa *mp);
void insere_termo(Mapa *mp, char *s);
int incrementa(Mapa *mp, char *s);
int escreve_cont(Mapa* mp, char *s, int c);
int le_contador(Mapa *mp, char *s);
void remove_termo(Mapa *mp, char *s);
void libera_mapa(Mapa *mp);
int tamanho_mapa(Mapa *mp);
int le_termo(Mapa *mp, int i, char *t, int *c);
void imprime_mapa(Mapa* mp);
void ordena_para_cima(Mapa* mp, int i);
void ordena_para_baixo(Mapa* mp, int i);

#endif // MAPA_H_INCLUDED
