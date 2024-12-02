#include <bits/stdc++.h>
#define fo(i, a, b) for (int i = a; i <= b; ++i)
#define fd(i, a, b) for (int i = a; i >= b; --i)
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define ii pair<int, int>
#define iii pair<int, ii>
#define ll long long
#define pb push_back
#define se second
#define fi first
#define el '\n'
using namespace std;

const int maxn = 30;

int n, m, a[maxn][maxn];
int res = -1;
vector<int> b;

int main()
{
    cin.tie(nullptr)->ios_base::sync_with_stdio(false);

    if (fopen("w.input", "r"))
    {
        freopen("w.input", "r", stdin);
        freopen("w.output", "w", stdout);
    }

    cin >> n >> m;
    fo(i, 1, n) fo(j, 1, m) cin >> a[i][j];

    int lim = n + m;
    fo(i, 1, lim) b.push_back(i);

    fo(mask, 0, 1 << lim)
    {
        vector<int> pos;
        rep(i, 0, lim) if (mask & (1 << i))
            pos.push_back(b[i]);

        int first_a[maxn][maxn];
        fo(i, 1, n) fo(j, 1, m)
            first_a[i][j] = a[i][j];

        for (int vt : pos)
        {
            if (vt <= n) fo(i, 1, m)
                first_a[vt][i] ^= 1;
            else fo(i, 1, n)
                first_a[i][vt - (n - 1)] ^= 1;
        }

        int cnt = 0;
        fo(i, 1, n) fo(j, 1, m)
            if (first_a[i][j] == 1) ++cnt;

        res = max(res, cnt);
    }

    cout << res;

    return 0;
}
