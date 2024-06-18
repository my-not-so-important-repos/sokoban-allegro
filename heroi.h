#ifndef H8OR_HEROI
#define H8OR_HEROI

#include <allegro.h>

#define NUM_DIRECOES        4
#define FRAMES_POR_DIRECAO  3
#define FRAME_WIDTH        24
#define FRAME_HEIGHT       32

#define DIRECAO_CIMA       0
#define DIRECAO_DIREITA    1
#define DIRECAO_BAIXO      2
#define DIRECAO_ESQUERDA   3



class CHeroi
{
public:
    BITMAP *imagem[NUM_DIRECOES][FRAMES_POR_DIRECAO];
    int posLin, posCol;
    int direcao;
    volatile int *hClock;

    CHeroi();
    ~CHeroi();
    void CarregarBitmaps(char*);
    BITMAP* getImagem();

};
#endif
