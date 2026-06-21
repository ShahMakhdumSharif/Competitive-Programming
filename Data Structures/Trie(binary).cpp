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
struct Node
{
    Node* arr[2];
    Node()
    {
        arr[0]=arr[1]=NULL;
    }
};

struct Trie
{
    ll k;
    Node *root;
    Trie(ll k)
    {
        this->k=k;
        root=new Node;
    }
    void Insert(ll val)
    {
        Node *cur=root;
        for(ll i=k-1;i>=0;i--)
        {
            ll bit=(val>>i)&1LL;
            if(cur->arr[bit]==NULL)
                cur->arr[bit]=new Node();
            cur=cur->arr[bit];
        }
    }
    ll Find(ll val)
    {
        Node* cur=root;
        ll ret=0;
        for(ll i=k-1;i>=0;i--)
        {
            ll bit=(val>>i)&1LL;
            ll tbit=1-bit;
            if(cur->arr[bit]==NULL&&cur->arr[tbit]==NULL)
                return -1;
            if(cur->arr[bit]!=NULL)
            {
                if(bit)
                    ret+=(bit<<i);
                cur=cur->arr[bit];
            }
            else
            {
                if(tbit)
                    ret+=(tbit<<i);
                cur=cur->arr[tbit];
            }
        }
        return ret;
    }
};
struct point
{
    ll l, r, x, val;
    point()
    {
        l = r = x = 0;
        val = -1;
    }
};
void solve(ll tc)
{
    ll n, k;
    cin>>n>>k;
    vector<ll> a(n);
    map<ll, ll> pos;
    for(ll i=0;i<n;i++)
        cin>>a[i];
    Trie tr(k);
    tr.Insert(a[0]);
    pos[a[0]]=0;
    point pt;
    for(ll i=1;i<n;i++)
    {
        ll tem=tr.Find(a[i]);
        if(pos.find(tem)==pos.end())
        {
            tr.Insert(a[i]);
            pos[a[i]]=i;
            continue;
        }
        ll x=0, mx=0;;
        for(ll j=k-1;j>=0;j--)
        {
            ll tbit=(tem>>j)&1LL;
            ll abit=(a[i]>>j)&1LL;
            if(tbit==abit)
            {
                if(tbit==0)
                    x+=(1LL<<j);
                mx+=(1LL<<j);
            }
        }
        if(pt.val<mx)
        {
            pt.l=pos[tem];
            pt.r=i;
            pt.x=x;
            pt.val=mx;
            //pt={i+1, pos[tem]+1, x, mx};
        }
        tr.Insert(a[i]);
        pos[a[i]]=i;
    }
    cout<<pt.l+1<<" "<<pt.r+1<<" "<<pt.x<<"\n";
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto clockStart = high_resolution_clock::now();
    ll t = 1;
    cin >> t;
    for (ll tc = 1; tc <= t; tc++)
    {
        debug(tc);
        solve(tc);
        endline;
    }
    auto clockEnd = high_resolution_clock::now();
    auto clockDuration = duration_cast<milliseconds>(clockEnd - clockStart);
    auto clockTime=clockDuration.count();
    debug(clockTime);
    return 0;
}