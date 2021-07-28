#ifndef COMBAT_H_INCLUDED
#define COMBAT_H_INCLUDED
#include <SDL/SDL.h>
#include "proto.h"

void afficherRange(SDL_Rect* positionAllie, int range, SDL_Surface* fog_eqpAllie, SDL_Rect* positionFog_eqpAllie, int** fogAllie);
void fenetreErreurDrone();
void fenetreErreurPortee();
void jappuiSurLaSouris(int range, TypUnite* allier, TypEquipe* enemis, int joueur);
void click_sur_enemis_ou_non(int tableauCoord[2], TypUnite* allier, TypEquipe* enemis, int joueur);
void application_des_dmg(TypUnite* allier, TypUnite* enemis_qui_encaisse_les_degats);
void fenetreAveugle();

#endif // COMBAT_H_INCLUDED

extern int sizeMaxField;
extern int continuer;
extern SDL_Surface *ecran;
extern SDL_Surface* fog_mapRouge;
extern SDL_Surface* fog_mapBleu;
extern SDL_Surface *positionUniteActuelle;
extern SDL_Surface *Rouge_fantassin, *Rouge_mobile, *Rouge_lourde, *Rouge_drone;
extern SDL_Surface *Bleu_fantassin, *Bleu_mobile, *Bleu_lourde, *Bleu_drone;
extern SDL_Surface *Bleu_flag,  *Rouge_flag;
