/* 
* 	Sabber Ahamed
* 	Homework -2 
* 	Programming tools for Eanginners and scientists
* 	Spring 2015
*/


//header files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int findMax(const vector<int>&);
int findMin(const vector<int>&);
double findAvg(const vector<int>&);

// Main function 
int main() {
    // Variables declarations 
    ifstream inputFile;
    ofstream outputFile;
	vector<int> inputNumbers;
	vector<int> primeNumbers;
	vector<int> nonPrimeNumbers;
	int number;
	bool isPrime;
	string inputFileName;
    string outputFileName;


   //********* reading numbers from file *****************
    cout<< "Please provide the Input File Name : "<< endl;
    cin >> inputFileName ;
    inputFile.open("inputFileName");

    // Checks error related to inputfile 
    inputFile.open(inputFileName.c_str());
    if (inputFile.fail()) { 
      cout << "error" << endl; 
      return 1;

    } 

    // if there is no error, following code will start reading numbers
    while (!inputFile.eof()) { 
        inputFile >> number;
        inputNumbers.push_back(number);

    } 
  	
  	//********* Sorting Prime and Non prime numbers *****************
    for (unsigned int i = 0; i < inputNumbers.size() ; i++) {
    	int currentNumber = inputNumbers[i];
            isPrime = true;

            for (int j = 2; j < currentNumber; j++) {
                if (currentNumber % j == 0) {
                    isPrime = false;
                    break;
                } 
            }

            if (isPrime == false) {
               nonPrimeNumbers.push_back(currentNumber);
            } 
            else {
                if (currentNumber == 0 || currentNumber == 1 || currentNumber < 0 ){
                    nonPrimeNumbers.push_back(currentNumber);
                } 
                else {
                    primeNumbers.push_back(currentNumber);
                }
            }
    }

    //********* Writing prime numbers in output file *****************
    cout<< "Please provide the Output File Name : " << endl;
    cin >> outputFileName;
    outputFile.open(outputFileName.c_str());

    // checking outputfile status
    if(outputFile.fail()) { 
      cout << "error" << endl; 
      return 1;
    } 
    // writing outputs
    for (unsigned int i = 0; i<primeNumbers.size(); i++) {
        outputFile << primeNumbers[i] <<endl;
    }


    //*************************** printing results ******************************
    cout << "Total Numbers read in   : "        << inputNumbers.size()    << endl;
    cout << "Total Prime numbers     : "        << primeNumbers.size()    << endl;
    cout << "Total Non prime numbers : "        << nonPrimeNumbers.size() << endl;

    cout << "Maxima (all, prime, non prime) : " << findMax(inputNumbers) 
                                                << " , " << findMax(primeNumbers) 
                                                << " , " << findMax(nonPrimeNumbers) <<endl;

    cout << "Minima (all, prime, non prime) : " << findMin(inputNumbers) 
                                                << " , " << findMin(primeNumbers) 
                                                << " , " << findMin(nonPrimeNumbers) <<endl;

    cout << "Average (all, prime, non prime) : "<< findAvg(inputNumbers) 
                                                << " , " << findAvg(primeNumbers) 
                                                << " , " << findAvg(nonPrimeNumbers) <<endl;                                          

    //closing files 
    inputFile.close();
    outputFile.close();

	return 0;
}

//******************************* Functions *****************
//******************************* Functions *****************

// Finiding maximum value 
int findMax(const vector<int>& a) {
    
    int max = a[0];
    if (a.size() <= 0) {
    max = 0;
    }
    else {
       for (unsigned int i = 0; i<a.size(); i++) {
          if(a[i] > max)
                max = a[i];
       }
    }
    return max; 
}

//Finding Minimum value
int findMin(const vector<int>& a) {

    int min = a[0];
    if (a.size() <= 0) {
    min = 0;
    }
    else {
       for (unsigned int i = 0; i < a.size(); i++) {
          if(a[i] < min)
                min = a[i];
        } 
    }
    return min;  
}

//Finding average value
double findAvg(const vector<int>& a) {

    double avg = 0;
    if (a.size() <= 0) {
    avg = 0; 
    }
    else {
       for (unsigned int i = 0; i < a.size(); i++) {
          avg += a[i]; 
       }
    avg = avg / a.size();
   }
    return avg;  
}




