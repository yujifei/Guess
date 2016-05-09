#include<time.h>
#include<stdlib.h>
#include "guess.h"

unsigned int guessed_number[8];//这里保存着本次你曾猜过的数字
unsigned char guessed_number_index;//本次猜过的数的个数



void regist_guessed(unsigned int guessed)
{
     guessed_number[guessed_number_index] = guessed;
     guessed_number_index++;
}
void reset_guessed()
{
     guessed_number_index=0;
}

str_num separate(unsigned int num)//将一个数的每一位分开
{
    int gw,shw,bw,qw;
    qw=num/1000;
    bw=num/100-qw*10;
    shw=num/10-(qw*10+bw)*10;
    gw=num-((qw*10+bw)*10+shw)*10;
    str_num  sep_num={{gw,shw,bw,qw}};
    return sep_num;
}

int not_guessed(unsigned int num)
{
    unsigned char not_guess=1,i;
    for(i=0;i<guessed_number_index;i++)
        if(num==guessed_number[i])
        {
            not_guess=0;
            break;
        }
    return not_guess;
}

unsigned int  produce_a_random_number(void)//产生一个随机数它有四位，且任意两位不同
{
    unsigned int rand_num;
    char judge=0;
    str_num num;
    srand(time(NULL));
    while(!judge)
    {
        rand_num=rand()%10000;
        num=separate(rand_num);
        if(num.nums[0]!=num.nums[1] && num.nums[0]!=num.nums[2] && num.nums[0]!=num.nums[3] &&\
           num.nums[1]!=num.nums[2] && num.nums[1]!=num.nums[3] && num.nums[2]!=num.nums[3])
              judge=1;
    }
    return rand_num;
}

int compare(unsigned int rand, unsigned int input)//compare the number you have input and that one produced by compute 
{
    int i,j,state;
    int pos_num=0,only_num=0;

    str_num rand_num,input_num;
    rand_num = separate(rand);
    input_num = separate(input);
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(rand_num.nums[i]==input_num.nums[j])
            {
                if(i==j)
                    pos_num++;
                else
                    only_num++;
            }
    if(4==pos_num)
        state=100;

    else
        state=pos_num*10+only_num;
    return state;
}
