#include <iostream>
#include"expression.h"
#include"differentation.h"
#include"BaseConverter.h"
#include"linearAlgebra.h"
using namespace std;
void emptyBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void MainProgram() {
     cout << "welcome to ibcu Calculator for dr tantawy " << endl;
      while (true) {
          short choice ;
          cout << "Operations available : " << "[linearAlgebra] , [differentiation and integration of polynomials] , [base converter] , [expression evaluator ] " << endl;
          cout << "Type your choice : " << "1[linearAlgebra] , , 2  [differentiation and integration of polynomials] , 3[base converter] , 4[expression evaluator ] , [5] exit " << endl;
          cin>> choice ;
          while (cin.fail() && choice < 1 || choice > 5 ) {
              cin.clear() ;
              cin.ignore(numeric_limits<streamsize>::max(), '\n') ;
              cout << "enter a valid input from 1 till 4" << endl;
              cout << "Type your choice : " << "1[linearAlgebra] , , 2  [differentiation and integration of polynomials] , 3[base converter] , 4[expression evaluator] , [5] exit " << endl;
              cin>>choice ;
          }
         if (choice==1) {

             linearAlgebra();
         }
         else if (choice==2) {

              menu differentiation ;
             differentiation.main_menu();
          }
         else if (choice==3 ) {

             BaseConverter();
         }
          else if (choice ==4 ) {
              expression();
          }
          else {
              cout << "thank you for using this calculator hope it helps :)" << endl;
              return ;
          }


      }
}

int main() {
    MainProgram();
    return 0;
}
