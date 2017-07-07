#include <map>
#include <cstdio>
#include <algorithm>
#define MAX_K 14
using namespace std;
typedef long long ll;
int n, cards[MAX_K];
map<ll, int> mem;
inline ll zip() {//将当前牌压缩
    ll state = 0;
    for (int i = 0; i < MAX_K; ++i) {
        state = state * 5 + cards[i];
    }
    return state;
}
int search() {
    ll state = zip();
    int ans = 30;
    if (state == 0) return 0;
    if (mem.count(state)) return mem[state];
    bool flag = false;
    //炸弹
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (cards[i] == 4) {
            cards[i] -= 4;
            ans = min(ans, search() + 1); flag = true;
            cards[i] += 4;
        }
    }
    //对子&火箭
    for (int i = 0; i < MAX_K; ++i) {
        if (cards[i] >= 2) {
            cards[i] -= 2;
            ans = min(ans, search() + 1); flag = true;
            cards[i] += 2;
        }
    }
    //三张牌
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (cards[i] >= 3) {
            cards[i] -= 3;
            ans = min(ans, search() + 1); flag = true;
            cards[i] += 3;
        }
    }
    //三带一（可以带火箭）
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (cards[i] >= 3) {
            cards[i] -= 3;
            for (int j = 0; j < MAX_K; ++j) {
                if (cards[j] > 0) {
                    cards[j]--;
                    ans = min(ans, search() + 1); flag = true;
                    cards[j]++;
                }
            }
            cards[i] += 3;
        }
    }
    //三带二（不能带火箭）
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (cards[i] >= 3) {
            cards[i] -= 3;
            for (int j = 0; j < MAX_K - 1; ++j) {
                if (cards[j] >= 2) {
                    cards[j] -= 2;
                    ans = min(ans, search() + 1); flag = true;
                    cards[j] += 2;
                }
            }
            cards[i] += 3;
        }
    }
    //单顺子
    for (int i = 0, j; i < MAX_K - 2 - 4; ++i) {
        if (cards[i] && cards[i+1] && cards[i+2] && cards[i+3] && cards[i+4]) {
            cards[i]--; cards[i+1]--; cards[i+2]--; cards[i+3]--; cards[i+4]--;
            ans = min(ans, search() + 1); flag = true;
            for (j = i + 5; j < MAX_K - 2; ++j) {
                if (!cards[j]) {
                    break;
                }else {
                    cards[j]--;
                    ans = min(ans, search() + 1);
                }
            }
            for(int k = i; k < j; ++k) cards[k]++;
        }
    }
    //双顺子
    for (int i = 0, j; i < MAX_K - 2 - 2; ++i) {
        if (cards[i] >= 2 && cards[i+1] >= 2 && cards[i+2] >= 2) {
            cards[i] -= 2; cards[i+1] -= 2; cards[i+2] -= 2;
            ans = min(ans, search() + 1); flag = true;
            for (j = i + 3; j < MAX_K - 2; ++j) {
                if (cards[j] < 2) {
                    break;
                }else {
                    cards[j] -= 2;
                    ans = min(ans, search() + 1);
                }
            }
            for (int k = i; k < j; ++k) cards[k] += 2;
        }
    }
    //三顺子
    for (int i = 0, j; i < MAX_K - 2 - 1; ++i) {
        if (cards[i] >= 3 && cards[i+1] >= 3) {
            cards[i] -= 3; cards[i+1] -= 3;
            ans = min(ans, search() + 1); flag = true;
            for (j = i + 2; j < MAX_K - 2; ++j) {
                if (cards[j] < 3) {
                    break;
                }else {
                    cards[j] -= 3;
                    ans = min(ans, search() + 1);
                }
            }
            for (int k = i; k < j; ++k) cards[k] += 3;
        }
    }
    //四带二
    for (int i = 0; i < MAX_K - 1; ++i) {
        if (cards[i] == 4) {
            cards[i] -= 4;
            for (int j = 0; j < MAX_K; ++j) {
                if (!cards[j]) continue;
                cards[j]--;
                for (int k = 0; k < MAX_K; ++k) {
                    if (!cards[k]) continue;
                    cards[k]--;
                    ans = min(ans, search() + 1); flag = true;
                    cards[k]++;
                }
                cards[j]++;
            }
            for (int j = 0; j < MAX_K; ++j) {
                if (cards[j] < 2) continue;
                cards[j] -= 2;
                for (int k = 0; k < MAX_K; ++k) {
                    if (cards[k] < 2) continue;
                    cards[k] -= 2;
                    ans = min(ans, search() + 1); flag = true;
                    cards[k] += 2;
                }
                cards[j] += 2;
            }
            cards[i] += 4;
        }
    }
    //一口气出完单牌
    if (!flag) {
        ans = 0;
        for (int i = 0; i < MAX_K; ++i) ans += cards[i];
    }
    return mem[state] = ans;
}
int main() {
    int casenum = 0;
    scanf("%d%d", &casenum, &n);
    while (casenum--) {
        fill(cards, cards + MAX_K, 0);
        for (int i = 0; i < n; ++i) {
            int a, b; scanf("%d%d", &a, &b);
            if (a == 0) cards[13]++;
            else if (a == 1) cards[11]++;
            else if (a == 2) cards[12]++;
            else cards[a - 3]++;
        }
        printf("%d\n", search());
        mem.clear();
    }
    return 0;
}