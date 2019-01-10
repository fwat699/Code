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
const int N = 3e5 + 7, inf = 0x3f3f3f3f;
int n, m, edc, gg, tl;
int head[N], dis[N], from[N], du[N], sa[N],  q[N];
vector<int> ans;
struct edge {
	int lst, to;
	edge(){}edge(int lst, int to):lst(lst), to(to){}
}e[N << 1];
void Add(int a, int b) {
	e[++edc] = edge(head[a], b), head[a] = edc;
	e[++edc] = edge(head[b], a), head[b] = edc;
	++du[a], ++du[b];
}
queue<int>Q;
void bfs(int u) {
	Q.push(u);
	while(!Q.empty()) {
		int u = Q.front();Q.pop();
		go(u)if(dis[v] == inf) {
			dis[v] = dis[u] + 1;
			from[v] = u;
			Q.push(v);
		}
	}
}
void out(int u) {
	if(u != 1) out(from[u]);
	ans.pb(u);
}
int main() {
#ifndef ONLINE_JUDGE
#endif
	n = gi(), m = gi();
	rep(i, 1, m) Add(gi(), gi());
	memset(dis, 0x3f, sizeof dis);dis[1] = 0;
	bfs(1); 
	gg = dis[n]; 
	if(gg != inf) out(n);
	
	if(gg <= 4) { printf("%d\n", gg);  for(int i = 0; i < ans.size(); ++i) printf("%d%c", ans[i], i == ans.size() - 1 ?'\n':' ');return 0;}
	rep(i, 1, n) if(dis[i] == 2) {
		printf("4\n"), printf("%d %d %d %d %d\n", 1, from[i], i, 1, n);
		return 0;
	}if(gg <= 5){ printf("%d\n", gg);  for(int i = 0; i < ans.size(); ++i) printf("%d%c", ans[i], i == ans.size() - 1 ?'\n':' ');return 0;}
	
	rep(i, 1, n) if(dis[i] == 1) q[++tl] = i;
	sort(q + 1, q + 1 + tl, [&](const int &a, const int &b) { return du[a] < du[b];});
	
	memset(dis, 0x3f, sizeof dis);dis[1] = 0;
	rep(i, 1, tl) {
		if(dis[q[i]] == inf) dis[q[i]] = 0, bfs(q[i]);
	}
	
	rep(i, 1, tl) if(dis[q[i]] == 2) {
		int u = q[i];
		printf("5\n"), printf("%d %d %d %d %d %d\n", 1, from[from[u]], from[u], u, from[from[u]], n);
		return 0;
	}
	if(gg != inf) { printf("%d\n", gg);  for(int i = 0; i < ans.size(); ++i) printf("%d%c", ans[i], i == ans.size() - 1 ?'\n':' ');return 0;}
	else puts("-1");
	return 0;
}
