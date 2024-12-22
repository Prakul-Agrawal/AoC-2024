//
// Created by Prakul Agrawal on 12/22/24.
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

void updateMap(map<ll, ll> &curr, map<ll, ll> &next) {
    for(auto [key, val] : curr) {
        if (key == 0){
            next[1] += val;
        }
        else {
            int digitCnt = 0;
            ll temp = key;
            while(temp){
                digitCnt++;
                temp /= 10;
            }
            if (digitCnt % 2){
                next[key * 2024] += val;
            }
            else {
                ll tenPow = 1;
                rep(i, 0, digitCnt / 2){
                    tenPow *= 10;
                }
                ll firstPart = key / tenPow;
                ll secondPart = key % tenPow;
                next[firstPart] += val;
                next[secondPart] += val;
            }
        }
    }
    curr = next;
    next.clear();
}

void solve(string &filename, int n) {
    string s = readFile(filename);
    istringstream iss(s);
    ll value;
    map<ll, ll> curr, next;
    while(iss >> value) {
        curr[value]++;
    }
    rep(i, 0, n) {
        updateMap(curr, next);
    }
    ll ans = 0;
    for(auto [key, val] : curr) {
        ans += val;
    }
    cout << ans << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve(filename, 25);
    solve(filename, 75);
}