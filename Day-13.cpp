//
// Created by Prakul Agrawal on 12/23/24.
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

void solve(string &filename, ll val) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int len = (sz(v) + 3) / 4;
    ll ans = 0;
    rep(i,0,len){
        string buttonA = v[i*4];
        string buttonB = v[i*4+1];
        string prize = v[i*4+2];
        smatch m;
        regex buttonR(".*X\\+(\\d+), Y\\+(\\d+)");
        regex_search(buttonA, m, buttonR);
        ll buttonAX = stoi(m[1]);
        ll buttonAY = stoi(m[2]);
        regex_search(buttonB, m, buttonR);
        ll buttonBX = stoi(m[1]);
        ll buttonBY = stoi(m[2]);
        regex prizeR(".*X=(\\d+), Y=(\\d+)");
        regex_search(prize, m, prizeR);
        ll prizeX = stoi(m[1]) + val;
        ll prizeY = stoi(m[2]) + val;
        ll b = (buttonAX * prizeY - buttonAY * prizeX) / (buttonAX * buttonBY - buttonAY * buttonBX);
        ll a = (prizeX - buttonBX * b) / buttonAX;
        if (a * buttonAX + b * buttonBX == prizeX && a * buttonAY + b * buttonBY == prizeY){
            ans += 3 * a + b;
        }
    }
    cout << ans << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve(filename, 0);
    solve(filename, 10000000000000);
}