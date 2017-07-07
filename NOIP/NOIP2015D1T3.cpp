#include <map>
#include <cstdio>
#include <algorithm>
#define MAX_K 14
using namespace std;
typedef long long ll;
int n, card[MAX_K];
map<ll, int> m;
inline ll zip() {//将当前牌压缩
    ll state = 0;
    for (int i = 0; i < MAX_K; ++i) {
        state = state * 5 + card[i];
    }
    return state;
}
int dfs() {
    ll state = zip();
    int ans = 30;
    if (state == 0) return 0;
    if (m.count(state)) return m[state];
    bool flag = false;
    //炸弹
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (card[i] == 4) {
            card[i] -= 4;
            ans = min(ans, dfs() + 1); flag = true;
            card[i] += 4;
        }
    }
    //对子&火箭
    for (int i = 0; i < MAX_K; ++i) {
        if (card[i] >= 2) {
            card[i] -= 2;
            ans = min(ans, dfs() + 1); flag = true;
            card[i] += 2;
        }
    }
    //三张牌
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (card[i] >= 3) {
            card[i] -= 3;
            ans = min(ans, dfs() + 1); flag = true;
            card[i] += 3;
        }
    }
    //三带一（带火箭）
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (card[i] >= 3) {
            card[i] -= 3;
            for (int j = 0; j < MAX_K; ++j) {
                if (card[j] > 0) {
                    card[j]--;
                    ans = min(ans, dfs() + 1); flag = true;
                    card[j]++;
                }
            }
            card[i] += 3;
        }
    }
    //三带二（不带火箭）
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (card[i] >= 3) {
            card[i] -= 3;
            for (int j = 0; j < MAX_K - 1; ++j) {
                if (card[j] >= 2) {
                    card[j] -= 2;
                    ans = min(ans, dfs() + 1); flag = true;
                    card[j] += 2;
                }
            }
            card[i] += 3;
        }
    }
    //单顺子
    for (int i = 0, j; i < MAX_K - 2 - 4; ++i) {
        if (card[i] && card[i + 1] && card[i + 2] && card[i + 3] && card[i + 4]) {
            card[i]--; card[i + 1]--; card[i + 2]--; card[i + 3]--; card[i + 4]--;
            ans = min(ans, dfs() + 1); flag = true;
            for (j = i + 5; j < MAX_K - 2; ++j) {
                if (!card[j]) {
                    break;
                }else {
                    card[j]--;
                    ans = min(ans, dfs() + 1);
                }
            }
            for(int k = i; k < j; ++k) card[k]++;
        }
    }
    //双顺子
    for (int i = 0, j; i < MAX_K - 2 - 2; ++i) {
        if (card[i] >= 2 && card[i + 1] >= 2 && card[i + 2] >= 2) {
            card[i] -= 2; card[i + 1] -= 2; card[i + 2] -= 2;
            ans = min(ans, dfs() + 1); flag = true;
            for (j = i + 3; j < MAX_K - 2; ++j) {
                if (card[j] < 2) {
                    break;
                }else {
                    card[j] -= 2;
                    ans = min(ans, dfs() + 1);
                }
            }
            for (int k = i; k < j; ++k) card[k] += 2;
        }
    }
    //三顺子
    for (int i = 0, j; i < MAX_K - 2 - 1; ++i) {
        if (card[i] >= 3 && card[i+1] >= 3) {
            card[i] -= 3; card[i + 1] -= 3;
            ans = min(ans, dfs() + 1); flag = true;
            for (j = i + 2; j < MAX_K - 2; ++j) {
                if (card[j] < 3) {
                    break;
                }else {
                    card[j] -= 3;
                    ans = min(ans, dfs() + 1);
                }
            }
            for (int k = i; k < j; ++k) card[k] += 3;
        }
    }
    //四带二
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (card[i] == 4) {
            card[i] -= 4;
            for (int j = 0; j < MAX_K; ++j) {
                if (!card[j]) continue;
                card[j]--;
                for (int k = 0; k < MAX_K; ++k) {
                    if (!card[k]) continue;
                    card[k]--;
                    ans = min(ans, dfs() + 1); flag = true;
                    card[k]++;
                }
                card[j]++;
            }
            for (int j = 0; j < MAX_K; ++j) {
                if (card[j] < 2) continue;
                card[j] -= 2;
                for (int k = 0; k < MAX_K; ++k) {
                    if (card[k] < 2) continue;
                    card[k] -= 2;
                    ans = min(ans, dfs() + 1); flag = true;
                    card[k] += 2;
                }
                card[j] += 2;
            }
            card[i] += 4;
        }
    }
    //单牌
    if (!flag) {
        ans = 0;
        for (int i = 0; i < MAX_K; ++i) ans += card[i];
    }
    return m[state] = ans;
}
int main() {
    int casenum = 0;
    scanf("%d%d", &casenum, &n);
    while (casenum--) {
        fill(card, card + MAX_K, 0);
        for (int i = 0, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            if (a == 0) card[13]++;
            else if (a == 1) card[11]++;
            else if (a == 2) card[12]++;
            else card[a - 3]++;
        }
        printf("%d\n", dfs());
        m.clear();
    }
    return 0;
}