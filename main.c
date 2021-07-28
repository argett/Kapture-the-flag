#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "proto.h"
#include "menu.h"
#include "jeu.h"
#include "combat.h"
#include "afficher.h"

int sizeMaxField;
int f,m,l;
int unite_dans_le_champ_ou_non;
int continuer = 1;
int **terrain;

int **fogRouge ;
int **fogBleu ;

SDL_Surface *ecran = NULL;
TypEquipe rouge;
TypEquipe bleu;
SDL_Surface* explosion[8]; //tableau des 8 frames d'explosion

SDL_Surface* fog_mapRouge = NULL;
SDL_Surface* fog_mapBleu= NULL;
SDL_Surface* positionUniteActuelle = NULL;
SDL_Surface* Rouge_fantassin = NULL, *Rouge_mobile = NULL, *Rouge_lourde = NULL, *Rouge_drone = NULL;
SDL_Surface* Bleu_fantassin = NULL, *Bleu_mobile = NULL, *Bleu_lourde = NULL, *Bleu_drone = NULL;
SDL_Surface* Bleu_flag = NULL,  *Rouge_flag = NULL ;
SDL_Surface* Eau = NULL, *Terre = NULL, *Herbe = NULL;


int main(int argc, char *argv[])
{
    SDL_Surface *spawnFlagR = NULL, *spawnFlagB = NULL;
    SDL_Rect positionRougeFlag, positionBleuFlag ;
    SDL_Rect positionSpawnFlagRouge, positionSpawnFlagBleu;

    spawnFlagR = SDL_LoadBMP("red_flagSpawn.bmp");
    spawnFlagB = SDL_LoadBMP("blue_flagSpawn.bmp");
/*
    positionRougeFlag.x = 6*24;
    positionRougeFlag.y = 6*24;
    positionBleuFlag.x = 18*24;
    positionBleuFlag.y = 18*24;
*/
    Menu(&positionRougeFlag, spawnFlagR, &positionBleuFlag, spawnFlagB);    //on choisi la composition de l'equipe et la position des bases
    positionSpawnFlagRouge = positionRougeFlag;
    positionSpawnFlagBleu = positionBleuFlag;

    int a,b;

    int **fogRouge ;
    int **fogBleu ;

    fogRouge = (int **)malloc(sizeMaxField * sizeof(int*)) ;
    fogBleu = (int **)malloc(sizeMaxField * sizeof(int*)) ;

    for (a=0; a<sizeMaxField; a++)
        fogRouge[a] = (int*)malloc(sizeMaxField * sizeof(int));
    for (b=0; b<sizeMaxField; b++)
        fogBleu[b] = (int*)malloc(sizeMaxField * sizeof(int));

    for (a=0; a<sizeMaxField; a++)
        free(fogRouge[a]);
    for (b=0; b<sizeMaxField; b++)
        free(fogBleu[b]);
    free(fogRouge);
    free(fogBleu);


    initEquipe(&rouge, &positionSpawnFlagRouge);
    initEquipe(&bleu, &positionSpawnFlagBleu);

    //on rempli la carte de fog
    fillFog(fogRouge, (positionRougeFlag.x)/24, (positionRougeFlag.y)/24);
    fillFog(fogBleu, (positionBleuFlag.x)/24, (positionBleuFlag.y)/24);

    //-------------------------CHARGEMENT DE LA SDL----------------------------
    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
    loadIMG();
    SDL_WM_SetIcon(SDL_LoadBMP("Kapture_icone.bmp"), NULL); //  mettre l'icone avant le set_video_mode
    ecran = SDL_SetVideoMode(24*sizeMaxField, 24*sizeMaxField, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //doublebuff est pour l'optimisation d'imge et �viter les scitillements
    SDL_WM_SetCaption("Kapture", NULL);
    if (ecran == NULL) // Si l'ouverture a �chou�, on le note et on arr�te
    {
        fprintf(stderr, "Impossible de charger le mode video : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    //---------------------------------------------------------------------------------

    leJeuCommence(&rouge, fogRouge, &bleu, fogBleu); //en faite c'est tout le jeu qui est là mdr

/*
    for (i=0; i<sizeMaxField; i++)
    {
        free(terrain[i]) ;
    }*/
    //SDL_FreeSurface(imgDeFond); // Libération de la surface

    for (a=0; a<sizeMaxField; a++)
        free(fogRouge[a]);
    for (b=0; b<sizeMaxField; b++)
        free(fogBleu[b]);
    free(fogRouge);
    free(fogBleu);


    SDL_Quit();

    return EXIT_SUCCESS;
}
