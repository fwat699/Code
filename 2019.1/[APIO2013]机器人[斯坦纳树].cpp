#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define go(u) for(register int i = head[u], v = e[i].to; i; i=e[i].lst, v=e[i].to)
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
template <typename T> inline bool Max(T &a, T b){return a < b ? a = b, 1 : 0;}
template <typename T> inline bool Min(T &a, T b){return a > b ? a = b, 1 : 0;}
const int N = 504, inf = 0x3f3f3f3f;
int n, R, C, low;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
char s[N][N];
int vis[4][N][N], f[10][10][N][N];
struct data {
	int x, y;
	data(){}data(int x, int y):x(x), y(y){}
	data operator +(int d) const {
		return data(x + dx[d], y + dy[d]);
	}
}g[4][N][N];
bool ok(data u) {
	return u.x > 0 && u.y > 0 && u.x <= R && u.y <= C && s[u.x][u.y] != 'x';
}
data dfs(data u, int d) {
	data &res = g[d][u.x][u.y];
	if(vis[d][u.x][u.y] == low) return data(-inf, -inf);
	vis[d][u.x][u.y] = low;
	if(res.x != 0) return res;
	int t = s[u.x][u.y] == 'A' ? (d + 1) % 4 : s[u.x][u.y] == 'C' ? (d - 1 + 4) % 4 : d;
	data v = u;
	while(1) {
		data tmp = v + t;
		if(ok(tmp)) v = tmp;
		else break;
		if(s[v.x][v.y] == 'A' || s[v.x][v.y] == 'C') break;
	}
	if(s[v.x][v.y] == '.' || isdigit(s[v.x][v.y]) || (u.x == v.x && u.y == v.y)) res = v;
	else
	res = dfs(v, t);
	return res;
}
data q[N * N];
queue<data>Q1, Q2;
int mark1[N][N], mark2[N][N];
void dijk(int (*f)[N]) {
	int tp = 0;
	rep(i, 1, R)rep(j, 1, C) if(f[i][j] != inf) q[++tp] = data(i, j);
	sort(q + 1, q + 1 + tp, [&](const data &a, const data &b){ return f[a.x][a.y] < f[b.x][b.y];});
	rep(i, 1, tp) Q1.push(q[i]);
	while(!Q1.empty() || !Q2.empty()) {
		data u;
		if(Q1.empty()) u = Q2.front(), Q2.pop();
		else if(Q2.empty()) u = Q1.front(), Q1.pop();
		else {
			data a = Q1.front(), b = Q2.front();
			if(f[a.x][a.y] < f[b.x][b.y]) {
				u = a;
				Q1.pop();
			}else {
				u = b;
				Q2.pop();
			}
		}
		if(mark2[u.x][u.y] == low) continue;
		mark2[u.x][u.y] = low;
		rep(d, 0, 3) {
			data v = g[d][u.x][u.y];
			if(ok(v) && Min(f[v.x][v.y], f[u.x][u.y] + 1)) {
				if(mark1[v.x][v.y] ^ low) {
					mark1[v.x][v.y] = low;
					Q2.push(v);
				}
			}
		}
	}
}
int main() {
	n = gi(), C = gi(), R = gi();
	rep(i, 1, R) scanf("%s", s[i] + 1);
	rep(i, 1, R) rep(j, 1, C){
		rep(d, 0, 3) 
		if(s[i][j] != 'x')
		++low, dfs(data(i, j), d);
		else g[d][i][j] = data(-inf, -inf);
	}
	memset(f, 0x3f, sizeof f);
	rep(len, 1, n) rep(l, 1, n - len + 1) {
		int r = l + len - 1;
		rep(i, 1, R) rep(j, 1, C) {
			int &t = f[l][r][i][j];
			if(len == 1) t = s[i][j] - '0' == l ? 0 : inf;
			else {
				rep(x, l, r - 1)
				Min(t, f[l][x][i][j] + f[x + 1][r][i][j]);
			}
		}
		++low, dijk(f[l][r]);
	}
	int ans = inf;
	rep(i, 1, R) rep(j, 1, C) Min(ans, f[1][n][i][j]);
	printf("%d\n", ans == inf ? -1 : ans);
	return 0;
}
