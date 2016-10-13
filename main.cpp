#include <iostream>
#include "BooleanMatrix.h"

using namespace std;

int main() {
    cout << "Begin!" << endl;
    Matrix *M = new Matrix(4);
    for (int i = 0;i < 4;i++)
        for (int j = 0;j < 4;j++){
            cin >> M->mat[i][j];
        }
    BooleanMatrix A(M,2);
    for (int i = 0;i < 4;i++)
        for (int j = 0;j < 4;j++){
            cin >> M->mat[i][j];
        }
    BooleanMatrix B(M,2);
    BooleanMatrix C = A*B;
    C.print();
    cout << &C << " Address" << endl;
    return 0;
}