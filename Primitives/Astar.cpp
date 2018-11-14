/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse

Projet de TDLog*/

#include <iostream>
#include "Astar.h"
#include "../GameCore.h"
#include "../Map.h"
#include "../Tile.h"
#include "../Settings.h"

std::vector<Point> astar(int x, int y, int x2, int y2)
{
    ///Initialisation de l'algorithme
    std::vector<Point> chemin;
    Noeud* depart=new Noeud;
    depart->x=x/TILE_SIZE;depart->y=y/TILE_SIZE;
    depart->parent=NULL;
    depart->h=abs(depart->x-x2/TILE_SIZE)+abs(depart->y-y2/TILE_SIZE);
    depart->f=depart->h;
    depart->g=0;
    std::vector<Noeud*> openlist;
    std::vector<Noeud*> closelist;
    openlist.push_back(depart);

    Noeud* endingnode=NULL;

    bool continuer=true;

    ///Début de l'algorithme
    while (continuer)
    {
        int num=-1,best=0;
        if ((int)(openlist.size()) > 0) { num = 0; best = openlist[0]->f; }
        //On vérifie quel est le meilleur noeud dans la liste ouverte
        for (int i=0 ; i<(int)(openlist.size()) ; i++) {
            if (openlist[i]->f<best) {best=openlist[i]->f;num=i;}
        }
        if (num == -1 || /*(int)(closelist.size())>=80 || */(openlist[num]->x==x2/TILE_SIZE && openlist[num]->y==y2/TILE_SIZE)) {
            if (num>-1) {endingnode=openlist[num];}
            continuer=false;
            break;
        }
        Noeud* current=openlist[num];
        //On l'ajoute dans la liste fermée
        closelist.push_back(openlist[num]);
        //On le retire de la liste ouverte
        for (int i=num ; i<(int)(openlist.size())-1 ; i++) {openlist[i]=openlist[i+1];}
        openlist.pop_back();

        //On ajoute les 4 noeuds voisins
        for (int j=0 ; j<4 ; j++) {
            int newx=current->x,newy=current->y;
            if (j==0) {newy--;}
            else if (j==1) {newx++;}
            else if (j==2) {newy++;}
            else if (j==3) {newx--;}
            int w = GameCore::getInstance()->getMap()->getW();
            int h = GameCore::getInstance()->getMap()->getH();
            if (newx >= 0 && newy >= 0 && newx < w && newy < h && !GameCore::getInstance()->getMap()->getTile(newx,newy).isSolid()) {
                //on vérifie si le noeud n'est pas dans la liste fermée
                bool okay=true;
                for (int i=0 ; i<(int)(closelist.size()) ; i++) {
                    if (closelist[i]->x==newx && closelist[i]->y==newy) {okay=false;break;}
                }
                if (okay) {
                    //on vérifie si le noeud n'est pas dans la liste ouverte
                    okay=true;
                    int othernum=0;
                    for (int i=0 ; i<(int)(openlist.size()) ; i++) {
                        if (openlist[i]->x==newx && openlist[i]->y==newy) {othernum=i;okay=false;break;}
                    }
                    if (okay) {
                        //Alors on l'ajoute à la liste ouverte
                        Noeud* newnoeud=new Noeud;
                        newnoeud->x=newx;
                        newnoeud->y=newy;
                        newnoeud->g=current->g+1;
                        newnoeud->h=abs(newnoeud->x-x2/TILE_SIZE)+abs(newnoeud->y-y2/TILE_SIZE);
                        newnoeud->f=newnoeud->g+newnoeud->h;
                        newnoeud->parent=current;
                        openlist.push_back(newnoeud);
                    }
                    else {
                        if (current->g+1<openlist[othernum]->g) {
                            openlist[othernum]->g=current->g+1;
                            openlist[othernum]->f=openlist[othernum]->g+openlist[othernum]->h;
                            openlist[othernum]->parent=current;
                        }
                    }
                }
            }
        }
    }
    //Algorithme fini, on retrace le parcours
    while (endingnode!=NULL) {
        Point p;
        p.x=endingnode->x;p.y=endingnode->y;
        chemin.push_back(p);
        endingnode=endingnode->parent;
    }

    ///FIN DE L'ALGORITHME
    return chemin;
}
