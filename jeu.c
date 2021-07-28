#include "proto.h"
#include "jeu.h"

int joueur = 1;

void leJeuCommence(TypEquipe* rouge,  int** fogRouge, TypEquipe* bleu, int** fogBleu)
{
    SDL_Rect positionFog_mapRouge, positionFog_mapBleu;

    while (continuer==1)
    {
        if (joueur%2==1)
        {
            mouvementEquipe(rouge, bleu, fog_mapRouge, &positionFog_mapRouge, fogRouge);
            joueur += 1;
        }
        else
        {
            mouvementEquipe(bleu, rouge, fog_mapBleu, &positionFog_mapBleu, fogBleu);
            joueur -= 1;
        }
    }
}

void mouvementEquipe(TypEquipe* eqpAllie, TypEquipe* eqpEnemie, SDL_Surface* fog_eqpAllie, SDL_Rect* positionFog_eqpAllie, int** fogAllier)
{
    int cpt;

    for(cpt=0; cpt<=4 && continuer; cpt++)
    {
        if (eqpAllie->mobile[cpt].statut == 1)
        {
            mouvementUnite(&(eqpAllie->mobile[cpt]), eqpAllie, fogAllier, fog_eqpAllie, positionFog_eqpAllie, eqpEnemie);
        }
    }


    for(cpt=0; cpt<=4 && continuer; cpt++)
    {
        if (eqpAllie->fantassin[cpt].statut == 1)
        {
            mouvementUnite(&(eqpAllie->fantassin[cpt]), eqpAllie, fogAllier, fog_eqpAllie, positionFog_eqpAllie, eqpEnemie);
        }
    }

    for(cpt=0; cpt<=4 && continuer; cpt++)
    {
        if (eqpAllie->lourde[cpt].statut == 1)
        {
            mouvementUnite(&(eqpAllie->lourde[cpt]), eqpAllie, fogAllier, fog_eqpAllie, positionFog_eqpAllie, eqpEnemie);
        }
    }

    if(eqpAllie->drone.statut == 1  && continuer)
    {
        mouvementUnite(&(eqpAllie->drone), eqpAllie, fogAllier, fog_eqpAllie, positionFog_eqpAllie, eqpEnemie);
    }

    fprintf(stderr, "fin mouvement equipe %d\n",continuer);
}

void mouvementUnite (TypUnite* unite, TypEquipe* eqpAllie, int** fogAllie, SDL_Surface* fog_eqpAllie, SDL_Rect* positionFog_eqpAllie, TypEquipe* eqpEnemie)
{
    afficherTOUT(joueur, unite, 0, 0, 0); //dès qu'on change d'équipe il faut que la nouvelle soit affichée immédiatement
    SDL_Flip(ecran);

    SDL_Event event;
    int nbMvmt;
    nbMvmt = unite->deplacement;
    int futurX, futurY;
    int r=0; //r ou "rien" est une variable qui sert à optimiser le cas ou on ne fait rien avec une unite

    while (continuer == 1 && nbMvmt>0)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                nbMvmt = 0;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_q: //la touche "a" sert a passer le tour de l'unite
                        nbMvmt = 0;
                        r=1;
                        break;
                    case SDLK_UP: // Fleche haut
                        futurX = 0 ;
                        futurY = -24 ;
                        deplacement(futurX, futurY, unite, eqpAllie, eqpEnemie);
                        break;
                    case SDLK_DOWN:
                        futurX = 0 ;
                        futurY = 24 ;
                        deplacement(futurX, futurY, unite, eqpAllie, eqpEnemie);
                        break;
                    case SDLK_RIGHT:
                        futurX = 24 ;
                        futurY = 0 ;
                        deplacement(futurX, futurY, unite, eqpAllie, eqpEnemie);
                        break;
                    case SDLK_LEFT:
                        futurX = -24 ;
                        futurY = 0 ;
                        deplacement(futurX, futurY, unite, eqpAllie, eqpEnemie);
                        break;
                    case SDLK_p:
                        futurX = 0;
                        futurY = 0;
                        combatOUnon(unite, joueur, fog_eqpAllie, positionFog_eqpAllie, fogAllie, eqpAllie, eqpEnemie);
                        break;
                    case SDLK_TAB:
                        continuer = 0;
                        nbMvmt = 0;
                        break;
                    default:
                        r=1;
                        break;
                }
                fprintf(stderr, "mouvement unite apres wait %d\n",continuer);
                if (r==0)
                {
                    onEnleveLeMvmnt(&nbMvmt, unite);
                    afficherTOUT(joueur, unite, 1, -futurX, -futurY); // 1=mvmt meme equipe, X&Y actuel, X&Y avant deplacement
                    SDL_Flip(ecran);
                }
                r=0;
                break;
            default: break;
        }
    }
    fprintf(stderr, "fin mouvement unite %d\n",continuer);
}

void deplacement(int futurX, int futurY, TypUnite* unite, TypEquipe* eqpAllie, TypEquipe* eqpEnemie)
{
    if (unite->position.x + futurX <= (sizeMaxField-1)*24 && unite->position.x + futurX >= 0)
    {
        if (unite->position.y + futurY <= (sizeMaxField-1)*24&& unite->position.y + futurY >= 0)
        {
            if (collision(futurX, futurY, unite, eqpAllie,  eqpEnemie)== 0)
            {
                unite->position.x += futurX ;
                unite->position.y += futurY ;
            }
        }
    }
}

int collision(int futurX, int futurY, TypUnite* unite, TypEquipe* eqpAllie, TypEquipe* eqpEnemie)
{
    int i=0;
    //on peux comparer notre unite avec les autres, mais on va tomber forcement sur la notre, ce qui est pas grave vu que sa position et sa future sont !=
    for(i=0;i<=4;i++)
    {
        //collision alliés
        if (eqpAllie->fantassin[i].statut == 1)
        {
            if (eqpAllie->fantassin[i].position.x == (unite->position.x + futurX) && eqpAllie->fantassin[i].position.y == (unite->position.y + futurY)) {return 1;}
        }
        if (eqpAllie->lourde[i].statut == 1)
        {
            if (eqpAllie->lourde[i].position.x == (unite->position.x + futurX) && eqpAllie->lourde[i].position.y == (unite->position.y + futurY)) {return 1;}
        }
        if (eqpAllie->mobile[i].statut == 1)
        {
            if (eqpAllie->mobile[i].position.x == (unite->position.x + futurX) && eqpAllie->mobile[i].position.y == (unite->position.y + futurY)) {return 1;}
        }
        //collision enemie
        if (eqpEnemie->fantassin[i].statut == 1)
        {
            if (eqpEnemie->fantassin[i].position.x == (unite->position.x + futurX) && eqpEnemie->fantassin[i].position.y == (unite->position.y + futurY)) {return 1;}
        }
        if (eqpEnemie->lourde[i].statut == 1)
        {
            if (eqpEnemie->lourde[i].position.x == (unite->position.x + futurX) && eqpEnemie->lourde[i].position.y == (unite->position.y + futurY)) {return 1;}
        }
        if (eqpEnemie->mobile[i].statut == 1)
        {
            if (eqpEnemie->mobile[i].position.x == (unite->position.x + futurX) && eqpEnemie->mobile[i].position.y == (unite->position.y + futurY)) {return 1;}
        }
    }

    if (eqpAllie->drone.statut == 1)
    {
        if (eqpAllie->drone.position.x == (unite->position.x + futurX) && eqpAllie->drone.position.y == (unite->position.y + futurY)) {return 1;}
    }

// Le drone allié peux aller sur une unité ennemie
/*
    if (eqpEnemie->drone.statut == 1)
    {
        if (eqpEnemie->drone.position.x == (unite->position.x + futurX) && eqpEnemie->drone.position.y == (unite->position.y + futurY)) {return 1;}
    }
*/
    //si aucune unite n est dans la future case
    return 0;
}

void onEnleveLeMvmnt (int* nbMvmnt, TypUnite* unite)
{
    /*
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,1,0,0,2,2,2,2,2,2,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,0,0,0,0,2,1,1,0,0,0,0,0,0},
    {0,0,0,0,1,1,2,0,0,0,0,0,0,0,2,1,1,0,0,0,0,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,2,1,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}} ; */

    if (unite->eauLLreadyINwater == 1 && unite->eauLLreadyINwater != 9) //au tour precedent, est ce que l unite etait dans leau ? Ce netait pas un drone ?
    {
        unite->eauLLreadyINwater = 0;
        *nbMvmnt = 0;
    }
    if (terrain[(unite->position.y)/24][(unite->position.x)/24] == 0) {*nbMvmnt -= 1;} //sol
    if (terrain[(unite->position.y)/24][(unite->position.x)/24] == 1) {*nbMvmnt -= 2;} //herbe
    if (terrain[(unite->position.y)/24][(unite->position.x)/24] == 2)
    {
        if (unite->eauLLreadyINwater != 9)
        {
            unite->eauLLreadyINwater = 1;
            *nbMvmnt = 0;
        }
        else
        {
            *nbMvmnt -= 1; //le drone ne pert que 1 mvmnt dans l'eau
        }
    }
}
