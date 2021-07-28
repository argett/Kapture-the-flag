#ifndef PROTO_H_INCLUDED
#define PROTO_H_INCLUDED
#include <SDL/SDL.h>


typedef struct {
    int deplacement;
    int pv;
    int attk;
    int statut;
    int eauLLreadyINwater;
    SDL_Rect position;
}TypUnite;

typedef struct {
    TypUnite fantassin[5];
    TypUnite mobile[5];
    TypUnite lourde[5];
    TypUnite drone;
    SDL_Rect base;
    int PV_base;
}TypEquipe;

void fillFog(int **fog, int drapeauX, int drapeauY);
void MAJfog(TypEquipe* equipe, int **fog);
void TESTfog(TypUnite* unite, int** fog, int i, int j);
void afficherFog(SDL_Surface* fogMap, SDL_Rect* positionFog, int** fog);


void initEquipe(TypEquipe* Equipe, SDL_Rect* Drapeau);
void position(TypEquipe* Equipe);
void onTestLesCase(TypUnite* unite,int cpt, SDL_Rect* base);
void loadIMG();
#include "combat.h"
#endif // PROTO_H_INCLUDED

extern int f,m,l;
extern int sizeMaxField;
extern int unite_dans_le_champ_ou_non;

extern SDL_Surface* explosion[8];
extern SDL_Surface *ecran;
extern TypEquipe rouge;
extern TypEquipe bleu;
extern SDL_Surface* fog_mapRouge;
extern SDL_Surface* fog_mapBleu;
extern SDL_Surface *positionUniteActuelle;
extern SDL_Surface *Rouge_fantassin, *Rouge_mobile, *Rouge_lourde, *Rouge_drone;
extern SDL_Surface *Bleu_fantassin, *Bleu_mobile, *Bleu_lourde, *Bleu_drone;
extern SDL_Surface *Bleu_flag,  *Rouge_flag;
extern SDL_Surface *Eau, *Terre, *Herbe;
