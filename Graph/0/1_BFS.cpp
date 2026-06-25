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


void solve(ll tc)
{
    ll n, m;
    cin>>n>>m;
    map<pair<ll, ll>, vector<ll>> adj;
    vector<set<ll>> color(n+1);
    for(ll i=0;i<m;i++)
    {
        ll u, v, c;
        cin>>u>>v>>c;
        adj[{u, c}].push_back(v);
        adj[{v, c}].push_back(u);
        color[u].insert(c);
        color[v].insert(c);
    }
    ll b, e;
    cin>>b>>e;
    map<pair<ll, ll>, ll> vis;
    vis[{b, 0}]=0;
    /*
    0/1 BFS e deque use kora hoi,, eta Dijkstra er Priority_Queue
    er motoi distance golare sort kore rakhe.. (kivabe?: jodi amr
    computed distance 0 hoy taile ami push_front arr jodi computed
    distance 0 er theke boro hoi taile ami push_back(). etar karone 
    automatic sort hoye thake) and ei algorithm tokhon i use kora 
    jokhon kono edge er cost 0 arr kono edge er cost 1 hoi( assa  
    tahole dijkstra rekhe eta ken use korbo?: dijkstra r complexity
    hosse ElogV arr eta linear complexity, O(E) te kaj kore.).
    */
    deque<array<ll, 3>> dq;
    dq.push_front({b, 0, 0});
    ll ans=INF;
    while(!dq.empty())
    {
        auto [u, ci, d]=dq.front();
        dq.pop_front();
        if(vis[{u, ci}]!=d)
            continue;
        if(u==e)
            ans=min(ans, d);
        if(ci)
        {
            for(auto &v: adj[{u, ci}])
            {
                if(vis.find({v, ci})==vis.end()||vis[{v, ci}]>d)
                {
                    vis[{v, ci}]=d;
                    dq.push_front({v, ci, d});
                }
                if(vis.find({u, 0})==vis.end()||vis[{u, 0}]>d)
                {
                    vis[{u, 0}]=d;
                    dq.push_front({u, 0, d});
                }
            }
        }
        else
        {
            for(auto &ci: color[u])
            {
                if(vis.find({u, ci})==vis.end())
                {
                    vis[{u, ci}]=d+1;
                    dq.push_back({u, ci, d+1});
                }
            }
        }
    }
    cout<<ans<<"\n";
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