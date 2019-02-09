/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#include "MainPlayer.h"

MainPlayer::MainPlayer(Texture t, RenderingArray* a) : Character(a)
{
    tex = t;
}

MainPlayer::~MainPlayer()
{
}

void MainPlayer::addToFollowStack(Student* i)
    { followStack.push(i); }

Student* MainPlayer::lastFollowed() const
    { return followStack.top(); }

void MainPlayer::unstackFollow()
    { followStack.pop(); }

bool MainPlayer::isFollowStackEmpty() const
    { return followStack.empty(); }

int MainPlayer::followStackSize() const
    { return followStack.size(); }

void MainPlayer::catchStudent()
{
    int random_sentence = (rand() % 5);
    switch (random_sentence) {
        case 0:
            say(L"Eh toi je te connais!");
            break;
        case 1:
            say(L"Toi tu es perronet!");
            break;
        case 2:
            say(L"Eh toi je te vois courir partout!");
            break;
        case 3:
            say(L"Eh vous sortez!");
            break;
        case 4:
            say(L"Eh toi tu es 149!");
            break;
        default:
            break;
    }
}
