//
// Created by Prakul Agrawal on 12/30/24.
//

#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define INF 1e18
typedef long long ll;
//#define int long long;
typedef long double ldb;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<pli> vpli;
typedef vector<pil> vpil;
typedef vector<vpii> vvpii;
typedef vector<vpll> vvpll;
typedef vector<vpli> vvpli;
typedef vector<vpil> vvpil;
#define ff first
#define ss second
#define pb push_back
#define endl '\n'
#define all(s) s.begin(), s.end()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define tc int t; cin>>t; while(t--)
#define printcase int t; cin>>t; for(int i=1;i<=t;i++){cout<<"Case #"<<i<<": ";solve();}
#define max_heap(x) priority_queue<x>
#define min_heap(x) priority_queue<x, vector<x>, greater<x>>

string readFile(string filename) {
    ifstream file(filename);
    string s;
    string line;
    while (getline(file, line)) {
        s += line + "\n";
    }
    return s;
}

void solve1(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    ll ans = 0;
    rep(i, 0, sz(v)){
        ll x = stoll(v[i]);
        ll y;
        rep(j, 0, 2000){
            y = x << 6;
            x ^= y;
            x &= 16777215;
            y = x >> 5;
            x ^= y;
            x &= 16777215;
            y = x << 11;
            x ^= y;
            x &= 16777215;
        }
        ans += x;
    }
    cout << ans << endl;
}

void solve2(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    vpii memo(19*19*19*19, {0, -1});
    rep(i, 0, sz(v)){
        ll x = stoll(v[i]);
        ll y;
        deque<int> dq;
        int oldDigit = x % 10, newDigit;
        rep(j, 0, 4){
            y = x << 6;
            x ^= y;
            x &= 16777215;
            y = x >> 5;
            x ^= y;
            x &= 16777215;
            y = x << 11;
            x ^= y;
            x &= 16777215;
            newDigit = x % 10;
            dq.push_back(newDigit - oldDigit);
            oldDigit = newDigit;
        }
        int idx = 0;
        for(auto e : dq){
            idx = idx * 19 + e + 9;
        }
        memo[idx].ff += oldDigit;
        memo[idx].ss = i;
        rep(j, 0, 1996){
            y = x << 6;
            x ^= y;
            x &= 16777215;
            y = x >> 5;
            x ^= y;
            x &= 16777215;
            y = x << 11;
            x ^= y;
            x &= 16777215;
            newDigit = x % 10;
            dq.push_back(newDigit - oldDigit);
            oldDigit = newDigit;
            dq.pop_front();
            idx %= 19 * 19 * 19;
            idx = idx * 19 + dq[3] + 9;
            if(memo[idx].ss == i){
                continue;
            }
            memo[idx].ff += oldDigit;
            memo[idx].ss = i;
        }
    }
    int ans = 0;
    for(auto e : memo){
        ans = max(ans, e.ff);
    }
    cout << ans << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve1(filename);
    solve2(filename);
}