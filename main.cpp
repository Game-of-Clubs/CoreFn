#include <iostream>
#include <string>
#include <math>
#include <fstream>
using namespace std;

int main() {

    // Set-up parameters
    const int no_years = 4, no_players = 1, width = 3;
    ifstream file_reader;

    // Asset prices
    int stocks[no_years+1][width], fixed_1[no_years][width], fixed_2[no_years-1][width], fixed_3[no_years-2][width], fixed_4[no_years-3][width];
    int real_estate[no_years+1][width], ecommerce[no_years+1][width], farms[no_years+1][width];

    // Read-in data
    file_reader.open("AssetPrices.txt");
    
    for (int i=0; i<no_years+1; i++){
        for (int i=0; j<width; j++)
             file_reader >> stocks[i][j];
    }
    int index_control = no_years;
    for (int i=0; i<no_years; i++) {
        for (int index = 0; index<index_control; index++) {
            for (int j=0; j<width; j++) {
                file_reader >> fixed_1[i][j];
                if (index > 0) file_reader >> fixed_2[i][j];
                if (index > 1) file_reader >> fixed_3[i][j];
                if (index > 2) file_reader >> fixed_4[i][j];  
            }
        }
    }
                
   // Test
   for (int i = 0; i<no_years; i++) {
     for (int j = 0; j< width; j++) {
       cout << stocks[i][j] << " ";
     }
   cout << endl;
   }  

    system("pause");
}
