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
    ll n;
    cin>>n;
    vector<pair<string, string>> v;
    vector<pair<ll, ll>> a;
    map<string, ll> mp1, mp2;
    for(ll i=0;i<n;i++)
    {
        string x, y;
        cin>>x>>y;
        v.push_back({x, y});
        mp1[x]++;
        mp2[y]++;
    }
    ll cnt=0;
    for(auto &[key, val]: mp1)
        val=++cnt;
    for(auto &[key, val]: mp2)
        val=++cnt;
    for(auto &[x, y]: v)
    {
        a.push_back({mp1[x], mp2[y]});
    }
    vector<vector<ll>> adj(n+1, vector<ll>(n+1, 0));
    for(ll i=0;i<n;i++)
    {
        for(ll j=i+1;j<n;j++)
        {
            if(a[i].first==a[j].first||a[i].second==a[j].second)
                adj[i][j]=adj[j][i]=1;
        }
    }
    ll mx=0;
    function<void(void)> HamiltonianPath = [&](void)
    {
        vector<vector<bool>> dp(n + 1, vector<bool>((1 << n), 0));
        for (int i = 0; i < n; i++)
            dp[i][1 << i] = true;
        for (int i = 0; i < (1 << n); i++)
        {
            for (int j = 0; j < n; j++)
                if (i & (1 << j))
                {
                    for (int k = 0; k < n; k++)
                        if (i & (1 << k) && adj[k][j] && k != j && dp[k][(i ^ (1 << j))])
                        {
                            dp[j][i] = true;
                            break;
                        }
                    if (dp[j][i])
                        mx = max(mx, (ll)__builtin_popcountll(i));
                }
        }
        // for(int i=0; i<n; i++)
        //     if(dp[i][(1<<n)-1])
        //         return true;
        // return false;
    };
    HamiltonianPath();
    cout<<n-mx<<"\n";
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