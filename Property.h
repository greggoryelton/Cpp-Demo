#ifndef PROPERTY_H
#define PROPERTY_H
#include <vector> 
#include <iostream>
using namespace std;
#include "Record.h"

//This template class maintains a vector as a collection and overrides to operators, one that returns the record object
//of the specified index and one that adds a specific record pointer to the back of the storageVector;


template <class T>
class Property{
        public:
            Record* operator[](int);
            //we might have to overload these two function - so switch template thing
            T& operator+=(Record*);
            ~Property();
            int getSize();
            T getType();
            Property(T t);
           
        
        private:
            
            vector<Record*> storageVector;
            int size=0;
            T type;
          
            
            //Missing something here
};


template <class T>
Record* Property<T>::operator[](int i){
    if(i<0 || i > storageVector.size()){
        cout << "Error: Invalid Index" << endl;
    }
   return (storageVector.at(i));

}
template <class T>
T& Property<T>::operator+=(Record* rec){
    storageVector.push_back(rec);
    
}

template <class T>
T Property<T>::getType(){
    return type;
}

template<class T>
int Property<T>::getSize(){
    return storageVector.size();
}
template <class T>
Property<T>::Property(T t){
    type = t;
}

template <class T>
Property<T>::~Property(){
    for(int i=0;i<storageVector.size();i++){
        delete storageVector.at(i);
    }
    
}

#endif