#include "proto.h"


void initEquipe(TypEquipe* Equipe, SDL_Rect* Drapeau)
{
     int i;
     Equipe->base.x = Drapeau->x ;
     Equipe->base.y = Drapeau->y ;

     for (i=0;i<5;i++)
     {
        if (i<f)
        {
            Equipe->fantassin[i].statut = 1;
            Equipe->fantassin[i].deplacement = 4;
            Equipe->fantassin[i].pv = 10;
            Equipe->fantassin[i].attk = 5;
            Equipe->fantassin[i].eauLLreadyINwater = 0;
        }
        else {Equipe->fantassin[i].statut = 0;}
     }
     for (i=0;i<5;i++)
     {
        if (i<m)
        {
            Equipe->mobile[i].statut = 1;
            Equipe->mobile[i].deplacement = 6;
            Equipe->mobile[i].pv = 6;
            Equipe->mobile[i].attk = 2;
            Equipe->mobile[i].eauLLreadyINwater = 0;
        }
        else {Equipe->mobile[i].statut = 0;}
     }
     for (i=0;i<5;i++)
     {
        if (i<l)
        {
            Equipe->lourde[i].statut = 1;
            Equipe->lourde[i].deplacement = 3;
            Equipe->lourde[i].pv = 25;
            Equipe->lourde[i].attk = 11;
            Equipe->lourde[i].eauLLreadyINwater = 0;
        }
        else {Equipe->lourde[i].statut = 0;}
     }
     Equipe->drone.deplacement = 10;
     Equipe->drone.pv = 3;
     Equipe->drone.attk = 0;
     Equipe->drone.statut = 1;
     Equipe->drone.eauLLreadyINwater = 9; //le drone ne va pas dans l eau, il vole donc pas de allreadyinwater

     Equipe->PV_base = 25;

     position(Equipe);
}

void position(TypEquipe* Equipe)
{
    int cpt, nbUnite = 0;

    for(cpt=0;cpt<=4;cpt++)
    {
        if (Equipe->lourde[cpt].statut == 1)
        {
            onTestLesCase(&(Equipe->lourde[cpt]),nbUnite,&(Equipe->base));
            nbUnite ++;
        }
    }

    for(cpt=0;cpt<=4;cpt++)
    {
        if (Equipe->fantassin[cpt].statut == 1)
        {
            onTestLesCase(&(Equipe->fantassin[cpt]),nbUnite,&(Equipe->base)); //on ajoute le nombre d'unite precedente plus les nouvelle
            nbUnite ++;
        }
    }

    for(cpt=0;cpt<=4;cpt++)
    {
        if (Equipe->mobile[cpt].statut == 1)
        {
            onTestLesCase(&(Equipe->mobile[cpt]),nbUnite,&(Equipe->base));
            nbUnite ++;
        }
    }

    onTestLesCase(&(Equipe->drone),nbUnite,&(Equipe->base));

}

void onTestLesCase(TypUnite* unite,int cpt, SDL_Rect* base)
{
    unite->position.h = 24; //on sais pas a quoi ca sert alors on pose ça là
    unite->position.w = 24;
    switch (cpt)
    {
        case 0:
        {
            unite->position.x = 48;//base->x;
            unite->position.y = 48;//base->y-24;
            break;
        }
        case 1:
        {
            unite->position.x = base->x   ;
            unite->position.y = base->y+24;
            break;
        }
        case 2:
        {
            unite->position.x = base->x-24;
            unite->position.y = base->y   ;
            break;
        }
        case 3:
        {
            unite->position.x = base->x+24;
            unite->position.y = base->y   ;
            break;
        }
        case 4:
        {
            unite->position.x = base->x-24;
            unite->position.y = base->y-24;
            break;
        }
        case 5:
        {
            unite->position.x = base->x+24;
            unite->position.y = base->y-24;
            break;
        }
        case 6:
        {
            unite->position.x = base->x+24;
            unite->position.y = base->y+24;
            break;
        }
        case 7:
        {
            unite->position.x = base->x-24;
            unite->position.y = base->y+24;
            break;
        }
        case 8:
        {
            unite->position.x = base->x   ;
            unite->position.y = base->y-48;
            break;
        }
        case 9:
        {
            unite->position.x = base->x   ;
            unite->position.y = base->y+48;
            break;
        }
        case 10:
        {
            unite->position.x = base->x-48;
            unite->position.y = base->y   ;
            break;
        }
        case 11:
        {
            unite->position.x = base->x+48;
            unite->position.y = base->y   ;
            break;
        }
        case 12:
        {
            unite->position.x = base->x-48;
            unite->position.y = base->y-48;
            break;
        }
        case 13:
        {
            unite->position.x = base->x+48;
            unite->position.y = base->y-48;
            break;
        }
        case 14:
        {
            unite->position.x = base->x+48;
            unite->position.y = base->y+48;
            break;
        }
        case 15:
        {
            unite->position.x = base->x-48;
            unite->position.y = base->y+48;
            break;
        }
        default:
        {
            unite->position.x = base->x   ;
            unite->position.y = base->y   ;
            break;
        }
    }
}

void loadIMG()
{
    Terre = SDL_LoadBMP("carte terre.bmp");
    Eau = SDL_LoadBMP("carte eau.bmp");
    Herbe = SDL_LoadBMP("carte herbe.bmp");
    explosion[0] = SDL_LoadBMP("explosion1.bmp");
    explosion[1] = SDL_LoadBMP("explosion2.bmp");
    explosion[2] = SDL_LoadBMP("explosion3.bmp");
    explosion[3] = SDL_LoadBMP("explosion4.bmp");
    explosion[4] = SDL_LoadBMP("explosion5.bmp");
    explosion[5] = SDL_LoadBMP("explosion6.bmp");
    explosion[6] = SDL_LoadBMP("explosion7.bmp");
    explosion[7] = SDL_LoadBMP("explosion8.bmp");

    for (int i=0;i<=7;i++)
    {
        if (explosion[i]==NULL)
        {
            fprintf(stderr, "prblm chargement explosion %d\n",i);
        }
    }

    fog_mapRouge = SDL_LoadBMP("fog_map.bmp");
    fog_mapBleu = SDL_LoadBMP("fog_map.bmp"); //apres avoir fini, me suis rendu compte que 1 seul suffit
    positionUniteActuelle = SDL_LoadBMP("unite.bmp");

    Rouge_fantassin = SDL_LoadBMP("red_fantassin.bmp");
    Rouge_mobile = SDL_LoadBMP("red_mobile.bmp");
    Rouge_lourde = SDL_LoadBMP("red_lourde.bmp");
    Rouge_drone = SDL_LoadBMP("red_drone.bmp");

    Bleu_fantassin = SDL_LoadBMP("blue_fantassin.bmp");
    Bleu_mobile = SDL_LoadBMP("blue_mobile.bmp");
    Bleu_lourde = SDL_LoadBMP("blue_lourde.bmp");
    Bleu_drone = SDL_LoadBMP("blue_drone.bmp");

    Bleu_flag = SDL_LoadBMP("blue_flag.bmp");
    Rouge_flag = SDL_LoadBMP("red_flag.bmp");
}
