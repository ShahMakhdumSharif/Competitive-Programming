//the k-th number in sorted a[i ... j] segment.
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

struct vertex
{
    vertex *l, *r;
    ll sum;
    vertex(ll val): l(NULL), r(NULL), sum(val){}
    vertex(vertex *l, vertex *r):l(l), r(r), sum(0)
    {
        if(l)
            sum+=l->sum;
        if(r)
            sum+=r->sum;
    }
};

struct persistentSegment
{
    vertex *root;
    vertex* build(ll tl, ll tr)
    {
        if(tl==tr)
            return new vertex(0);
        ll tm=(tl+tr)/2;
        return new vertex(build(tl, tm), build(tm+1, tr));
    }

    vertex *update(vertex *v, ll tl, ll tr, ll pos)
    {
        if(tl==tr)
            return new vertex(v->sum+1);
        ll tm=(tl+tr)/2;
        if(pos<=tm)
            return new vertex(update(v->l, tl, tm, pos), v->r);
        else 
            return new vertex(v->l, update(v->r, tm+1, tr, pos));
    }
    ll find_kth(vertex *vl, vertex *vr, ll tl, ll tr, ll k)
    {
        if(tl==tr)  
            return tl;
        ll tm=(tl+tr)/2, left_count=vr->l->sum-vl->l->sum;
        if(left_count>=k)
            return find_kth(vl->l, vr->l, tl, tm, k);
        return find_kth(vl->r, vr->r, tm+1, tr, k-left_count);
    }
};

struct point
{
    ll i, j, k;
};
void solve(ll tc)
{
    ll n, m;
    cin>>n>>m;
    vector<ll> a(n);
    map<ll, ll> mp;
    for(ll i=0;i<n;i++)
    {
        cin>>a[i];
        mp[a[i]]++;
    }
    vector<point> q;
    for(ll i=0;i<m;i++)
    {
        ll l, r, k;
        cin>>l>>r>>k;
        l--;r--;
        q.push_back({l, r, k});
    } 
    map<ll, ll> unpack;
    ll cnt=1;
    for(auto &[key, val]: mp)
        mp[key]=cnt++;
    for(ll i=0;i<n;i++)
        unpack[mp[a[i]]]=a[i], a[i]=mp[a[i]];
    persistentSegment pst;
    vector<vertex*> roots;
    roots.push_back(pst.build(0, cnt));
    for(ll i=0;i<n;i++)
        roots.push_back(pst.update(roots.back(), 0, cnt, a[i]));
    for(ll i=0;i<m;i++)
    {
        ll ans=pst.find_kth(roots[q[i].i], roots[q[i].j+1], 0, cnt, q[i].k);
        cout<<unpack[ans]<<"\n";
    }
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
    //cin >> t;
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