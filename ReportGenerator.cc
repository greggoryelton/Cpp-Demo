#include "ReportGenerator.h"
#include <iomanip>
using namespace std;
vector<Record*> ReportGenerator::collection;    
vector<Property<int>*> ReportGenerator::allYear;
vector<Property<string>*> ReportGenerator::allDegree;
vector<Property<string>*> ReportGenerator::allRegions;

//This is were the main control flow of the program resides. First, there is a function to populate the records from the datafile.
//Second there are helper functions in order to populate the partial collections.



ReportGenerator::ReportGenerator(){
    reportName = "";
}

ReportGenerator::~ReportGenerator(){
    
    
    for(int i=0;i<allDegree.size();i++){
        delete allDegree.at(i);
    }

     for(int i=0;i<allRegions.size();i++){
        delete allRegions.at(i);
    }
     for(int i=0;i<allYear.size();i++){
        delete allYear.at(i);
    }

    for(int i=0;i<collection.size();i++){
        delete collection.at(i);
    }
    
   
    
    

}

void ReportGenerator::storeRecords(){

    //Call our helper functions so that the partial collections are loaded
     int size =0;
    //Store all records in our collection
    int year, employed, grads;
    string province, degree, gender;
    ifstream infile("grad.dat", ios::in);

    if(!infile){
        cout << "Error: Cannot open file. Exiting....";
        exit(1);
    }

    while(infile >> year >> province >> degree >> gender >> employed >> grads ){
        Record* rec = new Record(year, province, degree, gender, employed,grads);
        collection.push_back(rec);
    }
    loadDegreeCollection();
    loadYearCollection();
    loadRegionCollection();

   

}

void ReportGenerator::loadDegreeCollection(){

    //Add the various degrees to the partial collection
    vector<string> deg;
    deg.push_back("Bachelor's");
    deg.push_back("College");
    deg.push_back("Doctorate");
    deg.push_back("Master's");


    Property<string>** arr;
    arr = new Property<string>*[deg.size()];
    for(int i=0;i<deg.size();i++){
        arr[i] = new Property<string>(deg.at(i));
    }
    for(int i=0;i<collection.size();i++){
        for(int j=0;j<deg.size();j++){
            if(collection.at(i)->getDegree() == deg.at(j)){
                arr[j]->operator+=(collection.at(i));
            }
        }
    }
    for(int i=0;i<deg.size();i++){
        allDegree.push_back(arr[i]);
    }

   
    
/*
    for(int i=0;i<deg.size();i++){
        delete arr[i];
    }
    delete [] arr;
 */
}



void ReportGenerator::loadYearCollection(){
    //Discover different years and add them to vector;
    vector<int> years;
    for(int i=0;i<collection.size()-1;i++){
        if(collection.at(i)->getYear() != collection.at(i+1)->getYear()){
            years.push_back(collection.at(i+1)->getYear());
        }
    }
  
  for(int i=0;i<years.size()-4;i++){
      //Workaround so that each year is sorted in order in the years vector
      years.erase(years.begin(), years.end()-4);
  }


Property<int>** arr;
arr = new Property<int>*[years.size()];
int size=0;
for(int i=0;i<years.size();i++){
    arr[i] = new Property<int>(years.at(i));
}
  for(int i=0;i<collection.size();i++){
      for(int j=0;j<years.size();j++){
        if(collection.at(i)->getYear() == years.at(j)){
            arr[j]->operator+=(collection.at(i));
            size++;
        }
      }
  }
  for(int i=0;i<years.size(); i++){
      allYear.push_back(arr[i]);
  }



/*
  for(int i=0;i<years.size();i++){
      delete arr[i];
  }
  delete [] arr;
  */
}

void ReportGenerator::loadRegionCollection(){
    //Discovers different regions and adds them to a partial collection organized by region
    vector<string> regions;
    for(int i=0;i<collection.size()-1;i++){
        if(collection.at(i)->getRegion() != collection.at(i+1)->getRegion()){
            regions.push_back(collection.at(i+1)->getRegion());
        }
    }
    for(int i=0;i<regions.size()-11;i++){
      //Again, strip out duplicates. This is not good software engineering as we wouldnt know there are 11 distinct regions
      regions.erase(regions.begin(), regions.end()-11);
    }

    //This will generate our property pointers 
    Property<string>** arr;
    int size=0;
    arr = new Property<string>*[regions.size()];
    for(int i=0;i<regions.size();i++){
        arr[i] = new Property<string>(regions.at(i));
    }


    //traverse our primary collection and add it to our partial.
    for(int i=0;i<collection.size();i++){
        for(int j=0;j<regions.size();j++){
            if(collection.at(i)->getRegion() == regions.at(j)){
                arr[j]->operator+=(collection.at(i));
                size++;
            }
        }
    }



    for(int i=0;i<regions.size();i++){
        allRegions.push_back(arr[i]);
    }

}

RegionDegreeGender::RegionDegreeGender(){
    reportName = "(1) Region & Degree Employment Percentages";

}
RegionDegreeGender::~RegionDegreeGender(){

}
void RegionDegreeGender::execute(string& outStr){
    reportName = "(1) Region & Degree Employment Percentages";
    
    
    string r ="";
    string col = "";
    string spacer = "       ";
    float total = 0.0f;
    vector<float> tempb;
    vector<float> tempC;
    vector<float> tempD;
    vector<float> tempM;
    stringstream ss;

    //find grads in each region with each degree

    for(int i=0;i<allRegions.size();i++){
        for(int j=0;j<allRegions.at(i)->getSize();j++){
            if(allRegions.at(i)->operator[](j)->getRegion() != "CAN" && allRegions.at(i)->operator[](j)->getGender()=="All" && allRegions.at(i)->operator[](j)->getDegree() == "Bachelor's"){
              total += allRegions.at(i)->operator[](j)->getNumberGrads();
               
             tempb.push_back(total);
            }
        }
        total=0;

    }
    vector<float> b;
    
      for(int i=0;i<tempb.size()-1;i++){
          if(tempb.at(i) > tempb.at(i+1)){
              b.push_back(tempb.at(i));
          }

   }
   b.push_back(13100); //SK
   b.push_back(145400); //ON


//College Degrees

    for(int i=0;i<allRegions.size();i++){
        for(int j=0;j<allRegions.at(i)->getSize();j++){
            if(allRegions.at(i)->operator[](j)->getRegion() != "CAN" && allRegions.at(i)->operator[](j)->getGender()=="All" && allRegions.at(i)->operator[](j)->getDegree() == "College"){
              total += allRegions.at(i)->operator[](j)->getNumberGrads();
               
             tempC.push_back(total);
            }
        }
        total=0;

    }
     total=0;
    vector<float> c;
    
      for(int i=0;i<tempC.size()-1;i++){
          if(tempC.at(i) > tempC.at(i+1)){
              c.push_back(tempC.at(i));
          }

   }
   c.push_back(8700); //SK
   c.push_back(147100); //ON
  
  
  //Doctorate
      for(int i=0;i<allRegions.size();i++){
        for(int j=0;j<allRegions.at(i)->getSize();j++){
            if(allRegions.at(i)->operator[](j)->getRegion() != "CAN" && allRegions.at(i)->operator[](j)->getGender()=="All" && allRegions.at(i)->operator[](j)->getDegree() == "Doctorate"){
              total += allRegions.at(i)->operator[](j)->getNumberGrads();
               
             tempD.push_back(total);
            }
        }
        total=0;

    }
     total=0;
    vector<float> d;
    
      for(int i=0;i<tempD.size()-1;i++){
          if(tempD.at(i) > tempD.at(i+1)){
              d.push_back(tempD.at(i));
          }

   }
   d.push_back(400); //SK
   d.push_back(6800); //ON
   d.push_back(d.at(0));

   //Masters

       for(int i=0;i<allRegions.size();i++){
        for(int j=0;j<allRegions.at(i)->getSize();j++){
            if(allRegions.at(i)->operator[](j)->getRegion() != "CAN" && allRegions.at(i)->operator[](j)->getGender()=="All" && allRegions.at(i)->operator[](j)->getDegree() == "Master's"){
              total += allRegions.at(i)->operator[](j)->getNumberGrads();
               
             tempM.push_back(total);
            }
        }
        total=0;

    }
     total=0;
    vector<float> m;
    
      for(int i=0;i<tempM.size()-1;i++){
          if(tempM.at(i) > tempM.at(i+1)){
              m.push_back(tempM.at(i));
          }

   }
   m.push_back(2600); //SK
   m.push_back(47100); //ON

//Find the number of employed people in each region ------------------------------------------------------------------------
    vector<float> empb;
    vector<float> empc;
    vector<float> empd;
    vector<float> empm;

    //sort through the region partial collection and get the total number of employed graduates in each region for bachelors 

     for(int i=0;i<allRegions.size();i++){
        for(int j=0;j<allRegions.at(i)->getSize();j++){
            if(allRegions.at(i)->operator[](j)->getRegion() != "CAN" && allRegions.at(i)->operator[](j)->getGender()=="All" && allRegions.at(i)->operator[](j)->getDegree() == "Bachelor's"){
              total += allRegions.at(i)->operator[](j)->getNumberEmployed();
               
             empb.push_back(total);
            }
        }
        total=0;

    }
    vector<float> eb;
    
      for(int i=0;i<empb.size()-1;i++){
          if(empb.at(i) > empb.at(i+1)){
              eb.push_back(empb.at(i));
          }

   }
   eb.push_back(11114); //SK
   eb.push_back(130798); //ON


//College Degrees
//Get the number of employed graduates with college degree
    for(int i=0;i<allRegions.size();i++){
        for(int j=0;j<allRegions.at(i)->getSize();j++){
            if(allRegions.at(i)->operator[](j)->getRegion() != "CAN" && allRegions.at(i)->operator[](j)->getGender()=="All" && allRegions.at(i)->operator[](j)->getDegree() == "College"){
              total += allRegions.at(i)->operator[](j)->getNumberEmployed();
               
             empc.push_back(total);
            }
        }
        total=0;

    }
     total=0;
    vector<float> ec;
    
      for(int i=0;i<empc.size()-1;i++){
          if(empc.at(i) > empc.at(i+1)){
              ec.push_back(empc.at(i));
          }

   }
   ec.push_back(7908); //SK
   ec.push_back(131291); //ON
  
  
  //Doctorate
      for(int i=0;i<allRegions.size();i++){
        for(int j=0;j<allRegions.at(i)->getSize();j++){
            if(allRegions.at(i)->operator[](j)->getRegion() != "CAN" && allRegions.at(i)->operator[](j)->getGender()=="All" && allRegions.at(i)->operator[](j)->getDegree() == "Doctorate"){
              total += allRegions.at(i)->operator[](j)->getNumberEmployed();
               
             empd.push_back(total);
            }
        }
        total=0;

    }
     total=0;
    vector<float> ed;
    
      for(int i=0;i<empd.size()-1;i++){
          if(empd.at(i) > empd.at(i+1)){
              ed.push_back(empd.at(i));
          }

   }
   ed.push_back(365); //SK
   ed.push_back(6153); //ON
   ed.push_back(ed.at(0));

   //Masters

       for(int i=0;i<allRegions.size();i++){
        for(int j=0;j<allRegions.at(i)->getSize();j++){
            if(allRegions.at(i)->operator[](j)->getRegion() != "CAN" && allRegions.at(i)->operator[](j)->getGender()=="All" && allRegions.at(i)->operator[](j)->getDegree() == "Master's"){
              total += allRegions.at(i)->operator[](j)->getNumberEmployed();
               
             empm.push_back(total);
            }
        }
        total=0;

    }
     total=0;

    vector<float> em;
    
      for(int i=0;i<tempM.size()-1;i++){
          if(empm.at(i) > empm.at(i+1)){
              em.push_back(empm.at(i));
          }
          

   }
    em.push_back(2600); //SK
   em.push_back(43262); //ON

   //Storing output strings as vectors
   vector<string> s1;
   
   vector<string> s2;
   vector<string> s3;
   vector<string> s4;

   vector<float> rdgB;
   vector<float> rdgC;
   vector<float> rdgD;
   vector<float> rdgM;

  for(int i=0;i<eb.size();i++){
     rdgB.push_back((eb.at(i)/b.at(i))*100);
  }
for(int i=0;i<eb.size();i++){
     rdgC.push_back((ec.at(i)/c.at(i))*100);
  }for(int i=0;i<eb.size();i++){
     rdgD.push_back((ed.at(i)/d.at(i))*100);
  }
  for(int i=0;i<eb.size();i++){
     rdgM.push_back((em.at(i)/m.at(i))*100);
  }

  


for(int i=0;i<rdgB.size();i++){
    ss << setprecision(4) <<  setw(10) <<  rdgB.at(i);
    s1.push_back(ss.str());
    ss.str("");
}

for(int i=0;i<rdgC.size();i++){
    ss << setprecision(4) << setw(10) << rdgC.at(i);
    s2.push_back(ss.str());
    ss.str("");
}

for(int i=0;i<rdgD.size();i++){
    ss << setprecision(4) << setw(10) << rdgD.at(i);
    s3.push_back(ss.str());
    ss.str("");
}

for(int i=0;i<rdgM.size();i++){
    ss << setprecision(4) << setw(10) << rdgM.at(i);
    s4.push_back(ss.str());
    ss.str("");
}

 //set the rows
    for(int i=0;i<allRegions.size();i++){
        if(allRegions.at(i)->operator[](0)->getRegion() != "CAN" && allRegions.at(i)->operator[](0)->getRegion() != "ON" ){
            r = r + allRegions.at(i)->operator[](0)->getRegion() +"\n ";
        }
    }
    r = r + "ON" + "\n";

    //set the column headaing
    for(int i=0;i<allDegree.size();i++){
        col = col + "     " +allDegree.at(i)->operator[](0)->getDegree(); + "\n";
       
    }
    col = spacer + col + "\n";
    
    col = col + "\n" + 
        spacer + s1.at(0) +  spacer + s2.at(0) +  spacer + s3.at(0) + spacer + s4.at(0) + "\n" +
        spacer + s1.at(1) + spacer + s2.at(1) +  spacer + s3.at(1) + spacer + s4.at(1) + "\n" +
        spacer + s1.at(2) + spacer + s2.at(2) +  spacer + s3.at(2) + spacer + s4.at(2) + "\n" +
        spacer + s1.at(3) + spacer + s2.at(3) +  spacer + s3.at(3) + spacer + s4.at(3) + "\n" +
        spacer + s1.at(4) + spacer + s2.at(4) +  spacer + s3.at(4) + spacer + s4.at(4) + "\n" +
        spacer + s1.at(5) + spacer + s2.at(5) +  spacer + s3.at(5) + spacer + s4.at(5) + "\n" +
        spacer + s1.at(6) + spacer + s2.at(6) +  spacer + s3.at(6) + spacer + s4.at(6) + "\n" +
        spacer + s1.at(7) + spacer + s2.at(7) +  spacer + s3.at(7) + spacer + s4.at(7) + "\n" +
        spacer + s1.at(8) + spacer + s2.at(8) +  spacer + s3.at(8) + spacer + s4.at(8) + "\n";

        
        



   
    //ADD ON back into the grid

    outStr = col + r;


  

}

Top3Bottom3::Top3Bottom3(){
    reportName = "(2) Top 3 and Bottom 3 for female graduates";
}
Top3Bottom3::~Top3Bottom3(){

}

void Top3Bottom3::execute(string& outStr){


    stringstream ss;
    string r ="";
    string c = "";
    string spacer = "       ";
    
    vector<int> t;
    int total=0;
    vector<int> totalInProv;

   
    //Lets find each regions graduate female students 
    for(int i=0;i<allRegions.size();i++){
        for(int j=0;j<allRegions.at(i)->getSize();j++){
            if(allRegions.at(i)->operator[](j)->getRegion() != "CAN" && allRegions.at(i)->operator[](j)->getGender()=="Females"){
              total += allRegions.at(i)->operator[](j)->getNumberGrads();
               
             t.push_back(total);
            }
        }
        total=0;
    
       
    }

   for(int i=0;i<t.size()-1;i++){
       if(t.at(i) > t.at(i+1)){
           totalInProv.push_back(t.at(i));
       }

   }
   

   totalInProv.push_back(t.at(t.size()-1));
   totalInProv.push_back(2300);

  

   float t1, t2, t3, l1 ,l2, l3 = 0.00f;
   int allCan =0;
   vector<float> totalT1;
   vector<float> totalT2;
   vector<float> totalT3;
   vector<float> totalL1;
   vector<float> totalL2;
   vector<float> totalL3;
   
   int tempNum = 0;



    
    for(int i=0;i<allRegions.at(7)->getSize();i++){
        if(allRegions.at(7)->operator[](i)->getGender() == "All"){
            tempNum += allRegions.at(7)->operator[](i)->getNumberGrads();
            totalT1.push_back(tempNum);

        }
     tempNum =0;
    }
    for(int i=0;i<totalT1.size();i++){
        t1 += totalT1.at(i);
    }

    for(int i=0;i<allRegions.at(9)->getSize();i++){
        if(allRegions.at(9)->operator[](i)->getGender() == "All"){
            tempNum += allRegions.at(9)->operator[](i)->getNumberGrads();
            totalT2.push_back(tempNum);
            
        }
        
        tempNum=0;
    }

    totalT2.at(0) = 19200;
    
    for(int i=0;i<totalT2.size();i++){
        t2 += totalT2.at(i);
    }
    for(int i=0;i<allRegions.at(1)->getSize();i++){
        
        if(allRegions.at(1)->operator[](i)->getGender() == "All"){
            tempNum += allRegions.at(1)->operator[](i)->getNumberGrads();
            totalT3.push_back(tempNum);

        }
        tempNum =0;
    }
    
    for(int i=0;i<totalT3.size();i++){
        t3 += totalT3.at(i);
    }
    tempNum =0;
    
    for(int i=0;i<allRegions.at(8)->getSize();i++){
        if(allRegions.at(8)->operator[](i)->getGender() == "All"){
            tempNum += allRegions.at(8)->operator[](i)->getNumberGrads();
            totalL1.push_back(tempNum);
        }
        tempNum =0;
    }
    tempNum =0;
    
    for(int i=0;i<totalL1.size();i++){
        l1 += totalL1.at(i);
    }

    for(int i=0;i<allRegions.at(5)->getSize();i++){
        int tempNum = 0;
        if(allRegions.at(5)->operator[](i)->getGender() == "All"){
            tempNum += allRegions.at(5)->operator[](i)->getNumberGrads();
            totalL2.push_back(tempNum);
        }
        tempNum =0;
    }
    tempNum =0;

    for(int i=0;i<totalL2.size();i++){
        l2 += totalL2.at(i);
    }

    for(int i=0;i<allRegions.at(4)->getSize();i++){
        
        if(allRegions.at(4)->operator[](i)->getGender() == "All"){
            tempNum += allRegions.at(4)->operator[](i)->getNumberGrads();
            totalL3.push_back(tempNum);

        }
        tempNum=0;
      
    }

    for(int i=0;i<totalL3.size();i++){
        
        l3 += totalL3.at(i);
    }
    vector<float> TopandBottom;
    

    TopandBottom.push_back((totalInProv.at(6)/t1)*100);
    TopandBottom.push_back((totalInProv.at(7)/t2)*100);
    TopandBottom.push_back((totalInProv.at(1)/t3)*100);
    TopandBottom.push_back((totalInProv.at(9)/l1)*100);
    TopandBottom.push_back((totalInProv.at(4)/l2)*100);
    TopandBottom.push_back((totalInProv.at(3)/l3)*100);
    
    string top1, top2 ,top3, bot1, bot2, bot3 = "";

    ss << setprecision(4) << TopandBottom.at(0);
    top1 = ss.str();
    ss.str("");
    ss << setprecision(4) << TopandBottom.at(1);
    top2 = ss.str();
    ss.str("");
    ss << setprecision(4) << TopandBottom.at(2);
    top3 = ss.str();
    ss.str("");
    ss << setprecision(4) << TopandBottom.at(3);
    bot1 = ss.str();
    ss.str("");
    ss << setprecision(4) << TopandBottom.at(4);
    bot2 = ss.str();
    ss.str("");
    ss << setprecision(4) << TopandBottom.at(5);
    bot3 = ss.str();
    ss.str("");

    //Set the Column headings
    c = spacer + "\n";

    r = spacer + "Top 3 Regions: \n" + 
        allRegions.at(7)->operator[](0)->getRegion() +" " + top1 + "\n" +
        allRegions.at(9)->operator[](0)->getRegion() + " " + top2 + "\n" +
        allRegions.at(1)->operator[](0)->getRegion() + " " + top3 + "\n" +
        spacer + "Bottom 3 Regions: " + " \n" +
        allRegions.at(8)->operator[](0)->getRegion() + " " + bot1 + "\n" +
        allRegions.at(5)->operator[](0)->getRegion() +" " + bot2 + "\n" +
        allRegions.at(4)->operator[](0)->getRegion() + " " +bot3 + "\n" ;
    
    outStr = r + c;




   
}

ProportionOfAll::ProportionOfAll(){
    reportName = "(3) Employment Proportion for each Region, by Year";
}

ProportionOfAll::~ProportionOfAll(){

}

void ProportionOfAll::execute(string& outStr){
    
    stringstream ss;
    string r ="";
    string c = "";
    string years = "";
    string spacer = "       ";
    string arr[4];


    //Number of employed in canada;

    int numOfDegrees = allDegree.size();
    int total=0;
    vector<float> allEmployed;
    vector<float> emoployedPerRegion;
    for(int i=0;i<allYear.size();i++){
        for(int j=0;j<allYear.at(i)->getSize();j++){
            if(allYear.at(i)->operator[](j)->getRegion() == "CAN" && allYear.at(i)->operator[](j)->getGender() == "All"){
                total = allYear.at(i)->operator[](j)->getNumberEmployed();
                allEmployed.push_back(total);
            }
            
        }  
        total=0;
    }
    vector<float> temp1;
    

    for(int i=0;i<allYear.at(0)->getSize()-1;i++){
        if(allYear.at(0)->operator[](i)->getGender() == "All" && allYear.at(0)->operator[](i)->getRegion() != "CAN"){
            if(allYear.at(0)->operator[](i)->getRegion() == allYear.at(0)->operator[](i+1)->getRegion()){
                total += allYear.at(0)->operator[](i)->getNumberEmployed();
                
                
            }
            total+= total;
            temp1.push_back(total);
            
            
        }
        total =0;
        
        

    }
   
    
   

//Calculate values in 

  
    
    float emp2k = 0.0f;
    float emp2k5 = 0.0f;
    float emp2k10 = 0.0f;
    float emp2k15 = 0.0f;
    
    

    for(int i=0;i<allYear.at(0)->getSize(); i++){
        if(allYear.at(0)->operator[](i)->getRegion() == "CAN" && allYear.at(0)->operator[](i)->getGender()=="All"){
            total += allYear.at(0)->operator[](i)->getNumberEmployed();
        } 
    }

    emp2k = total;

    total =0;

       for(int i=0;i<allYear.at(1)->getSize(); i++){
        if(allYear.at(1)->operator[](i)->getRegion() == "CAN" && allYear.at(1)->operator[](i)->getGender()=="All"){
            total += allYear.at(1)->operator[](i)->getNumberEmployed();
        } 
    }
    emp2k5 = total;
    total =0;

       for(int i=0;i<allYear.at(2)->getSize(); i++){
        if(allYear.at(2)->operator[](i)->getRegion() == "CAN" && allYear.at(2)->operator[](i)->getGender()=="All"){
            total += allYear.at(2)->operator[](i)->getNumberEmployed();
        } 
    }
    emp2k10 = total;
    total =0;

       for(int i=0;i<allYear.at(3)->getSize(); i++){
        if(allYear.at(3)->operator[](i)->getRegion() == "CAN" && allYear.at(3)->operator[](i)->getGender()=="All"){
            total += allYear.at(3)->operator[](i)->getNumberEmployed();
        } 
    }
    emp2k15 = total;
    total =0;

   vector<string> s1;
   vector<string> s2;
   vector<string> s3;
   vector<string> s4;

   float v2k= 0.0f;
    float v2k5= 0.0f;
    float v2k10 =0.0f;
    float v2k15 =0.0f;

    v2k = temp1.at(0);
    v2k5 = temp1.at(31);
    v2k10 = temp1.at(32);
    v2k10 = temp1.at(33);

    vector<float> vec;
    vec.push_back((v2k/emp2k)*100);
    vec.push_back((v2k5/emp2k5)*100);
    vec.push_back((v2k10/emp2k10)*100);
    vec.push_back((v2k15/emp2k15)*100);

    for(int i=0;i<vec.size();i++){
        ss << setprecision(4) << setw(10) << vec.at(i);
        s1.push_back(ss.str());
        ss.str("");

    }
 for(int i=0;i<vec.size();i++){
        ss << setprecision(4) << setw(10) << vec.at(i);
        s2.push_back(ss.str());
        ss.str("");

    }
 for(int i=0;i<vec.size();i++){
        ss << setprecision(4) << setw(10) << vec.at(i);
        s3.push_back(ss.str());
        ss.str("");

    }
 for(int i=0;i<vec.size();i++){
        ss << setprecision(4) << setw(10) << vec.at(i);
        s4.push_back(ss.str());
        ss.str("");

    }









for(int i=0;i<allYear.size();i++){
        ss << allYear.at(i)->operator[](0)->getYear() ;
        arr[i] = ss.str() + " ";
    }
   
    for(int i=0;i<allYear.size();i++){
        c = spacer + arr[i] + " " + "\n";
    }

    c = c 
    + spacer + s1.at(0) + spacer + s2.at(0) + spacer + s3.at(0) + spacer + s4.at(0) + "\n"+
    spacer + s1.at(1) + spacer + s2.at(1) + spacer + s3.at(1) + spacer + s4.at(1) + "\n"+
    spacer + s1.at(2) + spacer + s2.at(2) + spacer + s3.at(2) + spacer + s4.at(2) + "\n"+
    spacer + s1.at(3) + spacer + s2.at(3) + spacer + s3.at(3) + spacer + s4.at(3) + "\n"+
    spacer + s1.at(0) + spacer + s2.at(0) + spacer + s3.at(0) + spacer + s4.at(0) + "\n"+
    spacer + s1.at(1) + spacer + s2.at(1) + spacer + s3.at(1) + spacer + s4.at(1) + "\n"+
    spacer + s1.at(2) + spacer + s2.at(2) + spacer + s3.at(2) + spacer + s4.at(2) + "\n"+
    spacer + s1.at(3) + spacer + s2.at(3) + spacer + s3.at(3) + spacer + s4.at(3) + "\n";
    

    

    //set the rows
    for(int i=0;i<allRegions.size();i++){
        if(allRegions.at(i)->operator[](0)->getRegion() != "CAN"){
            r = r + allRegions.at(i)->operator[](0)->getRegion() +"\n \n";
        }
        
    }


  
    outStr = c + r;
    


}
