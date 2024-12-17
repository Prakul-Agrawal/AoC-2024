//
// Created by Prakul Agrawal on 12/18/24.
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

void solve1() {
    string s = readFile("input.txt");
    istringstream iss(s);
    string line;
    ll ans = 0;
    while (getline(iss, line)) {
        istringstream iss2(line);
        string start;
        iss2 >> start;
        set<ll> store;
        store.insert(stoll(start.substr(0, start.find(":"))));
        vl vals;
        ll val;
        while (iss2 >> val) {
            vals.pb(val);
        }
        while(!vals.empty()) {
            val = vals.back();
            vals.pop_back();
            set<ll> temp;
            for (ll i : store) {
                if (i % val == 0) {
                    temp.insert(i / val);
                }
                temp.insert(i - val);
            }
            store = temp;
        }
        if (store.find(0) != store.end()) {
            ans += stoll(start.substr(0, start.find(":")));
        }
    }
    cout << ans << endl;
}

void solve2() {
    string s = readFile("input.txt");
    istringstream iss(s);
    string line;
    ll ans = 0;
    while (getline(iss, line)) {
        istringstream iss2(line);
        string start;
        iss2 >> start;
        set<ll> store;
        store.insert(stoll(start.substr(0, start.find(":"))));
        vl vals;
        ll val;
        while (iss2 >> val) {
            vals.pb(val);
        }
        while(!vals.empty()) {
            val = vals.back();
            vals.pop_back();
            set<ll> temp;
            for (ll i : store) {
                if (i % val == 0) {
                    temp.insert(i / val);
                }
                temp.insert(i - val);
                ll tempVal = val;
                while (tempVal != 0) {
                    if (i % 10 == tempVal % 10) {
                        i /= 10;
                        tempVal /= 10;
                    }
                    else {
                        break;
                    }
                }
                if (tempVal == 0) {
                    temp.insert(i);
                }
            }
            store = temp;
        }
        if (store.find(0) != store.end()) {
            ans += stoll(start.substr(0, start.find(":")));
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0); // To increase input-output speed
    cin.tie(0);
    solve1();
    solve2();
}