// ************************************** Game of Clubs engine dev ******************************************
//   Ayotunde Odejayi 2016 (c)
// **********************************************************************************************************
//
// TODO 
// lending/borrowing
// consistent accurate computation across years
// (bug) Amount available left to invest gets wrong at times eg. val_club 4 gives 80M after RealEstate
// cash/total amount
// make get_user_data() less repetitive with array/loops
// convert into driver, specification & implementation (,cpp and .h separate files) as we approach MVC model

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <iomanip>
using namespace std;


void welcome();
// Set-up parameters
static const int no_years = 4, width = 2;
int no_players, p1_val, p2_val;

class gameOfClubsPlayer{
  public:
  double initial_cash, valid_input_sum, stock_val, fixed1_val, fixed2_val, fixed3_val, fixed4_val, real_estate_val, ecommerce_val, farms_val;
  double valuation_results[no_years][11];
  int curr_yr, pIndex;
  bool cashless;

  // Asset prices
  double stocks[no_years+1][width], fixed_1[no_years][width], fixed_2[no_years-1][width], fixed_3[no_years-2][width], fixed_4[no_years-3][width];
  double real_estate[no_years+1][width], ecommerce[no_years+1][width], farms[no_years+1][width];

  // constructor
  gameOfClubsPlayer(int playerIndex):pIndex(playerIndex) {
      valid_input_sum = 0.00, stock_val = 0.00, fixed1_val = 0.00, fixed2_val = 0.00, fixed3_val = 0.00, fixed4_val = 0.00, 
      real_estate_val = 0.00, ecommerce_val = 0.00, farms_val = 0.00, initial_cash = 100000000.00, curr_yr = 0, cashless = false; 
  }; 

  void setup() {
      // Initialize valuation_results array
      for (int i =0; i<no_years; i++) 
          for (int j=0; j<11; j++) 
              valuation_results[i][j] = 0.00;

      // Read-in data
      ifstream file_reader;
      file_reader.open("assetPrices.txt");
      for (int i=0; i<no_years+1; i++) 
          for (int j=0; j<width; j++) 
              file_reader >> stocks[i][j];

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
      for (int i=0; i<no_years+1; i++)
          for (int j=0; j<width; j++)
              file_reader >> real_estate[i][j];
      for (int i=0; i<no_years+1; i++)
          for (int j=0; j<width; j++)
              file_reader >> ecommerce[i][j];
      for (int i=0; i<no_years+1; i++)
          for (int j=0; j<width; j++)
              file_reader >> farms[i][j];
      /*Debug
      for (int i=0; i<3; i++) {
          for (int j=0; j<width; j++)
              cout <<fixed_2[i][j] << endl;
          cout<<endl;
      }*/
  }

  int compute_valuation() {
      valuation_results[curr_yr][0] = (stocks[curr_yr+1][0]/100+1.0) * stock_val;    
      valuation_results[curr_yr][1] = ((fixed_1[curr_yr][0]+fixed_1[curr_yr][1])/100+1.0) * fixed1_val;
      valuation_results[curr_yr][2] = pow((fixed_2[curr_yr][0]+fixed_2[curr_yr][1])/100.0+1.0, 2)*fixed2_val/(fixed_1[curr_yr+1][0]/100.0+1.0);
      valuation_results[curr_yr][3] = pow((fixed_3[curr_yr][0]+fixed_3[curr_yr][1])/100.0+1.0, 3)*fixed3_val/pow(fixed_2[curr_yr+1][0]/100.0+1.0, 2);
      valuation_results[curr_yr][4] = pow((fixed_4[curr_yr][0]+fixed_4[curr_yr][1])/100.0+1.0, 4)*fixed4_val/pow(fixed_3[curr_yr+1][0]/100.0+1.0, 3);
      valuation_results[curr_yr][5] = ((real_estate[curr_yr][0]+real_estate[curr_yr][1])/100 + 1.0) * real_estate_val;    
      valuation_results[curr_yr][6] = ((ecommerce[curr_yr][0]+ecommerce[curr_yr][1])/100 + 1.0) * ecommerce_val;
      valuation_results[curr_yr][7] = ((farms[curr_yr][0]+farms[curr_yr][1])/100 + 1.0) * farms_val;    

      for (int i = 0; i<10; i++) 
          valuation_results[curr_yr][10] += valuation_results[curr_yr][i]; 

      return valuation_results[curr_yr][10];
  }  

  // Print results
  void print_valuation() {
      cout << "\n\n***Player "<<pIndex<<" Valuation results for Yr("<<curr_yr+1<<") are:*** \nStock Portfolio: N"<<setprecision(2)<< valuation_results[curr_yr][0]<<" | Fixed Income: N" 
           << valuation_results[curr_yr][2] << " | Fixed Inc 2-yr: N"
           << valuation_results[curr_yr][3] << " | Fixed Inc 3-yr: N" << valuation_results[curr_yr][4] << " | Fixed Inc 4-yr: N0.00" << " | Real Estate: N" 
           << valuation_results[curr_yr][5] << " | VC: e-commerce: N" << valuation_results[curr_yr][6] << " | VC:Farm: N" << valuation_results[curr_yr][7] 
           << "\nLending/Borrowing:  N" 
           << valuation_results[curr_yr][8] << " | Cash: N" << valuation_results[curr_yr][9] 
           << "\nTOTAL: N" << valuation_results[curr_yr][10] << "\n";     
      curr_yr++;
  }
  
  void get_user_data() {
        bool valid_inp = false;
        string resp;
        cout << "\nPlayer ("<<pIndex<<")"; 
        do {
            // Reset
            cashless = false;
            while (!valid_inp && !cashless) { 
                cout << "\nStock Portfolio: (Eg. 50000 for N50,000 & 0 for No investment) ";
                cin >> stock_val;
                valid_inp = ensure_valid_input(stock_val);
            }; 
            valid_inp = false;
            while (!valid_inp && !cashless) {
                cout << "fixed income (yr 1): ";
                cin >> fixed1_val;
                valid_inp = ensure_valid_input(fixed1_val);
            }; 
            valid_inp = false;
            while (!valid_inp && !cashless) {
                cout << "fixed income (yr 2): ";
                cin >> fixed2_val;
                valid_inp = ensure_valid_input(fixed2_val);
            }; 
            valid_inp = false;
            while (!valid_inp && !cashless) {
                cout << "fixed income (yr 3): ";
                cin >> fixed3_val;
                valid_inp = ensure_valid_input(fixed3_val);
            }; 
            valid_inp = false;
            while (!valid_inp && !cashless) {
                cout << "fixed income (yr 4): ";
                cin >> fixed4_val;
                valid_inp = ensure_valid_input(fixed4_val);
            }; valid_inp = false;
            while (!valid_inp && !cashless) {
                cout << "Real_estate: ";
                cin >> real_estate_val;
                valid_inp = ensure_valid_input(real_estate_val);
            }; 
            valid_inp = false;
            while (!valid_inp && !cashless) {
                cout << "E-commerce: ";
                cin >> ecommerce_val;
                valid_inp = ensure_valid_input(ecommerce_val);
            }; 
            valid_inp = false;
            while (!valid_inp && !cashless) {
                cout << "Farms: ";
                cin >> farms_val;
                valid_inp = ensure_valid_input(farms_val);
            };

            cout << fixed << setprecision(1) << "***Your current investments for Yr(" << curr_yr+1 << ")*** are:  \nStock: N" << stock_val << " | Fixed_1: N" 
                << fixed1_val << " | Fixed_2: N" << fixed2_val << " | Fixed_3: N" << fixed3_val << " | Fixed_4: N" << fixed4_val 
                << " | Real estate: N" << real_estate_val << " | E-commerce: N" << ecommerce_val << " | Farms: N" << farms_val << "\n\n";

            cout << "\n\nDo you wish to proceed? (Enter 'Y' to proceed or 'N' to reset investment values): "; cin >> resp;
        } while (resp == "N" || resp == "n"); 
    }

    bool ensure_valid_input (double input_val) {
        valid_input_sum += input_val;

        if (input_val < 0) {
            cout << "Invalid_inp input! please try again.\n";
            return false; }
        else if (valid_input_sum >= initial_cash) {
            if (valid_input_sum - initial_cash > 0) { 
                cout << fixed << "***Sorry!*** You only have N" << setprecision(1) << initial_cash - (valid_input_sum - input_val) << " left to invest\n\n";
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

};


int main() {

  //welcome();

  gameOfClubsPlayer p1(1);//, p2(2);
  p1.setup();
  //p2.setup();

  for (int yr_iter = 1; yr_iter<no_years-1; yr_iter++) {
      cout << "\n\n\n*** Year (" <<yr_iter<< ") ***\n";
      cout << fixed << "\nYou have N" << setprecision(1) << p1.initial_cash << " cash available\n";  
      p1.get_user_data();
      //cout << fixed << "\nYou have N" << setprecision(1) << p2.initial_cash << " cash available\n";  
      //p2.get_user_data();

      p1_val = p1.compute_valuation();
      //p2_val = p2.compute_valuation();
      
      p1.print_valuation();
      // p2.print_valuation();
       
      p1.initial_cash = p1_val;
      //p2.initial_cash = p2_val;
      
      /*cout << "\n";
      if (yr_iter<4){ 
          if (p1_val > p2_val) cout << "Player 1 wins Year "<<yr_iter;
          else if (p2_val > p1_val) cout << "Player 2 wins Year "<<yr_iter;
          else cout << "There is a tie in Year"<<yr_iter;
      } else {
          if (p1_val > p2_val) cout << "Player 1 wins!"; 
          else if (p2_val > p1_val) cout << "Player 2 wins!";
          else cout << "There is a tie!"; 
      }*/
  }

  return 0;
}


void welcome() {

   cout << "\n******************************************************************* Welcome to Game of Clubs *************************************************************" << endl;
   cout << "\nYour investment options are:\n Stock Portfolio\n Fixed Income: 1yr\n Fixed Income: 2yr\n Fixed Income: 3yr\n Fixed Income: 4yr\n Real Estate\n VC: e-commerce\n VC: Farm";
   cout << "\n\nEnter 1 through 3 for no. of players (default is 1 player): ";
   cin >> no_players;
   if (no_players>3 || no_players<1 || (no_players%2!=0 && no_players%3!=0))
       no_players  = 1;

}
