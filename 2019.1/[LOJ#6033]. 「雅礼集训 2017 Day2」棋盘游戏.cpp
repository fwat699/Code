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
const int N = 1e4 + 7;
int dx[]={1, 0, -1, 0}, dy[]={0, -1, 0, 1};char s[104][104]; 
vector<int>G[N], ans;
int n, m, ndc, low, x[N], y[N];
int pp[N], id[104][104], vis[N], mark[N];
int find(int u) {
	int q;
	for(auto v:G[u]) if(vis[v] ^ low){
		vis[v] = low, q = pp[v], pp[v] = u, pp[u] = v;
		if(!q || find(q)) return 1;
		pp[v] = q; pp[q] = v, pp[u] = 0;
	}
	return 0;
}
void get(int u) {
	mark[u] = 1;ans.pb(u);
	for(auto v:G[u]) if(!mark[pp[v]]) get(pp[v]);
}
bool cmp(int a, int b) {
	if(x[a] != x[b]) return x[a] < x[b];
	return y[a] < y[b];
}
int main() {
	n = gi(), m = gi();
	rep(i, 1, n) scanf("%s", s[i] + 1);
	rep(i, 1, n) rep(j, 1, m) if(i + j & 1) id[i][j] = ++ndc, x[ndc] = i, y[ndc] = j;
	rep(i, 1, n) rep(j, 1, m) if(!(i + j & 1)) id[i][j] = ++ndc, x[ndc] = i, y[ndc] = j;
	
	rep(i, 1, n) rep(j, 1, m) if(s[i][j] != '#'){
		rep(d, 0, 3) {
			int tx = i + dx[d], ty = j + dy[d];
			if(tx && ty && tx <= n && ty <= m && s[tx][ty] != '#') G[id[i][j]].pb(id[tx][ty]);
		}
	}
	rep(i, 1, n) rep(j, 1, m) if((i + j & 1) && s[i][j] == '.') {
		++low;	find(id[i][j]);
	}
	rep(i, 1, n) rep(j, 1, m) if(s[i][j] == '.' && !pp[id[i][j]]) get(id[i][j]);
	printf("%d\n", ans.size());
	sort(ans.begin(), ans.end(), cmp);
	for(auto v:ans) printf("%d %d\n", x[v], y[v]);
	return 0;
}
