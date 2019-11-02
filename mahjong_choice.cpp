//
// Created by lm on 2019/11/1.
//
/*
#include "Mahjong.h"
inline int min(int a,int b){return (a>b?b:a);}
double Mahjong::expectance(const int *_hand_cnts, const int* known_remain_cnt, int discard, int remaining_cards){
    int hand_cnts[35];
    memcpy(hand_cnts,_hand_cnts,35*sizeof(int));
    hand_cnts[discard]--;

    memset(_dp_buf,0,dp_buf_size*sizeof(double));
    dp_buf(0,0,0,0,0,0)=1;

    int maxk=0;
    double win_permutations[21];memset(win_permutations,0,21* sizeof(double));
    for(int i=0;i<34;++i)
    {
            printf("%d\n",i);
        double debug_max=0;
        for(int newnum=0;newnum<=known_remain_cnt[i];++newnum)
        {
            int inum = newnum + hand_cnts[i];
            for(int k=0;k<=maxk&&k+newnum<18;++k)
            {
//                printf("i:%d newnum:%d k:%d:",i,newnum,k);
                for(int x1=0;x1<=2;++x1)
                    for(int x2=0;x2<=2;++x2)
                        for(int f=0;f<=4;++f)
                            for (int head = 0; head <= 1; ++head) {
//                                printf("%d ",dp_buf(i,k,x1,x2,f,head));
                                double adder = dp_buf(i, k, x1, x2, f, head) * permutation[known_remain_cnt[i]][newnum];
                                for(int temp=0;temp<newnum;++temp)
                                    adder/=(remaining_cards-k-temp);

                                if(debug_max<adder && adder<1)
                                {
                                    debug_max=adder;
                                  //  printf("i:%d max:%lf\n",i,debug_max);
                                }
                                if(adder<0)
                                    printf("1");
                                assert(adder>=0);


                                if(head>0 && (f+min(x1,inum)>=4 || (inum>=3 && f+min(x1,inum-3)+1>=4))) {
                                    if(adder>0 && k+newnum < 2)
                                        printf("win:%d %d %d i:%d %e %e\n",k+newnum,k,newnum,i,win_permutations[k+newnum],adder);
                                    win_permutations[k + newnum] += adder;
                                }
                                for (int i1 = 0; i1 <= inum && i1 <= x1; ++i1)
                                    for (int i2 = 0; i2 <= inum - i1 && i2 <= x2; ++i2) {
                                        if(inum - i1 - i2 >= 3)
                                            dp_buf(i + 1, k + newnum, i2, inum - i1 - i2 - 3, f + i1 + 1, head) += adder;
                                        else
                                            dp_buf(i + 1, k + newnum, i2, inum - i1 - i2, f + i1, head) += adder;
//                                        if(adder>0)printf("val1 %d %d %d %d %d %d adds %d\n",i + 1, k + newnum, i2, inum - i1 - i2, f + i1, head, adder);

                                        if (head == 0 && inum - i1 - i2 >= 2) {
                                            dp_buf(i + 1, k + newnum, i2, inum - 2 - i1 - i2, f + i1, 1)+=adder;
//                                            if(adder>0)printf("val2 %d %d %d %d %d %d adds %d\n",i + 1, k + newnum, i2, inum - 2 - i1 - i2, f + i1, head, adder);
                                        }
                                    }
                            }

//                printf("\n");
            }
        }
        maxk = maxk + known_remain_cnt[i];
    }
    double expectation=0.0;
    double prob=0.0;
    for(int i=1;i<18;++i)
        printf("i:%d perm:%.9e\n",i,win_permutations[i]);
    for(int i=1;i<18;++i)
    {
        double newprob = win_permutations[i];
        //expectation += i * (newprob - prob);
        expectation += newprob;
        //printf("%.5e\n",expectation);
        if(expectation>0) {
            printf("%d %.5e ", i,expectation);
        }
        prob = newprob;
    }
    return expectation;
}
 */
