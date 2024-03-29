#include <bits/stdc++.h>
#include "Mahjong.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-register"
using namespace std;

#include<cstdio>
#include<cstring>
#include<map>

#define RI register int
#define CI const int&
using namespace std;
const int N = 105, MX = 21000, mod = 998244353;



inline void maxer(int &x, CI y) {
    if (y > x) x = y;
}

inline int min(CI a, CI b) {
    return a < b ? a : b;
}

struct Matrix {
    int mat[3][3];

    inline int *operator[](CI x) { return mat[x]; }

    inline Matrix(void) {
        memset(mat, -1, sizeof(mat));
    }

    friend inline bool operator!=(Matrix A, Matrix B) {
        for (RI i = 0; i < 3; ++i)
            for (RI j = 0; j < 3; ++j)
                if (A[i][j] != B[i][j]) return 1;
        return 0;
    }

    friend inline bool operator<(Matrix A, Matrix B) {
        for (RI i = 0; i < 3; ++i)
            for (RI j = 0; j < 3; ++j)
                if (A[i][j] != B[i][j]) return A[i][j] < B[i][j];
    }

    inline bool Com_Hu(void) {
        for (RI i = 0; i < 3; ++i)
            for (RI j = 0; j < 3; ++j)
                if (mat[i][j] >= 4) return 1;
        return 0;
    }

    inline void flush(Matrix pre, CI num, bool isone) {
        for (RI i = 0; i < 3; ++i)
            for (RI j = 0; j < 3; ++j)
                if (~pre[i][j]) {
                    if (isone)
                        for (RI k = 0; k < 3 && j + k <= num; ++k)
                            maxer(mat[j][k], min(pre[i][j] + (num - j - k) / 3, 4));
                    else
                        for (RI k = 0; k < 3 && i + j + k <= num; ++k)
                            maxer(mat[j][k], min(i + pre[i][j] + (num - i - j - k) / 3, 4));
                }
    }
};

struct Hu_Auto_Node {
    Matrix p[2];
    int cur, ch[10];

    inline Hu_Auto_Node(void) {
        memset(ch, 0, sizeof(ch));
        cur = 0;
        p[0] = p[1] = Matrix();
    }

    inline bool is_Hu(void) {
        if (cur >= 7) return 1;
        return p[1].Com_Hu();
    }


    friend inline bool operator<(Hu_Auto_Node A, Hu_Auto_Node B) {
        if (A.cur != B.cur) return A.cur < B.cur;
        if (A.p[0] != B.p[0]) return A.p[0] < B.p[0];
        if (A.p[1] != B.p[1]) return A.p[1] < B.p[1];
        return 0;
    }
};
    inline Hu_Auto_Node add(Hu_Auto_Node A, CI num,bool isone) {
        if (A.is_Hu()) return  A;
        Hu_Auto_Node s;
        s.p[0].flush(A.p[0], num,isone);
        s.p[1].flush(A.p[1], num,isone);
        if (num >= 2) s.p[1].flush(A.p[0], num - 2,isone);
        s.cur = A.cur + (num >= 2);
        return s;
    }

class Hu_Automation {
private:
    map<Hu_Auto_Node, int> Hash;

    inline void expand(CI id) {
        for (RI i = 0; i <= 4; ++i) {
            Hu_Auto_Node son2 = add(node[id], i, false);
            if (!Hash.count(son2)) node[Hash[son2] = ++tot] = son2;
            node[id].ch[i] = Hash[son2];

            Hu_Auto_Node son = add(node[id], i, true);
            if (!Hash.count(son)) node[Hash[son] = ++tot] = son;
            node[id].ch[i+5] = Hash[son];
        }
    }

public:
    Hu_Auto_Node node[MX];
    int tot;

    inline Hu_Automation(void) {
        node[1].p[0][0][0] = 0;
        node[tot = 2].cur = -1;
        Hash[node[1]] = 1;
        Hash[node[2]] = 2;
        expand(1);
        for (RI i = 3; i <= tot; ++i) {
            expand(i);
        }
        printf("expand:%d\n", tot);
    }
    /*inline void check(void)
    {
        printf("%d\n",tot); for (RI i=1;i<=tot;++i,putchar('\n'))
        for (RI j=0;j<=4;++j) printf("%d ",node[i].ch[j]);
    }*/
} HA;

unsigned long long f[2][136][MX];
int n, m, x, y, nw;
unsigned long long ans;
double fact[N << 2];

inline void inc(unsigned long long &x, CI y) {
    assert(x + y >= x);
    x += y;
}

inline void init(CI n) {
    RI i;
    for (fact[0] = i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
}

const long long C[5][5] = {{1},
                           {1, 1},
                           {1, 2, 1},
                           {1, 3, 3, 1},
                           {1, 4, 6, 4, 1}};

inline void calc(CI x, CI y) {
    ans += f[nw][x][y];
}

const double round_prob[19] = {1.000000, 1.000000, 0.999708, 0.998029, 0.991947, 0.976532, 0.946340, 0.897968, 0.831425,
                               0.750198, 0.660036, 0.567684, 0.479381, 0.399071, 0.329266, 0.270215, 0.221551, 0.182120,
                               0.00000};

double expectance(const int *_hand_cnts, const int *known_remain_cnt, int discard, int remaining_cards, int round) {
    int hand_cnts[35];
    memcpy(hand_cnts, _hand_cnts, 35 * sizeof(int));
    hand_cnts[discard]--;

    RI i, j, k, t;
    int n = 34;

    m = remaining_cards;
    for (t = 0; t < 136; ++t)
        for (k = 0; k < MX; ++k)
            f[0][t][k] = 0;
    f[0][0][1] = 1;
    for (i = 1; i <= n; ++i) {
        nw = i & 1;
        for (t = 0; t < 136; ++t)
            for (k = 0; k < MX; ++k)
                f[nw][t][k] = 0;
        for (j = m; ~j; --j)
            for (k = 1; k <= HA.tot; ++k)
                if (f[nw ^ 1][j][k] > 0)
                    for (t = 0; t <= known_remain_cnt[i - 1]; ++t)
                        f[nw][j + t][HA.node[k].ch[hand_cnts[i - 1] + t + ((i==10||i==18||i>=28)?5:0)]] +=
                                f[nw ^ 1][j][k] * C[known_remain_cnt[i - 1]][t];
    }
    double last_possibility = 0;
    double fail_possibility = 0;

    m = remaining_cards;
    double temps[17];
    double temps2[17];
    for (nw = n & 1, i = 1; i <= 16; ++i) {
        ans = 0;
        for (calc(i, 1), j = 3; j <= HA.tot; ++j) if(!HA.node[j].is_Hu()) calc(i, j);
        double sum = 1 - ans * fact[i] * fact[m - i] / fact[m];//not hu at this round,from i=1:~1(tianhu) to i=18:liuju
        //a possibility including the next one
        printf("%lld,",ans);
        temps[i]=sum;
//        fail_possibility += last_possibility;
// roundprob[i]:after getting i cards still playing?
        fail_possibility += (sum-last_possibility)*round_prob[min(i-2+round,18)];
        temps2[i]=fail_possibility;
//        printf("i:%d add:%d * %.3lf = %d fail: %d\n",i,temp2,round_prob[i-1],temp,fail_possibility);
        last_possibility = sum;
        //roundprob[i-1] most likely this is the first player. roundprob[1] tianhu.
    }
    printf("\n %d,",known_remain_cnt[discard]);
    for (i = 1; i <= 16; ++i) {
        printf("%lf,",temps[i]);
    }
    printf("\n 0,",known_remain_cnt[discard]);
    for (i = 1; i <= 16; ++i) {
        printf("%lf,",temps2[i]);
    }
    return fail_possibility + 1;
}

int decide(const int *_hand_cnts, const int *known_remain_cnt, int round) {
    int best_card = 0;
    double best_expectance = 0;
    int remaining_cards = 0;
    for (int i = 0; i < 34; ++i) remaining_cards += known_remain_cnt[i];
    for (int i = 0; i < 34; ++i) {
        if (_hand_cnts[i] > 0) {
            char mname_buf[4];
            printf("%3s,", Mahjong().mname(i * 4, mname_buf));
            double result = expectance(_hand_cnts, known_remain_cnt, i, remaining_cards,round);
            printf("%d, %lf\n",i,result);
            if (result > best_expectance)best_card = i, best_expectance = result;
        }
    }
//    printf("\n");
    return best_card;
}

int main() {
    freopen("out.csv","w",stdout);
    Mahjong mahjong;
    int deck[136];
    init(136);
    for (int i = 0; i < 136; ++i) deck[i] = i;
 //   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

   // std::shuffle(deck, deck + 136, std::default_random_engine(seed));
     std::random_shuffle(deck, deck + 136);
    //swap(deck[30],deck[60]);
    char mname_buf[4];
    mname_buf[3] = 0;
    int poi = 18;
    int next_dora = 8;
    printf("Bonus Card Indicator:%3s\n", mahjong.mname(deck[next_dora], mname_buf));
    next_dora += 2;
    int hand_cnt[35];
    int known_remain_cnt[34];
    for (int i = 0; i < 34; ++i)known_remain_cnt[i] = 4;
    memset(hand_cnt, 0, 35 * sizeof(int));
    int tempdraw[]={7,3,4,5,6,10,21,25,26,27,28,29,30};
    for (int i = 0; i < 13; ++i) {
        int draw = deck[poi++] / 4;
        draw = tempdraw[i];
        /*
        draw = i;
        if(draw==9)draw = 0;
        if(draw==10)draw = 0;
        if(draw==11)draw = 8;
        if(draw==12)draw = 8;
*/
        hand_cnt[draw]++;
        known_remain_cnt[draw]--;
    }
    int round = 1;
    while (poi < 56) {
        int draw = deck[poi] / 4;
        hand_cnt[draw]++;
        known_remain_cnt[draw]--;
//        printf("round %d get: %3s\n", round, mahjong.mname(deck[poi], mname_buf));
        if (mahjong.ishu(hand_cnt)) {
            printf("zimo!");
            break;
        }
//        for (int i = 0; i < 34; ++i) {
//            for (int j = 0; j < hand_cnt[i]; ++j) printf("%3s ", mahjong.mname(i * 4, mname_buf));
//        }
//        printf("\n");
        for (int i = 0; i < 34; ++i) {
            for (int j = 0; j < hand_cnt[i]; ++j) printf("%3s,", mahjong.mname(i * 4, mname_buf));
        }
        printf("\n");
        int choice = decide(hand_cnt, known_remain_cnt,round);
        assert(hand_cnt[choice] > 0);
        hand_cnt[choice]--;
//        if(choice!=draw) {
//            printf("round %d get: %3s:", round, mahjong.mname(deck[poi], mname_buf));
//            for (int i = 0; i < 34; ++i) {
//                for (int j = 0; j < hand_cnt[i]; ++j) printf("%3s ", mahjong.mname(i * 4, mname_buf));
//            }
//            printf("discard %3s\n", mahjong.mname(choice * 4, mname_buf));
//        }
//        else printf("...\n");
        if(choice!=draw) printf("change ");
        printf("discard %3s\n", mahjong.mname(choice * 4, mname_buf));
        for (int i = 0; i < 34; ++i)
            printf("%3s,", mahjong.mname(i * 4, mname_buf));
        printf("\n");
        for (int i = 0; i < 34; ++i)
            printf("%d,", known_remain_cnt[i]);
        printf("\n\n");

        ++poi;
        ++round;
    }
    for (int i = 0; i < 34; ++i) {
        for (int j = 0; j < 4 - known_remain_cnt[i]; ++j) printf("%3s ", mahjong.mname(i * 4, mname_buf));
    }
}


#pragma clang diagnostic pop