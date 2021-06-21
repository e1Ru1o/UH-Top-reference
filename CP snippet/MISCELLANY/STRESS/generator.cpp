#include <bits/stdc++.h>

#define int long long

using namespace std;

mt19937_64 random_number(chrono::steady_clock::now().time_since_epoch().count());

int rng(int a, int b)
{
    return uniform_int_distribution<int>(a,b)(random_number);
}

bool fc()
{
    ifstream f1("work/ans1.txt");
    ifstream f2("work/ans2.txt");

    string s1, s2;

    while(f1 >> s1)
    {
        f2 >> s2;
        if(s1 != s2)return false;
    }
    return true;
}

void generator()
{
    ofstream fout("work/tc.txt");

    int A = rng(1,1000);
    int B = rng(1,1000);

    fout << A << " " << B << '\n';
}

int32_t main()
{
    ///compiles the codes

    // system("g++ good.cpp -o good");
    // system("g++ bad.cpp -o bad");


    ///copy in the other codes

    //freopen("work/tc.txt", "r", stdin);
    //freopen("work/ans1/2.txt", "w", stdout);

    int tc = 1000000000000;
    int error = 0;

    for(int i = 1 ; i <= tc ; i++)
    {
        generator();
        system("./good");
        system("./bad");

        if(fc() == false)
        {
            error++;
        }

        cout << i << " " << error << '\n';
    }

    return 0;
}
