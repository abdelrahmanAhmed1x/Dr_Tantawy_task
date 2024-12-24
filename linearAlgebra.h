//
// Created by abody on 12/24/24.
//

#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H
#include <iostream>
#include<vector>
#include<eigen3/Eigen/Dense>
using namespace std;
using namespace Eigen;

class linearAlgebra {
    class linearEquations {
    typedef vector<vector<double>>Matrix ;
    void upper_triangular(Matrix &A, int n) {
        for (int i = 0; i < n; i++) {
            int pivot_row = i;
            for (int j = i+1; j < n; j++) {
                if (abs(A[j][i]) > abs(A[pivot_row][i])) {
                    pivot_row = j;
                }
            }
            if (pivot_row != i) {
                for (int j = i; j <= n; j++) {
                    swap(A[i][j], A[pivot_row][j]);
                }
            }
            for (int j = i+1; j < n; j++) {
                double factor = A[j][i] / A[i][i];
                for (int k = i; k <= n; k++) {
                    A[j][k] -= factor * A[i][k];
                }
            }
        }
    }
    void back_sub(Matrix &A, int n, vector<double> &solutions) {
        for (int i = n-1; i >= 0; i--) {
            double sum = 0;
            for (int j = i+1; j < n; j++) {
                sum += A[i][j] * solutions[j];
            }
            solutions[i] = (A[i][n] - sum) / A[i][i];
        }
    }
public:
    linearEquations() {
        int n ;
        cout << "enter the the number of rows of the coffecient matrix : " << endl;
        cin>> n;
        Matrix A(n , vector<double>(n+1)) ; // matrix n x n+1  the extra column for constants
        for (int i = 0 ; i < n; ++ i ) {
            cout << "enter the coffecients of the equation , example :   (ax + by + cz = d ) enter a , b , c , d  in order " << endl;    // ax + by + cz = d
            for (int j = 0 ; j < n+1 ; ++ j ) {
                cin>>A[i][j];
            }
        }
        vector<double>solutions(n);
        upper_triangular(A, n);
        back_sub(A, n, solutions);

        cout << "Solution for the system:\n";
        for (int i = 0; i < n; i++) {

            cout << solutions[i] << endl;
        }
    }
};
    class matrixOperatrions{
    typedef MatrixXd Matrix ;
    Matrix m ;
public:
    matrixOperatrions(const long &size):m(Matrix::Zero(size, size)){}
    matrixOperatrions(const matrixOperatrions &other):m(other.m) {}
    int size()const {
        return m.rows() ;
    }
    void transpose() {
        m.transposeInPlace() ;
    }
    friend istream &operator>>(istream &in ,  matrixOperatrions &other) {
        for (int i = 0 ; i < other.m.rows() ; ++i) {
            for (int  j = 0 ; j < other.m.cols(); ++ j ) {
                in>> other.m(i,  j ) ;
            }
        }
        return in ;
    }
    friend ostream &operator <<(ostream &out , matrixOperatrions &other) {
        for (int i = 0 ; i < other.m.rows() ; ++i) {
            for (int  j = 0 ; j < other.m.cols(); ++ j ) {
                out << other.m(i , j ) << '\t' ;
            }
            out << '\n' ;
        }
        return out ;
    }
    matrixOperatrions operator+(const matrixOperatrions &other) {
        m = m+other.m ;
        return *this ;
    }
    matrixOperatrions operator-(const matrixOperatrions &other)  {
        m = m - other.m ;
        return *this ;
    }
    matrixOperatrions operator*(const matrixOperatrions &other)  {
       m = m * other.m ;
        return *this ;
    }
    template<class T >
    matrixOperatrions operator*(const T &other )  {
        m = m *other ;
        return *this ;
    }
    template<class T >
    T &operator()(const long &i , const long  &j )const{
        return m(i,j) ;
    }
    template<class T >
    const T &operator()(const long &i , const long &j)const {
        return m(i , j );
    }
    bool isSymmetric() const {
        return m.isApprox(m.transpose());
    }
    bool isSkewSymmetric() const {
        return m.isApprox(-m.transpose());
    }
    bool isUpperTriangular() const {
        return m.isUpperTriangular();
    }
    bool isLowerTriangular() const {
        return m.isLowerTriangular();
    }
    bool isDiagonal() const {
        return m.isDiagonal();
    }
    bool isIdentity() const {
        return m.isApprox(MatrixXd::Identity(m.rows(), m.cols()));
    }
    double getDeterminant() const {
        return m.determinant();
    }
    VectorXcd getEigenValues() const {
        EigenSolver<MatrixXd> solver(m);
        return solver.eigenvalues().real();
    }
    // VectorXcd getEigenVectors() const {
    //     EigenSolver<MatrixXd> solver(m);
    //     return solver.eigenvectors().real();
    //
    // }
    void getInverse()const {
        if (getDeterminant() == 0) {
            cout <<"the matrix does not have an inverse [ determinant = 0 ] " << endl;
        }
        else {
            Matrix A = m.inverse() ;
            cout << "inverse is : " << endl;
            cout << A << endl;
        }
    }
    bool isOrthogonal() const {
        Matrix I = MatrixXd::Identity(m.rows(), m.cols()) ;
        Matrix P =  m.adjoint() * m  ;
        return P.isApprox(I) ;
    }
    bool isOrthonormal()const {
        if (!isOrthogonal())return false ;
        for (long i = 0 ; i< m.cols() ; ++ i ) {
             if (m.col(i).norm()!=1.0)return false ;
        }
        return true ;
    }
    void gramShmidt() {
        // gram shmidt transform non orthogonal matrix  to orthogonal
        Matrix A = m ;
        for (int i = 0 ; i < A.cols() ; ++ i ) {
            for (int j = 0 ; j< i ;++ j ) {
                A.col(i) -= (A.col(j).dot(A.col(i)) / A.col(j).dot(A.col(j))) * A.col(j);
            }
        }
        m = A ;
    }

};
public:
    linearAlgebra() {
         int choice;

    do {
        cout << "\n=== Linear Algebra Menu ===\n";
        cout << "1. Solve Linear Equations\n";
        cout << "2. Matrix Operations\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                linearAlgebra::linearEquations le;
                break;
            }
            case 2: {
                int size;
                cout << "Enter the size of the square matrix: ";
                cin >> size;

                linearAlgebra::matrixOperatrions mo(size);
                cout << "Enter the matrix elements (row by row):\n";
                cin >> mo;

                int matrixOpChoice;
                do {
                    cout << "\n=== Matrix Operations Menu ===\n";
                    cout << "1. Transpose\n";
                    cout << "2. Addition\n";
                    cout << "3. Subtraction\n";
                    cout << "4. Multiplication\n";
                    cout << "5. Scalar Multiplication\n";
                    cout << "6. Check Properties (Symmetric, etc.)\n";
                    cout << "7. Determinant\n";
                    cout << "8. Eigenvalues\n";
                    cout << "10. Inverse\n";
                    cout << "11. Check Orthogonality/Orthonormality\n";
                    cout << "12. Gram-Schmidt\n";
                    cout << "0. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> matrixOpChoice;

                    switch (matrixOpChoice) {
                        case 1:
                            mo.transpose();
                            cout << "Transposed Matrix:\n" << mo << endl;
                            break;
                        case 2: {
                            linearAlgebra::matrixOperatrions mo2(size);
                            cout << "Enter the second matrix:\n";
                            cin >> mo2;
                            matrixOperatrions m3  = mo + mo2 ;
                            cout << "Result:\n" << m3 ;
                            break;
                        }
                        case 3: {
                            linearAlgebra::matrixOperatrions mo2(size);
                            cout << "Enter the second matrix:\n";
                            cin >> mo2;
                            matrixOperatrions m3 = mo - mo2 ;
                            cout << "Result:\n" << m3;
                            break;
                        }
                        case 4: {
                            linearAlgebra::matrixOperatrions mo2(size);
                            cout << "Enter the second matrix:\n";
                            cin >> mo2;
                             matrixOperatrions m3 = mo *mo2 ;
                            cout << "Result:\n" << (m3);
                            break;
                        }
                        case 5: {
                            double scalar;
                            cout << "Enter scalar: ";
                            cin >> scalar;
                             matrixOperatrions m2 = mo * scalar;
                            cout << "Result:\n" << (m2) << endl;
                            break;
                        }
                        case 6:
                            cout << "Is Symmetric: " << mo.isSymmetric() << endl;
                            cout << "Is Skew-Symmetric: " << mo.isSkewSymmetric() << endl;
                            cout << "Is Upper Triangular: " << mo.isUpperTriangular() << endl;
                            cout << "Is Lower Triangular: " << mo.isLowerTriangular() << endl;
                            cout << "Is Diagonal: " << mo.isDiagonal() << endl;
                            cout << "Is Identity: " << mo.isIdentity() << endl;
                            break;
                        case 7:
                            cout << "Determinant: " << mo.getDeterminant() << endl;
                            break;
                        case 8:
                            cout << "Eigenvalues:\n" << mo.getEigenValues() << endl;
                            break;
                        case 10:
                            mo.getInverse();
                            break;
                        case 11:
                            cout << "Is Orthogonal: " << mo.isOrthogonal() << endl;
                            cout << "Is Orthonormal: " << mo.isOrthonormal() << endl;
                            break;
                        case 12:
                            mo.gramShmidt();
                            cout << "Gram-Schmidt Transformed Matrix:\n" << mo << endl;
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                } while (matrixOpChoice != 0);
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    }

};



#endif //LINEARALGEBRA_H
