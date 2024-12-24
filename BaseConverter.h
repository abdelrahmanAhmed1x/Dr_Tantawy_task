//
// Created by abody on 12/24/24.
//

#ifndef BASECONVERTER_H
#define BASECONVERTER_H
#include <algorithm>
#include<iostream>
#include <limits>
#include <ranges>
#include<string>
using namespace std ;
class BaseConverter {
     string decimalToBase(long long  number , short BaseNumber) {
          string ans  ;
          while (number) {
               const short rem =number%BaseNumber; ;
               ans+= rem < 10 ? static_cast<char>(rem+'0') : static_cast<char>(rem + 'A') ;
               number/=BaseNumber ;
          }
          for (int i =  0 ; i< ans.size()/2  ; ++ i )swap(ans[i] , ans[ans.size()-i-1]);  // reverse string
          return ans ;
     }
     long long  baseToDecimal(string number ,  short BaseNumber) {
          int ans = 0  , multiplier = 1;
          for (int i = number.size()-1 ; i >= 0  ; i--) {
               if (number[i] >='0' && number[i] <= '9') {
                    ans+=  multiplier*(number[i] - '0') ;
               }
               else {
                      ans +=  multiplier * (number[i] - 'A' + 10) ;
               }
               multiplier *= BaseNumber ;
          }
          return ans ;
     }
     string baseToBase(string number1 ,  short BaseNumber1 , short BaseNumber2) {
          long long decimal = baseToDecimal(number1 , BaseNumber1) ;
          string ans  = decimalToBase(decimal , BaseNumber2) ;
          return ans ;
     }
     void clearBuffer() {
          cin.clear() ;
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') ;
     }
public:
     BaseConverter() {
          cout << "enter your number :" ; string number ; cin>>number ;
          cout << endl ;
          cout << "enter which base you want to convert from range [ 2 , 35 ] : " ;
          short baseNumber1  ; cin>>baseNumber1 ;
          cout << endl ;
          while (cin.fail() && baseNumber1 < 2 || baseNumber1 > 35) {
                   clearBuffer() ;
               cout << "please enter a range [ 2 , 35 ]" << endl ;
               cin >> baseNumber1 ;
          }
          cout << "enter which base you want to convert to range [2 ,35 ] : " ;
          short baseNumber2  ; cin>>baseNumber2 ;
          while (cin.fail() && baseNumber2 < 2 || baseNumber2 > 35) {
               clearBuffer() ;
               cout << "please enter a range [2 ,35 ]" << endl ;
               cin >> baseNumber2 ;
          }
          string answer = baseToBase(number , baseNumber1 , baseNumber2) ;
          cout << "the number is : " << answer << endl;
     }
};



#endif //BASECONVERTER_H
