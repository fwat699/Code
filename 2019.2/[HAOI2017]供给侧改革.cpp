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
template <typename T> inline bool Max(T &a, T b){return a < b ? a = b, 1 : 0;}
template <typename T> inline bool Min(T &a, T b){return a > b ? a = b, 1 : 0;}
const int N = 1e5 + 7;
int n, Q, ndc;
int ch[N * 40][2], f[50], g[N * 40], ans[N];
char s[N];
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
vector<pii>q[N];
void insert(int x) {
	int u = 0;
	for(int i = 1; i <= min(n - x + 1, 40); ++i) {
		int &v = ch[u][s[x + i - 1] - '0'];
		if(!v) v = ++ndc;
		else Max(f[i], g[v]);
		g[v] = x;
		u = v;
	}
}
int main() {
	n = gi(), Q = gi();
	scanf("%s", s + 1);
	rep(i, 1, Q) {
		int L = gi(), R = gi();
		q[R].pb(mp(L, i));
	}
	for(int i = 1; i <= n; ++i) {
		insert(i);
		for(auto v:q[i]) {
			int now = i - 1, t = 0;
			while(now >= v.fi) {
				ans[v.se] += t * (now - max(f[t + 1], v.fi - 1));
				now = f[++t];
			}
		}
	}
	rep(i, 1, Q) printf("%d\n", ans[i]);
	return 0;
}
