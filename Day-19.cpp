//
// Created by Prakul Agrawal on 12/27/24.
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

map<string, ll> memo;

string readFile(string filename) {
    ifstream file(filename);
    string s;
    string line;
    while (getline(file, line)) {
        s += line + "\n";
    }
    return s;
}

ll patternPossible(string &s, int index, vvi &trie, vi &trieEnd) {
    if (index == sz(s)) {
        return 1;
    }
    if (memo.find(s.substr(index)) != memo.end()) {
        return memo[s.substr(index)];
    }
    int node = 0;
    ll ways = 0;
    for (int i = index; i < sz(s); i++) {
        int idx = s[i] - 'a';
        if (trie[node][idx] == -1) {
            memo[s.substr(index)] = ways;
            return ways;
        }
        node = trie[node][idx];
        if (trieEnd[node]) {
            ways += patternPossible(s, i + 1, trie, trieEnd);
        }
    }
    memo[s.substr(index)] = ways;
    return ways;
}

void solve(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    vvi trie(1, vi(26, -1));
    vi trieEnd(1, 0);
    istringstream iss2(v[0]);
    while (iss2 >> line) {
        int node = 0;
        for (char c : line) {
            if (c == ',') {
                continue;
            }
            int idx = c - 'a';
            if (trie[node][idx] == -1) {
                trie[node][idx] = sz(trie);
                trie.pb(vi(26, -1));
                trieEnd.pb(0);
            }
            node = trie[node][idx];
        }
        trieEnd[node] = 1;
    }
    int ans1 = 0;
    ll ans2 = 0;
    rep(i, 2, sz(v)){
        ll ways = patternPossible(v[i], 0, trie, trieEnd);
        if (ways) {
            ans1++;
        }
        ans2 += ways;
    }
    cout << ans1 << endl;
    cout << ans2 << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve(filename);
}