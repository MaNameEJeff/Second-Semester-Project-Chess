#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void intro();
void rook(int r, int c);
void bishop(int r, int c);
void horse(int r, int c);
void queen(int r, int c);
void king(int r, int c);
void pawn(int r, int c);
int check_pos(int row, int column);
int is_capital(char letter);
int input(int moving);
void display(int temp);
void initialize();
void get_moves(char piece, int r, int c);
void reset_moves();
bool check_for_attack(char piece);
void check();

char current_player = 'W';
char board[8][8] = {};
int moves[8][8] = {};
bool checked = false;

void intro() {
	FILE* ptr;
    char str[50];
    ptr = fopen("chess.txt", "r");
    while (fgets(str, 50, ptr) != NULL) {
        printf("%s", str);
    }
 
    fclose(ptr);

}

// Valid moves for the rook
void rook(int r, int c) {
	int checked = 0;
	bool u_flag = true, d_flag = true, l_flag = true, r_flag = true;

	for(int i = 1; i<8; i++) {
		checked = check_pos(r-i, c);

		if((r-i) >= 0 && u_flag){
			if(!checked || (checked == 2)) {
				moves[r-i][c] = checked;
				u_flag = false;
			}
			moves[r-i][c] = checked;
		}

		checked = check_pos(r+i, c);
		if((r+i) < 8 && d_flag){
			if(!checked || (checked == 2)) {
				moves[r+i][c] = checked;
				d_flag = false;
			}
			moves[r+i][c] = checked;
		}

		checked = check_pos(r, c-i);
		if((c-i) >= 0 && l_flag){
			if(!checked || (checked == 2)) {
				moves[r][c-i] = checked;
				l_flag = false;
			}
			moves[r][c-i] = checked;
		}
		
		checked = check_pos(r, c+i);
		if((c+i) < 8 && r_flag){
			if(!checked || (checked == 2)) {
				moves[r][c+i] = checked;
				r_flag = false;
			}
			moves[r][c+i] = checked;
		}
	}
}

// Valid moves for the bishop
void bishop(int r, int c) {
	int checked = 0;
	bool ul_flag = true, ur_flag = true, ll_flag = true, lr_flag = true;

	for(int i = 1; i<8; i++) {
		checked = check_pos(r-i, c-i);

		if((r-i) >= 0 && (c-i) >= 0 && ul_flag){
			if(!checked || (checked == 2)) {
				moves[r-i][c-i] = checked;
				ul_flag = false;
			}
			moves[r-i][c-i] = checked;
		}

		checked = check_pos(r-i, c+i);
		if((r-i) >= 0 && (c+i) <8 && ur_flag){
			if(!checked || (checked == 2)) {
				moves[r-i][c+i] = checked;
				ur_flag = false;
			}
			moves[r-i][c+i] = checked;
		}

		checked = check_pos(r+i, c-i);
		if((r+i) < 8 && (c-i) >= 0 && ll_flag){
			if(!checked || (checked == 2)) {
				moves[r+i][c-i] = checked;
				ll_flag = false;
			}
			moves[r+i][c-i] = checked;
		}
		
		checked = check_pos(r+i, c+i);
		if((r+i) < 8 && (c+i) < 8 && lr_flag){
			if(!checked || (checked == 2)) {
				moves[r+i][c+i] = checked;
				lr_flag = false;
			}
			moves[r+i][c+i] = checked;
		}
	}
}

// Valid moves for horse
void horse(int r, int c) {

	int c_sign = -1, r_sign = -1, checked = 0;

	for(int i = 0; i<2; i++) {
		for(int j = 0; j<2; j++) {

			checked = check_pos(r+(r_sign*2), c+(c_sign*1));
			if(checked == 1 || checked == 2)
				moves[r+(r_sign*2)][c+(c_sign*1)] = checked;
			
			checked = check_pos(r+(c_sign*1), c+(r_sign*2));
			if(checked == 1 || checked == 2)
				moves[r+(c_sign*1)][c+(r_sign*2)] = checked;
			
			c_sign *= -1;
		}
		r_sign *= -1;
	}
}

// Valid moves for the queen
void queen(int r, int c) {
	bishop(r, c);
	rook(r, c);
}

// Valid moves for the king
void king(int r, int c) {

	enum directions {U, D, L, R, UL, UR, DL, DR};

	typedef struct {
		int row;
		int col;
	} cell;

	cell possible_moves[8];
	int checked = 0;

	possible_moves[U] = (cell){r+1, c};
	possible_moves[D] = (cell){r-1,  c};
	possible_moves[L] = (cell){r,    c-1};
	possible_moves[R] = (cell){r,    c+1};
	possible_moves[UL] = (cell){r+1, c-1};
	possible_moves[UR] = (cell){r+1, c+1};
	possible_moves[DL] = (cell){r-1, c-1};
	possible_moves[DR] = (cell){r-1,  c+1};

	for(int i = 0; i<8;i++) {
		checked = check_pos(possible_moves[i].row, possible_moves[i].col);
		if(checked == 2 || checked == 1)
			moves[possible_moves[i].row][possible_moves[i].col] = checked;
	}
	moves[r][c] = 3;
}

// Valid moves for pawn
void pawn(int r, int c) {

	int sign = 1;

	if(current_player == 'B')
		sign *= -1;
		
	if(board[r-(1*sign)][c] == '\0')
		moves[r-(1*sign)][c] = 1;
	if(((r==6) && (current_player == 'W')) || ((r==1) && (current_player == 'B')))
		if(board[r-(2*sign)][c] == '\0')
			moves[r-(2*sign)][c] = 1;

	if(check_pos(r-(1*sign), c-(1*sign*-1)) == 2)
		moves[r-(1*sign)][c-(1*sign*-1)] = 2;
	if(check_pos(r-(1*sign), c+(1*sign*-1)) == 2)
		moves[r-(1*sign)][c+(1*sign*-1)] = 2;
}

//Perform checks to see if position is valid
int check_pos(int row, int column) {

	if((column < 0) || (column > 7) || (row < 0) || (row > 7)) {
		// Out of board
		return -1;
	} else if (board[row][column] == '\0') {
		// Empty
		return 1;
	} else if((current_player == 'W') && !is_capital(board[row][column]) || (current_player == 'B') && is_capital(board[row][column])) {
		// Opponent piece
		return 2;
	}

	// Player piece
	return 0;
}

//Check if letter is capital
int is_capital(char letter) {
	if(((int)letter >= (int)'A') && ((int)letter <= (int)'Z'))
		return true;
	else
		return false;
}

//Get input from the user and check if its valid
int input(int moving) {

	static char s[3] = {};

	while(1) {

		//Display prompts
		printf("\nEnter the column and row of a pawn to move ( CR ): ");
		scanf("%2s", s);
		if(check_pos(s[1]-49, s[0]-65) && !moving)
			continue;
        break;
	}
	return ((int)(s[0]-65)*10 + (int)(s[1]-49));
}

//Output the board in formatted form
// void display(int temp) {
// 	int count = 1;

// 	for(int k = (int)'A'; k<=(int)'H';k++)
// 		printf("-----");
// 	printf("\n");

// 	for(int i = 0; i<8; i++) {

// 		//Display the column indices
// 		if(i == 0) {
// 			for(int k = (int)'A'; k<=(int)'H';k++)
// 				printf(" %c  ", k);
// 			printf("\n\n");
// 		}

// 		for(int j = 0; j<9; j++) {

// 			//Display the row indices
// 			if(j == 8) {
// 				printf(" %d", count);
// 				count++;
// 			} else {

// 				//Display the elements in board
// 				if(temp) {
// 					if(board[i][j])
// 						printf("[%c] ", board[i][j]);
// 					else
// 						printf("[ ] ");
// 				} else {
// 					if(moves[i][j])
// 						printf("[%d] ", moves[i][j]);
// 					else
// 						printf("[ ] ");
// 				}
// 			}
// 		}
// 		printf("\n\n");
// 	}
// }

char* unicode_symbols(char piece) {
    switch(piece) {
		case 'K':
			return "\u2654";
		case 'Q':
			return "\u2655";
		case 'B':
			return "\u2657";
		case 'H':
			return "\u2658";
		case 'R':
			return "\u2656";
		case 'P':
			return "\u2659";
		case 'k':
			return "\u265A";
		case 'q':
			return "\u265B";
		case 'b':
			return "\u265D";
		case 'h':
			return "\u265E";
		case 'r':
			return "\u265C";
		case 'p':
			return "\u265F";
    }
}

void display(int display_moves) {
    int count = 1;

    for(int k = (int)'A'; k<=(int)'H';k++)
        printf("-----");
    printf("\n");

    for(int i = 0; i<8; i++) {

        //Display the column indices
        if(i == 0) {
            for(int k = (int)'A'; k<=(int)'H';k++)
                printf(" %c ", k);
            printf("\n\n");
        }

        for(int j = 0; j<9; j++) {

            //Display the row indices
            if(j == 8) {
                printf(" %d", count);
                count++;
            } else {

                //Display the elements in board
                if(display_moves == 1) {
                    if(board[i][j]) {
                    	//printf("i=%d\tj=%d\tmoves[i][j]=%d\n", i, j, moves[i][j]);
                        if((i+j)%2==0) {
                        	if(moves[i][j] == 1)
                        		printf("\033[48;2;211;215;207;38;2;0;0;0m %s \033[0m", unicode_symbols(board[i][j]));
                        	else
                        		printf("\033[48;2;211;215;207;38;2;0;0;0m %s \033[0m", unicode_symbols(board[i][j]));
                        } else {
                        	if(moves[i][j] == 1)
                        		printf("\033[48;2;139;69;19;38;2;0;0;0m %s \033[0m", unicode_symbols(board[i][j]));
                        	else
                            	printf("\033[48;2;139;69;19;38;2;0;0;0m %s \033[0m", unicode_symbols(board[i][j]));
                        }
                    } else {
                        if(i) {
                            if ((i+j)%2==0) {
                            	if(moves[i][j] == 1)
                        			printf("\033[48;2;211;215;207;38;2;0;255;0m · \033[0m");
                        		else
                        			printf("\033[48;2;211;215;207;38;2;0;0;0m   \033[0m");
                        	} else {
                        		if(moves[i][j] == 1)
                        			printf("\033[48;2;139;69;19;38;2;0;255;0m · \033[0m");
                        		else
                            		printf("\033[48;2;139;69;19;38;2;0;0;0m   \033[0m");
                        	}
                        }
                    }
                } else {
                    if(moves[i][j])
                        printf("[%d] ", moves[i][j]);
                    else
                        printf("[ ]");
                }
            }
        }
        printf("\n");
    }
}



//Set the board to its starting position
void initialize() {
	char *pawns = "rhbqkbhr";

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

//Get the possible moves for a respective piece
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

//Reset the moves 2D array
void reset_moves() {
	for(int i = 0; i<8; i++) {
		for(int j = 0; j<8; j++) {
			moves[i][j] = 0;
		}
	}
}

//Check if the player king is being attacked
bool check_for_attack(char piece) {
	for(int i = 0; i<8; i++) {
		for(int j = 0; j<8; j++) {
			if((moves[i][j] == 2) && (board[i][j] == piece)) {
				reset_moves();
				return true;
			}
		}
	}
	reset_moves();
	return false;
}

void check() {
	checked = false;
	for(int i = 0; i<8; i++) {
		if(checked)
			break;
		for(int j = 0; j<8; j++) {
			if((current_player == 'W') && (board[i][j] == 'K')) {
				queen(i, j);
				if(check_for_attack('q')) {
					checked = true;
					break;
				}
				rook(i, j);
				if(check_for_attack('r')) {
					checked = true;
					break;
				}
				bishop(i, j);
				if(check_for_attack('b')) {
					checked = true;
					break;
				}
				horse(i, j);
				if(check_for_attack('h')) {
					checked = true;
					break;
				}
			} else if((current_player == 'B') && (board[i][j] == 'k')) {
				queen(i, j);
				if(check_for_attack('Q')) {
					checked = true;
					break;
				}
				rook(i, j);
				if(check_for_attack('R')) {
					checked = true;
					break;
				}
				bishop(i, j);
				if(check_for_attack('B')) {
					checked = true;
					break;
				}
				horse(i, j);
				if(check_for_attack('H')) {
					checked = true;
					break;
				}
			}
		}
	}
}

int main() {

    while(true) {
    	
    	//exit(0);

        system("@cls||clear");
        // printf("----------------\n");
        // printf("   Chess in C\n");
        // printf("----------------\n\n");
        intro();
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

    while(true){
    	not_cleared_check:
        system("@cls||clear");
        if(current_player == 'W')
        	printf("White's turn\n");
        else
        	printf("Black's turn\n");
        display(1);

     	int pos = input(0);
     	int column = pos/10, row = pos%10;
     	get_moves(board[row][column], row, column);

     	moves[row][column] = 3;
        //system("@cls||clear");
        display(1);
        display(0);
        printf("\n");

        retry:
        pos = input(1);
        int new_column = pos/10, new_row = pos%10;
        char temp_piece  = board[new_row][new_column];

        if(moves[new_row][new_column] == 1 || moves[new_row][new_column] == 2){
            board[new_row][new_column] = board[row][column];
            board[row][column] = '\0';
            check();
            printf("CHECKED = %d", checked);
            if(checked == true) {
            	printf("\n\nCHECKED!!!!!\n\n");
            	board[row][column] = board[new_row][new_column];
            	board[new_row][new_column] = temp_piece;
            	goto not_cleared_check;
            }
        } else {
        	goto retry;
        }

        reset_moves();
        if(current_player == 'W')
        	current_player = 'B';
        else
        	current_player = 'W';
    }
    return 0;
}
