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
const int N = 3e5 + 7;
int n;
int adv[N << 2], c[N], id[N];
#define Ls o << 1
#define Rs o << 1 | 1
struct data {
	int mx, pos;
	data operator +(const data &b) const {
		data res;
		res.mx = max(mx, b.mx);
		if(res.mx == mx) res.pos = pos;
		else res.pos = b.pos;
		return res;
	}
}t[N << 2];
void st1(int o, int v) {
	t[o].mx += v;
	adv[o] += v;
}
void pushdown(int o) {
	if(!adv[o]) return;
	st1(Ls, adv[o]);
	st1(Rs, adv[o]);
	adv[o] = 0;
}
void build(int l, int r, int o) {
	adv[o] = 0;
	if(l == r) {t[o] = (data){ -l, l}; return;}
	int mid = l + r >> 1;
	build(l, mid, Ls);
	build(mid + 1, r, Rs);
	t[o] = t[Ls] + t[Rs];
}
void modify(int L, int R, int l, int r, int o, int v) {
	if(L > R) return;
	if(L <= l && r <= R) {st1(o, v); return;}
	pushdown(o);int mid = l + r >> 1;
	if(L <= mid) modify(L, R, l, mid, Ls, v);
	if(R > mid)  modify(L, R, mid + 1, r, Rs, v);
	t[o] = t[Ls] + t[Rs];
}
data query(int L, int R, int l, int r, int o) {
	if(L <= l && r <= R) return t[o];
	pushdown(o);int mid = l + r >> 1;
	if(R <= mid) return query(L, R, l, mid, Ls);
	if(L > mid)  return query(L, R, mid + 1, r, Rs);
	return query(L, R, l, mid, Ls) + query(L, R, mid + 1, r, Rs);
}
int up(int a, int b) {
	return a / b + (bool)(a % b);
}
void calc(int x1, int x2, int k1, int k2, bool swp) {
	puts("Yes");
	if(!swp) {
		printf("%d %d\n", k1, k2);
		for(int i = 1; i <= k1; ++i) printf("%d%c", id[i], i == k1 ? '\n':' ');
		for(int i = k1 + 1; i <= k1 + k2; ++i) printf("%d%c", id[i], i == k1 + k2 ? '\n':' ');
	}else {
		printf("%d %d\n", k2, k1);
		for(int i = k1 + 1; i <= k1 + k2; ++i) printf("%d%c", id[i], i == k1 + k2 ? '\n':' ');
		for(int i = 1; i <= k1; ++i) printf("%d%c", id[i], i == k1 ? '\n':' ');
	}
}
bool solve(int x1, int x2, bool swp) {
	build(1, n, 1);
	rep(i, 1, n) modify(up(x2, c[i]), n, 1, n, 1, 1);
	int k1, k2, cnt = 0;
	for(int i = 1, j = 1; i <= n; ++i) {
		while(j <= n && up(x1, i) < up(x2, j)) ++j;
		while(cnt + 1 <= n && c[cnt + 1] >= up(x1, i)) ++cnt;
		if(j > n - i) return 0;
		if(cnt < i) continue;
		
		data res = query(j, n - i, 1, n, 1);
		if(res.mx >= i) {
			k1 = i, k2 = res.pos;
			calc(x1, x2, k1, k2, swp);
			return 1;
		}
	}
	return 0;
}
int main() {
	n = gi();int a = gi(), b = gi();
	rep(i, 1, n) c[i] = gi(), id[i] = i;
	sort(id + 1, id + 1 + n, [&] (const int &a, const int &b) {	return c[a] > c[b];});
	sort(c + 1, c + 1 + n,   [&] (const int &a, const int &b) { return a > b;});
	if(solve(a, b, 0)) return 0;
	if(solve(b, a, 1)) return 0;
	puts("No");
	return 0;
}
