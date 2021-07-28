#include "proto.h"
#include "afficher.h"
#include "jeu.h"


void afficherTOUT(int joueur, TypUnite* unite, int choix, int ancienX, int ancienY)
{
    int** fogAllie;
    TypEquipe eqpAllie;
    SDL_Surface* fog_eqpAllie;
    SDL_Rect positionFog_eqpAllie;

    if (joueur%2 == 1)
    {
        eqpAllie = rouge;
        fog_eqpAllie = fog_mapRouge;
        fogAllie = fogRouge;
    }
    else
    {
        eqpAllie = bleu;
        fog_eqpAllie = fog_mapBleu;
        fogAllie = fogBleu;
    }
    afficherCarte(choix, unite, ancienX, ancienY);

    //cadre pour montrer l unite actuelle
    SDL_SetColorKey(positionUniteActuelle, SDL_SRCCOLORKEY, SDL_MapRGB(positionUniteActuelle->format, 224, 0, 192));
    SDL_BlitSurface(positionUniteActuelle, NULL, ecran, &(unite->position));
    //-----------------------------------

    afficherUnite(&eqpAllie, joueur); //on affiche unite
    afficherEnemis(joueur);
    MAJfog(&eqpAllie, fogAllie);
    afficherFog(fog_eqpAllie, &positionFog_eqpAllie, fogAllie); //on affiche le fog apres les unite pour les cache si besoin
}

void afficherUnite(TypEquipe* equipe, int joueur)
{
    int cpt;
    afficherBase();

    for(cpt=0;cpt<=4;cpt++)  //on regrde les 5 unites du tableau et on vérifie si elle sont vivntes ou non
    {
        if (joueur%2==1)
        {
            if (equipe->fantassin[cpt].statut == 1)
            {
                SDL_SetColorKey(Rouge_fantassin, SDL_SRCCOLORKEY, SDL_MapRGB(Rouge_fantassin->format, 224, 0, 192));
                SDL_BlitSurface(Rouge_fantassin, NULL, ecran, &(equipe->fantassin[cpt].position));
            }
            if (equipe->mobile[cpt].statut == 1)
            {
                SDL_SetColorKey(Rouge_mobile, SDL_SRCCOLORKEY, SDL_MapRGB(Rouge_mobile->format, 224, 0, 192));
                SDL_BlitSurface(Rouge_mobile, NULL, ecran, &equipe->mobile[cpt].position);
            }
            if (equipe->lourde[cpt].statut == 1)
            {

                SDL_SetColorKey(Rouge_lourde, SDL_SRCCOLORKEY, SDL_MapRGB(Rouge_lourde->format, 224, 0, 192));
                SDL_BlitSurface(Rouge_lourde, NULL, ecran, &equipe->lourde[cpt].position);
            }
            if (equipe->drone.statut == 1) //comme on a 1 seul drone, pas besoin de do while
            {
                SDL_SetColorKey(Rouge_drone, SDL_SRCCOLORKEY, SDL_MapRGB(Rouge_drone->format, 224, 0, 192));
                SDL_BlitSurface(Rouge_drone, NULL, ecran, &equipe->drone.position);
            }
        }
        else
        {
            if (equipe->fantassin[cpt].statut == 1)
            {
                SDL_SetColorKey(Bleu_fantassin, SDL_SRCCOLORKEY, SDL_MapRGB(Bleu_fantassin->format, 224, 0, 192));
                SDL_BlitSurface(Bleu_fantassin, NULL, ecran, &(equipe->fantassin[cpt].position));
            }
            if (equipe->mobile[cpt].statut == 1)
            {
                SDL_SetColorKey(Bleu_mobile, SDL_SRCCOLORKEY, SDL_MapRGB(Bleu_mobile->format, 224, 0, 192));
                SDL_BlitSurface(Bleu_mobile, NULL, ecran, &(equipe->mobile[cpt].position));
            }
            if (equipe->lourde[cpt].statut == 1)
            {
                SDL_SetColorKey(Bleu_lourde, SDL_SRCCOLORKEY, SDL_MapRGB(Bleu_lourde->format, 224, 0, 192));
                SDL_BlitSurface(Bleu_lourde, NULL, ecran, &(equipe->lourde[cpt].position));
            }
            if (equipe->drone.statut == 1)
            {
                SDL_SetColorKey(Bleu_drone, SDL_SRCCOLORKEY, SDL_MapRGB(Bleu_drone->format, 224, 0, 192));
                SDL_BlitSurface(Bleu_drone, NULL, ecran, &(equipe->drone.position));
            }
        }
    }
}

void afficherCarte(int choix, TypUnite* unite, int ancienX, int ancienY)
{
    int i,j;
    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;
    if (choix == 0) //on change d'équipe, on réaffiche tout
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); //on efface l'ecran (ou rempli de blanc)
        for (i=0;i<sizeMaxField;i++)
        {
            for (j=0;j<sizeMaxField;j++)
            {
                switch(terrain[i][j])
                {
                    case 0:
                    {
                        SDL_BlitSurface(Terre, NULL, ecran, &positionFond); //on affiche la carte
                        break;
                    }
                    case 1:
                    {
                        SDL_BlitSurface(Herbe, NULL, ecran, &positionFond); //on affiche la carte
                        break;
                    }
                    case 2:
                    {
                        SDL_BlitSurface(Eau, NULL, ecran, &positionFond); //on affiche la carte
                        break;
                    }
                    default:
                        break;
                }
                positionFond.x +=24; // IMPORTANT
                fprintf(stderr,"%d ",terrain[i][j]);
            }
            positionFond.y +=24;  // IMPORTANT
            positionFond.x = 0;   // IMPORTANT
            fprintf(stderr, "\n");
        }
        fprintf(stderr, "\n\n");
        SDL_Flip(ecran);
    } //-------------------------------------------------------------------------------
    else //mvmt même unité
    {
        positionFond.x = unite->position.x;
        positionFond.y = unite->position.y;
        switch(terrain[unite->position.y/24][unite->position.x/24])
        {
            case 0:
            {
                SDL_BlitSurface(Terre, NULL, ecran, &positionFond); //on affiche la carte
                break;
            }
            case 1:
            {
                SDL_BlitSurface(Herbe, NULL, ecran, &positionFond); //on affiche la carte
                break;
            }
            case 2:
            {
                SDL_BlitSurface(Eau, NULL, ecran, &positionFond); //on affiche la carte
                break;
            }
            default:
                fprintf(stderr,"\n erreur de chatgement image pour affichage terrain/mm joueur à la case '%d/%d' \n",unite->position.x,unite->position.y);
                break;
        }
        //----------------------------------------------------------------------------------
        int enX, enY;
        enX=(unite->position.x/24)+(ancienX/24);
        enY=(unite->position.y/24)+(ancienY/24);
        positionFond.x = unite->position.x+ancienX;
        positionFond.y = unite->position.y+ancienY;
        switch(terrain[enY][enX])
        {
            case 0:
            {
                SDL_BlitSurface(Terre, NULL, ecran, &positionFond); //on affiche la carte
                break;
            }
            case 1:
            {
                SDL_BlitSurface(Herbe, NULL, ecran, &positionFond); //on affiche la carte
                break;
            }
            case 2:
            {
                SDL_BlitSurface(Eau, NULL, ecran, &positionFond); //on affiche la carte
                break;
            }
            default:
                fprintf(stderr,"\n erreur de chatgement image pour affichage terrain/mm joueur à la case '%d/%d' \n",unite->position.x,unite->position.y);
                break;
        }
    }
    SDL_Flip(ecran);
}

void afficherEnemis(int joueur)
{
    int cpt;

    if (joueur%2 == 1)
    {
        for (cpt=0; cpt<=4;cpt++)  //on regrde les 5 unites du tableau et on vérifie si elle sont vivntes ou non
        {
            if (rouge.fantassin[cpt].statut == 1)
                CheckUnite(&(rouge.fantassin[cpt]), joueur, 0);

            if (rouge.mobile[cpt].statut == 1)
                CheckUnite(&(rouge.mobile[cpt]), joueur, 0);

            if (rouge.lourde[cpt].statut == 1)
                CheckUnite(&(rouge.lourde[cpt]), joueur, 0);
        }
    }
    else
    {
        for (cpt=0; cpt<=4;cpt++)  //on regrde les 5 unites du tableau et on vérifie si elle sont vivntes ou non
        {
            if (bleu.fantassin[cpt].statut == 1)
                CheckUnite(&(bleu.fantassin[cpt]), joueur, 0);

            if (bleu.mobile[cpt].statut == 1)
                CheckUnite(&(bleu.mobile[cpt]), joueur, 0);

            if (bleu.lourde[cpt].statut == 1)
                CheckUnite(&(bleu.lourde[cpt]), joueur, 0);
        }
    }
}

void CheckUnite(TypUnite* allier, int joueur, int choix)
{
    int cpt2;
    int rangeVision;

    if (allier->deplacement == 3) {rangeVision = 2;} //pour savoir dans 2 fonctions le diametre du cercle de vision en nb de case
    else {rangeVision = 1;} //les lourdes ayant 2 de vision, les autres n'ont que 1 donc c'est le cas  "else"

    for(cpt2=0;cpt2<=4;cpt2++)  //on regarde les 5 unites du tableau et on vérifie si elle sont vivntes ou non
    {
        if (joueur%2 == 1) {checkUniteBleu(allier->position, cpt2, choix, rangeVision);}
        else {checkUniteRouge(allier->position, cpt2, choix, rangeVision);}
    }
}

void checkUniteBleu(SDL_Rect uniteAllieRougeAComparer, int cpt2, int choix, int rangeVision)
{
    if (bleu.fantassin[cpt2].statut == 1)
    {
        if ((compareAutour(uniteAllieRougeAComparer, &(bleu.fantassin[cpt2]), rangeVision)) == 1)
        {
            if (choix==0) //on se sert de cette fonction pour afficher les unitees enemies
            {
                SDL_SetColorKey(Bleu_fantassin, SDL_SRCCOLORKEY, SDL_MapRGB(Bleu_fantassin->format, 224, 0, 192));
                SDL_BlitSurface(Bleu_fantassin, NULL, ecran, &(bleu.fantassin[cpt2].position));
            }
            if (choix==1) //ici  c'est pour voir si il y a bien un enemis avant de lancer la fonction combat
            {
                unite_dans_le_champ_ou_non=1;
            }
        }
        //si la base est à côté de l'ennemis afin que celui-ci l'attaquer sans présence  d'énnemis
        if (choix == 1)
        {
            checkBase(&(rouge.base),&(bleu.fantassin[cpt2]),rangeVision);
        }
    }
    if (bleu.mobile[cpt2].statut == 1)
    {
        if ((compareAutour(uniteAllieRougeAComparer, &(bleu.mobile[cpt2]), rangeVision)) == 1)
        {
            if (choix==0)
            {
                SDL_SetColorKey(Bleu_mobile, SDL_SRCCOLORKEY, SDL_MapRGB(Bleu_mobile->format, 224, 0, 192));
                SDL_BlitSurface(Bleu_mobile, NULL, ecran, &(bleu.mobile[cpt2].position));
            }
            if (choix==1)
            {
                unite_dans_le_champ_ou_non=1;
            }
        }
        //si la base est à côté pour l'attaquer sans présence  d'énnemis
        if (choix == 1)
        {
            checkBase(&(rouge.base),&(bleu.mobile[cpt2]),rangeVision);
        }
    }
    if (bleu.lourde[cpt2].statut == 1)
    {
        if ((compareAutour(uniteAllieRougeAComparer, &(bleu.lourde[cpt2]), rangeVision)) == 1)
        {
            if (choix==0)
            {
                SDL_SetColorKey(Bleu_lourde, SDL_SRCCOLORKEY, SDL_MapRGB(Bleu_lourde->format, 224, 0, 192));
                SDL_BlitSurface(Bleu_lourde, NULL, ecran, &(bleu.lourde[cpt2].position));
            }
            if (choix==1)
            {
                unite_dans_le_champ_ou_non=1;
            }
        }
        //si la base est à côté pour l'attaquer sans présence  d'énnemis
        if (choix == 1)
        {
            checkBase(&(rouge.base),&(bleu.lourde[cpt2]),rangeVision);
        }
    }
    //il n'y a pas de drone car il ne devoile pas les enemis
}

void checkUniteRouge(SDL_Rect uniteAllieBleuAComparer, int cpt2, int choix, int rangeVision)
{
    if (rouge.fantassin[cpt2].statut == 1)
    {
        if ((compareAutour(uniteAllieBleuAComparer, &(rouge.fantassin[cpt2]), rangeVision)) == 1)
        {
            if (choix==0)
            {
                SDL_SetColorKey(Rouge_fantassin, SDL_SRCCOLORKEY, SDL_MapRGB(Rouge_fantassin->format, 224, 0, 192));
                SDL_BlitSurface(Rouge_fantassin, NULL, ecran, &(rouge.fantassin[cpt2].position));
            }
            if (choix==1)
            {
                unite_dans_le_champ_ou_non=1;
            }
        }
        //si la base est à côté pour l'attaquer sans présence  d'énnemis
        if (choix == 1)
        {
            checkBase(&(bleu.base),&(rouge.fantassin[cpt2]),rangeVision);
        }
    }
    if (rouge.mobile[cpt2].statut == 1)
    {
        if ((compareAutour(uniteAllieBleuAComparer, &(rouge.mobile[cpt2]), rangeVision)) == 1)
        {
            if (choix==0)
            {
                SDL_SetColorKey(Rouge_mobile, SDL_SRCCOLORKEY, SDL_MapRGB(Rouge_mobile->format, 224, 0, 192));
                SDL_BlitSurface(Rouge_mobile, NULL, ecran, &(rouge.mobile[cpt2].position));
            }
            if (choix==1)
            {
                unite_dans_le_champ_ou_non=1;
            }
        }
        //si la base est à côté pour l'attaquer sans présence  d'énnemis
        if (choix == 1)
        {
            checkBase(&(bleu.base),&(rouge.mobile[cpt2]),rangeVision);
        }
    }
    if (rouge.lourde[cpt2].statut == 1)
    {
        if ((compareAutour(uniteAllieBleuAComparer, &(rouge.lourde[cpt2]), rangeVision)) == 1)
        {
            if (choix==0)
            {
                SDL_SetColorKey(Rouge_lourde, SDL_SRCCOLORKEY, SDL_MapRGB(Rouge_lourde->format, 224, 0, 192));
                SDL_BlitSurface(Rouge_lourde, NULL, ecran, &(rouge.lourde[cpt2].position));
            }
            if (choix==1)
            {
                unite_dans_le_champ_ou_non=1;
            }
        }
        //si la base est à côté pour l'attaquer sans présence  d'énnemis
        if (choix == 1)
        {
            checkBase(&(bleu.base),&(rouge.lourde[cpt2]),rangeVision);
        }
    }
    //il n'y a pas de drone car il ne devoile pas les enemis
}

void checkBase(SDL_Rect* base,TypUnite* Enemi, int rangeVision)
{
    int i,j;
    for (i=-24*rangeVision; i<=24*rangeVision; i+=24) //la range est le diametre en nombre de case où l'on regarde autour de l'unite
    {
        for (j=-24*rangeVision; j<=24*rangeVision; j+=24) //la Lourde a une range de 2
        {
            if ((base->x+i) == Enemi->position.x)
            {
                if ((base->y+j) == Enemi->position.y)
                {
                    unite_dans_le_champ_ou_non=1;
                }
            }
        }
    }
}

int compareAutour(SDL_Rect positionAllie, TypUnite* Enemi, int range)
{
    int i,j;

    for (i=-24*range; i<=24*range; i+=24) //la range est le diametre en nombre de case où l'on regarde autour de l'unite
    {
        for (j=-24*range; j<=24*range; j+=24) //la Lourde a une range de 2
        {
            if ((positionAllie.x+i) == Enemi->position.x)
            {
                if ((positionAllie.y+j) == Enemi->position.y)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void afficherBase()
{
    SDL_SetColorKey(Rouge_flag, SDL_SRCCOLORKEY, SDL_MapRGB(Rouge_flag->format, 224, 0, 192));
    SDL_BlitSurface(Rouge_flag, NULL, ecran, &(rouge.base));

    SDL_SetColorKey(Bleu_flag, SDL_SRCCOLORKEY, SDL_MapRGB(Bleu_flag->format, 224, 0, 192));
    SDL_BlitSurface(Bleu_flag, NULL, ecran, &(bleu.base));
}

void afficherExplosion(SDL_Rect* ennemis, int joueur, TypUnite* allier)
{
    int i, a;
    for (i=0;i<=7;i++)
    {
        afficherCarte(1, allier, 0, 0);
        SDL_SetColorKey(explosion[i], SDL_SRCCOLORKEY, SDL_MapRGB(explosion[i]->format, 224, 0, 192));
        SDL_BlitSurface(explosion[i], NULL, ecran, ennemis);
        SDL_Flip(ecran);
        for (a=0;a<=30000000;a++){;}
    }
    afficherCarte(0, allier, 0, 0); //pour enlever la dernière frame de l'explosion

}
