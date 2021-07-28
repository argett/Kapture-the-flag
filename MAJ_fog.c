#include "proto.h"
#include <SDL/SDL.h>

void fillFog (int **fog, int drapeauX, int drapeauY)
{
    int i,j, a,b;

    for (i=0; i<sizeMaxField; i++)
    {
        for (j=0; j<sizeMaxField; j++)
        {
            fog[i][j] = 0;
        }
    }

    for (a = (-1); a <= 1; a++)
    {
        for (b = (-1); b <= 1; b++)
        {
            fog[drapeauY + b][drapeauX + a] = 0;
        }
    }
}


void MAJfog(TypEquipe* equipe, int **fog)
{
    int cpt, i, j;
    for(cpt=0;cpt<=4;cpt++)
    {
        if (equipe->fantassin[cpt].statut == 1)
        {
            for (i=(-1); i<=1; i+=1) //dans un rayon du 1 case, on enleve le fog
            {
                for (j=(-1); j<=1; j+=1)
                {
                    TESTfog(&(equipe->fantassin[cpt]), fog, i, j);
                }
            }
        }
        if (equipe->mobile[cpt].statut == 1)
        {
            for (i=(-1); i<=1; i+=1)
            {
                for (j=(-1); j<=1; j+=1)
                {
                    TESTfog(&(equipe->mobile[cpt]), fog, i, j);
                }
            }
        }
        if (equipe->lourde[cpt].statut == 1)
        {
            for (i=(-2); i<=2; i+=1)
            {
                for (j=(-2); j<=2; j+=1)
                {
                    TESTfog(&(equipe->lourde[cpt]), fog, i, j);
                }
            }
        }
    }
    if (equipe->drone.statut == 1) //comme on a 1 seul drone, pas besoin de do while
    {
        TESTfog(&(equipe->drone), fog, 0, 0);
    }
}

void TESTfog(TypUnite* unite, int** fog, int i, int j)
{
    //on regarde si les coord du fog ne depassent pas la  taille du tableau --> C'est (sizeMaxField-1) car la tableau a sizeMaxField cases et commence à 0
    if (((unite->position.y)/24+j <= sizeMaxField-1) && (unite->position.y)/24+j >= 0) //bas, haut
    {
        if (((unite->position.x)/24+i <= sizeMaxField-1) && (unite->position.x)/24+i >= 0) //droite, gauche
        {
            int a = fog[3][5];
            fog[((unite->position.y)/24)+j][((unite->position.x)/24)+i] = 0;
        }
    }
}

void afficherFog(SDL_Surface* fogMap, SDL_Rect* positionFog, int** fog)
{
    int i,j;
    for (i=0; i<sizeMaxField; i++)
    {
        for (j=0; j<sizeMaxField; j++)
        {
            if (fog[i][j] == 1)
            {
                positionFog->x = (24*j);
                positionFog->y = (24*i) ;
                SDL_BlitSurface(fogMap, NULL, ecran, positionFog) ;
            }
        }
    }
}
