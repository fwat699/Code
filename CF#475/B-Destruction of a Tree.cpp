#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define go(u) for(int i = head[u], v = e[i].to; i; i=e[i].lst, v=e[i].to)
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define pb push_back
#define re(x) memset(x, 0, sizeof x)
inline int gi() {
    int x = 0,f = 1;
    char ch = getchar();
    while(!isdigit(ch)) { if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) { x = (x << 3) + (x << 1) + ch - 48; ch = getchar();}
    return x * f;
}
template <typename T> inline void Max(T &a, T b){if(a < b) a = b;}
template <typename T> inline void Min(T &a, T b){if(a > b) a = b;}
const int N = 2e5 + 7;
int n, edc, rt;
int head[N], son[N];
struct edge {
	int lst, to;
	edge(){}edge(int lst, int to):lst(lst), to(to){}
}e[N << 1];
void Add(int a, int b) {
	e[++edc] = edge(head[a], b), head[a] = edc;
	e[++edc] = edge(head[b], a), head[b] = edc;
}
void dfs1(int u, int fa) {
	son[u] = 1;
	go(u)if(v ^ fa) {
		dfs1(v, u);
		son[u] += son[v];
	}
}
void solve(int u, int fa) {
	go(u)if(v ^ fa) {
		if(son[v] % 2 == 0) solve(v, u);
	}
	printf("%d\n", u);
	go(u)if(v ^ fa) {
		if(son[v] & 1) solve(v, u);
	}
}
int main() {
	n = gi();
	if(n % 2 == 0) return puts("NO"), 0;
	puts("YES");
	rep(i, 1, n) {
		int x = gi();
		if(x) Add(x, i);
		else rt = i;
	}
	dfs1(rt, 0);
	solve(rt, 0);
	return 0;
}
