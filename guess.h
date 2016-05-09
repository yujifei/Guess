#ifndef guess_h

#define guess_h  1 

typedef struct           //保存一个数的每位
{
    int nums[4];
}str_num;

void reset_guessed();
void regist_guessed(unsigned int guessed);
str_num separate(unsigned int num);
int not_guessed(unsigned int num);
unsigned int  produce_a_random_number(void);
int compare(unsigned int rand, unsigned int input);

#endif
