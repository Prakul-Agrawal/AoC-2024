//
// Created by Prakul Agrawal on 12/24/24.
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

void solve1(string &filename, ll n, ll m, ll secs) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    vvi quad(2, vi(2, 0));
    regex re(R"(^p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+)$)");
    smatch match;
    for(auto info : v){
        if (regex_search(info, match, re)){
            ll x = stoll(match[1]);
            ll y = stoll(match[2]);
            ll vx = stoll(match[3]);
            ll vy = stoll(match[4]);
            ll nx = ((x + secs * vx) % n + n) % n;
            ll ny = ((y + secs * vy) % m + m) % m;
            int a = nx < n / 2 ? 0 : 1;
            int b = ny < m / 2 ? 0 : 1;
            if (nx != n / 2 && ny != m / 2){
                quad[a][b]++;
            }
        }
    }
    ll ans = 1;
    for(auto row : quad){
        for(auto val : row){
            ans *= val;
        }
    }
    cout << ans << endl;
}

void solve2(string &filename, ll n, ll m) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    vvi robots(sz(v), vi(4, 0));
    regex re(R"(^p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+)$)");
    smatch match;
    rep(i, 0, sz(v)){
        if (regex_search(v[i], match, re)){
            int x = stoll(match[1]);
            int y = stoi(match[2]);
            int vx = stoi(match[3]);
            int vy = stoi(match[4]);
            robots[i] = {x, y, vx, vy};
        }
    }
    ll secs = 0;
    while(secs < 10000){
        secs++;
        vector<string> grid(m, string(n, '.'));
        for(auto &robot : robots){
            robot[0] = ((robot[0] + robot[2]) % n + n) % n;
            robot[1] = ((robot[1] + robot[3]) % m + m) % m;
            grid[robot[1]][robot[0]] = '#';
        }
        bool flag = false;
        string substr = "############";
        rep(i,0,m){
            if (grid[i].find(substr) != string::npos){
                flag = true;
                break;
            }
        }
        if (flag){
            cout << secs << endl << endl;
            rep(i,0,m){
                cout << grid[i] << endl;
            }
            cout << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve1(filename, 101, 103, 100);
    cout << endl;
    solve2(filename, 101, 103);
}