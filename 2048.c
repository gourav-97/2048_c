#include "2048.h"
/*int NotEmpty()**********************
**Returns 1 if no space is available**
**else returns 0					**
*************************************/
int NotEmpty()
{
	int i = 0;
	int Full = 1;

	for(i = 0, Full = 1; i < GAMESIZE && Full; ++i)
	{
		if(Tiles[i] == 0)
		{
			Full = 0;
		}
	}

	return Full;
}

int Empty(void)
{
	return !NotEmpty();
}
/*int random_index(int x)***
**Generates Random indexes**
***************************/
int random_index(int x)
{
	int index;
	index=rand()%x + 0;
	return index;
}

/*******************************************
**Initialise all places to zero in begining**
*******************************************/
void Initialise(void)
{
	int i = 0;
	for(i = 0; i < GAMESIZE; ++i){
		Tiles[i] = 0;
	}
}
/*************************************
**Generates 2 or 4 in random indexes**
*************************************/
int generate_new_index()
{
	int index;
	int flag=1;
	if(NotEmpty())
		return 0;
	if(!NotEmpty())
	{
		while(flag)
		{
			int i=random_index(16);
			if(Tiles[i]==0)
			{
				int y=rand()%10+0;
				if(y<8)
				{
					Tiles[i]=2;
				}
				else
				{
					Tiles[i]=4;
				}
				flag=0;
			}
		}
	return 1;
	}
}
/* Shifting in the board using the func.**** 
*** ShiftLeft,ShiftRight,ShiftUp,ShiftDown**
*/
void ShiftRight(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int mes = 0;
	
	for(i = 0; i < D; ++i)
	{
		mes = 4*i + D-1;
		for(j = mes; j > 4*i; --j)
		{
			if(Tiles[j] != 0) continue;
			for(k = j-1; k >= 4*i; --k)
			{
				if(Tiles[k] != 0) break;
			}
			if(k >= 4*i && Tiles[k] != 0)
			{ 
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void ShiftLeft(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int mes = 0;
	
	for(i = 0; i < D; ++i){
		mes = 4*i + 0;
		for(j = mes; j < 4*i + D-1; ++j){
			if(Tiles[j] != 0) continue;

			for(k = j+1; k <= 4*i+D-1; ++k){
				if(Tiles[k] != 0) break;
			}
			if(k <= 4*i+D-1 && Tiles[k] != 0)
			{ 
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void ShiftDown(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int mes = 0;
	
	for(i = 0; i < D; ++i)
	{
		mes = i + D*(D-1);
		for(j = mes; j >  i; j-=4)
		{
			if(Tiles[j] != 0) continue;
			for(k = j-4; k >= i; k-=4)
			{
				if(Tiles[k] != 0) break;
			}
			if(k >= i && Tiles[k] != 0)
			{
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}
void ShiftUp(void)

{
	int i = 0;
	int j = 0;
	int k = 0;
	
	for(i = 0; i < D; ++i)
	{
		for(j = i; j < D*(D-1) + i; j += 4)
		{
			if(Tiles[j] != 0) continue;
			for(k = j+4; k <= D*(D-1)+i; k += 4)
			{
				if(Tiles[k] != 0) break;
			}
			if(k <= D*(D-1)+i && Tiles[k]!= 0)
			{
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}
/*Shifting Logic Ends*/

/*****************************************
**Merging the shifted board using func ***
**MergeRight,MergeLeft,MergeDown,MergeUp**
*****************************************/

void MergeRight(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	undo_score=0;
	for(i = 0; i < D; ++i)
	{
		for(j = 4*i + D-1; j > 4*i; --j)
		{
			if(Tiles[j]==0) continue;
			for(k = j-1; k >= 4*i; --k)
			{
				if(Tiles[k]==0) continue;
				if(Tiles[k] == Tiles[j])
				{
					Tiles[j] *= 2;
					score+=Tiles[j];
					undo_score=Tiles[j];
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}
ShiftRight();
}

void MergeLeft(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	undo_score=0;
	for(i = 0; i < D; ++i)
	{
		for(j = 4*i; j < 4*i + D-1; ++j)
		{
			if(Tiles[j] == 0) continue;
			for(k = j+1; k <= 4*i + D-1; ++k)
			{
				if(Tiles[k] == 0) continue;
				if(Tiles[j] == Tiles[k])
				{
					Tiles[j] *= 2;
					score+=Tiles[j];
					undo_score=Tiles[j];
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}
	ShiftLeft();	
}

void MergeDown(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	undo_score=0;
	for(i = 0; i < D; ++i)
	{
		for(j = D*(D-1) + i; j > i; j -= D)
		{
			if(Tiles[j] == 0) continue;
			for(k = j - D; k >= i; k -= D)
			{
				if(Tiles[k] == 0) continue;
				if(Tiles[j] == Tiles[k])
				{
					Tiles[j] *= 2;
					score+=Tiles[j];
					undo_score=Tiles[j];
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}
ShiftDown();
}

void MergeUp(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	undo_score=0;
	for(i = 0; i < D; ++i)
	{
		for(j = i; j < D*(D-1) + i; j += D)
		{
			if(Tiles[j] == 0) continue;
			for(k = j + D; k <= D*(D-1) + i; k += D)
			{
				if(Tiles[k] == 0) continue;
				if(Tiles[j] == Tiles[k]){
					Tiles[j] *= 2;
					score+=Tiles[j];
					undo_score=Tiles[j];
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}
	
ShiftUp();
}
/*********************************
**Function PrintBoard prints the**
**complete display including the**
**board,score and the keys to use**
**********************************/
void PrintBoard()
{
	int i;
	printf("\n\n\n\n");
	printf("\t \t\t \t \t \t   SCORE \t%d\n",score);
	for(i=0;i<16;i++)
	{
		if(i%4==0)
				printf("\n\n\n                        |");
		if(Tiles[i]!=0)
			printf("%4d      |",Tiles[i]);
		else
			printf("%4c      |",' ');
	}
	printf("\n\n\n");
	printf(" \t\t\t\t\t\t\tr-Restart\n\t\tw\t\t\t^\t\ti-Instructions\n\ta\ts\td\t<\tv\t>\tq-Quit  u-Undo\n\n");
	
} 
/*/*********************************
**Function Instructions Prints the**
**complete instruction for the game**
**********************************/

void instructions()
{
	printf("\n\t\t\tInstructions for playing 2048 are:: \n \n");
	printf(" \tFor moving tiles enter \t\t\t\tw-move up\t\t\t\ta-move left\n\t\t\t\t\t\t\td-move right\t\t\t\ts-move down\n");
	printf(" \tWhen two tiles with same number touch, they merge into one.\tWhen 2048 is created, the player wins!\n\t\t\t\t");
}
/*********************************
**Function restart is to start a **
**new game with a score total=zero**
**********************************/

void restart()
{
	char ch;
	printf("\n\t\t\t\tAre you sure to restart the game??\n\n");
	printf(" \t\t\t\t Enter Y to restart and N to continue.\n\n");
	ch=getch();
	if(ch=='y')
	{
		system("cls");
		score=0;
		Initialise();
		generate_new_index();
		generate_new_index();
	}
	else if(ch=='n')
		system("cls");
}

int calculate_max()
{
	int i,j;
	int max=0;
	for(i=0;i<16;i++)
	{
			if(Tiles[i]>max)
			{
				max=Tiles[i];
			}
	}
	return max;
}

void lost()
{
	
	printf("  \tGAME OVER\n\n");
	printf("  \tYour final score is %d \n\n",score);
	printf("  \tThanks for trying!!!\n\n");
	exit(0);
}
void ends()
{
	printf("\n\tYour final score is :: %d \n\n");
	printf("  \tGame Ends!!!\n\n");
	
}

int game_ends()
{
	int i,j,flag=1;

		for(i=0;i<12;i=i+4)
		{
			for(j=i;j<i+3;j++)
			{
				if(Tiles[j]==Tiles[j+1])
				{
					flag=0;
					break;
				}
			}
			if(flag==0)
			{
				break;
			}
		}
			if(flag==1)
		{
			for(i=0;i<4;i++)
			{
				for(j=i;j<i+12;j=j+4)
				{
					if(Tiles[j]==Tiles[j+4])
					{
						
						flag=0;
						break;
					}
				}
				if(flag==0)
				{
					break;
				}
			}
		}
	return flag;
}

void wins()
{
	printf("  \tYOU WON!!!\n\n");
	printf("  \tYour total score is %d \n\n",score);	
}


/*************************
**Start() holds the main** 
**logicflow  of the game**
*************************/
void Start()
{
	char userChoice='w';
	Initialise();
	generate_new_index(); 	
	PrintBoard();
	printf("\n Choice ");
	do
	{	
		while((userChoice=='w'||userChoice=='a'||userChoice=='s'||userChoice=='d'||userChoice=='i'||userChoice=='r'||userChoice=='u')) //if user enters any other key than directional ones or .
		{
			if(userChoice!='u')
			{	int i;
				for(i=0;i<GAMESIZE;i++)
				{
					Tiles_copy[i]=Tiles[i];
				}	
			}
			switch(userChoice)
			{
			case 'a':
				MergeLeft(); system("cls");break;
			case 'd':
				MergeRight();  system("cls");break;
			case 'w':
				MergeUp();system("cls"); break;
			case 's':
				MergeDown();system("cls"); break;
			case 'i':
				system("cls");
				instructions(); break;
			case 'r':
				system("cls");
				restart(); break;
			case 'u':
				if(undo_flag==0)
				{	
					int j;
					for(j=0;j<GAMESIZE;j++)
						{
							Tiles[j]=Tiles_copy[j];
						}
					score-=undo_score;
					undo_score=0;
					undo_flag++;
					system("cls");
					//PrintBoard();
				}
				else
				{
					//system("cls");
					printf("\n\nYou cannot undo the matrix consequtively\n\nSorry!!!\n");
				}
				break;
			}
				
			if(userChoice=='w'||userChoice=='a'||userChoice=='s'||userChoice=='d') generate_new_index();
			PrintBoard();
			int find_max=calculate_max();
			if(find_max==2048)
			{
				wins();
			}
			if(NotEmpty())
			{
				if(game_ends())
				{
					lost();
				}
			}	
			userChoice = getch();
			undo_flag=0;
			while((userChoice!='w'  && userChoice!='s'  && userChoice!='d'  && userChoice!='a' && userChoice!='q' && userChoice!='u' && userChoice!='i' && userChoice!='r' ))
			{
				userChoice = getch();
				undo_flag=0;
			}		
		}	
	}while(Empty() && userChoice != 'q');
	
	
}

int main()
{

	Start();
}
