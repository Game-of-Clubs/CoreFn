// ****** Game of Clubs Back-end dev ******
//
//  Ayotunde Odejayi 2016 (c)
// ****************************************

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;

int main() {

    // Set-up parameters
    const int no_years = 4, no_players = 1, width = 3;
    ifstream file_reader;

    // Asset prices
    float stocks[no_years+1][width], fixed_1[no_years][width], fixed_2[no_years-1][width], fixed_3[no_years-2][width], fixed_4[no_years-3][width];
    float real_estate[no_years+1][width], ecommerce[no_years+1][width], farms[no_years+1][width];

    // Read-in data
    file_reader.open("AssetPrices.txt");
    
    for (int i=0; i<no_years+1; i++){
        for (int j=0; j<width; j++)
             file_reader >> stocks[i][j];
    }
    int index = 0;
    for (int i=0; i<no_years; i++) {
            for (int j=0; j<width; j++) 
                file_reader >> fixed_1[i][j];
            if (index < 3) {for (int j = 0; j<width; j++)
                file_reader >> fixed_2[i][j];}
            if (index < 2) {for (int j = 0; j<width; j++)
                file_reader >> fixed_3[i][j];}
            if (index < 1) {for (int j = 0; j<width; j++) 
                file_reader >> fixed_4[i][j];}  

            index++;
    }
    for (int i=0; i<no_years+1; i++){
        for (int j=0; j<width; j++)
             file_reader >> real_estate[i][j];
    }
    for (int i=0; i<no_years+1; i++){
        for (int j=0; j<width; j++)
             file_reader >> ecommerce[i][j];
    }
    for (int i=0; i<no_years+1; i++){
        for (int j=0; j<width; j++)
             file_reader >> farms[i][j];
    }
                
  // Computations
 /
  
  return 0;
}
