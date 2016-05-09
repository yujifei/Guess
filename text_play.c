#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<setjmp.h>
#include "guess.h"

#define DO_CONTINUE \
do{system("clear");continue;}while(0)

#define DO_EXIT \
do{printf("Thanks.Bye .\n");exit(0);}while(0)

#define DO_ABOUT \
do{about();printf("Press any key...\n");getch();}while(0)



static char getch(void)
{
    char c;
    system("stty raw");
    c=getchar();
    system("stty cooked");
    return c;
}

static void print_char_picture()
{
    system("clear");
    unsigned char guess[5][8]= 
    {{0x00,0x72,0xfb,0x89,0x89,0x7f,0xf7,0x80},
     {0x00,0xf8,0xfc,0x06,0x06,0xf8,0xfc,0x04},
     {0x00,0x78,0xfc,0xa4,0xa4,0xa4,0xec,0x68},
     {0x00,0x48,0xec,0xa2,0xb2,0x92,0xdc,0x48},
     {0x00,0x48,0xec,0xa2,0xb2,0x92,0xdc,0x48}};
    unsigned char row,col,*p=&guess[0][0];
    for(row=0;row<8;row++)
    {
        for(col=0;col<40;col++)
        {
            if(*(p+col)&0x80)
                printf(" G ");
            else
                printf("   ");
            *(p+col)<<=1;
          
        }
        printf("\n");
    }
    printf("\n..................Version 1.0.................\n");
}

static void about(void)
{
     system("clear");
     printf("\nThis is a simple program.\n");
     printf("Writen by yujihui in 2008-11-7 at I-419 room of DingXiang dormitory in XiDian University\n");
     printf("Compiler:gcc-4.1.2.\n");
     printf("Test Environment:RedHat Fedora 7.Kernel version:Linux-2.6.21\n");
     printf("Designed only for Linux/Unix but may compatible on Windows.\n");
     printf("\n  If you want to compiler this program on Windows such as with Visual C++6.0\n");
     printf("please delete the function \"system(\"clear\")\"(line 13 and 37 ).");
     printf("\n  Thank you for your using");
}

static void  dis_menu(void)
{
     printf("\n             (1) Play.\n");
     printf("\n             (2) About.\n");
     printf("\n             (3) Quit.\n\n");
     printf("select:\n");
}

static int getin(void)//output a number
{
    unsigned int output;
    unsigned char enable_number=0;
    str_num str_out;
    while(0==enable_number)
    {
        printf("OK，please input 4 different figures :");
        scanf("%d",&output);
	getchar();
        if(output>9999)
        {
            printf("\nBad input!it's too large!\n!");
            continue;
        }
        if(!not_guessed(output))
        {
            printf("\nBad input!You have guessed this number!\n");
            continue;
        }        
        str_out=separate(output);
        if(str_out.nums[0]!=str_out.nums[1] && str_out.nums[0]!=str_out.nums[2] && str_out.nums[0]!=str_out.nums[3] &&\
           str_out.nums[1]!=str_out.nums[2] && str_out.nums[1]!=str_out.nums[3] && str_out.nums[2]!=str_out.nums[3])
            enable_number=1;
        else
            printf("\nBad input!must 4 different figueres!\n"); 
    }
    regist_guessed(output);
    return  output;
}

static void play_game(void)//Now play the game. guess the number within 8 times.Good luck to you!
{
     reset_guessed();
     unsigned int  r_num,in_num;
     char times=0;
     int result;
     r_num=produce_a_random_number();
     printf("\n%d\n",r_num);
     while(++times)
     {
         printf("OK,you have guessed %d times...",times);
         in_num=getin();
         result = compare(r_num,in_num);
         if(100==result)
	 {
	      printf("You win!");
	      break;
	 }
         else
	      printf("%dA%dB\n",result/10,result%10);

         if(times>8)
         {
             printf("You are failed!\n");
             break;
         }
     }
}
void text_mode_run()
{
    char select1,select2;
    print_char_picture();
    while(1)
    {
        dis_menu();
        select1=getch();
        if('1'==select1)
        {
            while(1)
            {  
                play_game();
                printf("Try again?[Y/N]");
                select2=getch();
                if('n'==select2||'N'==select2)
                    break;
                else
                    continue;
		system("clear");
            }
        }
        if('2'==select1)
	    DO_ABOUT;
        if('3'==select1)
            DO_EXIT;
        else
            DO_CONTINUE;
    }
}
