//
// Created by abody on 12/24/24.
//

#include "expression.h"
int expression::weight(char op) {
    if (op=='^')return 5 ;
    if (op=='/' || op=='*' || op=='%')return 4 ;
    if (op=='+' || op=='-')return 3 ;
    return 0  ;
}
bool expression::isOperator(char i) {
    return i=='^' || i=='/' || i=='*' || i=='+' || i=='-'  || i=='%';
}
bool expression::isDigit(char i) {
    return i>='0' && i<='9' ;
}
double expression::calculate(char op, const double num1,const  double num2) {
    switch(op) {
        case '+':return num1+num2 ;
        case '-':return num1-num2 ;
        case '*':return num1*num2 ;
        case '/':return num1/num2 ;
        case '%':return fmod(num1 ,num2);
        case '^':return pow(num1,num2) ;
        default: throw runtime_error("Invalid operator encountered");
    }
}
string expression::infixToPostfix() {
    Stack<char , 10 > st ;
    string result ;
    for (size_t i = 0 ; i < Expression.size() ; ++ i ) {
        char c = Expression[i] ;
        if (isDigit(c)) {
            result += c ;
        }
        else if (c=='(') {
            st.push(c) ;
        }
        else if (c==')') {
            while (!st.isEmpty() && st.getTop()!='('){result+=st.getTop(); st.pop(); }
            st.pop();
        }
        else if (isOperator(c)) {
            if (isDigit(Expression[i-1]))result+=' ' ;
            while (!st.isEmpty() && st.getTop()!='(' && weight(c)<=weight(st.getTop())) {
                result += st.getTop() ;
                st.pop();
            }
            st.push(c) ;
        }
    }
    while (!st.isEmpty()){result+=st.getTop() ; st.pop();}
    return result ;
}
double expression::answer() {
    Expression = infixToPostfix() ;
    Stack<double ,20>st ;
    string number ;
    for (size_t i= 0 ; i < Expression.size(); ++ i ) {
        char c = Expression[i] ;
        if (isDigit(c)) {
            number += c ;
        }
        else if (isOperator(c)) {
            if (!number.empty()) {
                st.push(stod(number));
                number = "" ;
            }
            const double num2 = st.getTop() ; st.pop();
            const double num1 = st.getTop() ; st.pop();
            double ans = calculate(c,num1,num2) ;
            st.push(ans) ;
        }
        else {
            if (!number.empty()) {
                st.push(stod(number));
                number = "" ;
            }
        }
    }

    return st.getTop();
}
expression::expression() {
    cout << "Enter the mathematical expression: ";
    string s ;
    cin.ignore() ;
    getline(cin, s);

    try {
        Expression = s ;
        double ans = answer();
        if (isinf(ans)) {
            cout << "Invalid expression." << endl;
        } else {
            cout << "The result is: " << ans << endl;
        }
    } catch (const exception &ex) {
        cout << "Error: " << ex.what() << endl;
    }
}
expression::~expression() {
    cout <<  "hope it helped you :)" << endl;
}



