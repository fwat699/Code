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
const int N = 4e4 + 7;
int n, m;
int a[N], R[N], L[N], sa[N], k[N], tt[N], rk[N];
#define Ls o << 1
#define Rs (o << 1 | 1)
struct sgt {
	int adv[N << 2], val[N << 2], id;
	void st1(int o, int v) {
		adv[o] += v;
		val[o] += v;
	}
	void pushdown(int o) {
		if(adv[o]) {
			st1(Ls, adv[o]);
			st1(Rs, adv[o]);
		}
		adv[o] = 0;
	}
	void pushup(int o) {
		if(!id) val[o] = max(val[Ls], val[Rs]);
		else val[o] = min(val[Ls], val[Rs]);
	}
	void build(int l, int r, int o) {
		if(l == r) {
			if(!id) val[o] = -sa[R[tt[l]]];
			else val[o] = -sa[L[tt[l]] - 1];
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
	int query(int L, int R, int l, int r, int o) {
		if(L > R) return 0;
		if(L <= l && r <= R) return val[o];
		pushdown(o);int mid = l + r >> 1;
		if(R <= mid) return query(L, R, l, mid, Ls);
		if(L > mid)  return query(L, R, mid + 1, r, Rs);
		if(!id) return max(query(L, R, l, mid, Ls), query(L, R, mid + 1, r, Rs));
		else return min(query(L, R, l, mid, Ls), query(L, R, mid + 1, r, Rs));
	}
}t[2];
bool cmp(int a, int b) {
	return L[a] < L[b];
}
int main() {
	n = gi();
	int x = gi(), y = gi(), z = gi(), P = gi();
	rep(i, 1, n) {
		a[i] = ((i - x) * (i - x) + (i - y) * (i - y) + (i - z) * (i - z)) % P;
		sa[i] = sa[i - 1] + a[i];
	}
	
	m = gi(), k[1] = gi(), k[2] = gi(), x = gi(), y = gi(), z = gi(), P = gi();
	if(!m) return 0;
	rep(i, 3, m) {
		k[i] = (x * k[i - 1] + y * k[i - 2] + z) % P;
	}
	rep(i, 1, m) L[i] = gi(), R[i] = gi();
	rep(i, 1, m) tt[i] = i;
	sort(tt + 1, tt + 1 + m, cmp);
	rep(i, 1, m) rk[tt[i]] = i;
	t[1].id = 1; t[0].build(1, m, 1); t[1].build(1, m, 1);
	rep(i, 1, m) {
		int a = t[0].query(rk[i], m, 1, m, 1), b = t[1].query(1, rk[i], 1, m, 1);
		int ans = min(b - a, k[i]);
		printf("%d\n", ans);
		t[0].modify(rk[i], m, 1, m, 1, ans);
		t[1].modify(rk[i] + 1, m, 1, m, 1, ans);
	}
	return 0;
}
