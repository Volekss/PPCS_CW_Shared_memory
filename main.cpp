#include <iostream>
#include <omp.h>
#include <sysinfoapi.h>
#include "functions.h"

using std::cout;
using std::cin;

int p, n;
float h;
int num = 1;

/*int e;
int *A, *B, *C;
int *MX, *MZ;*/
int e;
int m;
int l;
int *MA, *MO,*MK, *MS, *MF, *MR;

void init_memory() {
    MA = (int *) malloc((size_t)(n * n * 4));
    MO = (int *) malloc((size_t)(n * n * 4));
    MK = (int *) malloc((size_t)(n * n * 4));
    MS = (int *) malloc((size_t)(n * n * 4));
    MF = (int *) malloc((size_t)(n * n * 4));
    MR = (int *) malloc((size_t)(n * n * 4));
}

void free_memory() {
    free(MA); //for output
    free(MO);
    free(MK);
    free(MS);
    free(MF);
    free(MR);
}

int main() {
    cout << "Enter p:\n";
    cin >> p;
    cout << "Enter n:\n";
    cin >> n;

    //Counting time
    long int before = GetTickCount();

    h = (float) n / p;

    cout << "h = " << h << "\n";

    init_memory();

    m = INT_MAX;
    l = INT_MAX;

    omp_set_num_threads(p);
#pragma omp parallel
    {
        int tid = omp_get_thread_num(); // get thread id

        // local variables for
        int e_local;
        int *MS_local;
        int m_local;
        int l_local;

#pragma critical
        {
            cout << "Thread " << tid << " start\n";
        };


        if (tid == 0) {
            e = num;
            fillMatrix(num, MA, n);
            fillMatrix(num, MR, n);
            fillMatrix(num, MO, n);
            // MO[3] = 4;
        }

        if (tid == p - 1) {
            fillMatrix(num, MS, n);
            fillMatrix(num, MF, n);
            fillMatrix(num, MK, n);
            //B[0] = 20;

        }

#pragma omp barrier // wait until finish enter data
        m_local = matrixMin(MO, int(h * tid), (int)(h * (tid + 1)), n);


#pragma omp critical
        {
            if((m_local) < m){
                m = m_local;
            }
        };

        l_local = matrixMin(MR, int(h * tid), (int)(h * (tid + 1)), n);

#pragma omp critical
        {
            if((l_local) < l){
                l = l_local;
            }
        };
#pragma omp barrier //wait for min
#pragma omp critical
        {
            m_local = m;
            l_local = l;
            e_local = e;
            MS_local = MS;

        };




#pragma omp barrier // wait until copy made

        F(MA,  m_local,  MK,  e_local,  MS_local,  MF, l_local, (int) h * tid, int(h * (tid + 1)), n);


#pragma omp barrier // wait until computing finish
#pragma critical
        {
            if ((tid == p - 1)&&(n<10)) {
                cout << "MA = \n";
                printMatrix(MA, n);
            }
            cout << "T" << tid << " finish\n";
        };



    };

    free_memory();

    long int after = GetTickCount();
    long int timeForCompletion = after - before;
    cout << "time = " << timeForCompletion << " ms";
    return 0;
}
