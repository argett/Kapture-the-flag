#include "menu.h"

void aleaTT(int i, int j);

void Menu (SDL_Rect* positionRougeFlag, SDL_Surface* spawnFlagR, SDL_Rect* positionBleuFlag, SDL_Surface* spawnFlagB)
{
    SDL_Surface *ecran = NULL, *fondEcran = NULL;
    SDL_Rect positionEcran;
    SDL_Event event;
    positionEcran.x = 0;
    positionEcran.y = 0;
    creationCarte();
    int tailleMap;
    tailleMap = sizeMaxField *  24;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(tailleMap, tailleMap, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); /* Double Buffering */
    Menu1(ecran,fondEcran,positionEcran,event);
    Menu2(ecran,fondEcran,positionEcran,event);
    Menu3(ecran,fondEcran,positionEcran,event);
    ChoisirBase(ecran, fondEcran, positionEcran, event, positionRougeFlag, spawnFlagR, positionBleuFlag, spawnFlagB);

    SDL_FreeSurface(fondEcran); // Liberation de la surface
    SDL_Quit();
    return EXIT_SUCCESS;
}

void Menu1 (SDL_Surface* ecran,SDL_Surface* fondEcran,SDL_Rect positionEcran,SDL_Event event)
{

    fondEcran = SDL_LoadBMP("menu 1.bmp") ;
    int continuer = 1;
    SDL_WM_SetCaption("Kapture - Menu Fantassins", NULL);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if ((3*24<event.button.x && event.button.x<5*24) && (9*24<event.button.y && event.button.y<11*24)) {f = 0; continuer = 0;}
                if ((6*24<event.button.x && event.button.x<8*24) && (9*24<event.button.y && event.button.y<11*24)) {f = 1; continuer = 0;}
                if ((9*24<event.button.x && event.button.x<11*24) && (9*24<event.button.y && event.button.y<11*24)) {f = 2;continuer = 0;}
                if ((12*24<event.button.x && event.button.x<14*24) && (9*24<event.button.y && event.button.y<11*24)) {f = 3;continuer = 0;}
                if ((15*24<event.button.x && event.button.x<17*24) && (9*24<event.button.y && event.button.y<11*24)) {f = 4;continuer = 0;}
                if ((18*24<event.button.x && event.button.x<20*24) && (9*24<event.button.y && event.button.y<11*24)) {f = 5;continuer = 0;}
                break;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 96, 224, 64));
        SDL_BlitSurface(fondEcran, NULL, ecran, &positionEcran);
        SDL_Flip(ecran);
    }
}

void Menu2 (SDL_Surface* ecran,SDL_Surface* fondEcran,SDL_Rect positionEcran,SDL_Event event)
{
    fondEcran = SDL_LoadBMP("menu 2.bmp") ;

    int continuer = 1;
    SDL_WM_SetCaption("Kapture - Menu Mobiles", NULL);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if ((3*24<event.button.x && event.button.x<5*24) && (9*24<event.button.y && event.button.y<11*24)) {m = 0;continuer = 0; }
                if ((6*24<event.button.x && event.button.x<8*24) && (9*24<event.button.y && event.button.y<11*24)) {m = 1;continuer = 0; }
                if ((9*24<event.button.x && event.button.x<11*24) && (9*24<event.button.y && event.button.y<11*24)) {m = 2;continuer = 0;}
                if ((12*24<event.button.x && event.button.x<14*24) && (9*24<event.button.y && event.button.y<11*24)) {m = 3;continuer = 0;}
                if ((15*24<event.button.x && event.button.x<17*24) && (9*24<event.button.y && event.button.y<11*24)) {m = 4;continuer = 0;}
                if ((18*24<event.button.x && event.button.x<20*24) && (9*24<event.button.y && event.button.y<11*24)) {m = 5;continuer = 0;}
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 96, 224, 64));
        SDL_BlitSurface(fondEcran, NULL, ecran, &positionEcran);
        SDL_Flip(ecran);
    }
}

void Menu3 (SDL_Surface* ecran,SDL_Surface* fondEcran,SDL_Rect positionEcran,SDL_Event event)
{
    fondEcran = SDL_LoadBMP("menu 3.bmp") ;

    int continuer = 1;
    SDL_WM_SetCaption("Kapture - Menu Lourdes", NULL);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if ((3*24<event.button.x && event.button.x<5*24) && (9*24<event.button.y && event.button.y<11*24)) {l = 0;continuer = 0; }
                if ((6*24<event.button.x && event.button.x<8*24) && (9*24<event.button.y && event.button.y<11*24)) {l = 1;continuer = 0;}
                if ((9*24<event.button.x && event.button.x<11*24) && (9*24<event.button.y && event.button.y<11*24)) {l = 2;continuer = 0;}
                if ((12*24<event.button.x && event.button.x<14*24) && (9*24<event.button.y && event.button.y<11*24)) {l = 3;continuer = 0;}
                if ((15*24<event.button.x && event.button.x<17*24) && (9*24<event.button.y && event.button.y<11*24)) {l = 4;continuer = 0;}
                if ((18*24<event.button.x && event.button.x<20*24) && (9*24<event.button.y && event.button.y<11*24)) {l = 5;continuer = 0;}
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 96, 224, 64));
        SDL_BlitSurface(fondEcran, NULL, ecran, &positionEcran);
        SDL_Flip(ecran);
    }
}

void ChoisirBase(SDL_Surface* ecran, SDL_Surface* fondEcran, SDL_Rect positionEcran, SDL_Event event, SDL_Rect* positionRougeFlag, SDL_Surface* spawnFlagR, SDL_Rect* positionBleuFlag, SDL_Surface* spawnFlagB)
{
    int continuer = 1;
    int X,Y;
    SDL_Rect positionFog;
    SDL_WM_SetCaption("Kapture - Emplacement Base", NULL);
    positionFog.x = 0;
    positionFog.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                X = event.button.x;
                Y = event.button.y;
                if ((24*3<X && X<24*(sizeMaxField - 3)) && (24*3<Y && Y<24*(sizeMaxField - 3)))
                {
                    positionRougeFlag->x =  (event.button.x/24)*24 ;
                    positionRougeFlag->y =  (event.button.y/24)*24 ;
                    continuer = 0;
                }
                break;
            }
            case SDL_MOUSEMOTION:
            {
                positionRougeFlag->x = event.motion.x;
                positionRougeFlag->y = event.motion.y;
                break;
            }
        }
         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 100, 100, 100)); //on efface l'ecran (ou rempli de blanc)
        SDL_SetColorKey(spawnFlagR, SDL_SRCCOLORKEY, SDL_MapRGB(spawnFlagR->format, 224, 0, 192));
        SDL_BlitSurface(spawnFlagR, NULL, ecran, positionRougeFlag);
        SDL_Flip(ecran);
    }

    continuer = 1;
    positionFog.x = 0;
    positionFog.y = 0;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                X = event.button.x;
                Y = event.button.y;
                if ((24*3<X && X<24*(sizeMaxField - 3)) && (24*3<Y && Y<24*(sizeMaxField - 3)))
                {
                    positionBleuFlag->x = (event.button.x/24)*24 ;
                    positionBleuFlag->y = (event.button.y/24)*24 ;
                    continuer = 0;
                }
                break;
            }
            case SDL_MOUSEMOTION:
            {
                positionBleuFlag->x = event.motion.x;
                positionBleuFlag->y = event.motion.y;
                break;
            }
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 100, 100, 100)); //on efface l'ecran (ou rempli de blanc)
        SDL_SetColorKey(spawnFlagB, SDL_SRCCOLORKEY, SDL_MapRGB(spawnFlagB->format, 224, 0, 192));
        SDL_BlitSurface(spawnFlagB, NULL, ecran, positionBleuFlag);
        SDL_Flip(ecran);
    }
}

void creationCarte()
{
    //très important
    srand(time(NULL));
    int k,rdm,ran;
    int a,i,j;
    sizeMaxField = 29;

    //on créer la carte
    terrain = (int **)malloc(sizeMaxField * sizeof(int*)) ;
    for (k=0;k<sizeMaxField;k++) {terrain[k] = (int*)malloc(sizeMaxField * sizeof(int));}

    //on fait la première ligne et première colone
    for (a=0;a<sizeMaxField;a++)
    {
        ran = rand()%(sizeMaxField*2);
        rdm = rand()%(sizeMaxField*2);
        //on s'occupe de la variable 'ran'
        aleaCo(ran,a);
        //on s'occupe de la variable 'rdm'
        aleaLi(rdm,a);
    }

    //maintenant le reste de la map
    for (i=1;i<sizeMaxField;i++)
    {
        for (j=1;j<sizeMaxField;j++)
        {
            aleaTT(i,j);
        }
    }
}

void aleaTT(int i, int j)
{
    int  x;
    x = rand()%10 ; //valeur possibles : 0 1 2 3 4 5 6

    //si la case au-dessus = herbe
    if (terrain[i-1][j] == 1)
    {
        if (terrain[i][j-1] == 1) //si la case à gauche = herbe
        {
            if (5<x)
                terrain[i][j] = 1; //     4/10 chance d'herbe
            else if (x==2 || x==3 || x==4 || x==5)
                terrain[i][j] = 0; //     4/10 chance terre
            else
                terrain[i][j] = 2; //     1/10 chance eau
        }
        else if (terrain[i][j-1] == 2) //si la case à gauche = eau
        {
            if (5<x)
                terrain[i][j] = 0; //     4/10 chance terre
            else if (x==4 || x==5)
                terrain[i][j] = 1; //     2/10 chance d'herbe
            else
                terrain[i][j] = 2; //     4/10 chance eau
        }
        else //si herbe dessus | terre gauche
        {
            if (6<x)
                terrain[i][j] = 1; //     3/10 chance d'herbe
            else
                terrain[i][j] = 0; //     7/10 chance terre
        }
    }

    //si la case au-dessus = eau
    else if (terrain[i-1][j] == 2)
    {
        if (terrain[i][j-1] == 1) //si la case à gauche = herbe
        {
            if (5<x)
                terrain[i][j] = 0; //     4/10 chance terre
            else if (x==3 || x==4 || x==5)
                terrain[i][j] = 1; //     3/10 chance d'herbe
            else
                terrain[i][j] = 2; //     3/10 chance eau
        }
        else if (terrain[i][j-1] == 2) //si la case à gauche = eau
        {
           if (1<x)
                terrain[i][j] = 2; //     8/10 chance eau
            else if (x==1)
                terrain[i][j] = 1; //     1/10 chance terre
            else
                terrain[i][j] = 2; //     1/10 chance d'herbe
        }
        else //si eau dessus | terre gauche
        {
            if (4<x)
                terrain[i][j] = 0; //     5/10 chance terre
            else if (x==2 || x==3 || x==4)
                terrain[i][j] = 2; //     3/10 chance eau
            else
                terrain[i][j] = 1; //     2/10 chance d'herbe
        }
    }

    //sinon dessus = terre
    else
    {
        if (terrain[i][j-1] == 1) //si la case à gauche = herbe
        {
            if (2<x)
                terrain[i][j] = 0; //     7/10 chance terre
            else
                terrain[i][j] = 1; //     3/10 chance d'herbe
        }
        else if (terrain[i][j-1] == 2) //si la case à gauche = eau
        {
            if (3<x)
                terrain[i][j] = 0; //     7/10 chance terre
            else if (x==2 || x==3)
                terrain[i][j] = 1; //     1/10 chance herbe
            else
                terrain[i][j] = 2; //     2/10 chance eau
        }
        else //si terre dessus | terre gauche
        {
            if (x==0)
                terrain[i][j] = 1; //     1/10 chance herbe
            else
                terrain[i][j] = 0; //     9/10 chance terre
        }
    }
}

void aleaCo(int usk2, int a)
{
    if (1 <= usk2 && usk2 <= (sizeMaxField + sizeMaxField/2)) //terre
    {
        terrain[a][0] = 0;
    }
    else if ((sizeMaxField + sizeMaxField/2) < usk2) //foret
    {
        terrain[a][0] = 1;
    }
    else //normalement ran == 0 --> eau
    {
        fprintf(stderr, "la colone 0 est : %d \n\n",usk2);
        terrain[a][0] = 2;
    }
}

void aleaLi(int usk2, int a)
{
    if (1 <= usk2 && usk2 <= (sizeMaxField + sizeMaxField/2)) //terre
    {
        terrain[0][a] = 0;
    }
    else if ((sizeMaxField + sizeMaxField/2) < usk2) //foret
    {
        terrain[0][a] = 1;
    }
    else //normalement ran == 0 --> eau
    {
        fprintf(stderr, "la ligne 0 est : %d\n\n",usk2);
        terrain[0][a] = 2;
    }
}
