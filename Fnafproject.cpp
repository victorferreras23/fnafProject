#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
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

    void pushBackOne(){
        if (position > 0)
            position-=1;
    }

    static bool sameSide(const Animatronic& a , const Animatronic& b){
        if (a.side == b.side)
            return true;
        return false;
    }

    void resetPosition() {
    position = 0;
    }
      
};

string helper(int p){
    if (p == 0)
        return "Stage";
    if (p == 1)
        return "Hallway";
    if (p == 2)
        return "At door";
    else{
        return "Office";
    }

}

void playJumpscare(const string& path) {
    ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}



int main() {
    cout << "Night Simulator starting...\n";
    srand(time(nullptr));

    bool leftDoorClosed = false;
    bool rightDoorClosed = false;
    int power = 100;
    int hour = 12;

    Animatronic bonnie("Bonnie",'L', 7);
    Animatronic chica("Chica",'R', 6);
    Animatronic foxy("Foxy",'L',9);
    Animatronic freddy("Freddy",'R', 7);


    for (int i = 0; i<6; i++){
        cout << "Hour: " << hour << endl;
    cout << "Power: " << power << "%" << endl;

    cout << "Left Door: " 
        << (leftDoorClosed ? "CLOSED" : "OPEN") 
        << endl;

    cout << "Right Door: " 
        << (rightDoorClosed ? "CLOSED" : "OPEN") 
        << endl;


    cout << "\nChoose action:\n";
    cout << "1. Check Cameras\n";
    cout << "2. Toggle Left Door\n";
    cout << "3. Toggle Right Door\n";
    cout << "4. Do Nothing\n";
    cout << "5. Toggle Both Doors\n";

    int choice;
    cin >> choice;

    int noise = 0;
    int powerdrain = 2;

    if (choice == 1){
        cout << "\n--- CAMERAS ---\n";
        cout << bonnie.getName()
        << " (" << bonnie.getSide() << ") - "
        << helper(bonnie.getPosition())
        << endl;
        cout << chica.getName()
        << " (" << chica.getSide() << ") - "
        << helper(chica.getPosition())
        << endl;
        cout << foxy.getName()
        << " (" << foxy.getSide() << ") - "
        << helper(foxy.getPosition())
        << endl;
        cout << freddy.getName()
        << " (" << freddy.getSide() << ") - "
        << helper(freddy.getPosition())
        << endl;

        noise += 15;
        powerdrain += 2;
    }

    else if (choice == 2){
        leftDoorClosed = !leftDoorClosed;
        noise += 5;
    }
    else if (choice == 3){
        rightDoorClosed = !rightDoorClosed;
        noise += 5;
    }
    else if (choice == 4){

    }
    else if (choice == 5) {
    leftDoorClosed = !leftDoorClosed;
    rightDoorClosed = !rightDoorClosed;
    noise += 8;
    }
    else{
        cout << "Invalid choice. Doing nothing.\n";
    }
    if (leftDoorClosed){
        powerdrain += 3;
    }
    if (rightDoorClosed){
        powerdrain += 3;
    }

    power -= powerdrain;

    if (power <= 0){
        power = 0;
        leftDoorClosed = false;
        rightDoorClosed = false;
        cout << "\nPOWER OUT\n" << endl;
    }

    bonnie.move(noise);
    chica.move(noise);
    foxy.move(noise);
    freddy.move(noise);


    //  CHECK FOR DEATH

    if (bonnie.atOffice()){
        if (bonnie.getSide() == 'L'){
            if (leftDoorClosed == false){
                cout << "\nBONNIE JUMPSCARE\n" << endl;
                playJumpscare("C:/Users/sava1/Videos/jumpscares/bonnie.mp4");
                system("pause");

                return 0;
            }
            else{
                cout << "\nBonnie Blocked\n" << endl;
                bonnie.resetPosition();

                
            }
            
        }
        else if (bonnie.getSide() == 'R'){
            if (rightDoorClosed == false){
                cout << "\nBONNIE JUMPSCARE\n" << endl;
                playJumpscare("C:/Users/sava1/Videos/jumpscares/bonnie.mp4");
                system("pause");

                return 0;
            }
            else{
                cout << "\n Bonnie Blocked\n" << endl;
                bonnie.resetPosition();
            }
            
        }

    }

    if (chica.atOffice()){
        if (chica.getSide() == 'L'){
            if (leftDoorClosed == false){
                cout << "\nCHICA JUMPSCARE\n" << endl;
                playJumpscare("C:/Users/sava1/Videos/jumpscares/chica.mp4");
                system("pause");

                return 0;
            }
            else{
                cout << "\nCHICA Blocked\n" << endl;
                chica.resetPosition();
            }
            
        }
        else if (chica.getSide() == 'R'){
            if (rightDoorClosed == false){
                cout << "\nCHICA JUMPSCARE\n" << endl;
                playJumpscare("C:/Users/sava1/Videos/jumpscares/chica.mp4");
                system("pause");

                return 0;
            }
            else{
                cout << "\n CHICA Blocked\n" << endl;
                chica.resetPosition();
            }
            
        }

    }

    if (foxy.atOffice()){
        if (foxy.getSide() == 'L'){
            if (leftDoorClosed == false){
                cout << "\nFOXY JUMPSCARE\n" << endl;
                playJumpscare("C:/Users/sava1/Videos/jumpscares/foxy.mp4");
                system("pause");

                return 0;
            }
            else{
                cout << "\nFOXY Blocked\n" << endl;
                foxy.resetPosition();
            }
            
        }
        else if (foxy.getSide() == 'R'){
            if (rightDoorClosed == false){
                cout << "\nFOXY  JUMPSCARE\n" << endl;
                playJumpscare("C:/Users/sava1/Videos/jumpscares/foxy.mp4");
                system("pause");

                return 0;
            }
            else{
                cout << "\nFOXY Blocked\n" << endl;
                foxy.resetPosition();
            }
            
        }

    }

    if (freddy.atOffice()){
        if (freddy.getSide() == 'L'){
            if (leftDoorClosed == false){
                cout << "\nFREDDY JUMPSCARE\n" << endl;
                playJumpscare("C:/Users/sava1/Videos/jumpscares/freddy.mp4");
                system("pause");

                return 0;
            }
            else{
                cout << "\nFREDDY Blocked\n" << endl;
                freddy.resetPosition();
            }
            
        }
        else if (freddy.getSide() == 'R'){
            if (rightDoorClosed == false){
                cout << "\nFREDDY JUMPSCARE\n" << endl;
                playJumpscare("C:/Users/sava1/Videos/jumpscares/freddy.mp4");
                system("pause");
                return 0;
            }
            else{
                cout << "\nFREDDY Blocked\n" << endl;
                freddy.resetPosition();
            }
            
        }

    }
     if (hour == 12){
        hour = 1;
     }
     else{
        hour += 1;
     }






    }
cout << "\nGOOD JOB SURVIVING!!!!\n" << endl;

    

    return 0;
}

