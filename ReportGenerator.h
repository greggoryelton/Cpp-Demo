#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H
using namespace std;
#include <iostream>
#include "Record.h"
#include "Property.h"
#include <cstdlib>
#include <iterator>
#include <fstream>
#include <sstream>
#define MAX_DEG 4
#define MAX_YEAR 4
#define MAX_REGION 11



class ReportGenerator{
    public:
        ReportGenerator();
        ~ReportGenerator();
        static void storeRecords();
        //Pure Virtual execute to be used in derived concrete classes
        virtual void execute(string& outStr)=0;
        static void loadDegreeCollection();
        static void loadYearCollection();
        static void loadRegionCollection();
        string reportName;
        
        

    protected:    
        static vector<Record*> collection;    
        //These will be our partials
        static vector<Property<int>*> allYear;
        static vector<Property<string>*> allRegions;
        static vector<Property<string>*> allDegree;
        
        
    
};

class RegionDegreeGender: public ReportGenerator{
    public: 
        RegionDegreeGender();
        virtual void execute(string& outStr);
        virtual ~RegionDegreeGender();
};

class Top3Bottom3: public ReportGenerator{
    public:
        Top3Bottom3();
        virtual void execute(string& outStr);
        virtual ~Top3Bottom3();
};

class ProportionOfAll: public ReportGenerator{
    public:
        ProportionOfAll();
        virtual void execute(string& outStr);
       virtual  ~ProportionOfAll();
        

};

//TODO
//Report 4 
//Report 5' classes
#endif