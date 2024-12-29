//
// Created by Prakul Agrawal on 12/28/24.
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
#define sz(x) (ll)(x).size()
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

void solve(string &filename, int iterations) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    map<string, set<string>> stringMap = {
            {"AA", {"A"}},
            {"A^", {"<A"}},
            {"Av", {"<vA", "v<A"}},
            {"A<", {"v<<A"}},
            {"A>", {"vA"}},
            {"^A", {">A"}},
            {"^^", {"A"}},
            {"^v", {"vA"}},
            {"^<", {"v<A"}},
            {"^>", {"v>A", ">vA"}},
            {"vA", {"^>A", ">^A"}},
            {"v^", {"^A"}},
            {"vv", {"A"}},
            {"v<", {"<A"}},
            {"v>", {">A"}},
            {"<A", {">>^A"}},
            {"<^", {">^A"}},
            {"<v", {">A"}},
            {"<<", {"A"}},
            {"<>", {">>A"}},
            {">A", {"^A"}},
            {">^", {"<^A", "^<A"}},
            {">v", {"<A"}},
            {"><", {"<<A"}},
            {">>", {"A"}},
    };
    vector<string> numPad = {
            "789",
            "456",
            "123",
            " 0A"
    };
    map<char, pii> numPadPos;
    rep(i, 0, 4) {
        rep(j, 0, 3) {
            numPadPos[numPad[i][j]] = {i, j};
        }
    }
    vector<char> numPadChars = {'7', '8', '9', '4', '5', '6', '1', '2', '3', '0', 'A'};
    for(auto i: numPadChars){
        for(auto j: numPadChars){
            string sPair = string(1, i) + string(1, j);
            pair diff = {numPadPos[j].ff - numPadPos[i].ff, numPadPos[j].ss - numPadPos[i].ss};
            string downUp = "", leftRight = "";
            while(diff.ff != 0){
                if(diff.ff > 0){
                    downUp += "v";
                    diff.ff--;
                } else {
                    downUp += "^";
                    diff.ff++;
                }
            }
            while(diff.ss != 0){
                if(diff.ss > 0){
                    leftRight += ">";
                    diff.ss--;
                } else {
                    leftRight += "<";
                    diff.ss++;
                }
            }
            stringMap[sPair].insert(leftRight + downUp + "A");
            stringMap[sPair].insert(downUp + leftRight + "A");
        }
    }
    stringMap["A7"].erase("<<^^^A");
    stringMap["A4"].erase("<<^^A");
    stringMap["A1"].erase("<<^A");
    stringMap["07"].erase("<^^^A");
    stringMap["04"].erase("<^^A");
    stringMap["01"].erase("<^A");
    stringMap["7A"].erase("vvv>>A");
    stringMap["4A"].erase("vv>>A");
    stringMap["1A"].erase("v>>A");
    stringMap["70"].erase("vvv>A");
    stringMap["40"].erase("vv>A");
    stringMap["10"].erase("v>A");

    map<string, ll> lengthMap;
    for(auto [key, value]: stringMap){
        ll minLen = LLONG_MAX;
        for(auto x: value){
            minLen = min(minLen, sz(x));
        }
        lengthMap[key] = minLen;
    }
    rep(i, 0, iterations){
        map<string, ll> tempMap;
        for(auto [key, value]: stringMap){
            ll minLen = LLONG_MAX;
            for(auto x: value){
                string nx = "A" + x;
                ll currLen = 0;
                rep(j, 0, sz(nx) - 1){
                    string sPair = "";
                    sPair += nx[j];
                    sPair += nx[j + 1];
                    currLen += lengthMap[sPair];
                }
                minLen = min(minLen, currLen);
            }
            tempMap[key] = minLen;
        }
        lengthMap = tempMap;
    }
    ll ans = 0;
    for(auto e : v){
        string code = "A" + e;
        ll val = 0;
        rep(i, 0, sz(code) - 1){
            string sPair = "";
            sPair += code[i];
            sPair += code[i + 1];
            val += lengthMap[sPair];
        }
        ans += val * stoll(e.substr(0, sz(e) - 1));
    }
    cout << ans << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve(filename, 2);
    solve(filename, 25);
}