//
// Created by Prakul Agrawal on 12/31/24.
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

int dfs(map<string, tuple<int, string, string>> &instructions, map<string, int> &wireValue, string wire) {
    if(wireValue[wire] != -1) {
        return wireValue[wire];
    }
    int opVal = get<0>(instructions[wire]);
    int val1 = dfs(instructions, wireValue, get<1>(instructions[wire]));
    int val2 = dfs(instructions, wireValue, get<2>(instructions[wire]));
    if(opVal == 1) {
        wireValue[wire] = val1 & val2;
    } else if(opVal == 2) {
        wireValue[wire] = val1 | val2;
    } else {
        wireValue[wire] = val1 ^ val2;
    }
    return wireValue[wire];
}

void solve1(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    map<string, int> wireValue;
    while (getline(iss, line) && line != "") {
        istringstream iss2(line);
        string wire, valStr;
        iss2 >> wire >> valStr;
        wireValue[wire.substr(0, sz(wire)-1)] = stoi(valStr);
    }
    map<string, tuple<int, string, string>> instructions;
    vector<string> zWires;
    while (getline(iss, line)) {
        istringstream iss2(line);
        string wire1, op, wire2, arrow, wire3;
        iss2 >> wire1 >> op >> wire2 >> arrow >> wire3;
        int opVal = 0;
        if (op == "AND") {
            opVal = 1;
        } else if (op == "OR") {
            opVal = 2;
        } else {
            opVal = 3;
        }
        instructions[wire3] = {opVal, wire1, wire2};
        wireValue[wire3] = -1;
        if(wire3[0] == 'z') {
            zWires.pb(wire3);
        }
    }
    sort(all(zWires), greater<string>());
    ll ans = 0;
    for(auto wire : zWires) {
        ans = ans * 2 + dfs(instructions, wireValue, wire);
    }
    cout << ans << endl;
}

void solve2(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line) && line != "") {}
    vector<string> zWires;
    map<string, tuple<int, string, string>> instructions;
    while (getline(iss, line)) {
        istringstream iss2(line);
        string wire1, op, wire2, arrow, wire3;
        iss2 >> wire1 >> op >> wire2 >> arrow >> wire3;
        int opVal = 0;
        if (op == "AND") {
            opVal = 1;
        } else if (op == "OR") {
            opVal = 2;
        } else {
            opVal = 3;
        }
        instructions[wire3] = {opVal, wire1, wire2};
        if(wire3[0] == 'z') {
            zWires.pb(wire3);
        }
    }
    sort(all(zWires), greater<string>());
//  Solution uses the fact that the circuit is a Ripple Carry Adder
    set<string> wrongWires;
    for(auto [res, instr] : instructions) {
        auto [fn, op1, op2] = instr;
        if(res[0] == 'z' && res != zWires[0] && fn != 3) {
            wrongWires.insert(res);
        }
        if(res == zWires[0] && fn != 2) {
            wrongWires.insert(res);
        }
        if(fn == 2 || fn == 3){
            for(auto [subRes, subInstr] : instructions) {
                auto [subFn, subOp1, subOp2] = subInstr;
                if (subFn == 2 && (res == subOp1 || res == subOp2)) {
                    wrongWires.insert(res);
                }
            }
        }
        if(fn == 1 && (op1 != "x00" && op2 != "x00")) {
            for(auto [subRes, subInstr] : instructions) {
                auto [subFn, subOp1, subOp2] = subInstr;
                if (subFn != 2 && (res == subOp1 || res == subOp2)) {
                    wrongWires.insert(res);
                }
            }
        }
        if(fn == 3 && (op1 != "x00" && op2 != "x00")) {
            string temp = "";
            temp += op1[0];
            temp += op2[0];
            sort(all(temp));
            if (temp != "xy" && res[0] != 'z' || temp == "xy" && res[0] == 'z') {
                wrongWires.insert(res);
            }
        }
    }
    string ans = "";
    for(auto wire : wrongWires) {
        ans += wire + ",";
    }
    cout << ans.substr(0, sz(ans)-1) << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve1(filename);
    solve2(filename);
}