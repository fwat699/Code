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
const int N = 1e6 + 7;
int n, K, C, cnt, ID;
int a[N], pos[N];
vector<LL>w[333];
LL f[2][50004];
bool cmp(int a, int b) {
	return a > b;
}
struct data {
	int l, p;
}q[N];
LL calc(int p, int a) {
	return f[ID - 1 & 1][pos[a]] + w[ID][min((int)w[ID].size() - 1, p - a - 1)];
}
bool better(int p, int a, int b) {
	return calc(p, a) >= calc(p, b);
}
int find(int l, int r, int a, int b) {
	while(l < r) {
		int mid = l + r >> 1;
		if(better(mid, a, b)) r = mid;
		else l = mid + 1;
	}
	return l;
}
void solve() {
	int hd = 1, tl = 0;
	rep(i, 1, cnt) {
		for(; hd < tl && q[hd + 1].l <= i; ++hd);
		if(i ^ 1) Max(f[ID & 1][pos[i]], calc(i, q[hd].p));
		for(; hd <= tl && better(max(i + 1, q[tl].l), i, q[tl].p); --tl);
		if(hd > tl) q[++tl] = (data){ i + 1, i};
		else if(i < cnt && better(cnt, i, q[tl].p)) q[tl + 1] = (data){ find(max(i + 1, q[tl].l), cnt, i, q[tl].p), i}, ++tl;
	}
}
int main() {
	n = gi(), K = gi();
	rep(i, 0, 300) w[i].pb(0);
	rep(i, 1, n) {
		int v = gi(), x = gi();
		w[v].pb(x);
		Max(C, v);
	}
	rep(i, 1, C) {
		ID = i;
		sort(w[i].begin(), w[i].end(), cmp);
		for(int j = 1; j < w[i].size(); ++j) w[i][j] += w[i][j - 1];
		rep(j, 0, K) f[i & 1][j] = f[i - 1 & 1][j];
		rep(j, 0, i - 1) {
			cnt = 0;
			for(int k = j; k <= K; k += i) pos[++cnt] = k;
			if(cnt) solve();
		}
	}
	for(int i = 1; i <= K; ++i) printf("%lld%c", f[C & 1][i], i == K ? '\n':' ');
	return 0;
}
