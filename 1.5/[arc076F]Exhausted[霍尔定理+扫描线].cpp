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
int n, m, ans;
int adv[N << 2], mx[N << 2];
#define Ls o << 1
#define Rs (o << 1 | 1)
void st1(int o, int v) {
	adv[o] += v;
	mx[o] += v;
}
void pushdown(int o) {
	if(!adv[o]) return;
	st1(Ls, adv[o]);
	st1(Rs, adv[o]);
	adv[o] = 0;
}
void pushup(int o) {
	mx[o] = max(mx[Ls], mx[Rs]);
}
void build(int l, int r,int o){ 
	if(l == r) {
		mx[o] = l;
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
	if(L <= l && r <= R) return mx[o];
	pushdown(o);int mid = l + r >> 1;
	if(R <= mid) return query(L, R, l, mid, Ls);
	if(L > mid)  return query(L, R, mid + 1, r, Rs);
	return max(query(L, R, l, mid, Ls), query(L, R, mid + 1, r, Rs));
}
vector<int> h[N];
int main() {
	n = gi(), m = gi();
	rep(i, 1, n) {
		int l = gi(), r = gi();
		h[l].pb(r);
	}
	build(0, m + 1, 1);
	rep(l, 0, m + 1) {
		for(auto r: h[l] ) {
			modify(0, r, 0, m + 1, 1, 1);
		}
		Max(ans, query(l + 1, m + 1, 0, m + 1, 1) - l - m - 1);
	}
	printf("%d\n", max(n - m, ans));
	return 0;
}
