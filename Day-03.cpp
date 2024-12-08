//
// Created by Prakul Agrawal on 12/8/24.
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
        int cnt = 0;
        ll x = 0, y = 0;
        int flag = 0;
        for(char c: line){
            if (cnt == 0 && c == 'm' || cnt == 1 && c == 'u' || cnt == 2 && c == 'l' || cnt == 3 && c == '('){
                cnt++;
            }
            else if (cnt == 4){
                if (isdigit(c)){
                    flag = 1;
                    x = x * 10 + c - '0';
                }
                else if (c == ',' && flag){
                    flag = 0;
                    cnt++;
                }
                else{
                    cnt = 0;
                    x = 0;
                    y = 0;
                }
            }
            else if (cnt == 5){
                if (isdigit(c)){
                    flag = 1;
                    y = y * 10 + c - '0';
                }
                else if (c == ')' && flag){
                    flag = 0;
                    cnt++;
                }
                else{
                    cnt = 0;
                    x = 0;
                    y = 0;
                }
            }
            else{
                cnt = 0;
                x = 0;
                y = 0;
            }
            if (cnt == 6){
                ans += x * y;
                cnt = 0;
                x = 0;
                y = 0;
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
    int enabled = 1;
    while (getline(iss, line)) {
        int cnt = 0;
        ll x = 0, y = 0;
        int flag = 0;
        int zone = 0;
        for(char c: line){
            if (zone == 1 || cnt == 0 && c == 'm' && enabled) {
                zone = 1;
                if (cnt == 0 && c == 'm' || cnt == 1 && c == 'u' || cnt == 2 && c == 'l' || cnt == 3 && c == '(') {
                    cnt++;
                } else if (cnt == 4) {
                    if (isdigit(c)) {
                        flag = 1;
                        x = x * 10 + c - '0';
                    } else if (c == ',' && flag) {
                        flag = 0;
                        cnt++;
                    } else {
                        cnt = 0;
                        x = 0;
                        y = 0;
                        zone = 0;
                    }
                } else if (cnt == 5) {
                    if (isdigit(c)) {
                        flag = 1;
                        y = y * 10 + c - '0';
                    } else if (c == ')' && flag) {
                        flag = 0;
                        cnt++;
                    } else {
                        cnt = 0;
                        x = 0;
                        y = 0;
                        zone = 0;
                    }
                } else {
                    cnt = 0;
                    x = 0;
                    y = 0;
                    zone = 0;
                }
                if (cnt == 6) {
                    ans += x * y;
                    cnt = 0;
                    x = 0;
                    y = 0;
                    zone = 0;
                }
            }
            else if (zone == 2 || cnt == 0 && c == 'd'){
                zone = 2;
                if (cnt == 0 && c == 'd' || cnt == 1 && c == 'o') {
                    cnt++;
                }
                else if (cnt == 2 && c == 'n') {
                    cnt++;
                    zone = 3;
                }
                else if (cnt == 2 && c == '('){
                    cnt++;
                }
                else if (cnt == 3 && c == ')'){
                    enabled = 1;
                    cnt = 0;
                    zone = 0;
                }
                else{
                    cnt = 0;
                    zone = 0;
                }
            }
            else if (zone == 3){
                if (cnt == 3 && c == '\'' || cnt == 4 && c == 't' || cnt == 5 && c == '('){
                    cnt++;
                }
                else if (cnt == 6 && c == ')'){
                    enabled = 0;
                    cnt = 0;
                    zone = 0;
                }
                else{
                    cnt = 0;
                    zone = 0;
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