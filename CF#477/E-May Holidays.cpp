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
const int N = 1e5 + 7, M = 600;
int n, m, tim, edc;
int fa[N], vfa[N], adv[N], ptr[N], siz[N], on[N], w[N];
int qry[N], vac[N], cnt[N], rev[N], head[N];
vector<int>f[N];
struct edge {
	int lst, to;
	edge(){}edge(int lst, int to):lst(lst), to(to){}
}e[N << 1];
void Add(int a, int b) {
	e[++edc] = edge(head[a], b), head[a] = edc;
	e[++edc] = edge(head[b], a), head[b] = edc;
}
void dfs(int u) {
	rev[++tim] = u;
	go(u)if(v ^ fa[u]) dfs(v);
}
int main() {
	n = gi(), m = gi();
	rep(i, 2, n) fa[i] = gi(), Add(fa[i], i);
	rep(i, 1, n) w[i] = gi();
	rep(i, 1, m) qry[i] = abs(gi());
	dfs(1);
	
	for(int l = 1, r = min(m, M); l <= m; l = r + 1, r = min(m, l + M - 1)) {
		re(siz), re(adv), re(ptr), re(on), re(cnt), re(vfa);
		rep(i, 1, n) f[i].clear();
		int ans = 0;
		for(int i = l; i <= r; ++i) on[qry[i]] = cnt[qry[i]] = 1;
		
		for(int i = n; i; --i) {
			int x = rev[i];
			if(cnt[fa[x]] && cnt[x]) on[fa[x]] = 1;
			siz[fa[x]] += siz[x] + vac[x];
			cnt[fa[x]] += cnt[x];
		}
		for(int i = n; i; --i) if(on[rev[i]]){
			int x = rev[i];
			int u;
			for(u = fa[x]; u && !on[u]; u = fa[u]) if(!vac[u]) f[x].pb(w[u] - siz[u]);
			
			vfa[x] = u;
			if(!f[x].empty()) {
				sort(f[x].begin(), f[x].end());
				ptr[x] = lower_bound(f[x].begin(), f[x].end(), 0) - f[x].begin();
			}
		}
		rep(i, 1, n) ans += !vac[i] && w[i] < siz[i];

		for(int i = l; i <= r; ++i) {
			int x = qry[i], val = vac[x] ? -1 : 1;vac[x] ^= 1;
			if(w[x] < adv[x] + siz[x]) ans -= val;
			siz[x] -= val;
			for(int u = x; u; u = vfa[u]) {
				if(x != u && !vac[u] && w[u] < adv[u] + siz[u]) ans--;
				adv[u] += val;
				if(x != u && !vac[u] && w[u] < adv[u] + siz[u]) ans++;
				
				ans -= ptr[u];
				ptr[u] = lower_bound(f[u].begin(), f[u].end(), adv[u]) - f[u].begin();
				ans += ptr[u];
			}
			printf("%d%c", ans,  i == m ?'\n':' ');
		}
	}
	return 0;
}
