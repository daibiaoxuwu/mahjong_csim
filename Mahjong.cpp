//
// Created by lm on 2019/11/1.
//

#include "Mahjong.h"

char* Mahjong::mname(int num, char *ans) {
    int num2 = num / 4;
    const char* dragon_name[] = {"EST", "STH", "WST", "NTH", "BAI", " FA", "ZHO"};
    if(num2 < 9) ans[1]=num2+'1',ans[2]='B';
    else if(num2 < 18) ans[1]=num2+'1'-9, ans[2]='T';
    else if(num2 < 27) ans[1]=num2+'1'-18, ans[2]='W';
    else memcpy(ans,dragon_name[num2-27],4);
    if(num == 16 || num == 16 + 36 || num == 16 + 72) ans[0]='+'; else if(num2<27) ans[0]=' ';
    return ans;
}
bool Mahjong::ishu_without_head(const int *_hand_cnts, int st_idx) {
    int hand_cnts[35];
    memcpy(hand_cnts,_hand_cnts,35*sizeof(int));
    hand_cnts[st_idx]-=2;//remove head at indicated position
    for(;st_idx<34;++st_idx)
    {
        if(hand_cnts[st_idx]>0)
        {
            if(hand_cnts[st_idx]>=3) {
                hand_cnts[st_idx] -= 3;
                st_idx--;
            }
            else
            {
                hand_cnts[next_piece(st_idx)]-=hand_cnts[st_idx];
                if(hand_cnts[next_piece(st_idx)]<0) return false;
                hand_cnts[next_piece(next_piece(st_idx))]-=hand_cnts[st_idx];
                if(hand_cnts[next_piece(next_piece(st_idx))]<0) return false;
                hand_cnts[st_idx]=0;
            }
        }
    }
    return true;
}
bool ishu_special(const int *hand_cnts){
    //13x1+
    //26 for 9W
    for(int i = 26;i<34;++i)
        if(hand_cnts[i]==0)return false;
    //1B 9B 1T 9T 1W
    if(hand_cnts[0]>0 && hand_cnts[8]>0 && hand_cnts[9]>0 && hand_cnts[17]>0 && hand_cnts[18]>0) return true;
    //7x2
    for(int i=0;i<34;++i)
        if(hand_cnts[i]!=2)return false;
    return true;
}
bool Mahjong::ishu(const int *_hand_cnts){
    if(ishu_special(_hand_cnts)) return true;
    int hand_cnts[35];
    memcpy(hand_cnts,_hand_cnts,35*sizeof(int));
    if (hand_cnts[34]!=0) printf("%d\n",hand_cnts[34]);
    for(int st_idx=0;st_idx<34;++st_idx)
    {
        if(hand_cnts[st_idx]>0)
        {
            if(hand_cnts[st_idx]>=2) {
                if(ishu_without_head(hand_cnts,st_idx))return true;//suspected head at st_idx
            }
            if(hand_cnts[st_idx]>=3) {
                hand_cnts[st_idx] -= 3;
                st_idx--;
            }
            else
            {
                hand_cnts[next_piece(st_idx)]-=hand_cnts[st_idx];
                if(hand_cnts[next_piece(st_idx)]<0) return false;
                hand_cnts[next_piece(next_piece(st_idx))]-=hand_cnts[st_idx];
                if(hand_cnts[next_piece(next_piece(st_idx))]<0) return false;
                hand_cnts[st_idx]=0;
            }
        }
    }
    return true;
}
