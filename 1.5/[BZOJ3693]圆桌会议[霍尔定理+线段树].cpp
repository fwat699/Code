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
const int N = 4e5 + 7;
int T, n, m, vc;
LL adv[N << 2], mx[N << 2], V[N << 1];
#define Ls o << 1
#define Rs (o << 1 | 1)
void st1(int o, LL v) {
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
	adv[o] = 0;
	if(l == r) {
		mx[o] = V[l];
		return;
	}int mid = l + r >> 1;
	build(l, mid, Ls);
	build(mid + 1, r, Rs);
	pushup(o);
}
void modify(int L, int R, int l, int r,int o, LL v) {
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
struct qs {
	int l, r;LL a;
	bool operator <(const qs &rhs) const {
		return r < rhs.r;
	}
}q[N];
int main() {
	T = gi();
	while(T--) {
		n = gi(), m = gi();int ndc = n, sum = 0;vc = 0;
		rep(i, 1, n) {
			q[i].l = gi(), q[i].r = gi(), q[i].a = gi();sum += q[i].a;
			if(q[i].l <= q[i].r) q[++ndc] = (qs){ q[i].l + m, q[i].r + m, q[i].a};
			else q[i].r += m;
		}
		n = ndc;
		if(sum > m) { puts("No"); goto A;}
		
		sort(q + 1, q + 1 + n);
		rep(i, 1, n) V[++vc] = q[i].l, V[++vc] = q[i].r;
		sort(V + 1, V + 1 + vc);
		vc = unique(V + 1, V + 1 + vc) - V - 1;
		build(1, vc, 1);
		
		rep(i, 1, n) {
			q[i].l = lower_bound(V + 1, V + 1 + vc, q[i].l) - V;
			int pos = lower_bound(V + 1, V + 1 + vc, q[i].r - m + 1) - V;
			q[i].r = lower_bound(V + 1, V + 1 + vc, q[i].r) - V;
			
			modify(1, q[i].l, 1, vc, 1, q[i].a);
			LL res = query(pos, q[i].r, 1, vc, 1);
			if(res > V[q[i].r] + 1){ puts("No"); goto A;}
		}
		puts("Yes");
		A:;
	}
	return 0;
}
