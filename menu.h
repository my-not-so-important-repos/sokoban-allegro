/*
-----------------------------------------------
Menu System
-----------------------------------------------
*/

#ifndef MENU_H
#define MENU_H

#include <allegro.h>
#include "error.h"
#include <string>
//using namespace std;

/*! \class CMenu
*/
class CMenu
{
private:
	BITMAP *imagem;
	std::string nomeItens[3];
	int numeroItens;
	int corFonte, corFonteHighlited, corFundo;

public:
	int focus;

	~CMenu();
	void Draw();
	void Init();
	void FocusUp();
	void FocusDown();
};






#endif
