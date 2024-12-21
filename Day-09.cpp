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
    ll mul = 0;
    while (getline(iss, line)) {
        int posL = 0;
        int posR = sz(line) % 2 ? sz(line) - 1 : sz(line) - 2;
        while(posL <= posR) {
            if (posL % 2 == 0) {
                ll index = posL / 2;
                ll val = line[posL] - '0';
                ans += index * val * (2 * mul + val - 1) / 2;
                posL++;
                mul += val;
            }
            else {
                ll index = posR / 2;
                ll val1 = line[posL] - '0', val2 = line[posR] - '0';
                if (val1 < val2){
                    ans += index * val1 * (2 * mul + val1 - 1) / 2;
                    posL++;
                    mul += val1;
                    line[posR] = (val2 - val1) + '0';
                }
                else if (val1 > val2) {
                    ans += index * val2 * (2 * mul + val2 - 1) / 2;
                    posR -= 2;
                    mul += val2;
                    line[posL] = (val1 - val2) + '0';
                }
                else {
                    ans += index * val1 * (2 * mul + val1 - 1) / 2;
                    posL++;
                    posR -= 2;
                    mul += val1;
                }
            }
        }
    }
    cout << ans << endl;
}

void solve2() {
    string s = readFile("input.txt");
    istringstream iss(s);
    string line;
    ll ans = 0;
    vi file;
    vi indices;
    while (getline(iss, line)) {
        int flag = 1;
        int index = 0;
        for(auto c : line){
            int val = c - '0';
            if (flag) {
                rep(i,0,val){
                    file.pb(index);
                }
                index++;
            }
            else {
                rep(i,0,val){
                    file.pb(-1);
                }
            }
            flag = 1 - flag;
        }
        map<int, set<int>> freeSpaces;
        int last = -2;
        int fileSize = sz(file);
        int pos = 1;
        rep(i,0,fileSize){
            while(pos < sz(line) && line[pos] == '0'){
                pos += 2;
            }
            if (file[i] == -1 && last != -1){
                freeSpaces[line[pos] - '0'].insert(i);
                pos += 2;
            }
            last = file[i];
        }
        pos = sz(line) % 2 ? sz(line) - 1 : sz(line) - 2;
        int revPos = fileSize - 1;
        if (sz(line) % 2 == 0){
            revPos -= line[pos] - '0';
        }
        indices.assign(fileSize, 0);
        for(int i = pos; i >= 0; i -= 2){
            int val = line[i] - '0';
            index = i / 2;
            int updateKey = 0;
            int updatePos = fileSize;
            for(auto [key, value] : freeSpaces){
                if (key >= val && !value.empty() && *value.begin() < revPos){
                    if(updatePos > *value.begin()){
                        updatePos = *value.begin();
                        updateKey = key;
                    }
                }
            }
            if (updatePos == fileSize){
                rep(j,0,val){
                    indices[revPos - j] = index;
                }
                revPos -= val;
                if (i - 1 >= 0){
                    revPos -= line[i - 1] - '0';
                }
                continue;
            }
            rep(j,0,val){
                indices[updatePos + j] = index;
            }
            if (updateKey > val){
                freeSpaces[updateKey - val].insert(updatePos + val);
            }
            freeSpaces[updateKey].erase(updatePos);
            revPos -= val;
            if (i - 1 >= 0){
                revPos -= line[i - 1] - '0';
            }
        }
    }
    int fileSize = sz(file);
    rep(i,0,fileSize){
        if (indices[i] == -1){
            continue;
        }
        ans += (ll) i * indices[i];
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0); // To increase input-output speed
    cin.tie(0);
    solve1();
    solve2();
}