#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <SDL/SDL.h>
#include "proto.h"
#include "afficher.h"

void leJeuCommence(TypEquipe* rouge,  int** fogRouge, TypEquipe* bleu, int** fogBleu);
void mouvementEquipe(TypEquipe* eqpAllie, TypEquipe* eqpEnemie, SDL_Surface* fog_eqpAllie, SDL_Rect* positionFog_eqpAllie, int** fogAllie);
void mouvementUnite (TypUnite* unite, TypEquipe* eqpAllie, int** fogAllie, SDL_Surface* fog_eqpAllie, SDL_Rect* positionFog_eqpAllie, TypEquipe* eqpEnemie);
void deplacement(int futurX, int futurY, TypUnite* unite, TypEquipe* eqpAllie, TypEquipe* eqpEnemie);
int collision(int futurX, int futurY, TypUnite* unite, TypEquipe* eqpAllie, TypEquipe* eqpEnemie);
void onEnleveLeMvmnt (int* nbMvmnt, TypUnite* unite);

//combat ou non est dans le fichier "combat.c" mais déclarée ici pour des raisons d'ordre de déclaration de variables
void combatOUnon(TypUnite* unite, int joueur, SDL_Surface* fog_eqpAllie, SDL_Rect* positionFog_eqpAllie, int** fogAllie, TypEquipe* allier, TypEquipe* enemis);

#endif // JEU_H_INCLUDED

extern SDL_Surface *ecran;
extern int joueur;
extern int sizeMaxField;
extern int unite_dans_le_champ_ou_non;
extern int continuer;
extern int **terrain;
extern TypEquipe rouge;
extern TypEquipe bleu;
extern SDL_Surface* fog_mapRouge;
extern SDL_Surface* fog_mapBleu;
extern SDL_Surface *positionUniteActuelle;
extern SDL_Surface *Rouge_fantassin, *Rouge_mobile, *Rouge_lourde, *Rouge_drone;
extern SDL_Surface *Bleu_fantassin, *Bleu_mobile, *Bleu_lourde, *Bleu_drone;
extern SDL_Surface *Bleu_flag,  *Rouge_flag;
