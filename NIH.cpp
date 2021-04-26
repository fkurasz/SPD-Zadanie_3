#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <algorithm>
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
    int ilosc = N * M;

    for (int i = 0; i < ilosc; i++)
    {
        plik >> P[i];
    }

    plik.close();

    for (int i = 0; i < N; i++)
    {
        X[i] = i;
    }
}

int Cmax(int N, int M, int* P, int* X)
{
    int Tab[100];

    for (int i = 0; i <= M; i++)
    {
        Tab[i] = 0;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            Tab[j] = max(Tab[j], Tab[j - 1]) + P[(j - 1) + X[i] * M];
        }
    }
    return Tab[M];
}

int NEH(int N, int M, int* P, int* X)
{
    int* W = new int[N];

    for (int i = 0; i < N; i++)
    {
        W[i] = Cmax(1, M, P, &i);
    }
    delete[] W;


    for (int i = 0; i < N; i++)
    {
        int bestP = -1;
        int bestCmax = 999999999;

        for (int j = i; j >= 0; j--)
        {
            int tmp = Cmax(i + 1, M, P, X);

            if (tmp <= bestCmax)
            {
                bestP = j;
                bestCmax = tmp;
            }

            if (j)
            {
                swap(X[j], X[j - 1]);
            }
        }

        for (int k = 0; k < bestP; k++)
        {
            swap(X[k], X[k + 1]);
        }

    }
    return Cmax(N, M, P, X);
}

int main()
{
    string dane;
    time_t start, stop;
    double t = 0.0;

    int x = 0;
    int P[10000], X[1000];

    while(!plik.eof() || x > 120)
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