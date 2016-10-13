//
// Created by qcwang on 13/10/2016.
//

#include "BooleanMatrix.h"
#include <iostream>

using namespace std;

BooleanMatrix::BooleanMatrix(Matrix* M,int x_val) {
    n = M->n;
    x = x_val;
    k = n/x;
    cout << x << " " << k << " " << " " << n << " " << endl;
    for (int i = 0;i <MAXT;i++) {
        for (int j = 0;j < MAXT;j++) {
            Table[i][j] = 0;
            TableAdd[i][j] = 0;
        }
    }
    for (int i = 0;i < MAXP;i++) {
        Position[i] = 0;
    }
    for (int i = 0;i < k;i++)
        for (int j = 0; j < k;j++)
            for (int y = 0;y < x;y++)
                for (int z = 0;z < x;z++) {
                    if (M->mat[i*x+y][j*x+z] == 1) {
                        SetPosition(y*x+z,i*k+j);
                    }
                }
    BuildTable();

}

void BooleanMatrix::print() {
    int Tnum = 1 << (k*k);
    cout << x << " " << k << " " << " " << n << " " << Tnum << endl;
    for (int i = 0;i < Tnum;i++) {
        for (int y = 0;y < Tnum;y++) {
            cout << Table[i][y] << " ";
        }
        cout << endl;
    }
    cout << "ADDTABLE" << endl;
    for (int i = 0;i < Tnum;i++) {
        for (int y = 0;y < Tnum;y++) {
            cout << TableAdd[i][y] << " ";
        }
        cout << endl;
    }
    for (int i = 0;i < x*x;i++)
        cout << Position[i] << " ";
}

int BooleanMatrix::BuildTable(){
    int Tnum = 1 << (k*k);
    for (int i = 0;i < Tnum;i++) {
        int mata[100][100];
        for (int y = 0;y < k;y++)
            for (int z = 0;z < k;z++) {
                mata[y][z] = 0;
            }
        int m = i;int z = 0;int y = 0;
        while (m > 0) {
            if (m % 2 == 1) {
                mata[y][z] = 1;
            }
            z = z + 1;
            if (z >= k) {
                z = 0;
                y = y + 1;
            }
            m = m >> 1;
        }
        for (int j = 0;j < Tnum;j++) {
            int matb[100][100];
            for (int y = 0;y < k;y++)
                for (int z = 0;z < k;z++) {
                    matb[y][z] = 0;
                }
            int m = j;int z = 0;int y = 0;
            while (m > 0) {
                if (m % 2 == 1) {
                    matb[y][z] = 1;
                }
                z = z + 1;
                if (z >= k) {
                    z = 0;
                    y = y + 1;
                }
                m = m >> 1;
            }
            int matc[100][100];
            for (int y = 0;y < k;y++)
                for (int z = 0;z < k;z++) {
                    matc[y][z] = 0;
                }
            for (int y = 0;y < k;y++)
                for (int z = 0;z < k;z++) {

                    for (int a = 0; a < k; a++)
                        if (mata[y][a] & matb[a][z] == 1) {
                            matc[y][z] = 1;
                            continue;
                        }
                }
            m = 0; int a = 0;
            for (int y = 0;y < k;y++)
                for (int z = 0;z < k;z++) {

                    if (matc[y][z] == 1) {
                        m = m + (1 << a);
                        //cout << m << " " << a << endl;
                    }
                    a = a + 1;
                }
            Table[i][j] = m;
           // cout << i << " " << j << " " << m << endl;
            for (int y = 0;y < k;y++)
                for (int z = 0; z < k;z++) {
                    if (mata[y][z] == 1 || matb[y][z] == 1)
                        matc[y][z] = 1;
                }
            m = 0; a = 0;
            for (int y = 0;y < k;y++)
                for (int z = 0;z < k;z++) {
                    if (matc[y][z] == 1) {
                        m = m + (1 << a);
                    }
                    a = a + 1;
                }
            TableAdd[i][j] = m;
        }

    }
}

int BooleanMatrix::GetPosition(int i) {
    return Position[i];
}

int BooleanMatrix::SetBlock(int i, int id) {
    Position[i] = id;
    return 0;
}

int BooleanMatrix::SetPosition(int i, int position) {
    int m = 1<<position;
    Position[i]+=m;
    return 0;
}

BooleanMatrix BooleanMatrix::operator*(BooleanMatrix& B) {
    BooleanMatrix* C = new BooleanMatrix(B);
    cout << C << " Address" << endl;
    for (int i = 0;i < x;i++)
        for (int j = 0;j < x;j++) {
            int now = 0;
            for (int y = 0; y < x; y++) {
                int a = GetPosition(i*x+y);
                int b = B.GetPosition(y*x+j);
                int add = Table[a][b];
                now = TableAdd[add][now];
                cout << i << " " << j << " " << y << " " << a << " " << b << " " << add << " " << now << endl;
            }
            C->SetBlock(i*x+j,now);
        }
    return *C;
}