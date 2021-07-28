#ifndef AFFICHER_H_INCLUDED
#define AFFICHER_H_INCLUDED

void afficherTOUT(int joueur, TypUnite* unite, int choix, int ancienX, int ancienY);
void afficherUnite(TypEquipe* equipe, int joueur);
void afficherCarte(int choix, TypUnite* joueur, int ancienX, int ancienY);
void afficherEnemis(int joueur);
void CheckUnite(TypUnite* allier, int joueur, int choix);
void checkUniteBleu(SDL_Rect uniteAllieRougeAComparer, int cpt2, int choix, int rangeVision);
void checkUniteRouge(SDL_Rect uniteAllieBleuAComparer, int cpt2, int choix, int rangeVision);
int compareAutour(SDL_Rect positionAllie, TypUnite* Enemi, int range);
void afficherBase();
void afficherExplosion(SDL_Rect* ennemis, int joueur, TypUnite* allier);

#endif // AFFICHER_H_INCLUDED

extern SDL_Surface *ecran;
extern int joueur;
extern int sizeMaxField;
extern int unite_dans_le_champ_ou_non;
extern int** fogRouge;
extern int** fogBleu;
extern int** terrain;

extern TypEquipe rouge;
extern TypEquipe bleu;
extern SDL_Surface* explosion[8];
extern SDL_Surface* fog_mapRouge;
extern SDL_Surface* fog_mapBleu;
extern SDL_Surface *positionUniteActuelle;
extern SDL_Surface *Rouge_fantassin, *Rouge_mobile, *Rouge_lourde, *Rouge_drone;
extern SDL_Surface *Bleu_fantassin, *Bleu_mobile, *Bleu_lourde, *Bleu_drone;
extern SDL_Surface *Bleu_flag,  *Rouge_flag;
extern SDL_Surface *Eau, *Terre, *Herbe;
