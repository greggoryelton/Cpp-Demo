#include "Record.h"

using namespace std;

//This class is an entity class of the program that is used for creatign a record when it is read in from the program
Record::Record(int y, string p, string d, string g, int employed, int grads):year(y), province(p),degree(d), gender(g), numberEmployed(employed), numberGrads(grads) {

}
Record::Record(const Record& rec){
    province = rec.province;
    degree = rec.degree;
    numberEmployed = rec.numberEmployed;
    numberGrads = rec.numberGrads;
    gender = rec.gender;
    year = rec.year;
}

ostream& operator<<(ostream& output, Record& r){
    output << r.year << " " << r.province << " " << r.degree << " " << r.gender << " " << r.numberEmployed << " " << r.numberGrads << endl;
}

string Record::getDegree(){
    return degree;
}
string Record::getGender(){
    return gender;
}
string Record::getRegion(){
    return province;
}

int Record::getYear(){
    return year;
}

int Record::getNumberEmployed(){
    return numberEmployed;
}
int Record::getNumberGrads(){
    return numberGrads;
}
Record::~Record(){

}

