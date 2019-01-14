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
const int N = 2e5 + 7, Nd = N << 2, inf = 0x3f3f3f3f;
int n, m, type, lstans;
int t[N], mx[Nd], lf[Nd], ans[Nd];
#define Ls o << 1
#define Rs o << 1 | 1
int find(int l, int r, int o, int v) {
	if(l == r) return mx[o] >= v ? l : 0;
	int mid = l + r >> 1;
	if(mx[Rs] >= v) return find(mid + 1, r, Rs, v);
	return find(l, mid, Ls, v);
}
int query(int l, int r, int o, int v) {
	if(l == r) return mx[o] >= v ? ans[o] : inf;
	int mid = l + r >> 1;
	if(mx[Rs] >= v) return min(lf[o], query(mid + 1, r, Rs, v));
	return query(l, mid, Ls, v);
}
void pushup(int l, int r, int o) {
	mx[o] = max(mx[Ls], mx[Rs]);
	int x = mx[Rs], mid = l + r >> 1, pos = max(l - 1, find(l, mid, Ls, x));
	lf[o] = min(query(l, mid, Ls, x), pos + x + 1);
	ans[o] = min(lf[o], ans[Rs]);
}
void build(int l, int r, int o) {
	if(l == r) {
		mx[o] = t[l] - l, ans[o] = t[l];
		return;
	}int mid = l + r >> 1;
	build(l, mid ,Ls);
	build(mid + 1, r, Rs);
	pushup(l, r, o);
}
void modify(int p, int l, int r, int o) {
	if(l == r) { 
		mx[o] = t[l] - l, ans[o] = t[l];
		return;
	}int mid = l + r >> 1;
	if(p <= mid) modify(p, l, mid, Ls);
	else modify(p, mid + 1, r, Rs);
	pushup(l, r, o);
}
int main() {
	n = gi(), m = gi(), type = gi();
	rep(i, 1, n) t[i] = t[i + n] = gi();
	build(1, 2 * n, 1);
	printf("%d\n", lstans = lf[1] + n - 1);
	while(m--) {
		int x = gi(), y = gi();
		if(type) x ^= lstans, y ^= lstans;
		t[x] = t[x + n] = y;
		modify(x, 1, 2 * n, 1);
		modify(x + n, 1, 2 * n, 1);
		printf("%d\n", lstans = lf[1] + n - 1);
	}
	return 0;
}
