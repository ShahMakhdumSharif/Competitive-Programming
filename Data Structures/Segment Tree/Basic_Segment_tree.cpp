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
pair<ll, ll> combine(pair<ll, ll> &p, pair<ll, ll> &q)
{
    return {max(p.first, q.first), min(p.second, q.second)};
}
struct SegmentTree
{
    vector<ll> a, b;
    vector<pair<ll, ll>> st;//maxi, mini
    SegmentTree(vector<ll> &a, vector<ll> &b)
    {
        this->b=b;
        this->a=a;
        ll n=a.size();
        st.resize(4*n, {0, INF});
    }
    void build(ll v, ll l, ll r)
    {
        if(l==r)
        {
            st[v]={a[l], b[l]};
            return;
        }
        ll mid=(l+r)/2;
        build(2*v, l, mid);
        build(2*v+1, mid+1, r);
        st[v]=combine(st[2*v], st[2*v+1]);
    }
    pair<ll, ll> query(ll v, ll l, ll r, ll tl, ll tr)
    {
        if(tl>r||tr<l)
            return {0, INF};
        if(l>=tl&&r<=tr)
            return st[v];
        ll mid=(l+r)/2;
        auto left=query(2*v, l, mid, tl, tr);
        auto right=query(2*v+1, mid+1, r, tl, tr);
        return combine(left, right);
    }
};

void solve(ll tc)
{
    ll n;
    cin>>n;
    vector<ll> a(n), b(n);
    for(ll i=0;i<n;i++)
        cin>>a[i];
    for(ll i=0;i<n;i++)
        cin>>b[i];
    SegmentTree segt(a,b);
    segt.build(1, 0, n-1);
    vector<set<ll>> pos(n+10);
    for(ll i=0;i<n;i++)
    {
        pos[a[i]].insert(i);
    }
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    for(ll i=0;i<n;i++)
    {
        if(b[i]<a[i])
            return void(cout<<"NO\n");
        if(a[i]!=b[i])
            pq.push({b[i], i});
    }
    while(!pq.empty())
    {
        auto i=pq.top().second;
        pq.pop();
        auto lit=pos[b[i]].lower_bound(i);
        ll left=n, right=-1;
        auto rit=pos[b[i]].upper_bound(i);
        if(lit!=pos[b[i]].begin())
            left=*--lit;
        if(rit!=pos[b[i]].end())
            right=*rit;
        bool flag=false;
        if(left<i)
        {
            auto pr=segt.query(1, 0, n-1, left, i);
            if(pr.first==b[i]&&pr.second>=b[i])
                flag=true;
        }
        if(right>i)
        {
            auto pr=segt.query(1, 0, n-1, i, right);
            if(pr.first==b[i]&&pr.second>=b[i])
                flag=true;
        }
        if(!flag)
            return void(cout<<"NO\n");
    }
    cout<<"YES\n";
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto clockStart = high_resolution_clock::now();
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif
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