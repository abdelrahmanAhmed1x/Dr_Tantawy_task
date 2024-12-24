//
// Created by abody on 12/24/24.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include<iostream>
#include<string>
#include<cmath>
using namespace std ;


class expression {
      template <class T ,  size_t size >
class Stack {
            T arr[size] ;
            int top = -1  ;
      public:
            Stack()=default ;
            ~Stack()=default ;
            bool isEmpty()const {
                  return top==-1 ;
            }
            bool isFull()const {
                  return top==size-1 ;
            }
            void push(const T & item) {
                  if (!isFull()) {
                        arr[++top]=item;
                  }
            }
            void pop() {
                  if (!isEmpty()) {
                        --top ;
                  }
            }
            T getTop()const {
                  if (!isEmpty()) {
                        return arr[top] ;
                  }
            }

      };
      string Expression ;
      int weight(char op );
      bool isOperator(char i) ;
      bool isDigit(char i ) ;
      double calculate(char op , double num1 , double num2 );
      string infixToPostfix() ;
      double answer();
public:
      expression();
      ~expression();
};



#endif //EXPRESSION_H
