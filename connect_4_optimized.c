#include <stdio.h>
#include <stdlib.h>
//0th row is the first from top but displayed upside down

int mini(char [][7],int, int, int);
int max(char [][7], int,int, int);
int is_free(int col, char board[6][7])
{
    int i;
    for(i=0; i<6; i++)
        if(board[i][col]=='0')
            break;
    if(i<6)
        return 1;
    return 0;
}
void display(char board[][7])
{
    for(int i=5; i>=0; i--)
        {
            for(int j=0; j<7; j++)
                printf("%d", board[i][j]-'0');
            printf("\n");
        }
        printf("\n");
}
int check_win( char board[][7])  //1 for win, 2 for tie, 0 otherwise
{
    int i, j;
    //checks horizontal win
    for(i=0;i<6;i++)
        for(j=0;j<7-3;j++)
            if(board[i][j] != '0' && board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3])
                return 1;


    //checks vertical win
    for(i=0;i<6-3;i++)
        for(j=0;j<7;j++)
            if(board[i][j] != '0' && board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j])
                return 1;
                //return 2;

    //checks rigth diagonal win
    for(i=0;i<6-3;i++)
        for(j=0;j<7-3;j++)
            if(board[i][j] != '0' && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3])
                return 1;

    //checks left diagonal win
    for(i=0;i<6-3;i++)
        for(j=3;j<7;j++)
            if(board[i][j] != '0' && board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3])
                return 1;

    for(i=0;i<6;i++)
        for(j=0; j<7; j++)
            if(board[i][j]=='0')
                break;

    if(i==6 && j==7)
                return 2;

    return 0;
}
void update_board(int move, char choice, char board[][7])
{
    if(choice=='c')
    {
        for(int i=0; i<6; i++)
        {
            if(board[i][move-1]=='0')
            {
                board[i][move-1]='1';
                break;
            }
        }
        return;
    }
    if(choice=='s')
    {
        for(int i=0; i<6; i++)
        {
            if(board[i][move-1]=='0')
            {
                board[i][move-1]='2';
                break;
            }
        }
        return;
    }
    {
        int i;
        for(i=0; i<6; i++)
        {
            if(board[i][move-1]=='0')
            {
                board[i-1][move-1]='0';
                break;

            }
        }
        if(i==6)
        board[5][move-1]='0';
    }
}

//check 4 in a row
int appx_score(char board[6][7])
{
	int s_score=0, c_score=0;
	int i, j, temp;

    //checks horizontal win
    for(i=0;i<6;i++)
        for(j=0;j<7-3;j++)
        {
        	temp=(int)board[i][j]+(int)board[i][j+1]+(int)board[i][j+2]+(int)board[i][j+3];
            if(temp==195)
                c_score=c_score+10;
            else if(temp==198)
            	s_score=s_score+10;
        }

    //checks vertical win
    for(i=0;i<6-3;i++)
        for(j=0;j<7;j++)
        {
        	temp=(int)board[i][j]+(int)board[i+1][j]+(int)board[i+2][j]+(int)board[i+3][j];
            if(temp==195)
                c_score=c_score+10;
            else if(temp==198)
            	s_score=s_score+10;
        }
    //checks rigth diagonal win
    for(i=0;i<6-3;i++)
        for(j=0;j<7-3;j++)
        {
        	temp=(int)board[i][j]+(int)board[i+1][j+1]+(int)board[i+2][j+2]+(int)board[i+3][j+3];
            if(temp==195)
                c_score=c_score+10;
            else if(temp==198)
            	s_score=s_score+10;
        }
    //checks left diagonal win
    for(i=0;i<6-3;i++)
        for(j=0; j<7; j++)
        {
        	temp=(int)board[i][j]+(int)board[i+1][j-1]+(int)board[i+2][j-2]+(int)board[i+3][j-3];
            if(temp==195)
                c_score=c_score+10;
            else if(temp==198)
            	s_score=s_score+10;
        }

    return c_score-s_score;
}
int mini(char board[][7], int depth,int alpha, int beta)
{
    if(depth==0)
    {
        return appx_score(board);
    }
    else if(check_win(board)==1)
        return 100000+depth;
    else if(check_win(board)==2)
        return 0;
    else
    {
    int temp=0, ctr=0;

    int col_order[7]={3,2,4,1,5,0,6};
    int score_order[7]={100000, 100000, 100000, 100000, 100000, 100000, 100000};
    for(int i=0; i<7; i++)
    {
        if(is_free(i, board))
        {
            update_board(i+1, 's', board);
            score_order[ctr]=appx_score(board);
            col_order[ctr]=i;
            update_board(i+1, 'a', board);
            ctr=ctr+1;
        }
    }
    for(int x=0; x<ctr; x++)
	{
		for(int y=0; y<ctr-x-1; y++)
		{
			if(score_order[y]>score_order[y+1])
			{
				int temp2 = col_order[y+1];
				int temp1 = score_order[y+1];
				col_order[y+1] = col_order[y];
				col_order[y] = temp2;
				score_order[y+1] = score_order[y];
				score_order[y] = temp1;
			}
		}
	}
    for(int j=0; j<ctr; j++)
    {
        if(alpha<beta)

        {
            update_board(col_order[j]+1, 's', board);

            temp=max(board, depth-1, alpha, beta);
            if(temp<beta)
                beta=temp;

            update_board(col_order[j]+1, 'a', board);
        }
        else return beta;
    }
    return beta;   //alpha becomes beta
  }
}
int max(char board[][7], int depth, int alpha, int beta)
{
    if(depth==0)
    {
        return appx_score(board);
    }
    else if(check_win(board)==1)
        return -100000-depth;
    else if(check_win(board)==2)
        return 0;
    else
    {
    int temp=0, ctr=0;

    int col_order[7]={3,2,4,1,5,0,6};
    int score_order[7]={-100000, -100000, -100000, -100000, -100000, -100000, -100000};
    for(int i=0; i<7; i++)
    {
        if(is_free(i, board))
        {
            update_board(i+1, 'c', board);
            score_order[ctr]=appx_score(board);
            col_order[ctr]=i;
            update_board(i+1, 'a', board);
            ctr=ctr+1;
        }
    }
    for(int x=0; x<ctr; x++)
	{
		for(int y=0; y<ctr-x-1; y++)
		{
			if(score_order[y]<score_order[y+1])
			{
				int temp2 = col_order[y+1];
				int temp1 = score_order[y+1];
				col_order[y+1] = col_order[y];
				col_order[y] = temp2;
				score_order[y+1] = score_order[y];
				score_order[y] = temp1;
			}
		}
	}
    for(int j=0; j<ctr; j++)
    {
        if(alpha<beta)
        {
            update_board(col_order[j]+1, 'c', board);

            temp=mini(board, depth-1, alpha, beta);
            if(temp>alpha)
                alpha=temp;

            update_board(col_order[j]+1, 'a', board);
        }
        else return alpha;
    }
    return alpha;    //beta becomes alpha
   }

}
void play_server(char board[][7])
{
    int move=1,i, temp=100100;

    int col_order[7]={3,2,4,1,5,0,6};
    int alpha=-100100;
    int beta=+100100;
    for(int j=0; j<7; j++)
    {
        if(is_free(col_order[j], board))
        {

            update_board(col_order[j]+1, 's', board);

            temp=max(board,12,alpha, beta);
            if(temp<beta)
                {
                    beta=temp;
                    move=col_order[j]+1;
                }
            update_board(col_order[j]+1, 'a', board);

        }
    }

    update_board(move, 's', board);
}



int main()
{
    char board[6][7];
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            board[i][j]='0';
    int move;
    printf("enter first move\n");
    scanf("%d", &move);
    update_board(move, 'c', board);
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
            update_board(move, 'c', board);
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
