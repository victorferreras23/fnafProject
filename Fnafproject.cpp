#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


class Animatronic{
    private:
    string name;
    char side;
    int aggresion;
    int position;

    public:
    Animatronic(string name,char side,int aggresion){
        this-> name = name;
        this-> side = side;
        this-> aggresion = aggresion;
        this-> position = 0;
    }

    // getters

        
    string getName() const {return this-> name;}
    char getSide()  const{return this-> side;}
    int getPosition() const {return this-> position;}

    bool atDoor() const {
        if (position == 2)
            return true;
        return false;
    }
    bool atOffice() const {
        if (position >= 3)
            return true;
        return false;
    }

    void move(int playerNoise){
        if (position >= 3)
            return;
        int chance = (aggresion * 10) + playerNoise - (position * 5);

        if (chance < 5)
            chance = 5;
        if (chance > 95)
            chance = 95;

        int roll = rand() % 100;

        if (roll < chance) 
            position += 1;
    }

};



int main() {
    cout << "Night Simulator starting...\n";
    return 0;
}

