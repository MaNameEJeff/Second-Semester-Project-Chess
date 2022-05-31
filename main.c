#include <stdio.h>
#include <stdlib.h>

int moves[27] = {};
char board[8][8] = {};
char current_player = 'w';

//Check if letter is capital
int is_capital(char letter) {
	if(((int)letter >= (int)'A') && ((int)letter <= (int)'Z'))
		return 1;
	else
		return 0;
}

//Convert coordinates into indices of board
void get_indices(char* pos) {
	*pos = (char)((int)*pos - 17);
	pos++;
	*pos = (char)((int)*pos - 1);
}

//Output the board in formatted form
void display(char *b) {
	int count = 1;

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
				if(*b)
					printf("[%c] ", *b);
				else
					printf("[ ] ");
				b++;
			}
		}
		printf("\n\n");
	}
}

//Get input from the user and check if its valid
char* input() {

	static char s[3] = {};

	while(1) {

		//Display board and prompt
		display(&board[0][0]);
		printf("\nEnter the column and row of a pawn to move ( CR ): ");
		scanf("%2s", s);
		get_indices(s);

		//Perform checks to see if input is valid
		if(board[atoi(&s[1])][atoi(&s[0])] == '\0') {
			printf("\nThat position is empty\n");
			continue;
		} else if((atoi(&s[0]) < 0) || (atoi(&s[0]) > 7) || (atoi(&s[1]) < 0) && (atoi(&s[1]) > 7)) {
			printf("\nThat position is not on the board!\n");
			continue;
		} else if((current_player == 'w') && !is_capital(board[atoi(&s[1])][atoi(&s[0])]) || (current_player == 'b') && is_capital(board[atoi(&s[1])][atoi(&s[0])])) {
			printf("\nYou cannot move that piece\n");
			continue;
		}
		break;
	}
	return s;
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

int main() {
	initialize(&board[0][0]);
	printf("%s", input());
	return 0;
}