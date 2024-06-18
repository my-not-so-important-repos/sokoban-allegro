#include "heroi.h"

CHeroi::CHeroi()
{
    direcao = DIRECAO_BAIXO;
    for (int direcao = 0; direcao < NUM_DIRECOES; direcao++)
        for (int posicao = 0; posicao < FRAMES_POR_DIRECAO; posicao++)
            imagem[direcao][posicao] = create_bitmap(FRAME_WIDTH, FRAME_HEIGHT);
}

CHeroi::~CHeroi()
{
    for (int direcao = 0; direcao < NUM_DIRECOES; direcao++)
        for (int posicao = 0; posicao < FRAMES_POR_DIRECAO; posicao++)
            destroy_bitmap(imagem[direcao][posicao]);
}

void CHeroi::CarregarBitmaps(char *arquivoImagem)
{
    BITMAP *charset = load_bitmap(arquivoImagem, NULL);
    for (int direcao = 0; direcao < NUM_DIRECOES; direcao++)
        for (int posicao = 0; posicao < FRAMES_POR_DIRECAO; posicao++)
            blit(charset, imagem[direcao][posicao], posicao * FRAME_WIDTH, direcao * FRAME_HEIGHT, 0, 0, FRAME_WIDTH, FRAME_HEIGHT);
}

BITMAP* CHeroi::getImagem()
{
    int posicaoAtual = (*hClock / 15) % 4;
    if (posicaoAtual == 3)
        posicaoAtual = 1;
    return imagem[direcao][posicaoAtual];
}
