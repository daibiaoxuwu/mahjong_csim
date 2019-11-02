//
// Created by lm on 2019/11/1.
//

#ifndef MAHJONG_CSIM_MAHJONG_H
#define MAHJONG_CSIM_MAHJONG_H

#include <bits/stdc++.h>

class Mahjong {

public:
    //input large number 0-135 and space for ans(3 is enough)
    static char* mname(int num, char* ans);

    // input small number 0-33: ans=34 for 'no next piece in funct ishu'
    static int next_piece(int num){return (num==8||num==17||num>=27)?34:(num+1);}

    //input in counts(array of 35 with the 34th=0 for speed) and destructable of this array
    bool ishu(const int* _hand_cnts);
    //input also the head that is still there at st_idx, will be removed inside the function
    bool ishu_without_head(const int* _hand_cnts, int st_idx);

   // int decide(const int* _hand_cnts, const int* known_remain_cnt);
    static const int dp_buf_size = 35*21*3*3*5*2;
    const double permutation[5][5]={{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1}};
    double permute_total[136][21];

    Mahjong(){
        _dp_buf=new double[dp_buf_size+1];
        memset(_dp_buf,0,dp_buf_size*sizeof(double));
        for(int remaining_cards=0;remaining_cards<=122;remaining_cards++) {
            for (int i = 1; i < 21; ++i) {
                double mul = 1.0;
                for (int j = remaining_cards-i+1; j <= remaining_cards; ++j) mul *= j;
                permute_total[remaining_cards][i] = mul;
               // printf("r:%d %d %lf\n",remaining_cards,i,mul);
            }
        }
    }
private:
    const double round_prob[19] = {1.000000, 1.000000, 0.999708, 0.998029, 0.991947, 0.976532, 0.946340, 0.897968, 0.831425, 0.750198, 0.660036, 0.567684, 0.479381, 0.399071, 0.329266, 0.270215, 0.221551, 0.182120, 0.00000};
    double* _dp_buf;
    inline double& dp_buf(int i, int k, int x1, int x2, int f, int head){
        assert(i>=0 && i<35);
        assert(k>=0 && k<20);
        assert(x1>=0 && x1<=2);
        assert(x2>=0);
        assert(f>=0);
        assert(head>=0 && head<=1);
        if(f>4||x2>2)return _dp_buf[dp_buf_size];//blackhole
        return _dp_buf[((((i*21+k)*3+x1)*3+x2)*5+f)*2+head];}
    //for dp
  //  double expectance(const int *_hand_cnts, const int* known_remain_cnt,  int discard, int remaining_cards);




};


#endif //MAHJONG_CSIM_MAHJONG_H
