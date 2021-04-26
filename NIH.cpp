#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

string s;
ifstream plik;
string nazwa = "data.txt";
int N = 0, M = 0;

void LoadData(string nazwa, string dane, int* P, int* X)
{
    plik.open(nazwa);

    while (s != dane)
    {
        plik >> s;
    }

    plik >> N >> M;

    for (int i = 0; i < N * M; i++)
    {
        plik >> P[i];
    }

    plik.close();

    for (int i = 0; i < N; i++)
    {
        X[i] = i;
    }
}

int Cmax(int N, int M, int *P, int *X)
{
    int T[100];
    for (int i = 0; i <= M; i++)
    {
        T[i]=0;
    }
    for (int n = 0; n < N; n++)
    {
        for (int m = 1; m <= M; m++)
        {
            T[m]=max(T[m],T[m-1]) + P[(m-1)+X[n]*M];
        }
    }
    
    return T[M];
}

int NEH(int N, int M, int *P, int *X)
{
    int *W = new int [N];
    for (int i = 0; i < N; i++)
    {
        X[i]=i;
        W[i]=Cmax(1,M,P,&i);
    }
    for (int i = 0; i < N-1; i++)
    {   
        for (int j = 0; j < N-1; j++)
        {
            if(W[j]<W[j+1])
            {
                swap(W[j],W[j+1]);
                swap(X[j],X[j+1]);
            }
        }
    }
    delete[] W;

    for (int i = 0; i < N; i++)
    {
        int bestP=-1;
        int bestCmax=99999999;

        for (int j = i; j >= 0; j--)
        {
            int tmp = Cmax(i+1,M,P,X);
            if(bestCmax >= tmp)
            {
                bestCmax=tmp;
                bestP=j;
            }
            if(j)
            {
                swap(X[j],X[j-1]);
            } 
        }
        for (int j = 0; j < bestP; j++)
        {
            swap(X[j],X[j+1]);
        }
        
    }
    
    return Cmax(N,M,P,X);
}

int main()
{
    string dane;
    time_t start, stop;
    double t = 0.0;

    int x = 0;
    int P[10000], X[1000];

    while(x < 121)
    {
        if (x < 10)
            dane = "data.00";

        else if (x < 100)
            dane = "data.0";

        else
            dane = "data.";

        dane += to_string(x) + ':';
        cout << dane;

        LoadData(nazwa, dane, P, X);

        start = clock();
        cout << " Cmax: " << NEH(N, M, P, X);
        stop = clock();

        t = (double)(stop - start) / CLOCKS_PER_SEC;

        cout << " Czas: " << t << endl;
        x++;
    }
    return 0;
}