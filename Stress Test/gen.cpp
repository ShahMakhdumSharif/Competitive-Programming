// gen.cpp
//this is for generating test case
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll num=1e12;
ll sz=1e6;

int main()
{
    srand(time(0));
    //cout<<"1\n";
    ll n=100000;
    ll q=100000;
    cout<<n<<" "<<q<<"\n";
    vector<ll> a(n);
    for(ll i=0;i<n;i++)
        cout<<rand()%1000000000+1<<" ";
    cout<<"\n";
    while(q--)
    {
        ll l=rand()%n+1, r=rand()%n+1;
        if(l>r)
            swap(l, r);
        cout<<l<<" "<<r<<"\n";
    }
}