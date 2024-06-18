#include "cenario.h"



CCenario::CCenario()
{
    heroi = new CHeroi;
    heroi->CarregarBitmaps("res/personagem.bmp");
    for (int i = 0; i < NUM_IMAGENS_TILE; i++)
        tileset[i] = create_bitmap(TAMANHO_TILE, TAMANHO_TILE);
}



CCenario::~CCenario()
{
    for (int i = 0; i < NUM_IMAGENS_TILE; i++)
        destroy_bitmap(tileset[i]);
}



void CCenario::Init(char *arquivoMapa, char *arquivoTilesets)
{
    CarregaBitmaps(arquivoTilesets);
    CarregaMatriz(arquivoMapa);
}



void CCenario::CarregaMatriz(char *nomeArquivo)
{
    std::fstream arquivo(nomeArquivo, std::ios_base::in);
    arquivo >> numPontos >> posInicialLin >> posInicialCol >> numLinhas >> numColunas;

    matriz = new int* [numLinhas];
    for (int linha = 0; linha < numLinhas; linha++)
        matriz[linha] = new int [numColunas];

    buffer = create_bitmap(numColunas * TAMANHO_TILE, numLinhas * TAMANHO_TILE);

    for (int linha = 0; linha < numLinhas; linha++)
        for (int coluna = 0; coluna < numColunas; coluna++)
            arquivo >> matriz[linha][coluna];
    arquivo.close();

    heroi->posCol = posInicialCol;
    heroi->posLin = posInicialLin;
}



void CCenario::CarregaBitmaps(char *nomeArquivo)
{
    BITMAP *tilesetInteiro = load_bmp(nomeArquivo, NULL);
    for (int i = 0; i < NUM_IMAGENS_TILE; i++)
        blit(tilesetInteiro, tileset[i], i * TAMANHO_TILE, 0, 0, 0, TAMANHO_TILE, TAMANHO_TILE);
}



BITMAP* CCenario::DrawAll()
{
    clear_to_color(buffer, makecol(255, 255, 255)); // acho que não é necessário
    for (int linha = 0; linha < numLinhas; linha++)
    	for (int coluna = 0; coluna < numColunas; coluna++)
    	{
            if (matriz[linha][coluna] & 1)
                draw_sprite(buffer, tileset[TILE_PAREDE], coluna * 32, linha * 32);
            else
                draw_sprite(buffer, tileset[TILE_CHAO], coluna * 32, linha * 32);
            if (matriz[linha][coluna] & 2)
                draw_sprite(buffer, tileset[TILE_PONTO], coluna * 32, linha * 32);
            if (matriz[linha][coluna] & 4)
                draw_sprite(buffer, tileset[TILE_CAIXA], coluna * 32, linha * 32);
    	}
    draw_sprite(buffer, heroi->getImagem(), heroi->posCol * 32, heroi->posLin * 32);
    return buffer;
}



bool CCenario::IsValid(int linha, int coluna)
{
    if (linha >= 0 && linha < numLinhas && coluna >= 0 && coluna < numColunas)
        return true;
    return false;
}



void CCenario::MoveUp()
{
    heroi->direcao = DIRECAO_CIMA;
    if (IsValid(heroi->posLin - 1, heroi->posCol))
        if (!(matriz[heroi->posLin - 1][heroi->posCol] & 1))
            heroi->posLin--;
}



void CCenario::MoveRight()
{
    heroi->direcao = DIRECAO_DIREITA;
    if (IsValid(heroi->posLin, heroi->posCol + 1))
        if (!(matriz[heroi->posLin][heroi->posCol + 1] & 1))
            heroi->posCol++;
}



void CCenario::MoveDown()
{
    heroi->direcao = DIRECAO_BAIXO;
    if (IsValid(heroi->posLin + 1, heroi->posCol))
        if (!(matriz[heroi->posLin + 1][heroi->posCol] & 1))
            heroi->posLin++;
}



void CCenario::MoveLeft()
{
    heroi->direcao = DIRECAO_ESQUERDA;
    if (IsValid(heroi->posLin, heroi->posCol - 1))
        if (!(matriz[heroi->posLin][heroi->posCol - 1] & 1))
            heroi->posCol--;
}
