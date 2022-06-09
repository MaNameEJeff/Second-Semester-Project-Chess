#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int check_pos(int row, int column);
int is_capital(char letter);
int get_indices(char* pos);
void display();
int input(int moving);
void initialize();
void rook(int r, int c);
void bishop(int r, int c);

char current_player[] = "White";
char board[8][8] = {};
int moves[8][8] = {};

void rook(int r, int c) {
	int count = 1;

	while(1) {
		if(r-count >= 0) {
			if(board[r-count][c] != '\0') {
				if(!strcmp(current_player, "White") && !is_capital(board[r-count][c]) || !strcmp(current_player, "Black") && is_capital(board[r-count][c])) {
					moves[r-count][c] = 2;
				}
			} else {
				moves[r-count][c] = 1;
				count++;
				continue;
			}
		}
		break;
	}

	count=1;
	while(1) {
		if(r+count < 8) {
			if(board[r+count][c] != '\0') {
				if(!strcmp(current_player, "White") && !is_capital(board[r+count][c]) || !strcmp(current_player, "Black") && is_capital(board[r+count][c])) {
					moves[r+count][c] = 2;
				}
			} else {
				moves[r+count][c] = 1;
				count++;
				continue;
			}
		}
		break;
	}

	count=1;
	while(1) {
		if(c-count >= 0) {
			if(board[r][c-count] != '\0') {
				if(!strcmp(current_player, "White") && !is_capital(board[r][c-count]) || !strcmp(current_player, "Black") && is_capital(board[r][c-count])) {
					moves[r][c-count] = 2;
				}
			} else {
				moves[r][c-count] = 1;
				count++;
				continue;
			}
		}
		break;
	}
		
	count=1;
	while(1) {
		if(c+count < 8) {
			if(board[r][c+count] != '\0') {
				if(!strcmp(current_player, "White") && !is_capital(board[r][c+count]) || !strcmp(current_player, "Black") && is_capital(board[r][c+count])) {
					moves[r][c+count] = 2;
				}
			} else {
				moves[r][c+count] = 1;
				count++;
				continue;
			}
		}
		break;
	}
}

void bishop(int r, int c) {
	int count = 1;

	while(1) {
		if((r-count >= 0) && (c-count >= 0)) {
				
			if(board[r-count][c-count] != '\0') {
				if(!strcmp(current_player, "White") && !is_capital(board[r-count][c-count]) || !strcmp(current_player, "Black") && is_capital(board[r-count][c-count])) {
					moves[r-count][c-count] = 2;
				}
			} else {
				moves[r-count][c-count] = 1;
				count++;
				continue;
			}
		}
		break;
	}
	
	count=1;
	while(1) {
		if((r-count >= 0) && (c+count < 8)) {
			if(board[r-count][c+count] != '\0') {
				if(!strcmp(current_player, "White") && !is_capital(board[r-count][c+count]) || !strcmp(current_player, "Black") && is_capital(board[r-count][c+count])) {
					moves[r-count][c+count] = 2;
				}
				break;
			} else {
				moves[r-count][c+count] = 1;
				count++;
				continue;
			}
		}
		break;
	}

	count=1;
	while(1) {
		if((r+count < 8) && (c-count >= 0)) {
			if(board[r+count][c-count] != '\0') {
				if(!strcmp(current_player, "White") && !is_capital(board[r+count][c-count]) || !strcmp(current_player, "Black") && is_capital(board[r+count][c-count])) {
					moves[r+count][c-count] = 2;
				}
				break;
			} else {
				moves[r+count][c-count] = 1;
				count++;
				continue;
			}
		}
		break;
	}
		
	count=1;
	while(1) {
		if((r+count < 8) && (c+count < 8)) {
			if(board[r+count][c+count] != '\0') {
				if(!strcmp(current_player, "White") && !is_capital(board[r+count][c+count]) || !strcmp(current_player, "Black") && is_capital(board[r+count][c+count])) {
					moves[r+count][c+count] = 2;
				}
				break;
			} else {
				moves[r+count][c+count] = 1;
				count++;
				continue;
			}
		}
		break;
	}
}

void horse(int r, int c) {
	if((r-2 >= 0) && (c+1 < 8) && (board[r-2][c+1] != '\0')) {
		if(!strcmp(current_player, "White") && !is_capital(board[r-2][c+1]) || !strcmp(current_player, "Black") && is_capital(board[r-2][c+1])) {
			moves[r-2][c+1] = 2;
		}
	} else {
			moves[r-2][c+1] = 1;
	}

	if((r-2 >= 0) && (c-1 >= 0) && (board[r-2][c-1] != '\0')) {
		if(!strcmp(current_player, "White") && !is_capital(board[r-2][c-1]) || !strcmp(current_player, "Black") && is_capital(board[r-2][c-1])) {
			moves[r-2][c-1] = 2;
		}
	} else {
			moves[r-2][c-1] = 1;
	}

	if((r+2 < 8) && (c-1 >= 0) && (board[r+2][c-1] != '\0')) {
		if(!strcmp(current_player, "White") && !is_capital(board[r+2][c-1]) || !strcmp(current_player, "Black") && is_capital(board[r+2][c-1])) {
			moves[r+2][c-1] = 2;
		}
	} else {
			moves[r+2][c-1] = 1;
	}

	if((r+2 < 8) && (c+1 < 8) && (board[r+2][c+1] != '\0')) {
		if(!strcmp(current_player, "White") && !is_capital(board[r+2][c+1]) || !strcmp(current_player, "Black") && is_capital(board[r+2][c+1])) {
			moves[r+2][c+1] = 2;
		}
	} else {
			moves[r+2][c+1] = 1;
	}
}

void queen(int r, int c) {
	bishop(r, c);
	rook(r, c);
}

void king(int r, int c) {
	int j = -1;
	for(int i = r-1; i<=(r+1); i++) {
		if(i<0 || i>7 || (i==r && j==0))
			continue;
		if(board[i][c+j] != '\0') {
			if(!strcmp(current_player, "White") && !is_capital(board[i][c+j]) || !strcmp(current_player, "Black") && is_capital(board[i][c+j])) {
				moves[i][c+j] = 2;
			} else {
				moves[i][c+j] = 1;
			}
		}

	}
}

void pawn(int r, int c) {
	if(!strcmp(current_player, "White")) {
		if(board[r-1][c] == '\0') {
			moves[r-1][c] = 1;
		}
		if(r==6)
			if(board[r-2][c] == '\0') {
				moves[r-2][c] = 1;
		}
		if((board[r-1][c-1] != '\0') && !is_capital(board[r-1][c-1]))
			moves[r-1][c-1] = 2;
		if((board[r-1][c+1] != '\0') && !is_capital(board[r-1][c+1]))
			moves[r-1][c+1] = 2;
	} else {
		if(board[r+1][c] == '\0') {
			moves[r+1][c] = 1;
		}
		if(r==1)
			if(board[r+2][c] == '\0') {
				moves[r+2][c] = 1;
		}
		if((board[r+1][c-1] != '\0') && is_capital(board[r+1][c-1]))
			moves[r+1][c-1] = 2;
		if((board[r+1][c+1] != '\0') && is_capital(board[r+1][c+1]))
			moves[r+1][c+1] = 2;
	}
}

//Perform checks to see if position is valid
int check_pos(int row, int column) {
	//printf("\n\n%c\n\n", board[row][column]);

	if(board[row][column] == '\0') {
		printf("\nThat position is empty\n");
		return 0;
	} else if((column < 0) || (column > 7) || (row < 0) || (row > 7)) {
		printf("\nThat position is not on the board!\n");
		return 0;
	} else if((current_player == "White") && !is_capital(board[row][column]) || (current_player == "Black") && is_capital(board[row][column])) {
		printf("\nYou cannot move that piece\n");
		return 0;
	}

	return 1;
}

//Check if letter is capital
int is_capital(char letter) {
	if(((int)letter >= (int)'A') && ((int)letter <= (int)'Z'))
		return 1;
	else
		return 0;
}

//Get input from the user and check if its valid
int input(int moving) {

	static char s[3] = {};

	while(1) {

		//Display prompts
		printf("\nEnter the column and row of a pawn to move ( CR ): ");
		scanf("%2s", s);
		if(!check_pos(s[1]-49, s[0]-65) && !moving)
			continue;
        break;
	}
	return ((int)(s[0]-65)*10 + (int)(s[1]-49));
}

//Output the board in formatted form
void display(int display_moves) {
	int count = 1;

	for(int k = (int)'A'; k<=(int)'H';k++)
		printf("-----");
	printf("\n");

	for(int i = 0; i<8; i++) {

		//Display the column indices
		if(i == 0) {
			for(int k = (int)'A'; k<=(int)'H';k++)
				printf(" %c  ", k);
			printf("\n\n");
		}

		for(int j = 0; j<9; j++) {

			//Display the row indices
			if(j == 8) {
				printf(" %d", count);
				count++;
			} else {

				//Display the elements in board
				if(display_moves == 0) {
					if(board[i][j])
						printf("[%c] ", board[i][j]);
					else
						printf("[ ] ");
				} else {
					if(moves[i][j])
						printf("[%d] ", moves[i][j]);
					else
						printf("[ ] ");
				}
			}
		}
		printf("\n\n");
	}
}

//Set the board to its starting position
void initialize() {
	char *pawns = "rhbkqbhr";

	for(int i = 0; i< 8; i++) {
		for(int j = 0; j<8; j++) {

			switch(i) {

				//Set the black pieces
				case 0:
					board[i][j] = *pawns;
					pawns++;
					break;

				//Set the black pawns
				case 1:
					board[i][j] = 'p';
					break;

				//Set the white pieces
				case 7:
					board[i][j] = (char)((*pawns)-32); //Capitalize the pieces
					pawns--;
					break;

				//Set the white pawns
				case 6:
					board[i][j] = 'P';
					break;
			}
		}
		if(i==0)
			pawns--;
	}
}

void get_moves(char piece, int r, int c) {
	switch(piece) {
		case 'p':
		case 'P':
			pawn(r, c);
			break;
		case 'r':
		case 'R':
			rook(r, c);
			break;
		case 'h':
		case 'H':
			horse(r, c);
			break;
		case 'b':
		case 'B':
			bishop(r, c);
			break;
		case 'k':
		case 'K':
			king(r, c);
			break;
		case 'q':
		case 'Q':
			queen(r, c);
			break;
	}
}

//char message[] = "White's turn";
int main() {

    while(1) {

        system("@cls||clear");
        printf("----------------\n");
        printf("   Chess in C\n");
        printf("----------------\n\n");
        printf("1.Start\n");
        printf("2.Exit\n");
        printf("Input: ");
        int input;
        scanf("%d", &input);

        switch(input) {
            case 1:
                goto start;
                break;
            case 2:
                return 0;
                break;
            default:
            	printf("Wrong input");
        }
    }

    start:
    initialize();

    while(1){

        system("@cls||clear");
        printf("%s's turn\n", current_player);
        display(0);

     	int pos = input(0);
     	int column = pos/10, row = pos%10;
     	get_moves(board[row][column], row, column);
     	moves[row][column] = 3;
        //system("@cls||clear");
        display(1);
        printf("\n");

        retry:
        pos = input(1);
        int new_column = pos/10, new_row = pos%10;

        if(moves[new_row][new_column] == 1 || moves[new_row][new_column] == 2){
            board[new_row][new_column] = board[row][column];
            board[row][column] = '\0';
        } else {
        	goto retry;
        }

        for(int i = 0; i<8;i++) {
        	for(int j = 0; j<8;j++) {
        		moves[i][j] = 0;
        	}
        }
        if(current_player[0] == 'W')
        	strcpy(current_player, "Black");
        else
        	strcpy(current_player, "White");
    }
    return 0;
}
