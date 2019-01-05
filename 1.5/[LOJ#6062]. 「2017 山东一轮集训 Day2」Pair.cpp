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
int n, m, h, ans;
int a[N], b[N];
int mi[N << 2], adv[N << 2];
#define Ls o << 1
#define Rs (o << 1 | 1)
void st1(int o, int v) {
	adv[o] += v;
	mi[o] += v;
}
void pushdown(int o) {
	if(!adv[o]) return;
	st1(Ls, adv[o]);
	st1(Rs, adv[o]);
	adv[o] = 0;
}
void pushup(int o) {
	mi[o] = min(mi[Ls], mi[Rs]);
}
void build(int l, int r,int o){ 
	if(l == r) {
		mi[o] = -(m - l + 1);
		return;
	}int mid = l + r >> 1;
	build(l, mid, Ls);
	build(mid + 1, r, Rs);
	pushup(o);
}
void modify(int L, int R, int l, int r,int o, int v) {
	if(L > R) return;
	if(L <= l && r <= R) {
		st1(o, v);
		return;
	}
	pushdown(o);int mid = l + r >> 1;
	if(L <= mid) modify(L, R, l, mid, Ls, v);
	if(R > mid)  modify(L, R, mid + 1, r, Rs, v);
	pushup(o);
}
int main() {
#ifndef ONLINE_JUDGE
#endif
	n = gi(), m = gi(), h = gi();
	rep(i, 1, m) b[i] = gi();
	rep(i, 1, n) a[i] = gi();
	sort(b + 1, b + 1 + m);
	rep(i, 1, n)  a[i] = m - (lower_bound(b + 1, b + 1 + m, h - a[i]) - b) + 1;
	build(1, m, 1);
	rep(i, 1, m - 1) modify(1, a[i], 1, m, 1, 1);
	rep(i, m, n) {
		if(i ^ m) modify(1, a[i - m], 1, m, 1, -1);
		modify(1, a[i], 1, m, 1, 1);
		if(mi[1] >= 0) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}
