//check.cpp
//This is for pure brute force solution(to check the answer)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace chrono;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define ll long long
#define ld long double
#ifndef ONLINE_JUDGE
#define debug(x) do{cerr << #x << ": "; _print(x); cerr <<"\n";}while(0)
#define endline cerr << "\n---------------------------\n";
#else
#define endline
#define debug(x)
#endif



template <typename T> void _print(T t) {cerr << t;}
template <typename T, size_t N> void _print(const T (&arr)[N]) {cerr << "[ "; for (const auto& it : arr) cerr << it << ' '; cerr << "]\n";}
template <typename T> void _print(const vector<T>& v1) {cerr << "[ "; for (const auto& it : v1) cerr << it << ' '; cerr << "]\n";}
template <typename T> void _print(const deque<T>& dq) {cerr << "[ "; for (const auto& it : dq) cerr << it << ' '; cerr << "]\n";}
template <typename T> void _print(const set<T>& s) {cerr << "{ "; for (const auto& it : s) cerr << it << ' '; cerr << "}\n";}
template <typename T> void _print(const set<T, greater<T> >& s) {cerr << "{ "; for (const auto& it : s) cerr << it << ' '; cerr << "}\n";}
template <typename T> void _print(const multiset<T>& ms) {cerr << "{ "; for (const auto& it : ms) cerr << it << ' '; cerr << "}\n";}
template <typename T> void _print(const multiset<T, greater<T> >& ms) {cerr << "{ "; for (const auto& it : ms) cerr << it << ' '; cerr << "}\n";}
template <typename T, typename V>void _print(const pair<T,V>& p) {cerr << "{" << p.first << "," << p.second << "}\n";}



const ll MOD = 998244353;
const ll N = 500005;
const ll INF = 1e17;



int32_t main()
{
    ll t=1;
    //cin>>t;
    while(t--)
    {
        ll n, q;
        cin>>n>>q;
        vector<ll> a(n);
        for(ll i=0;i<n;i++)
            cin>>a[i];
        vector<ll> ans;
        for(ll i=0;i<q;i++)
        {
            // ll type;
            // cin>>type;
            // if(type==1)
            // {
            //     ll pos, x;
            //     cin>>pos>>x;
            //     pos--;
            //     a[pos]=x;
            // }
            // else if(type==2)
            // {
            ll l, r;
            cin>>l>>r;
            l--;r--;
            map<ll, ll> freq;
            set<ll> st;
            for(ll j=l;j<=r;j++)
                freq[a[j]]++, st.insert(a[j]);
            ll cnt=0;
            for(auto u: st)
            {
                if(freq[u]==u)
                    cnt++;
            }
            ans.push_back(cnt);
            //}
        }
        // for(auto u: ans)
        //     cout<<u<<"\n";
        vector<ll> orans(ans.size());
        ll sz=ans.size();
        for(ll i=0;i<sz;i++)
            cin>>orans[i];
        if(orans!=ans)
        {
            cout<<"Failed\n";
            return 0;
        }
        cout<<"OK\n";
    }
}