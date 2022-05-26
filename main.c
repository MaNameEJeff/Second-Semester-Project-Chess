#include <stdio.h>

int moves[27] = {};
char board[8][8] = {};

int input() {

	char str_pos[3] = {};
	printf("Enter a pawn to move: ");
	scanf("%2s", str_pos);

	

	return pos;
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
				case 6:
					board[i][j] = (char)((*pawns)-32); //Capitalize the pieces
					pawns--;
					break;

				//Set the white pawns
				case 7:
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
	display(&board[0][0]);
	return 0;
}