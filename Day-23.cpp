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

bool checkClique(vector<string> &nodes, map<string, set<string>> &adj) {
    int n = sz(nodes);
    rep(i, 0, n){
        rep(j, i + 1, n){
            if (adj[nodes[i]].find(nodes[j]) == adj[nodes[i]].end()){
                return false;
            }
        }
    }
    return true;
}

void solve1(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    set<string> v;
    while (getline(iss, line)) {
        v.insert(line);
    }
    map<string, vector<string>> adj;
    for(auto e : v){
        string a = e.substr(0, 2);
        string b = e.substr(3, 2);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    set<vector<string>> found;
    for(auto [key, value] : adj){
        if (key[0] != 't'){
            continue;
        }
        rep(i, 0, sz(value)){
            rep(j, i + 1, sz(value)){
                string a = value[i], b = value[j];
                string ab = a + "-" + b, ba = b + "-" + a;
                if (v.find(ab) != v.end() || v.find(ba) != v.end()){
                    vector<string> temp = {key, a, b};
                    sort(all(temp));
                    found.insert(temp);
                }
            }
        }
    }
    cout << sz(found) << endl;
}

void solve2(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    map<string, set<string>> adj;
    for(auto e : v){
        string a = e.substr(0, 2);
        string b = e.substr(3, 2);
        adj[a].insert(b);
        adj[b].insert(a);
    }
//    Figuring out heuristic to solve this problem
//    int maxCliqueSize = 0;
//    for(auto [key, value] : adj){
//        maxCliqueSize = max(maxCliqueSize, sz(value));
//    }
//    maxCliqueSize++;
//    int maxCommonSize = 0;
//    rep(i, 0, sz(v)){
//        string a = v[i].substr(0, 2);
//        string b = v[i].substr(3, 2);
//        set<string> common;
//        for(auto e : adj[a]){
//            if (adj[b].find(e) != adj[b].end()){
//                common.insert(e);
//            }
//        }
//        maxCommonSize = max(maxCommonSize, sz(common));
//    }
//    cout << maxCliqueSize << endl;
//    cout << maxCommonSize << endl;
    vector<string> maxClique;
    rep(i, 0, sz(v)){
        string a = v[i].substr(0, 2);
        string b = v[i].substr(3, 2);
        vector<string> common = {a, b};
        for(auto e : adj[a]){
            if (adj[b].find(e) != adj[b].end()){
                common.pb(e);
            }
        }
        if (checkClique(common, adj)){
            if (sz(common) > sz(maxClique)){
                maxClique = common;
            }
        }
    }
    sort(all(maxClique));
    string ans = "";
    for(auto e : maxClique){
        ans += e + ",";
    }
    cout << ans.substr(0, sz(ans) - 1) << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve1(filename);
    solve2(filename);
}