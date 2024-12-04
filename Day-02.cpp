//
// Created by Prakul Agrawal on 12/5/24.
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

int safe(vi &a){
    vi diff;
    int flag = 1;
    rep(i, 1, sz(a)) {
        diff.pb(a[i] - a[i - 1]);
        if (a[i] < a[i - 1]) {
            flag = -1;
        }
    }
    int check = 1;
    for(auto x: diff) {
        if (flag * x <= 0 || abs(x) > 3) {
            check = 0;
            break;
        }
    }
    return check;
}

void solve1() {
    string s = readFile("input.txt");
    istringstream iss(s);
    string line;
    int ans = 0;
    while (getline(iss, line)) {
        istringstream iss2(line);
        vi a;
        int p;
        while (iss2 >> p) {
            a.pb(p);
        }
        int check = safe(a);
        ans += check;
    }
    cout << ans << endl;
}

void solve2() {
    string s = readFile("input.txt");
    istringstream iss(s);
    string line;
    int ans = 0;
    while (getline(iss, line)) {
        istringstream iss2(line);
        vi a;
        int p;
        while (iss2 >> p) {
            a.pb(p);
        }
        int check = safe(a);
        ans += check;
        if (check == 0){
            rep(j, 0, sz(a)){
                vi b;
                rep(k, 0, sz(a)){
                    if (k != j){
                        b.pb(a[k]);
                    }
                }
                if (safe(b)){
                    ans += 1;
                    break;
                }
            }
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