#include "menu.h"

CMenu::~CMenu()
{
	destroy_bitmap(imagem);
}

void CMenu::Draw()
{
	static BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
	clear_to_color(buffer, makecol(255, 255, 255));
	blit(imagem, buffer, 0, 0, 0, 0, imagem->w, imagem->h);
	for (int i = 0; i < numeroItens; i++)
		textprintf_ex(buffer, font, 50, 270 + i * 8, (i == focus ? corFonteHighlited : corFonte ), this->corFundo, "%s", nomeItens[i].c_str());
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}



void CMenu::Init()
{
    numeroItens = 3;
	nomeItens[0] = "Jogar";
	nomeItens[1] = "Opções";
	nomeItens[2] = "Sair";
	focus = 0;
	corFonte = makecol(255, 255, 255);
	corFonteHighlited = makecol(255, 255, 0);
	corFundo = -1;
	imagem = load_bmp("res/titulo.bmp", NULL);
	if (!imagem)
		raise_error("Não foi possível carregar a imagem do menu.");
}


void CMenu::FocusUp()
{
	if (focus > 0)
		focus--;
}



void CMenu::FocusDown()
{
	if (focus < numeroItens - 1)
		focus++;
}
