#include <bits/stdc++.h>
#include "Mahjong.h"
#include "BigInteger.h"
using namespace std;
#include<cstdio>
#include<cstring>
#include<map>
#define RI register int
#define CI const int&
using namespace std;
const int N=105,MX=2100,mod=998244353;
inline void maxer(int& x,CI y)
{
    if (y>x) x=y;
}
inline int min(CI a,CI b)
{
    return a<b?a:b;
}
struct Matrix
{
    int mat[3][3];
    inline int* operator [] (CI x) { return mat[x]; }
    inline Matrix(void)
    {
        memset(mat,-1,sizeof(mat));
    }
    friend inline bool operator != (Matrix A,Matrix B)
    {
        for (RI i=0;i<3;++i) for (RI j=0;j<3;++j)
                if (A[i][j]!=B[i][j]) return 1; return 0;
    }
    friend inline bool operator < (Matrix A,Matrix B)
    {
        for (RI i=0;i<3;++i) for (RI j=0;j<3;++j)
                if (A[i][j]!=B[i][j]) return A[i][j]<B[i][j];
    }
    inline bool Com_Hu(void)
    {
        for (RI i=0;i<3;++i) for (RI j=0;j<3;++j)
                if (mat[i][j]>=4) return 1; return 0;
    }
    inline void flush(Matrix pre,CI num)
    {
        for (RI i=0;i<3;++i) for (RI j=0;j<3;++j)
                if (~pre[i][j]) for (RI k=0;k<3&&i+j+k<=num;++k)
                        maxer(mat[j][k],min(i+pre[i][j]+(num-i-j-k)/3,4));
    }
};
struct Hu_Auto_Node
{
    Matrix p[2]; int cur,ch[5];
    inline Hu_Auto_Node(void)
    {
        memset(ch,0,sizeof(ch)); cur=0; p[0]=p[1]=Matrix();
    }
    inline bool is_Hu(void)
    {
        if (cur>=7) return 1; return p[1].Com_Hu();
    }
    inline void Hu(void)
    {
        memset(ch,0,sizeof(ch)); cur=-1; p[0]=p[1]=Matrix();
    }
    friend inline bool operator < (Hu_Auto_Node A,Hu_Auto_Node B)
    {
        if (A.cur!=B.cur) return A.cur<B.cur;
        if (A.p[0]!=B.p[0]) return A.p[0]<B.p[0];
        if (A.p[1]!=B.p[1]) return A.p[1]<B.p[1]; return 0;
    }
    friend inline Hu_Auto_Node operator + (Hu_Auto_Node A,CI num)
    {
        if (A.is_Hu()) return A.Hu(),A; Hu_Auto_Node s;
        s.p[0].flush(A.p[0],num); s.p[1].flush(A.p[1],num);
        if (num>=2) s.p[1].flush(A.p[0],num-2);
        s.cur=A.cur+(num>=2); if (s.is_Hu()) s.Hu(); return s;
    }
};
class Hu_Automation
{
private:
    map <Hu_Auto_Node,int> Hash;
    inline void expand(CI id)
    {
        for (RI i=0;i<=4;++i)
        {
            Hu_Auto_Node son=node[id]+i;
            if (!Hash.count(son)) node[Hash[son]=++tot]=son;
            node[id].ch[i]=Hash[son];
        }
    }
public:
    Hu_Auto_Node node[2100]; int tot;
    inline Hu_Automation(void)
    {
        node[1].p[0][0][0]=0; node[tot=2].cur=-1;
        Hash[node[1]]=1; Hash[node[2]]=2; expand(1);
        for (RI i=3;i<=tot;++i) expand(i);
    }
    /*inline void check(void)
    {
        printf("%d\n",tot); for (RI i=1;i<=tot;++i,putchar('\n'))
        for (RI j=0;j<=4;++j) printf("%d ",node[i].ch[j]);
    }*/
}HA;
Int f[2][136][MX];
int n,m,x,y,nw;
Int ans;
Int fact[N<<2];
inline void inc(Int& x,CI y)
{
    assert(x+y>=x);
    x+=y;
}

inline void init(CI n)
{
    RI i; for (fact[0]=i=1;i<=n;++i) fact[i]=fact[i-1]*i;
}

const long long C[5][5]={{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1}};
inline void calc(CI x,CI y)
{
    ans+=f[nw][x][y];
}

const double round_prob[19] = {1.000000, 1.000000, 0.999708, 0.998029, 0.991947, 0.976532, 0.946340, 0.897968, 0.831425, 0.750198, 0.660036, 0.567684, 0.479381, 0.399071, 0.329266, 0.270215, 0.221551, 0.182120, 0.00000};
int expectance(const int *_hand_cnts, const int* known_remain_cnt, int discard, int remaining_cards){
        int hand_cnts[35];
        memcpy(hand_cnts,_hand_cnts,35*sizeof(int));
        hand_cnts[discard]--;

    RI i,j,k,t;
    int n=9;

    m=remaining_cards;
    for (t = 0; t < 136; ++t)
        for (k = 0; k < MX; ++k)
            f[0][t][k] = 0;
    f[0][0][1]=1;
    for (i=1;i<=n;++i) {
        nw = i & 1;
        for (t = 0; t < 136; ++t)
            for (k = 0; k < MX; ++k)
                f[nw][t][k] = 0;
        for (j = m; ~j; --j)
            for (k = 1; k <= HA.tot; ++k)
                if (f[nw ^ 1][j][k]>0)
                    for (t = 0; t <= known_remain_cnt[i-1]; ++t)
                        f[nw][j + t][HA.node[k].ch[hand_cnts[i-1] + t]] += f[nw ^ 1][j][k] * C[known_remain_cnt[i-1]][t];
    }
    const int amp=1e7;//amplify for bigints cannot devide to doubles
    int last_possibility=amp;
    int fail_possibility=0;

    m=remaining_cards;
    for (nw=n&1,i=1;i<=34;++i)
    {
        ans=0;
        for (calc(i,1),j=3;j<=HA.tot;++j) calc(i,j);
        int sum = int((ans*fact[i]*fact[m-i]*amp/fact[m]).longValue());//not hu at this round,from i=1:~1(tianhu) to i=18:liuju
        //a possibility including the next one
//printf("%d %d\n",i,sum);
        int temp2 = int(last_possibility - sum);

        int temp = int(round_prob[i-1] * (last_possibility - sum));
//        fail_possibility += temp;//roundprob[i]:after getting i cards still playing?
        fail_possibility += sum;
//        printf("i:%d add:%d * %.3lf = %d fail: %d\n",i,temp2,round_prob[i-1],temp,fail_possibility);
       // last_possibility = sum;
        //roundprob[i-1] most likely this is the first player. roundprob[1] tianhu.
    }
    return fail_possibility + 1;
}

int decide(const int *_hand_cnts, const int* known_remain_cnt) {
    int best_card=0;
    double best_expectance=1e12;
    int remaining_cards = 0;
    for(int i=0;i<34;++i) remaining_cards+=known_remain_cnt[i];
    for(int i=0;i<34;++i)
    {
        if(_hand_cnts[i]>0) {
            double result = expectance(_hand_cnts, known_remain_cnt, i, remaining_cards);
            printf("i:%d result:%lf\n",i,result);
            if (result < best_expectance)best_card = i, best_expectance = result;
        }
    }
    printf("\n");
    return best_card;
}
int main() {
    Mahjong mahjong;
    int deck[136];
    init(136);
    for (int i = 0; i < 136; ++i) deck[i] = i;
    std::shuffle(deck, deck + 136, std::mt19937(std::random_device()()));
    //swap(deck[30],deck[60]);
    char mname_buf[4];
    mname_buf[3]=0;
    int poi = 18;
    int next_dora = 8;
    printf("Bonus Card Indicator:%3s\n", mahjong.mname(deck[next_dora],mname_buf));
    next_dora += 2;
    int hand_cnt[35];
    int known_remain_cnt[34];
    for(int i=0;i<34;++i)known_remain_cnt[i]=4;
    memset(hand_cnt, 0, 35 * sizeof(int));
    for (int i = 0; i < 13; ++i) {
        int draw = deck[poi++] / 4;
        draw = i;
        if(draw==9)draw = 0;
        if(draw==10)draw = 0;
        if(draw==11)draw = 8;
        if(draw==12)draw = 8;

        hand_cnt[draw]++;
        known_remain_cnt[draw]--;
    }
    int round = 1;
    while (poi < 136) {
        int draw = deck[poi] / 4;
        hand_cnt[draw]++;
        known_remain_cnt[draw]--;
        printf("round %d get: %3s\n", round, mahjong.mname(deck[poi], mname_buf));
        if (mahjong.ishu(hand_cnt)) {
            printf("zimo!");
            return 0;
        }
        for (int i = 0; i < 34; ++i) {
            for (int j = 0; j < hand_cnt[i]; ++j) printf("%3s ", mahjong.mname(i*4, mname_buf));
        }
        printf("\n");
        int choice = decide(hand_cnt,known_remain_cnt);
        assert(hand_cnt[choice]>0);
        hand_cnt[choice]--;
        printf("discard %3s\n", mahjong.mname(choice*4, mname_buf));
        ++poi;
        ++round;
    }
}

