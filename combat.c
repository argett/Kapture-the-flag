#include "combat.h"
#include "proto.h"

void combatOUnon(TypUnite* unite, int joueur, SDL_Surface* fog_eqpAllie, SDL_Rect* positionFog_eqpAllie, int** fogAllie, TypEquipe* allier, TypEquipe* enemis)
{
    unite_dans_le_champ_ou_non = 0;
    switch (unite->deplacement)
    {
        case 3: //lourde a une range de 2 pour attaquer
            CheckUnite(unite, joueur, 1);
            if (unite_dans_le_champ_ou_non==1)
            {
                afficherRange(&(unite->position), 2,fog_eqpAllie, positionFog_eqpAllie, fogAllie);
                jappuiSurLaSouris(2, unite, enemis, joueur);
            }
            break;

        case 10: //drone n'attaque pas
            fenetreErreurDrone();
            break;

        default: //fantassin et mobile ont une range de 1
            CheckUnite(unite, joueur, 1);
            if (unite_dans_le_champ_ou_non==1)
            {
                afficherRange(&(unite->position), 1, fog_eqpAllie, positionFog_eqpAllie, fogAllie);
                jappuiSurLaSouris(1, unite, enemis, joueur);
            }
            break;
    }
    if (unite_dans_le_champ_ou_non == 0 && unite->deplacement != 10) //pas d'unite enemies a portée
    {
        fenetreErreurPortee();
    }
    afficherTOUT(joueur, unite, 0, 0, 0); //on enlève l'image
    SDL_Flip(ecran);
}

void fenetreErreurDrone()
{
    int i;
    SDL_Surface* msgdErreur = NULL;
    msgdErreur = SDL_LoadBMP("erreur drone.bmp");
    SDL_Rect positionMSG;
    positionMSG.x = ((sizeMaxField*24)/2)-135; //la largeur de l'img est de 170 pixel
    positionMSG.y = ((sizeMaxField*24)/2)-82 ; //la hauteur est de 164p

    SDL_SetColorKey(msgdErreur, SDL_SRCCOLORKEY, SDL_MapRGB(msgdErreur->format, 224, 0, 192));
    SDL_BlitSurface(msgdErreur, NULL, ecran, &positionMSG);
    SDL_Flip(ecran);

    for(i=0;i<=300000000;i++) {;} //une sorte de pause pour que l'image reste affichée
}

void fenetreErreurPortee()
{
    int i;
    SDL_Surface* msgdErreur = NULL;
    msgdErreur = SDL_LoadBMP("erreur portee.bmp");
    SDL_Rect positionMSG;
    positionMSG.x = ((sizeMaxField*24)/2)-135; //la largeur de l'img est de 270 pixel
    positionMSG.y = ((sizeMaxField*24)/2)-82 ; //la hauteur est de 164p

    SDL_SetColorKey(msgdErreur, SDL_SRCCOLORKEY, SDL_MapRGB(msgdErreur->format, 224, 0, 192));
    SDL_BlitSurface(msgdErreur, NULL, ecran, &positionMSG);
    SDL_Flip(ecran);

    for(i=0;i<=300000000;i++) {;} //une sorte de pause pour que l'image reste affichée
}

void afficherRange(SDL_Rect* positionAllie, int range, SDL_Surface* fog_eqpAllie, SDL_Rect* positionFog_eqpAllie, int** fogAllie)
{
    //la range est le diametre de vision d'une unite; Par ex le fantassin c'est un  carre de 1 de cote donc 9 cases
    SDL_Surface* caseBaree = NULL;
    SDL_Rect positionCaseBaree;
    caseBaree = SDL_LoadBMP("range_non_attaque.bmp");

    int a,b,i,j;
    int cpt;

    for (a=0;a<=sizeMaxField*24;a+=24) //on a en range la carte entière
    {
        for (b=0;b<=sizeMaxField*24;b+=24)
        {
            cpt=0;
            for (i=-24*range; i<=24*range; i+=24) //on a la range de l'unite
            {
                for (j=-24*range; j<=24*range; j+=24)
                {
                    if (((positionAllie->x+i) == a) && ((positionAllie->y+j) == b)) //si la case (a,b) ne correspond pas aux cases vision (x,y) alors on peux barrer cette case
                    {
                        cpt++;
//en faite, ici le programme check les cases (a,b) une par une puis regarde si cette case est autour de l'unite (dans sa range).
//donc a chaque case (a,b) il check 9 fois, or si (a,b) est 1 des 9 (x,y) alors elle est dans la range. Donc il faut que cpt n'augmente jamais
                    }
                }
            }
            if (cpt==0)
            {
                positionCaseBaree.x=a;
                positionCaseBaree.y=b;
                SDL_SetColorKey(caseBaree, SDL_SRCCOLORKEY, SDL_MapRGB(caseBaree->format, 224, 0, 192));
                SDL_BlitSurface(caseBaree, NULL, ecran, &(positionCaseBaree));
            }
        }
    }
    afficherFog(fog_eqpAllie, positionFog_eqpAllie, fogAllie); //autant ne barrer que la map visible, en plus du gris barré de violet c'est moche
    SDL_Flip(ecran);
}

void jappuiSurLaSouris(int range, TypUnite* allier, TypEquipe* enemis, int joueur) //quand on appuis sur combat ("c") puis qu'on clique sur le tableau pour désigner l'unite enemie
{
    int tableauDeCoordone[2]; //quand on appuie sur une case avec la souris on met (x,y) dedans
    SDL_Event event;
    int continuerLocal = 1;

    while (continuer && continuerLocal)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                tableauDeCoordone[0] = (event.button.x/24)*24;
                tableauDeCoordone[1] = (event.button.y/24)*24;
                continuerLocal = 0; //on veux quitter ce while, pas le jeux
                break;
            default: break;
        }
    }
    if (continuer == 1){click_sur_enemis_ou_non(tableauDeCoordone, allier, enemis, joueur);}
    fprintf(stderr, "fin mouvement combat %d\n",continuer);
}

void click_sur_enemis_ou_non(int tableauCoord[2], TypUnite* allier, TypEquipe* enemis, int joueur)
{
    //on chech si on a bien cliqué sur une unité enemie
    int cp, bien_vise;
    bien_vise = 0;

    for (cp=0;cp<5;cp++)
    {
        if (enemis->fantassin[cp].statut == 1)
        {
            if ((enemis->fantassin[cp].position.x == tableauCoord[0]) && (enemis->fantassin[cp].position.y == tableauCoord[1]))
            {
                application_des_dmg(allier, &(enemis->fantassin[cp]));
                afficherExplosion(&(enemis->fantassin[cp].position), joueur, allier);
                bien_vise = 1;
                break;
            }
        }
        if (enemis->mobile[cp].statut == 1)
        {
            if ((enemis->mobile[cp].position.x == tableauCoord[0]) && (enemis->mobile[cp].position.y == tableauCoord[1]))
            {
                application_des_dmg(allier, &(enemis->mobile[cp]));
                afficherExplosion(&(enemis->mobile[cp].position), joueur, allier);
                bien_vise = 1;
                break;
            }
        }
        if (enemis->lourde[cp].statut == 1)
        {
            if ((enemis->lourde[cp].position.x == tableauCoord[0]) && (enemis->lourde[cp].position.y == tableauCoord[1]))
            {
                application_des_dmg(allier, &(enemis->lourde[cp]));
                afficherExplosion(&(enemis->lourde[cp].position), joueur, allier);
                bien_vise = 1;
                break;
            }
        }
    }

    if ((enemis->base.x == tableauCoord[0]) && (enemis->base.y == tableauCoord[1]))
    {
        enemis->PV_base -= allier->attk;
        afficherExplosion(&(enemis->base), joueur, allier);
        bien_vise = 1;
        if (enemis->PV_base <= 0) {continuer = 0;}
    }

    if (bien_vise == 0) {fenetreAveugle();}
}

void application_des_dmg(TypUnite* allier, TypUnite* enemis_qui_encaisse_les_degats)
{
    enemis_qui_encaisse_les_degats->pv -= allier->attk;

    if(enemis_qui_encaisse_les_degats->pv <=0) //l'unité est morte
    {
        enemis_qui_encaisse_les_degats->statut = 0;
    }
}

void fenetreAveugle()
{
    int i;
    SDL_Surface* msgdErreur = NULL;
    msgdErreur = SDL_LoadBMP("erreur aveugle.bmp");
    SDL_Rect positionMSG;
    positionMSG.x = ((sizeMaxField*24)/2)-135; //la largeur de l'img est de 270 pixel
    positionMSG.y = ((sizeMaxField*24)/2)-82 ; //la hauteur est de 164p

    SDL_SetColorKey(msgdErreur, SDL_SRCCOLORKEY, SDL_MapRGB(msgdErreur->format, 224, 0, 192));
    SDL_BlitSurface(msgdErreur, NULL, ecran, &positionMSG);
    SDL_Flip(ecran);

    for(i=0;i<=500000000;i++) {;} //une sorte de pause pour que l'image reste affichée
}
