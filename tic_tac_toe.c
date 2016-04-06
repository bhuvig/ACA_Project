#include <stdio.h>
#include <stdlib.h>
char board[9]={'0','0','0','0','0','0','0','0','0'};
int mini(char *);
int max(char *);
void display(char board[])
{
    for(int i=0; i<9; i++)
        {
            printf("%d", board[i]-'0');
            if((i+1)%3==0)
                printf("\n");
        }
        printf("\n");
}
int check_win( char board[])  //1 for win, 2 for tie, 0 otherwise
{
    if(board[0]==board[1] && board[1]==board[2] && board[0]!='0')
        return 1;
    else if(board[3]==board[4] && board[4]==board[5] && board[3]!='0')
        return 1;
    else if(board[6]==board[7] && board[7]==board[8] && board[6]!='0')
        return 1;
    else if(board[0]==board[3] && board[3]==board[6] && board[0]!='0')
        return 1;
    else if(board[1]==board[4] && board[4]==board[7]&& board[1]!='0')
        return 1;
    else if(board[2]==board[5] && board[5]==board[8]&& board[2]!='0')
        return 1;
    else if(board[0]==board[4] && board[4]==board[8]&& board[0]!='0')
        return 1;
    else if(board[2]==board[4] && board[4]==board[6] && board[2]!='0')
        return 1;
    else if(board[0]!='0' && board[1]!='0' && board[2]!='0' && board[3]!='0' && board[4]!='0' && board[5]!='0' && board[6]!='0' && board[7]!='0' && board[8]!='0' )
        return 2;
    else
        return 0;
}
int mini(char board[])
{
    int score[9],ctr=0;
    for(int j=0; j<9; j++)
    {
        if(board[j]=='0')
        {
            board[j]='2';
            if(check_win(board)==1)
            {
                score[ctr++]=-10;
            }
            else if(check_win(board)==2)
            {
                score[ctr++]=0;
            }
            else
            {
                score[ctr++]=max(board);
            }
            board[j]='0';
        }
    }
    int min_score=score[0];
    for(int i=1; i<ctr; i++)
        if(score[i]<min_score)
            min_score=score[i];

     return min_score;

}
int max(char board[])
{

    int score[9],ctr=0;
    for(int j=0; j<9; j++)
    {
        if(board[j]=='0')
        {
            board[j]='1';
            if(check_win(board)==1)
            {
                score[ctr++]=10;
            }
            else if(check_win(board)==2)
            {
                score[ctr++]=0;
            }
            else
            {
                score[ctr++]=mini(board);
            }
            board[j]='0';
        }
    }
    int max_score=score[0];
    for(int i=1; i<ctr; i++)
        if(score[i]>max_score)
            max_score=score[i];

     return max_score;

}
void update_board(int move, char choice)
{
    if(choice=='c')
        board[move-1]='1';
    else
        board[move-1]='2';
}
void play_server(char board[])
{
    int min_score=10, move, temp=10;

    for(int j=0; j<9; j++)
    {
        if(board[j]=='0')
        {
            board[j]='2';
            temp=max(board);
            if(temp<=min_score)
            {
                move=j+1;
                min_score=temp;
            }

            board[j]='0';
        }
    }
    update_board(move, 's');
}

int main()
{
    int move;
    printf("enter first move\n");
    scanf("%d", &move);
    update_board(move, 'c');
    display(board);
    while(1)
    {
        play_server(board);
        display(board);
        if(check_win(board)==1)
        {
            printf("server wins");
            break;
        }
        else if(check_win(board)==2)
        {
            printf("draw");
            break;
        }
        else
        {
            printf("enter_move\n");
            scanf("%d", &move);
            update_board(move, 'c');
            display(board);
            if(check_win(board)==1)
            {
                printf("you win");
                break;
            }
            else if(check_win(board)==2)
            {
                printf("draw");
                break;
            }
        }
    }
    return 0;
}
