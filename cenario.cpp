#include "cenario.h"



CCenario::CCenario()
{
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
}



void CCenario::CarregaBitmaps(char *nomeArquivo)
{
    BITMAP *tilesetInteiro = load_bmp(nomeArquivo, NULL);
    for (int i = 0; i < NUM_IMAGENS_TILE; i++)
        blit(tilesetInteiro, tileset[i], i * TAMANHO_TILE, 0, 0, 0, TAMANHO_TILE, TAMANHO_TILE);
}



BITMAP* CCenario::DrawAll()
{
    clear_to_color(buffer, makecol(255, 255, 255));
    for (int linha = 0; linha < numLinhas; linha++)
    	for (int coluna = 0; coluna < numColunas; coluna++)
            switch(matriz[linha][coluna])
            {
            case TILE_CHAO:
                draw_sprite(buffer, tileset[TILE_CHAO], coluna * 32, linha * 32);
                break;

            case TILE_PAREDE:
                draw_sprite(buffer, tileset[TILE_PAREDE], coluna * 32, linha * 32);
                break;

            case TILE_PONTO:
                draw_sprite(buffer, tileset[TILE_PONTO], coluna * 32, linha * 32);
                break;

            case TILE_CAIXA:
                draw_sprite(buffer, tileset[TILE_CAIXA], coluna * 32, linha * 32);
                break;
            }
    return buffer;
}
