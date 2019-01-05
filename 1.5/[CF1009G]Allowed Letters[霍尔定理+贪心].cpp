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
const int N = 1e5 + 7;
int n, m;
int cnt[N][1 << 6], val[N], num[6], ans[N];
char s[N], s2[N];

int main() {
	scanf("%s", s + 1); 
	n = strlen(s + 1);
	rep(i, 1, n) num[s[i] - 'a'] ++;
	m = gi();
	rep(i, 1, m) {
		int x = gi();
		scanf("%s", s2 + 1);
		int len = strlen(s2 + 1);
		rep(j, 1, len) val[x] |= (1 << s2[j] - 'a');
	}
	for(int i = n; i; --i) {
		if(!val[i]) val[i] = (1 << 6) - 1;
		for(int j = 0; j < 1 << 6; ++j) {
			cnt[i][j] = cnt[i + 1][j];
			if((j & val[i]) == val[i]) cnt[i][j] ++;
		}
	}
	rep(i, 1, n) {
		for(int j = 0; j < 6; ++j) if(cnt[j] && val[i] >> j & 1){
			num[j]--;bool fg = 1;
			for(int S = 0; S < 1 << 6; ++S) {
				int c = 0;
				for(int k = 0; k < 6; ++k) if(S >> k & 1) c += num[k];
				if(c < cnt[i + 1][S]) fg = 0;
			}
			if(fg) {ans[i] = j; goto A;}
			num[j]++;
		}
		return puts("Impossible"), 0;
		A:;
	}
	rep(i, 1, n) printf("%c", ans[i] + 'a');
	puts("");
	return 0;
}
