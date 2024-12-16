//
// Created by Prakul Agrawal on 12/17/24.
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

void solve() {
    string s = readFile("input.txt");
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int pos = 0;
    set<pii> rules;
    while (v[pos] != "") {
        string rule = v[pos++];
        int pipe = rule.find('|');
        int before = stoi(rule.substr(0, pipe));
        int after = stoi(rule.substr(pipe + 1));
        rules.insert({before, after});
    }
    pos++;
    ll ans1 = 0, ans2 = 0;
    while (pos < sz(v)) {
        string update = v[pos++];
        vi values;
        int curr = 0;
        for (int i = 0; i < sz(update); i++) {
            if (update[i] == ',') {
                values.pb(curr);
                curr = 0;
            } else {
                curr = curr * 10 + (update[i] - '0');
            }
        }
        values.pb(curr);
        vi valuesCopy = values;
        sort(all(valuesCopy), [&](int a, int b) {
            if (rules.find({b, a}) != rules.end()) {
                return false;
            }
            return true;
        });
        int flag = 1;
        for (int i = 0; i < sz(values); i++) {
            if (values[i] != valuesCopy[i]) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            ans1 += valuesCopy[sz(values) / 2];
        }
        else {
            ans2 += valuesCopy[sz(values) / 2];
        }
    }
    cout << ans1 << endl;
    cout << ans2 << endl;
}

int main() {
    ios::sync_with_stdio(0); // To increase input-output speed
    cin.tie(0);
    solve();
}