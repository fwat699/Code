#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <= b; ++i)
template <typename T> inline bool Max(T &a, T b){return a < b ? a = b, 1 : 0;}
const int N = 20004;
int n, ndc;
int g[N][2004], f[2004][N], ch[N][10], fail[N], ok[2004][N];
char L[N], R[N];
int to(int u, int c) {
	if(!ch[u][c]) ch[u][c] = ++ndc;
	return ch[u][c];
}
void insert() {
	int l1 = strlen(L + 1), l2 = strlen(R + 1);
	rep(i, 1, l1) L[i] -= 48;
	rep(i, 1, l2) R[i] -= 48;
	int u1 = 0, u2 = 0;
	if(l1 == l2) {
		rep(i, 1, l1) {
			if(u1 == u2) {
				rep(j, L[i] + 1, R[i] - 1) ++g[to(u1, j)][l1 - i];
			}else {
				rep(j, L[i] + 1, 9) ++g[to(u1, j)][l1 - i];
				rep(j, i == 1 ? 1 : 0, R[i] - 1) ++g[to(u2, j)][l2 - i];//
			}
			u1 = to(u1, L[i]);
			u2 = to(u2, R[i]);
		}
		++g[u1][0];if(u1 ^ u2) ++g[u2][0];
	}else {
		rep(i, 1, l1) {
			rep(j, L[i] + 1, 9) ++g[to(u1, j)][l1 - i];
			u1 = to(u1, L[i]);
		}
		rep(i, 1, l2) {
			rep(j, i == 1 ? 1 : 0, R[i] - 1) ++g[to(u2, j)][l2 - i];
			u2 = to(u2, R[i]);
		}
		++g[u1][0], ++g[u2][0];
		rep(i, l1 + 1, l2 - 1)
		rep(j, 1, 9) ++g[to(0, j)][i - 1];
	}
}
void getfail() {
	queue<int>Q;
	rep(c, 1, 9) if(ch[0][c]) Q.push(ch[0][c]);
	while(!Q.empty()) {
		int u = Q.front();Q.pop();
		rep(c, 0, 9) {
			int &v = ch[u][c];
			if(!v) {v = ch[fail[u]][c]; continue;}
			Q.push(v);
			fail[v] = ch[fail[u]][c];
			rep(i, 0, n) g[v][i] += g[fail[v]][i];
		}
	}
}
bool vis[N];
int main() {
	scanf("%s%s%d", L + 1, R + 1, &n);
	insert();
	getfail();
	rep(i, 1, ndc)
	rep(j, 1, n) g[i][j] += g[i][j - 1];
	
	memset(f, 0xc0, sizeof f);f[0][0] = 0;
	rep(i, 0, n)
	rep(j, 0, ndc) if(f[i][j] >= 0){
		f[i][j] += g[j][n - i];
		rep(k, 0, 9)
		Max(f[i + 1][ch[j][k]], f[i][j]);
	}
	
	int ans = 0;
	rep(i, 0, ndc) Max(ans, f[n][i]);
	printf("%d\n", ans);
	
	rep(i, 0, ndc) if(f[n][i] == ans) ok[n][i] = 1;
	for(int i = n - 1; ~i; --i)
	rep(j, 0, ndc)
	rep(k, 0, 9) {
		if(f[i][j] + g[ch[j][k]][n - i - 1] == f[i + 1][ch[j][k]]) {
			ok[i][j] |= ok[i + 1][ch[j][k]];
		}
	}
	for(int i = 0, u = 0; i < n; ++i) {
		rep(k, 0, 9) if(f[i][u] + g[ch[u][k]][n - i - 1] == f[i + 1][ch[u][k]] && ok[i + 1][ch[u][k]]) {
			printf("%c", k + '0'); u = ch[u][k];
			break; 
		}
	}
	puts("");
	return 0;
}
