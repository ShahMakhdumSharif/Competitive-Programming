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
const ll N = 1000005;
const ll INF = 1e17;

// struct Update
// {
//     ll i, nval, pval;
// };
struct Query
{
    ll l, r, i;
};
void solve(ll tc)
{
    ll n, q;
    cin>>n>>q;
    vector<ll> a(n);//, uni;
    for(ll i=0;i<n;i++)
        cin>>a[i];//, uni.push_back(a[i]);
    vector<pair<ll, ll>> Operations;//type=1: Update, type=2:Query;
    for(ll i=0;i<q;i++)
    {
        ll l, r;
        cin>>l>>r;
        l--, r--;
        Operations.push_back({l, r});
    }
    // sort(uni.begin(), uni.end());
    // uni.erase(unique(uni.begin(), uni.end()), uni.end());
    // function<ll(ll)>compress=[&](ll x)
    // {
    //     return lower_bound(uni.begin(), uni.end(), x)-uni.begin();
    // };
    // for(ll i=0;i<n;i++)
    //     a[i]=compress(a[i]);
    //ll time=0;
    ll cnt=0;
    //vector<Update> updates;
    vector<Query> queries;
    vector<ll> tem=a;
    for(auto &pr: Operations)
    {
        auto &[u, v]=pr;
        // if(type==1)
        // {
        //     updates.push_back({u, v, tem[u]});
        //     tem[u]=v;
        //     time++;
        // }
        // else
        // {
        queries.push_back({u, v, cnt++});
        //}
    }
    ll Block=sqrt(n)+1;
    sort(queries.begin(), queries.end(), [&](auto &p, auto &q)
    {
        ll pbl=p.l/Block, qbl=q.l/Block;
        ll pbr=p.r/Block, qbr=q.r/Block;
        if(pbl!=qbl)
            return pbl<qbl;
        //if(pbr!=qbr)
            return pbr<qbr;
        //return p.t<q.t;
    });
    vector<ll> freq(N+1, 0);
    vector<ll> cur=a, base=a;
    ll Sum=0;
    auto add=[&](ll pos)
    {
        ll x=cur[pos];
        // if(x>N)
        //     return;
        Sum-=freq[x]*freq[x]*x;
        freq[x]++;
        Sum+=freq[x]*freq[x]*x; 
    };
    auto remove=[&](ll pos)
    {
        ll x=cur[pos];
        // if(x>N)
        //     return;
        Sum-=freq[x]*freq[x]*x;
        freq[x]--;
        Sum+=freq[x]*freq[x]*x;
    };
    // auto apply=[&](ll pos, ll l, ll r)
    // {
    //     auto &it=updates[pos];
    //     if(it.i>=l&&it.i<=r)
    //     {
    //         remove(it.i);
    //         cur[it.i]=it.nval;
    //         add(it.i);
    //     }
    //     else
    //         cur[it.i]=it.nval;
    // };
    // auto rollback=[&](ll pos, ll l, ll r)
    // {
    //     auto &it=updates[pos];
    //     if(it.i>=l&&it.i<=r)
    //     {
    //         remove(it.i);
    //         cur[it.i]=it.pval;
    //         add(it.i);
    //     }
    //     else
    //         cur[it.i]=it.pval;
    // };
    vector<ll> ans(cnt);
    ll curl=0, curr=-1;//, curt=0;
    for(auto &qr: queries)
    {
        // while(curt<qr.t)
        // {
        //     apply(curt, curl, curr);
        //     curt++;
        // }
        // while(curt>qr.t)
        // {
        //     curt--;
        //     rollback(curt, curl, curr);
        // }
        while(curl>qr.l)
            add(--curl);
        while(curr<qr.r)
            add(++curr);
        while(curl<qr.l)
            remove(curl++);
        while(curr>qr.r)
            remove(curr--);
        ans[qr.i]=Sum;
        //dif[qr.i]=qr.r-qr.l+1;
    }
    for(auto u: ans)
    cout<<u<<"\n";
    // for(ll i=0;i<cnt;i++)
    // {
    //     if(dif[i]!=ans[i])
    //         cout<<"NO\n";
    //     else cout<<"YES\n";
    // }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto clockStart = high_resolution_clock::now();
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