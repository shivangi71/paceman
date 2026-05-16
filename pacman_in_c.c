// Pacman in C language
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#include<dos.h>

// All the elements to be used 
// Declared here
#define width 70
#define height 30
#define pacman 'C'
#define wall '#'
#define FOOD '.'
#define empty ' '
#define demon 'X'

// Global variable are declared here 

int res = 0;
int score = 0;
int pacman_x , pacman_y;
char board[height][width];
int food = 0;
int curr = 0;

// prototypes of functions 

void initialize();
void draw();
void move(int move_x, int move_y);

// Main function
int main()
{
	char ch;
	int totalFood;
	system("color 0a");
	initialize();
	
	//food -= 35;
	totalFood = food;
	
	// Instructions to play
	
	printf("Use buttons for u(up) , l(left) , r(right) and d(down).\nAlso , Press q for quit\n");
	
	printf("Enter Y to continue: \n");
	
	ch = getch();
	if(ch != 'Y' && ch != 'y')
	{
		printf("Exit Game! ");
		return 1;
	}
	
	while(1)
	{
		draw();
		printf("Total Food count: %d\n",totalFood);
		printf("Total Food eaten: %d\n",curr);
		
		if(res == 1)
		{
			// Clear screen
			system("cls");
			printf("Game Over ! Dead by Demon\nYour Score: %d\n",score);
			return 1;
		}
		
		if(res == 2)
		{
			// Clear screen
			system("cls");
			printf("You Win ! \nYour Score: %d\n",score);
			return 1;
		}
		
		// Taking the Input from the user 
		ch = getch();
		
		// Moving according to the input character
		switch(ch)
		{
			case 'u':
				move(0,-1);
				break;
				
			case 'd':
				move(0,1);
				break;
				
			case 'l':
				move(-1,0);
				break;
				
			case 'r':
				move(1,0);
				break;
			
			case 'q':
				printf("Game Over ! Your Score: %d\n",score);
				return 0;
		}
	}
	return 0;
}
void initialize()
{
	int i,j,count = 50,val = 5,row;
	//putting Walls as boundary in the Game
	for(i=0 ; i < height ; i++)
	{
		for(j=0 ; j<width ; j++)
		{
			if(i == 0 || j == (width - 1) || j == 0 || i == (height - 1))
				board[i][j] = wall ;
			else
				board[i][j] = empty;
		}
	}
	// Putting Walls inside the Game
	srand(time(NULL));
	while (count != 0)
	{
		i = (rand() % (height + 1));
		j = (rand() % (width + 1));
		
		if(board[i][j] != wall && board[i][j] != pacman)
		{
			board[i][j] = wall;
			count--;
		}
		
	}
	while(val--)
	{
		//int row,j;
		row = (rand() % (height + 1));
		for(j = 3; j < width - 3; j++)
		{
			if(board[row][j] != wall && board[row][j] != pacman)
				board[row][j] = wall;
		}
	}

	//  Putting demons in the Game
	count = 10;
	while (count != 0)
	{
		i = (rand() % (height + 1));
		j = (rand() % (width + 1));
		
		if(board[i][j] != wall && board[i][j] != pacman)
		{
			board[i][j] = demon;
			count--;
		}
	}
	// cursor at center
	
	pacman_x = width/2;
	pacman_y = height/2;
	board[pacman_y][pacman_x] = pacman;
	
	//points placed
	
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			if((i%2 == 0 && j%2 == 0) && (board[i][j] != wall) && (board[i][j] != demon) && (board[i][j] != pacman))
			{
				board[i][j] = FOOD;
				food++;
			}
		}
	}
}
void draw()
{
	int i,j;
	// Clear screen
	system("cls");
	
	// Drawing all the elements in the screen
	for(i=0; i<height ;i++)
	{
		for(j=0; j<width ;j++)
		{
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
	printf("Score: %d\n",score);	
}
void move(int move_x, int move_y)
{
	int x,y,i,j,count=2;
	x = pacman_x + move_x;
	y = pacman_y + move_y;
	
	if(board[y][x] != wall)
	{
		if(board[y][x] == FOOD)
		{
			score++;
			food--;
			curr++;
			if(food == 0)
			{
				res = 2;
				return;
			}
			while (count != 0)
			{
				i = (rand() % (height + 1));
				j = (rand() % (width + 1));
				
				if(board[i][j] == empty)
				{
					board[i][j] = demon;
					count--;
				}
			}
		}
		else if(board[y][x] == demon)
		{
			res = 1;
		}
		board[pacman_y][pacman_x] = empty;
		pacman_x = x;
		pacman_y = y;
		board[pacman_y][pacman_x] = pacman;
	}
}
