/* 
*   Sabber Ahamed
*   Homework -3
*   Programming tools for Eanginners and scientists
*   Spring 2015
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

using namespace std;

// functions used in this programs are initialized first
void ShowReport(int **mainArray, string* stationName, int stationNumber, 
                string* instrumentName, int instrumentNumber);
void generateError(int errorNumber, string name);
int findMax(int* a, int length);
int findMin(int* a, int length);


//main function starts

int main() {

  // Input/Output reated variables
    ifstream inputFile;
    ofstream outputFile;
    string inputFileName;
    

    string line;
    int stationNumber;
    int instrumentNumber;
    int row;

  //********* reading numbers from file *****************
    cout<< "Please provide the Input File Name : "<< endl;
    cin >> inputFileName ;
    inputFile.open("inputFileName");

    // Checks error related to inputFile 
    inputFile.open(inputFileName.c_str());
    if (inputFile.fail()) { 
      cout << "Error reading the file  " << inputFileName << endl;
      generateError(1, inputFileName);
      return 1;

    } 
   
    /* reading the Number of stations and number 
    * of instruments from the first line */

    cout << "starts reading ...." <<endl;
    getline(inputFile, line);
    istringstream number (line);
    number >> stationNumber;
    number >> instrumentNumber;

    /* After reading the Number of stations and number 
    * of instruments we allocate the arrays below */

    string stationName[stationNumber];
    string instrumentName[instrumentNumber];
    string token[3];
    
    //2D array declarations for EQ events storing
    int **mainArray;
    mainArray = new int* [stationNumber];
    for (int i=0; i < stationNumber; i++)
        mainArray[i] = new int[instrumentNumber];

    
    //collecting station names :
    getline(inputFile, line);
    istringstream sss (line);
    for (int i = 0; i<stationNumber; i++){
       sss >> stationName[i];
    }
    cout << "Finished reading stations" << endl;

    //collecting instruments names :
    getline(inputFile, line);
    istringstream iss (line);
    for (int i = 0; i<instrumentNumber; i++){
       iss >> instrumentName[i];    
    }
    cout << "Finished reading instruments" << endl;

    // initializung mainarray 
    for (int i = 0; i < stationNumber ; i++) {
     for (int j = 0; j < stationNumber ; j++){
        mainArray[i][j] = 0;
      }
    }

    
    cout << "Started reading entries" << endl;
    while (!inputFile.eof()) {

      getline(inputFile, line);  
      istringstream rss (line);
      rss >> token[0];
      rss >> token[1];
      rss >> token[2];
    
    /*Checking the stations and instruments with the file 
      and second lines respectively */

      int arrayNumber;
      std::istringstream(token[2]) >> arrayNumber;
      //checking stations 
      for (int i = 0; i < stationNumber; i++) {
        if (token[0] == stationName[i]) {
          row = i;
          
          //Checking Instruments 
          for (int j =0; j<instrumentNumber ; j++) { 
            if (token[1] == instrumentName[j]) {
              if (arrayNumber < 0){
                  mainArray[row][j] =  0;
                  generateError(4, token[0]);
                  cout << "Error # 4 : "<<" Negetive number ( " <<  token[2] << " ) of events!! (become zero)" <<endl;
              }
              else {
                  mainArray[row][j] = arrayNumber;
              }
            }
            else {
               generateError(3, token[1]);
               continue ;
            }
          }
                     
        }
        else {
            generateError(2, token[0]);
            continue ;
        }
      }
       
    }
    
    cout << "Finished reading entries" << endl;
    cout << "Started generating reports" << endl;

    ShowReport(mainArray, stationName, stationNumber, 
               instrumentName, instrumentNumber);
    
    cout << "Congratulations !! Finished generating  reports" << endl;
    cout << "Finished " << endl;
 }
  




// This function is responsible for generating reports

void ShowReport(int **mainArray, string* stationName, int stationNumber, 
                string* instrumentName, int instrumentNumber) {

   int maxLength = 10;
   int kks[stationNumber];
   int kki[instrumentNumber];
   ofstream outputFile;

   outputFile.open("sabber.out");

   outputFile << "Number of Stations : "    << stationNumber << endl;
   outputFile << "Number of Instruments : " << instrumentNumber << endl;
   outputFile << endl;

   // reporting the information :
   outputFile << "\n";
   outputFile << "============================================"<< endl;
   outputFile << "==    Seismic Events Summary Report       ==" << endl;
   outputFile << "============================================"<< endl;
   outputFile << "\n";

   outputFile << "Station" << setw(20);

   for (int i = 0 ; i < instrumentNumber ; i++){
       outputFile << instrumentName[i] << setw(23);

   }
   outputFile<<"\n"<<"\n";

   for (int i = 0; i < stationNumber ; i++){
        int stationNamelength = stationName[i].length();
        int setwValue = 15 + (maxLength-stationNamelength) ;
        outputFile << stationName[i] << setw(setwValue);
        for (int j = 0; j < instrumentNumber ; j++){

           outputFile << mainArray[i][j] << setw(22);
       }
       outputFile<< "\n";
   }


   outputFile << "\n";
   outputFile << "============================================"<< endl;
   outputFile << "== Total number of events per Station ==" <<endl;
   outputFile << "============================================"<< endl;
   outputFile << endl;
   outputFile << " Station" << setw(maxLength+15) << " Total "<<endl;
   outputFile << "---------"<< setw(maxLength+15) << " -------- " << "\n";
   outputFile << endl;

   for (int i = 0; i < stationNumber ; i++){
        int stationNamelength = stationName[i].length();
        int setwValue = 20 + (maxLength-stationNamelength) ;
        outputFile << stationName[i] << setw(setwValue);
        int sum = 0;
        for (int j = 0; j < instrumentNumber ; j++){

           sum = sum + mainArray[i][j];
       }

        kks[i] = sum;
        outputFile << setw(setwValue);
        outputFile << std::right << sum ;
        outputFile << "\n";
   }

   outputFile << "\n";
   outputFile << "============================================"<< endl;
   outputFile << "== Total number of events per instrument  ==" <<endl;
   outputFile << "============================================"<< endl;
   outputFile << endl;
   outputFile << " Instrument " << setw(maxLength+15) << "  Total "<<endl;
   outputFile << "------------" << setw(maxLength+15) << " -------- " << "\n";
   outputFile << endl;

   for (int i = 0; i < instrumentNumber ; i++) {
        int instNamelength = instrumentName[i].length();
        int setwValue = 25 + (maxLength-instNamelength) ;
        outputFile << instrumentName[i] << setw(setwValue);
        int sum = 0;

        for (int j = 0; j < stationNumber ; j++){

           sum = sum + mainArray[j][i]; 


        }
        
        kki[i] = sum;
        outputFile <<setw(setwValue);
        outputFile << std::right << sum ;
        outputFile << "\n";
   }

   outputFile << "\n";
   outputFile << "============================================"<< endl;
   outputFile << "==       statistics of the evenets       ==" <<endl;
   outputFile << "============================================"<< endl;
   outputFile << endl;
   
   int j = findMax(kks, stationNumber);
   int k = findMin(kks, stationNumber);
   outputFile << "Station with the most records is: "  << stationName[j] << " with " 
              << kks[j] << " events " << endl;
   outputFile << "Station with the least records is: " << stationName[k] << " with "    
              << kks[k] << " events " << endl;


   j = findMax(kki, instrumentNumber);
   k = findMin(kki, instrumentNumber);
   outputFile << endl;
   outputFile << "Instrument with the most records is: "  << instrumentName[j] << " with " 
              << kki[j] << " events " << endl;
   outputFile << "Instrument with the least records is: " << instrumentName[k] << " with "    
              << kki[k] << " events " << endl;
}


// This function is responsible for generating error.

void generateError(int errorNumber, string name){

    ofstream outputErrorFile;
    outputErrorFile.open("sabber.err", ofstream::out | ofstream::app);
    switch (errorNumber) {
      case 1 : 
          outputErrorFile << "Error # 1"    << "Error reading the file  ' " << name << " '" << endl; 
          break;
      case 2 :
          outputErrorFile << "Error # 2 : " << name << " is not available in station list" <<endl;
          break;
      case 3 :
          outputErrorFile << "Error # 3 : " << name << " is not available in instrument list " <<endl;
          break;
      case 4 :
          outputErrorFile << "Error # 4 : " <<" Negetive number ( " <<  name << " ) of events (become 0)" <<endl;
          break;
    }
}


/*Finding maximum value and returning
* the corresponding index number*/

int findMax(int* a, int length) {
    int max = a[0];
    int kk;
    if (length <= 0) {
    max = 0;
    }
    else {
       for (int i = 0; i < length; i++) {
          if(a[i] >= max ) {
                max = a[i];
                kk = i ;
              }
       }
    }
    return kk; 
}

/*Finding Minimum value and returning
* the corresponding index number*/

int findMin(int* a, int length) {
    int min = a[0];
    int kk; 
    if (length <= 0) {
    min = 0;
    }
    else {
       for (int i = 0; i < length; i++) {
          if(a[i] <= min) {
                min = a[i];
                kk = i ;
              }
        } 
    }
    return kk;  
}

















