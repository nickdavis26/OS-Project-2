// Nicholas Davis
// 04/21/2022

#include <iostream>
#include <fstream>

using namespace std;

// global variables for the processes and resources
const int P = 5;
const int R = 3;

void calcNeed(int need[P][R], int maxm[P][R], int allot[P][R])
{
    for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)
            need[i][j] = maxm[i][j] - allot[i][j];    
}

bool isSafe(int processes[], int avail[], int maxm[][R], int allot[][R])
{
    int need[P][R];
    calcNeed(need, maxm, allot);
    bool finish[P] = {0};
    int safeSeq[P];
    int work[R];
    for (int i = 0; i < R ; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < P)
    {
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            if (finish[p] == 0)
            {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;
		    
                if (j == R)
                {
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
    
        if (found == false)
        {
            cout << "System is not in safe state.";
            return false;
        }
    }
    cout << "System is in safe state." << endl;
    cout << "Safe sequence: ";
    for (int i = 0; i < P ; i++)
        cout << safeSeq[i] << " ";
    cout << "\n";
    return true;
}

int main()
{
    int processes[] = {0,1,2,3,4};
    int available[3];
    int max[P][R];
    int allocation[P][R];

    // open input file
    ifstream inputFile("input.txt");
    while(inputFile)
    {
	    // get available resources
        for(int i=0;i<3;i++)
            inputFile >> available[i];

        // get values for allocation matrix
        for(int i=0;i<P;i++)
            for(int j=0;j<R;j++)
                inputFile >> allocation[i][j];

        // get values for max matrix
        for(int i=0;i<P;i++)
            for(int j=0;j<R;j++)
                inputFile >> max[i][j];

    }
    isSafe(processes, available, max, allocation);
    return 0;
}