#ifndef RECORD_H
#define RECORD_H
#include <string>
#include <iostream>
using namespace std;

class Record{
    friend ostream& operator<<(ostream&, Record&);
    public:
        Record(int=0, string="Province", string="Degree", string="Gender", int=0, int=0);
        Record(const Record&);
        string getGender();
        string getDegree();
        string getRegion();
        int getYear();
        int getNumberEmployed();
        int getNumberGrads();
        
        ~Record();



    private:
        string gender;
        string degree;
        string province;
        int numberEmployed;
        int numberGrads;
        int year;





};
#endif

