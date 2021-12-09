#ifndef CONTROL_H
#define CONTROL_H
#include <iostream>
#include <string>
using namespace std;
#include "Record.h"
#include "ReportGenerator.h"
#include "View.h"

class Control {
    public:
        void launch();
        
        

    private: 
        View v;
        int choice;
        ReportGenerator* reportOne;
        ReportGenerator* reportTwo;
        ReportGenerator* reportThree;
        ReportGenerator* reportFour;
        ReportGenerator* reportFive;
        string s="";





};
#endif