//
// Created by qcwang on 13/10/2016.
//

#ifndef BMM_BOOLEANMATRIX_H
#define BMM_BOOLEANMATRIX_H

#define MAXT 100
#define MAXP 1000

class Matrix {
public:
    int mat[MAXT][MAXT];
    int n;
    Matrix(int i) {

        for (int j = 0;j < i;j++)
            for (int k = 0;k < i;k++)
                mat[j][k] = 0;
        n = i;
    }
    ~Matrix() {

    }
};

class BooleanMatrix{
public:
   // int GetTableID(Matrix M);
    int BuildTable();
    int SetPosition(int i,int position);
    int GetPosition(int i);
    int SetBlock(int i, int id);
    int n;
    int k;
    int x;
    BooleanMatrix(const BooleanMatrix& A) {
        n = A.n;
        k = A.k;
        x = A.x;
        for (int i = 0;i < MAXT;i++)
            for (int j = 0;j < MAXT;j++) {
                TableAdd[i][j] = A.TableAdd[i][j];
                Table[i][j] = A.Table[i][j];
            }
        for (int i =0;i < MAXP;i++) {
            Position[i] = A.Position[i];
        }
    }
    BooleanMatrix operator* (BooleanMatrix& B);
    BooleanMatrix(Matrix* M,int x_val);
    BooleanMatrix() {
        for (int i = 0;i <MAXT;i++) {
            for (int j = 0;j < MAXT;j++) {
                Table[i][j] = 0;
                TableAdd[i][j] = 0;
            }
        }
        for (int i = 0;i < MAXP;i++) {
            Position[i] = 0;
        }
    }
    void print();
private:
    int Table[MAXT][MAXT];
    int TableAdd[MAXT][MAXT];
    int Position[MAXP];


};

#endif //BMM_BOOLEANMATRIX_H
