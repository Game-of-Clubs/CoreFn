// ****** Game of Clubs Back-end dev ******
//
//  Ayotunde Odejayi 2016 (c)
// ****************************************

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;

void get_user_data ();
bool ensure_valid_input (float);
void compute_valuation();

// Set-up parameters
  const int no_years = 4, no_players = 1, width = 3;
  const float initial_cash = 100000000.0;
  float stock_val = 0.0, fixed1_val = 0.0, fixed2_val = 0.0, fixed3_val = 0.0, fixed4_val = 0.0, real_estate_val = 0.0, ecommerce_val = 0.0, farms_val = 0.0;
  float valid_input_sum = 0.0;
  float valuation_results[no_years][11];
  int curr_yr = 1;
  bool cashless = false;

// Asset prices
    float stocks[no_years+1][width], fixed_1[no_years][width], fixed_2[no_years-1][width], fixed_3[no_years-2][width], fixed_4[no_years-3][width];
    float real_estate[no_years+1][width], ecommerce[no_years+1][width], farms[no_years+1][width];


int main() {

    // Initialize valuation_results array
    for (int i =0; i<no_years; i++) {
        for (int j=0; j<11; j++) {
            valuation_results[i][j] = 0.0;
        }
    }
    ifstream file_reader;

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
                
  // Core functionality
  get_user_data();

  compute_valuation();

  return 0;
}


void compute_valuation() {
    // Sort stocks
    valuation_results[curr_yr][0] = (stocks[curr_yr][1]/100 + 1.0) * stock_val;    
    valuation_results[curr_yr][1] = (fixed_1[curr_yr][1]/100 + 1.0) * fixed1_val;
    valuation_results[curr_yr][2] = (fixed_2[curr_yr][1]/100 + 1.0) * fixed2_val;
    valuation_results[curr_yr][3] = (fixed_3[curr_yr][1]/100 + 1.0) * fixed3_val;    
    valuation_results[curr_yr][4] = (fixed_4[curr_yr][1]/100 + 1.0) * fixed4_val;
    valuation_results[curr_yr][5] = (real_estate[curr_yr][1]/100 + 1.0) * real_estate_val;    
    valuation_results[curr_yr][6] = (ecommerce[curr_yr][1]/100 + 1.0) * ecommerce_val;
    valuation_results[curr_yr][7] = (farms[curr_yr][1]/100 + 1.0) * farms_val;    

    for (int i = 0; i<10; i++) 
        valuation_results[curr_yr][10] += valuation_results[curr_yr][i]; 
    
   // Valuation results
   cout << "\n\nValuation results for Yr(" << curr_yr << ") are: Stock Portfolio: N" << valuation_results[curr_yr][0] << " | Fixed Income: N" << valuation_results[curr_yr][1] << " | Fixed Inc 2-yr: N"
        << valuation_results[curr_yr][2] << " | Fixed Inc 3-yr: N" << valuation_results[curr_yr][3] << " | Fixed Inc 4-yr: N" << valuation_results[curr_yr][4] << " | Real Estate: N" 
        << valuation_results[curr_yr][5] << " | VC: e-commerce: N" << valuation_results[curr_yr][6] << " | VC:Farm: N" << valuation_results[curr_yr][7] << " | Lending/Borrowing:  N"
        << valuation_results[curr_yr][8] << " | Cash: N" << valuation_results[curr_yr][9] 
        << "TOTAL: N" << valuation_results[curr_yr][10] << "\n\n";     

}


void get_user_data() {
   //showFullScreen();
   bool valid = false;
   string resp;
   cout << "\n******************************** Welcome to Game of Clubs *******************************" << endl;
   cout << fixed << "\nYou have N" << setprecision(1) << initial_cash << " cash available\n";  
   cout << "\nYour investment options are:\n Stock Portfolio\n Fixed Income: 1yr\n Fixed Income: 2yr\n Fixed Income: 3yr\n Fixed Income: 4yr\n Real Estate\n VC: e-commerce\n VC: Farm\n\n";
  
   do {
       // Reset
       cashless = false;
       while (!valid && !cashless) { 
           cout << "\nStock Portfolio: (Eg. 50000 for N50,000 & 0 for No investment) ";
           cin >> stock_val;
           valid = ensure_valid_input(stock_val);
       }; 
       valid = false;
       while (!valid && !cashless) {
           cout << "fixed income (yr 1): ";
           cin >> fixed1_val;
           valid = ensure_valid_input(fixed1_val);
       }; 
       valid = false;
       while (!valid && !cashless) {
           cout << "fixed income (yr 2): ";
           cin >> fixed2_val;
           valid = ensure_valid_input(fixed2_val);
       }; 
       valid = false;
       while (!valid && !cashless) {
           cout << "fixed income (yr 3): ";
           cin >> fixed3_val;
           valid = ensure_valid_input(fixed3_val);
       }; 
       valid = false;
       while (!valid && !cashless) {
           cout << "fixed income (yr 4): ";
           cin >> fixed4_val;
           valid = ensure_valid_input(fixed4_val);
       }; 
       valid = false;
       while (!valid && !cashless) {
           cout << "Real_estate: ";
           cin >> real_estate_val;
           valid = ensure_valid_input(real_estate_val);
       }; 
       valid = false;
       while (!valid && !cashless) {
           cout << "E-commerce: ";
           cin >> ecommerce_val;
           valid = ensure_valid_input(ecommerce_val);
       }; 
       valid = false;
       while (!valid && !cashless) {
           cout << "Farms: ";
           cin >> farms_val;
           valid = ensure_valid_input(farms_val);
       };

       cout << fixed << setprecision(1) << "Your current investments for Yr(" << curr_yr+1 << ") are:  Stock: N" << stock_val << "  Fixed_1: N" << fixed1_val << "  Fixed_2: N" << fixed2_val << "  Fixed_3: N" << fixed3_val << "  Fixed_4: N" << fixed4_val 
           << "  Real estate: N" << real_estate_val << "  E-commerce: N" << ecommerce_val << "  Farms: N" << farms_val << "\n\n";

       cout << "\n\nDo you wish to proceed? (Enter 'Y' to proceed or 'N' to reset investment values): ";
       cin >> resp;
   } while (resp == "N"); 
   
   curr_yr++;
}

bool ensure_valid_input (float input_val) {
    valid_input_sum += input_val;

    if (input_val < 0) {
        cout << "Invalid input! please try again.\n";
        return false; }
    else if (valid_input_sum >= initial_cash) {
        if (valid_input_sum - initial_cash > 0) { 
            cout << fixed << "*Sorry!* You have only N" << setprecision(1) << initial_cash - (valid_input_sum - input_val) << " left to invest\n\n";
            valid_input_sum -= input_val;
        } else if (valid_input_sum-initial_cash == 0) {
            cout << "You have run out of cash to invest!\n\n\n"; 
            cashless = true;
        }
        return false; }
    else {
        cout << fixed << setprecision(2) << "You have N" << initial_cash-valid_input_sum << "left\n\n";
        return true; }
}


