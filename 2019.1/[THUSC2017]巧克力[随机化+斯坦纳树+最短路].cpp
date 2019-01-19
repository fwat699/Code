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
typedef pair<int, int> pii;
#define mp make_pair
#define fi first
#define se second
const int N = 240, inf = 0x3f3f3f3f;
int T, n, m, K;
int a[N][N], b[N][N], t1[N][N], t2[N][N], c[N], val[N];
pii f[1 << 5][N][N];
pii operator +(pii a, pii b) {
	return mp(a.fi + b.fi, a.se + b.se);
}
pii operator -(pii a, pii b) {
	return mp(a.fi - b.fi, a.se - b.se);
}
int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
struct data {
	int x, y; pii dis;
	bool operator <(const data &rhs) const {
		return rhs.dis < dis;
	}
};
priority_queue<data>Q;
bool ok(int x, int y) {
	return x && y && x <= n && y <= m && t1[x][y] != -1;
}
void dijk(int S) {
	rep(i, 1, n)rep(j, 1, m) if(t1[i][j] != -1) Q.push((data){ i, j, f[S][i][j]});
	while(!Q.empty()) {
		data u = Q.top();Q.pop();
		if(f[S][u.x][u.y] < u.dis) continue;
		rep(d, 0, 3) {
			int tx = u.x + dx[d], ty = u.y + dy[d];
			if(ok(tx, ty) && f[S][u.x][u.y] + mp(1, t2[tx][ty]) < f[S][tx][ty]) {
				f[S][tx][ty] = f[S][u.x][u.y] + mp(1, t2[tx][ty]);
				Q.push((data){ tx, ty, f[S][tx][ty]});
			}
		}
	}
}
pii steiner() {
	for(int S = 0; S < 1 << K; ++S)rep(i, 1, n)rep(j, 1, m) f[S][i][j] = mp(inf, inf);
	rep(i, 1, n) rep(j, 1, m) if(t1[i][j] != -1) f[1 << t1[i][j]][i][j] = mp(1, t2[i][j]);
	for(int S = 0; S < 1 << K; ++S) {
		rep(i, 1, n) rep(j, 1, m)
		for(int s = S; s; s = (s - 1) & S) if(t1[i][j] != -1) 
		Min(f[S][i][j], f[s][i][j] + f[S ^ s][i][j] - mp(1, t2[i][j]));
		dijk(S);
	}
	pii ans(inf, inf);
	rep(i, 1, n) rep(j, 1, m) Min(ans, f[(1 << K) - 1][i][j]);
	return ans;
}
pii check(int mid) {
	rep(i, 1, n) rep(j, 1, m) t2[i][j] = b[i][j] <= val[mid] ? -1 : 1;
	pii res = steiner();
	if(res.fi == inf || res.se > 0) return mp(inf, inf);
	return mp(res.fi, val[mid]);
}
int main() {
	T = gi();
	while(T--) {
		n = gi(), m = gi(), K = gi();
		rep(i, 1, n) rep(j, 1, m) a[i][j] = gi();
		rep(i, 1, n) rep(j, 1, m) b[i][j] = gi(), val[(i - 1) * m + j] = b[i][j];
		sort(val + 1, val + 1 + n * m);
		pii ans(inf, inf);
		for(int tt = 1; tt <= 130; ++tt) {
			rep(i, 1, n * m) c[i] = rand() % K;
			rep(i, 1, n) rep(j, 1, m) t1[i][j] = a[i][j] == -1 ? - 1 : c[a[i][j]];
			if(check(n * m).fi == inf) continue;
			int l = 1, r = n * m;
			while(l < r) {
				int mid = l + r >> 1;
				if(check(mid).fi != inf) r = mid;
				else l = mid + 1;
			}
			Min(ans, check(l));
		}
		printf("%d %d\n", ans.fi, ans.se);
	}
	return 0;
}
