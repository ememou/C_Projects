#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define EASY 6
#define MEDIUM 12
#define EXPERT 24
#define NOT_OBVIOUS '-'
#define NARKH '*'
char displayed[EXPERT][EXPERT], game[EXPERT][EXPERT];
//arxikopoiisi tou game
void game_start(int size);
void game_start(int size){
	
	int i, j, narkes, row, col, count=0, how_many=0;
	
	for(i=1; i<=size; i++){
		for(j=1; j<=size; j++){
			game[i][j]=NOT_OBVIOUS;
		} 
	}
	
	narkes=(size*size*20)/100;
	
	srand(time(NULL));
	
	while (how_many<narkes){
		row=rand()%size +1;
		col=rand()%size +1;
		if (game[row][col]!=NARKH){
			how_many++;
			game[row][col]=NARKH;
		}
	}
	//briskei ton arithmo pu antistoixei se kathe keli me basi twn arithmo twnn narkwn
	for(i=1; i<=size; i++){
		for(j=1; j<=size; j++){
			if(game[i][j]!=NARKH){
				if(i==1){
					if (j==1){
						if (game[i+1][j]==NARKH){
							count++;
						}
						if (game[i][j+1]==NARKH){
							count++;
						}
						if (game[i+1][j+1]==NARKH){
							count++;
						}
						game[i][j]=(char)count;
					}
					else if(j==size){
						if (game[i+1][j]==NARKH){
							count++;
						}
						if (game[i][j-1]==NARKH){
							count++;
						}
						if (game[i+1][j-1]==NARKH){
							count++;
						}
						game[i][j]=(char)count;
					}
					else{
						if (game[i+1][j]==NARKH){
							count++;
						}
						if (game[i+1][j-1]==NARKH){
							count++;
						}
						if (game[i][j-1]==NARKH){
							count++;
						}
						if (game[i][j+1]==NARKH){
							count++;
						}
						if (game[i+1][j+1]==NARKH){
							count++;
						}
						game[i][j]=(char)count;
					}
					count=0;
				}
				else if(i==size){
					if(j==1){
						if (game[i-1][j]==NARKH){
							count++;
						}
						if (game[i][j+1]==NARKH){
							count++;
						}
						if (game[i-1][j+1]==NARKH){
							count++;
						}
						game[i][j]=(char)count;
					}
					else if(j==size){
						if (game[i-1][j]==NARKH){
							count++;
						}
						if (game[i][j-1]==NARKH){
							count++;
						}
						if (game[i-1][j-1]==NARKH){
							count++;
						}
						game[i][j]=(char)count;
					}
					else{
						if (game[i-1][j]==NARKH){
							count++;
						}
						if (game[i-1][j-1]==NARKH){
							count++;
						}
						if (game[i][j-1]==NARKH){
							count++;
						}
						if (game[i][j+1]==NARKH){
							count++;
						}
						if (game[i-1][j+1]==NARKH){
							count++;
						}
						game[i][j]=(char)count;
					}
					count=0;
				}
				else if(j==1){
					if (game[i-1][j]==NARKH){
						count++;
					}
					if (game[i+1][j]==NARKH){
						count++;
					}
					if (game[i-1][j+1]==NARKH){
						count++;
					}
					if (game[i][j+1]==NARKH){
						count++;
					}
					if (game[i+1][j+1]==NARKH){
						count++;
					}
					game[i][j]=(char)count;
				}
				else if(j==size){
					if (game[i-1][j]==NARKH){
						count++;
					}
					if (game[i+1][j]==NARKH){
						count++;
					}
					if (game[i-1][j-1]==NARKH){
						count++;
					}
					if (game[i][j-1]==NARKH){
						count++;
					}
					if (game[i+1][j-1]==NARKH){
						count++;
					}
					game[i][j]=(char)count;
				}
				else{
					if (game[i-1][j-1]==NARKH){
						count++;
					}
					if (game[i-1][j]==NARKH){
						count++;
					}
					if (game[i-1][j+1]==NARKH){
						count++;
					}
					if (game[i][j-1]==NARKH){
						count++;
					}
					if (game[i][j+1]==NARKH){
						count++;
					}
					if (game[i+1][j-1]==NARKH){
						count++;
					}
					if (game[i+1][j]==NARKH){
						count++;
					}
					if (game[i+1][j+1]==NARKH){
						count++;
					}
					game[i][j]=(char)count;
				}
				count=0;
			}
		}
	}
}
//arxikopoiisi tou pinaka displayed
void displayed_start(int size);
void displayed_start(int size){
	int i, j;
	for(i=1; i<=size; i++){
		for(j=1; j<=size; j++){
			displayed[i][j]=NOT_OBVIOUS;
		}
	}
}

int main(int argc, char *argv[]) {
	
	char level, play;
	int i, j, row, col, size, narkes, flag=0;
	
	do{
		flag=0;
		//epilogi epipedou
		printf("\t1. EASY (E,e)\n");
		printf("\t2. MEDIUM (M,m)\n");
		printf("\t3. EXPERT (X,x)\n");
		printf("Choose difficulty level: ");
		scanf(" %c", &level);
		printf("\n");
		while (level!='E' && level!='e' && level!='M' && level!='m' && level!='X' && level!='x'){
			printf("\t1. EASY (E,e)\n");
			printf("\t2. MEDIUM (M,m)\n");
			printf("\t3. EXPERT (X,x)\n");
			printf("Choose difficulty level: ");
			scanf(" %c", &level);
			printf("\n");
		}
		
		if(level=='E' || level=='e'){
			size=EASY;
		}
		else if(level=='M' || level=='m'){
			size=MEDIUM;
		}
		else{
			size=EXPERT;
		}
		
		narkes=(size*size*20)/100;
		game_start(size);
		displayed_start(size);
		//ektipwsi pinaka displayed
		printf("   ");
		for(i=1; i<=size; i++){
			printf("%2d ", i);
		}
		printf("\n\n");
		for(i=1; i<=size; i++){
			printf("%2d ", i);
			for(j=1; j<=size; j++){
				printf("%2c ", displayed[i][j]);
			}
			printf("\n");
		}
		
		printf("\n");
		printf("Row> ");
		scanf("%d", &row);
		printf("Col> ");
		scanf("%d", &col);
		while(row>size || row<0 || col<=0 || col>size){
			if(row>size || row<0){
				printf("Invalid Row. Try again!\n");
				printf("Row> ");
				scanf("%d", &row);
			}
			else if(col>size || col<=0){
				printf("Invalid Column. Try again!\n");
				printf("Col> ");
				scanf("%d", &col);
			}
			else{
				printf("Invalid Row. Try again!\n");
				printf("Invalid Column. Try again!\n");
				printf("Row> ");
				scanf("%d", &row);
				printf("Col> ");
				scanf("%d", &col);
			}
		}
		if(row==0){														//an epileksei row=0 o xristis 
			printf("You selected to interrupt the current puzzle!\n\n");
			printf("Play again? (y/n) ");
			scanf(" %c", &play);
			printf("\n");
			while (play!='y' && play!='Y' && play!='N' && play!='n'){
				printf("Play again? (y/n) ");
				scanf(" %c", &play);
				printf("\n");
			}
			if (play=='n' || play=='N'){
				break;
			}
			displayed_start(size);
		}
		//ektipwsi displayed me basi tin epilogi tou xristi
		displayed[row][col]=game[row][col];
		while(displayed[row][col]!=NARKH && flag < size*size - narkes){
			displayed[row][col]=game[row][col];
			printf("   ");
			if(displayed[row][col]!=NARKH){
				for(i=1; i<=size; i++){
					printf("%2d ", i);
				}
				printf("\n\n");
				for(i=1; i<=size; i++){
					printf("%2d ", i);
					for(j=1; j<=size; j++){
						if (displayed[i][j]==NOT_OBVIOUS){
							printf("%2c ", displayed[i][j]);
						}
						else{
							printf("%2d ", displayed[i][j]);
						}
					}
					printf("\n");
				}
				
				if(flag<size*size - narkes - 1){
					printf("\n");
					printf("Row> ");
					scanf("%d", &row);
					printf("Col> ");
					scanf("%d", &col);
					while(row>size || row<0 || col<=0 || col>size){
						if(row>size || row<0){
							printf("Invalid Row. Try again!\n");
							printf("Row> ");
							scanf("%d", &row);
						}
						else if(col>size || col<=0){
							printf("Invalid Column. Try again!\n");
							printf("Col> ");
							scanf("%d", &col);
						}
						else{
							printf("Invalid Row. Try again!\n");
							printf("Invalid Column. Try again!\n");
							printf("Row> ");
							scanf("%d", &row);
							printf("Col> ");
							scanf("%d", &col);
						}
					}
					if(row==0){
						printf("You selected to interrupt the current puzzle!\n\n");
						printf("Play again? (y/n) ");
						scanf(" %c", &play);
						printf("\n");
						while (play!='y' && play!='Y' && play!='N' && play!='n'){
							printf("Play again? (y/n) ");
							scanf(" %c", &play);
							printf("\n");
						}
						if (play=='n' || play=='N'){
							return 0;
						}
						displayed_start(size);
					}
					if(displayed[row][col]!=NOT_OBVIOUS){
						flag--;
					}
				}
			}
			flag++;
		}
		
		printf("\n");
		//ektipwsi minimatos me basi to apotelesma tou paixnidiou 
		if (flag== size*size - narkes){
			printf("Congratulation you have solve the puzzle!\n\n");
		}
		else{
			printf("Oops! You selected a mine.\n\n");
		}
		printf("   ");
		for(i=1; i<=size; i++){
			printf("%2d ", i);
		}
		printf("\n\n");
		for(i=1; i<=size; i++){											//ektipwsi tou pinaka game
			printf("%2d ", i);
			for(j=1; j<=size; j++){
				if(game[i][j]==NARKH){
					printf("%2c ",game[i][j]);
				}
				else{
					printf("%2d ",game[i][j]);
				}
			}
			printf("\n");
		}
		printf("\n\n");
		
		printf("Play again? (y/n) ");
		scanf(" %c", &play);
		printf("\n");
		while (play!='y' && play!='Y' && play!='N' && play!='n'){
			printf("Play again? (y/n) ");
			scanf(" %c", &play);
			printf("\n");
		}
	}while(play=='y' || play=='Y');
	
	return 0;
}