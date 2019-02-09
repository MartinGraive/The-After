/*THE AFTER
Commence le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#pragma once

#include <stack>
#include "Character.h"
#include "Student.h"

class MainPlayer : public Character
{
    public:
        MainPlayer(Texture t, RenderingArray* a = NULL);
        ~MainPlayer();

        void addToFollowStack(Student* i);
        Student* lastFollowed() const;
        void unstackFollow();
        bool isFollowStackEmpty() const;
        int followStackSize() const;

        void catchStudent();
    private:
        std::stack<Student*> followStack;
};
