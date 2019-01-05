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
int n, m, d;
LL k;
struct data {
	LL mx, l, r, s;
	data operator +(const data &rhs) const {
		data res;
		res.mx = max(max(mx, rhs.mx), r + rhs.l);
		res.s = s + rhs.s;
		res.l = max(l, s + rhs.l);
		res.r = max(rhs.r, rhs.s + r);
		return res;
	}
}t[N << 2];
#define Ls o << 1
#define Rs o << 1 | 1
void pushup(int o) {
	t[o] = t[Ls] + t[Rs];
}
void build(int l, int r, int o) {
	if(l == r) {
		t[o].mx = t[o].s = -k;
		return;
	}int mid = l + r >> 1;
	build(l, mid, Ls);
	build(mid + 1, r, Rs);
	pushup(o);
}
void modify(int p, int l, int r, int o, int v) {
	if(l == r) {
		t[o].mx += v, t[o].s += v;
		t[o].l = t[o].r = t[o].s;
		return;
	}int mid = l + r >> 1;
	if(p <= mid) modify(p, l, mid, Ls, v);
	else modify(p, mid + 1, r, Rs, v);
	pushup(o);
}
int main() {
	n = gi(), m = gi(), k = gi(), d = gi();
	build(1, n, 1);
	while(m--) {
		int r = gi(), x = gi();
		modify(r, 1, n, 1, x);
		puts(t[1].mx > 1ll * d * k ? "NIE": "TAK");
	}
	return 0;
}
