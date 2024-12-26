//
// Created by Prakul Agrawal on 12/26/24.
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
    vvl store(2, vl(8, 0));
    rep(i,0,8){
        store[0][i] = i;
        store[1][i] = i;
    }
    store[1][4] = stoll(v[0].substr(12));
    store[1][5]= stoll(v[1].substr(12));
    store[1][6] = stoll(v[2].substr(12));
    string temp = v[4].substr(9);
    vi program;
    for(auto c : temp){
        if (c != ','){
            program.pb(c - '0');
        }
    }
    int n = sz(program);
    int ptr = 0;
    string ans = "";
    while(ptr < n){
        int opcode = program[ptr++];
        int operand = program[ptr++];
        if (opcode == 0){
            store[1][4] /= (1 << store[1][operand]);
        }
        else if (opcode == 1){
            store[1][5] ^= store[0][operand];
        }
        else if (opcode == 2){
            store[1][5] = store[1][operand] % 8;
        }
        else if (opcode == 3){
            if (store[1][4] != 0){
                ptr = store[0][operand];
            }
        }
        else if (opcode == 4){
            store[1][5] ^= store[1][6];
        }
        else if (opcode == 5){
            ans += to_string(store[1][operand] % 8) + ",";
        }
        else if (opcode == 6){
            store[1][5] = store[1][4] / (1 << store[1][operand]);
        }
        else {
            store[1][6] = store[1][4] / (1 << store[1][operand]);
        }
    }
    ans = ans.substr(0, sz(ans) - 1);
    cout << ans << endl;
}

// Coded for my specific input
// Instruction are:
// B = A % 8
// B = B ^ 2
// C = A / (1 << B)
// A = A / 8
// B = B ^ C
// B = B ^ 7
// OUTPUT B % 8
// REPEAT ABOVE TILL A != 0
void solve2(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    string temp = v[4].substr(9);
    vi program;
    for(auto c : temp){
        if (c != ','){
            program.pb(c - '0');
        }
    }
    int n = sz(program);
    reverse(all(program));
    ll A_old = 0;
    rep(i, 0, n){
        A_old <<= 3;
        rep(A_new, 0, 8){
            ll val = (A_old + A_new) / (1LL << (A_new ^ 2));
            val ^= (5 ^ A_new);
            if (val % 8 == program[i]){
                A_old += A_new;
                break;
            }
        }
    }
    cout << A_old << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve1(filename);
    solve2(filename);
}