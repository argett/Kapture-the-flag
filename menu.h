#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SDL/SDL.h>
#include "proto.h"
#include <time.h>

void Menu(SDL_Rect* positionRougeFlag, SDL_Surface* spawnFlagR, SDL_Rect* positionBleuFlag, SDL_Surface* spawnFlagB);
void Menu1(SDL_Surface* ecran,SDL_Surface* fondEcran,SDL_Rect positionEcran,SDL_Event event);
void Menu2(SDL_Surface* ecran,SDL_Surface* fondEcran,SDL_Rect positionEcran,SDL_Event event);
void Menu3(SDL_Surface* ecran,SDL_Surface* fondEcran,SDL_Rect positionEcran,SDL_Event event);
void ChoisirBase(SDL_Surface* ecran,SDL_Surface* fondEcran,SDL_Rect positionEcran,SDL_Event event, SDL_Rect* positionRougeFlag, SDL_Surface* spawnFlagR, SDL_Rect* positionBleuFlag, SDL_Surface* spawnFlagB);
void creationCarte();
void aleaCo(int usk2, int a);
void aleaLi(int usk2, int a);

#endif // MENU_H_INCLUDED

extern int f,m,l;
extern int sizeMaxField;
extern int **terrain;
extern TypEquipe rouge;
extern TypEquipe bleu;
