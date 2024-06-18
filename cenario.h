#ifndef H8OR_CENARIO
#define H8OR_CENARIO

#include <allegro.h>
#include <fstream>
#include "heroi.h"

#define TAMANHO_TILE 32

#define NUM_IMAGENS_TILE  4
#define   TILE_CHAO       0
#define   TILE_PAREDE     1
#define   TILE_PONTO      2
#define   TILE_CAIXA      3


class CCenario
{
protected:
    int **matriz;

public:
    BITMAP *buffer;
    BITMAP *tileset[NUM_IMAGENS_TILE];
    int numLinhas, numColunas;
    int posInicialLin, posInicialCol;
    int numPontos;
    CHeroi *heroi;

    CCenario();
    ~CCenario();
    void Init(char*, char*); // chama as funções CarregaMatriz() e CarregaBitmaps()
    void CarregaMatriz(char*);
    void CarregaBitmaps(char*);
    BITMAP* DrawAll();

    bool IsValid(int, int);

    void MoveUp();
    void MoveRight();
    void MoveDown();
    void MoveLeft();
};
#endif
