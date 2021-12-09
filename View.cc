#include "View.h"


void View::showMenu(int& choice){
    cout << endl <<endl;

    cout << "What would you like to do? : " << endl;

    cin >> choice;
    if(choice == 0){
        exit(1);
    }

    while(choice < 1 || choice > 5){
        cout << "Enter your selection: ";
        cin >> choice;
    }
}

void View::printStr(string str){
    cout << str <<endl;
}


