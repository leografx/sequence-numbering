#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

void config(char** argv);
void generateFirstRow();
void rowNumbersIncreaseByOne();
void outputNumbers();
string lpad(int number);
string header();

struct num { int startingNumber, quantity, nup, sheets; vector<int> firstRow; string leftPadding; ofstream numFile; string path;};
struct num num = { .startingNumber = 0, .quantity = 0, .nup=1, .sheets=1, .leftPadding = "n"  };

int main(int argc, char **argv ){
    num.path = (argc > 1)? argv[1] : "num";
   config(argv); 
   generateFirstRow();
   outputNumbers();
   num.numFile.close();
   
   return 0;
}

void config(char** argv){
    // cout << "Starting# " << *argv[3] << argv[3] << endl;
    num.startingNumber = atoi(argv[2]);
    num.quantity =  atoi(argv[3]);
    num.nup = atoi(argv[4]);
    num.sheets = ceil( ceil((double) num.quantity / (double) num.nup));

    num.leftPadding = argv[5];

}

string header(){
    string head = "";
    for (int i = 1; i <= num.nup; i++ ){
        string separator = (i == num.nup)? "\n":",";
        head += "C" + to_string(i) + separator;
    }
    cout << head << endl;
    return head;
}

void generateFirstRow(){
    num.firstRow.push_back(num.startingNumber);
    
    for (int i = 1; i < num.nup; i++ ){
        num.firstRow.push_back( num.startingNumber + num.sheets * i );
    }
}

void outputNumbers(){
        num.numFile.open(num.path+".csv");
        num.numFile << header();
    for (int i = 0; i < num.sheets; i++){
        rowNumbersIncreaseByOne();
    }
}

void rowNumbersIncreaseByOne(){
    

    string num4File = "";
    int size = num.firstRow.size();
    for (int i = 0; i < size; i++){
        string separator = (i == size-1)? "\n":",";
        int n = num.firstRow[i];
        cout << lpad(n) << separator;
        num4File += lpad(n);
        num4File += separator;
        num.firstRow[i] +=1;      
    }
    num.numFile << num4File;
    
}

string lpad(int number){
    int digits = to_string(num.startingNumber + num.quantity).length();
    string lpadString = "";
    int n = to_string(number).length();
    
    if( num.leftPadding == "y"){
        for(int i=0; i < digits - n; i++){
            lpadString += "0";
        }
    }

    return lpadString + to_string(number);
}