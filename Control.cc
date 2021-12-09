#include "Control.h"
#include <iostream> 
#include <string>
using namespace std;


void Control::launch(){
    vector<ReportGenerator*> r;

    reportOne = new RegionDegreeGender;
    reportTwo = new Top3Bottom3;
    reportThree = new ProportionOfAll;

    r.push_back(reportOne);
    r.push_back(reportTwo);
    r.push_back(reportThree);
    //r.push_back(reportOne);


    while(1){
        v.showMenu(choice);
        v.printStr("Select one of the following options: \n");
        v.printStr("Report 1: " +r.at(0)->reportName);
        v.printStr("Report 2: " +r.at(1)->reportName);
        v.printStr("Report 3: " +r.at(2)->reportName);
        v.printStr("Exit: (0) To leave the application");

       if(choice == 1){
           r.at(0)->storeRecords();
           r.at(0)->execute(s);
           v.printStr(s);
       }
         if(choice == 2){
            r.at(1)->storeRecords();
           r.at(1)->execute(s);
           v.printStr(s);
       }
         if(choice == 3){
            r.at(2)->storeRecords();
           r.at(2)->execute(s);
           v.printStr(s);
       }
       if(choice == 0){

           exit(1);
       }
       

    }

    for(int i=0;i<r.size();i++){
        delete r.at(i);
    }


    

}