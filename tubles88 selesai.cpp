#include<time.h>
#include <stdio.h>
#include <windows.h>

void boardSpace(); // untuk menginisialisasi posisi papan yang akan diisi oleh pemain
void getNamesPVP(); // input players name for player v player mode
void drawScoreboard(); // to show players scores
void drawScoreboardPVC(); // to show players scores p v c mode
void drawGameboard(); // show and create SOS board
int takeInput(); // return 1 input adalah valid, jika salah maka return 0. Salah jika mengisi di papan yg sudah terisi (buat pvp)
int ctrlFindSOS(); // return 1 jika ada tambahan skor, jika tidak return 0. Terdapat kondisi yg menyebabkan skor bertambah

void menu(); // page menu
void exit(); // page exit
void gameMode(); // choose mode of game, can be player v player or player v computer
void boardSize(); // choose the size of the board a.k.a the level; easy, med, hard
void winner(); // to show who's the winner of the game 
void winnerPVC(); // to show who's the winner of the game for player v computer
void loading(); // pengatur tampilnya UI fitur loading
void playagain(); // jika pemain memilih bermain kembali
void gameover(); // UI ketika game berakhir
void help(); // panduan cara bermain

void pvcomp(); // arahan alur permainan jika modenya adalah player v computer
void pvp(); // arahan alur permainan jika modenya adalah player v player
void getNamesPVComp(); // input player's name for player v computer mode
int takeInputPVComp(); // return 1 input adalah valid, jika salah maka return 0. Salah jika mengisi di papan yg sudah terisi (buat pvc)

int gameDonePVC(); // untuk menentukan permainan selesai atau belum sesuai dengan sisa posisi yang tersisa (khusus untuk mode player vs computer)
int positionValidPVC(); // untuk memvalidasi apakah suatu posisi benar belum terisi atau sudah terisi (khusus untuk mode player vs computer)
int findSOS_PVC (int, int, char); // untuk mencari huruf SOS yang berderetan untuk dijadikan skor (khusus untuk mode player vs computer)
int findPosition (int); // jika kondisi findSOS_PVC tidak terpenuhi, maka komputer akan mengisi huruf S pada posisi mana saja yang belum terisi (khusus untuk mode player vs computer)
void compMove(); // untuk menentukan pergerakan atau input yang akan diberikan komputer (khusus untuk mode player vs computer)
int compFindOS (); // untuk mencari huruf OS yang berderet sebagai penentu keputusan input komputer (khusus untuk mode player vs computer)
int compFindSS (); // untuk mencari huruf OS yang berderet sebagai penentu keputusan input komputer (khusus untuk mode player vs computer)

// variabel global
int counter = 1; 			// round counter
int got=0; 					// variabel di bagian perhitungan skor untuk mode player vs computer
int n,mode; 				// n untuk menentukan ukuran papan, mode untuk menentukan mode apa yang dipilih 
int currentPlayer = 0;		// save current player, can be 0 or 1
int row, col; 				// save selected row and column
char sos[10][10]; 			// save S and O
int scores[3] = { 0,0 };	// save players scores
char name[2][20]; 			// save player nicks
char com[10]="computer"; 	// inisialisasi nick name komputer


int main(){
	menu();
	if(mode==2){
		winner();
	}else if(mode==1){
		winnerPVC();
	}
	system("pause");
	system("cls");
	exit();
	system("cls");
	printf("BYE!");
}

void winner(){
	system("cls");
	system("color 0e");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t     _________________________ \n");
	printf("\t\t\t\t\t    |     |     ___     |     |\n");
	printf("\t\t\t\t\t    |_____|    /_  |    |_____|\n");
	printf("\t\t\t\t\t          |      | |    |      \n");
	printf("\t\t\t\t\t          |      | |    |      \n");
	printf("\t\t\t\t\t          |      |_|    |      \n");
	printf("\t\t\t\t\t          |_____________|      \n");
	printf("\t\t\t\t\t                |  |           \n");
	printf("\t\t\t\t\t                |  |           \n");
	printf("\t\t\t\t\t                |  |           \n");
	printf("\t\t\t\t\t              __|  |__         \n");
	printf("\t\t\t\t\t             |________|        \n");
	printf("\t\t\t\t\t          ________________     \n");
	printf("\t\t\t\t\t        ____________________   \n");
	if (scores[0] > scores[1]) printf("\t\t\t\t\t    \xaf\xaf %s won with %d score!! \xae\xae\n\n", name[0], scores[0]);
	else if (scores[0] < scores[1]) printf("\t\t\t\t\t    \xaf\xaf %s won with %d score!! \xae\xae\n\n", name[1], scores[1]);
	else printf("\t\t\t\t\t    \xaf\xaf Game draw!! \xae\xae\n\n"); 
	system("pause");
}

void gameover(){
	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("\t\t _____________________________________________________________________________ \n");
	printf("\t\t\xb3   _______   ______   ___   ___   _____     _____   _    __  _____   _____   \xb3\n");
	printf("\t\t\xb3  |  _____| |  __  | |   | |   | |  ___|   |  _  | | |  / / |  ___| |  ___|  \xb3\n");
	printf("\t\t\xb3  | |  ___  | |  | | |   |_|   | | |___    | | | | | | / /  | |___  | |      \xb3\n");
	printf("\t\t\xb3  | | |_  | | |__| | |  _   _  | |  ___|   | | | | | |/ /   | |___| | |      \xb3\n");
	printf("\t\t\xb3  | |___| | | |  | | | | | | | | | |___    | |_| | |   /    | |___  | |      \xb3\n");
	printf("\t\t\xb3  |_______| |_|  |_| |_| |_| |_| |_____|   |_____| |__/     |_____| |_|      \xb3\n");
	printf("\t\t\xb3_____________________________________________________________________________\xb3\n");
	system("pause");
}

void winnerPVC(){
	system("cls");
	system("color 0e");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t     _________________________ \n");
	printf("\t\t\t\t\t    |     |     ___     |     |\n");
	printf("\t\t\t\t\t    |_____|    /_  |    |_____|\n");
	printf("\t\t\t\t\t          |      | |    |      \n");
	printf("\t\t\t\t\t          |      | |    |      \n");
	printf("\t\t\t\t\t          |      |_|    |      \n");
	printf("\t\t\t\t\t          |_____________|      \n");
	printf("\t\t\t\t\t                |  |           \n");
	printf("\t\t\t\t\t                |  |           \n");
	printf("\t\t\t\t\t                |  |           \n");
	printf("\t\t\t\t\t              __|  |__         \n");
	printf("\t\t\t\t\t             |________|        \n");
	printf("\t\t\t\t\t          ________________     \n");
	printf("\t\t\t\t\t        ____________________   \n");
	if (scores[0] > scores[2]) printf("\t\t\t\t\t    \xaf\xaf %s won with %d score!! \xae\xae\n\n", name[0], scores[0]);
	else if (scores[0] < scores[2]) printf("\t\t\t\t\t    \xaf\xaf %s won with %d score!! \xae\xae\n\n", com, scores[2]);
	else printf("\t\t\t\t\t    \xaf\xaf Game draw!! \xae\xae\n\n"); 
	system("pause");
}

void menu(){
int men;
	menu:
		system("cls");
		system("color 5f");
		printf("\n\n\n\n");
		printf("\t\t\t\t\t\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf WELCOME TO \xae\xae\xae\xae\xae\xae\xae\xae\xae\xae\xae\xae\xae\n");
		printf("\t\t\t\t\t ____________________________________ \n");
		printf("\t\t\t\t\t\xb3                                    \xb3\n");
    	printf("\t\t\t\t\t\xb3    _______   ________   _______    \xb3\n");
    	printf("\t\t\t\t\t\xb3   |  _____| |   __   | |  _____|   \xb3\n");
    	printf("\t\t\t\t\t\xb3   | |_____  |  |  |  | | |_____    \xb3\n");
    	printf("\t\t\t\t\t\xb3   |_____  | |  |  |  | |_____  |   \xb3\n");
    	printf("\t\t\t\t\t\xb3    _____| | |  |__|  |  _____| |   \xb3\n");
    	printf("\t\t\t\t\t\xb3   |_______| |________| |_______|   \xb3\n");
    	printf("\t\t\t\t\t\xb3                                    \xb3\n");
    	printf("\t\t\t\t\t\xb3____________________________________\xb3\n");
		printf("\t\t\t\t\t\xb3  ___    ___  _     __     __   __  \xb3\n");
		printf("\t\t\t\t\t\xb3   |  |   |  | |_  |__    |__| |__| \xb3\n");
		printf("\t\t\t\t\t\xb3   |  |__ |  |___|  __|   |__| |__| \xb3\n");
		printf("\t\t\t\t\t\xb3____________________________________\xb3\n");
    	printf("\t\t\t\t\t\xb3           Press 1 to Play          \xb3\n");
    	printf("\t\t\t\t\t\xb3____________________________________\xb3\n");
    	printf("\t\t\t\t\t\xb3           Press 2 for Help         \xb3\n");
    	printf("\t\t\t\t\t\xb3____________________________________\xb3\n");
   		printf("\t\t\t\t\t            Pick: "); scanf("%d", &men);
   		system("cls");
   		switch(men){
   		case 1:
   			gameMode();
   			break;
        case 2:
   			help();	
   			break;
   		default:
   			printf("\t\t\t\t\xaf\xaf\xaf Invalid! Choose again!");
      		system("pause");
      		goto menu;
		}
}

void help(){
	int bahasa;
	printf("1. BAHASA INDONESIA\n2. ENGLISH\n");
	scanf("%d",&bahasa);
	switch(bahasa){
		case 1:
			system("cls");
			printf("1. Pada menu awal, klik 1 untuk mulai permainan.\n");
			printf("2. Masuk ke halaman Game Mode, pilih mode yang akan dimainkan.\n   Klik 1 untuk mode player vs computer, klik 2 untuk mode player vs player,\n   dan klik 3 untuk kembali ke halaman menu.\n");
			printf("3. Jika memilih kembali ke menu maka akan dialihkan ke halaman main menu.\n");
			printf("4. Jika memilih mode player vs player maka akan masuk ke halaman input nama untuk 2 pemain.\n");
			printf("5. Jika memilih mode player vs computer maka akan masuk ke halaman input nama untuk 1 pemain.\n");
			printf("6. Selanjutnya masuk ke halaman Game Board untuk memilih ukuran papan.\n   Ukuran 3x3 adalah easy level, 5x5 adalah medium level, dan 7x7 adalah hard level.\n");
			printf("7. Mainkan permainan. Pertama, anda harus menginputkan nomor baris, lalu nomor kolom,\n   dan yang terakhir adalah hurus S/O.\n");
			printf("8. Ketika permainan berakhir, anda akan diberi kesempatan untuk bermain satu kali lagi.\n");
			printf("9. Jika memilih untuk tidak melanjutkan permainan, anda bisa langsung close program.\n");
			printf("10.Jika anda memilih bermain kembali, maka anda akan dihadapkan dengan lawan yang sama.\n   dengan permainan pertama dan melanjutkan skor pada permainan pertama pula.\n");
			system("pause");
			break;	
		case 2:
			system("cls");
			printf("1. On the main menu, click 1 to start the game.\n");
			printf("2. At the Game Mode page, select the mode you want to play. \n   Click 1 for player vs computer mode, click 2 for player vs player mode, \n   and click 3 to return to the main menu page.\n");
			printf("3. If you choose to return to the menu, you will be redirected to the main menu page.\n");
			printf("4. If you select player vs player mode, you will enter the name input page for 2 players.\n");
			printf("5. If you select player vs player mode, you will enter the name input page for 1 player.\n");
			printf("6. Next, at the Game Board page, select a board size. \n   Size 3x3 is easy level, 5x5 is medium level, and 7x7 is hard level.\n");
			printf("7. Play the game. First, you have to enter the row number, \n   then the column number, and finally the S/O letter.\n");
			printf("8. When the game ends, you will be given the opportunity to play one more time.\n");
			printf("9. If you choose not to continue the game, you can immediately close the program.\n");
			printf("10.If you choose to play again, then you will be faced with \n   the same opponent as the first game and continue to score in the first game as well\n");
			system("pause");
			break;
		default :
			printf("Invalid! choose again");
			system("pause");
			help();
	}
	main();
}

void exit(){
	int back;
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t\t _____________________________________ \n");
	printf("\t\t\t\t\t\xb3  ______   _     _   ______     __   \xb3\n");
	printf("\t\t\t\t\t\xb3 |  ___ | | |   | | |  ____|   |  |  \xb3\n");
	printf("\t\t\t\t\t\xb3 | |__/ | | |___| | | |____    |  |  \xb3\n");
	printf("\t\t\t\t\t\xb3 |  ___ / |_____  | |  ____|   |__|  \xb3\n");
	printf("\t\t\t\t\t\xb3 | |__/ |  _____| | | |____     __   \xb3\n");
	printf("\t\t\t\t\t\xb3 |______| |_______| |______|   |__|  \xb3\n");
	printf("\t\t\t\t\t\xb3_____________________________________\xb3\n");
	printf("\t\t\t\t\t\xb3           SEE YOU AGAIN :*          \xb3\n");
	printf("\t\t\t\t\t\xb3_____________________________________\xb3\n");
	printf("\t\t\t\t\t\xb3       Close Program to Quit Game    \xb3\n");
	printf("\t\t\t\t\t\xb3_____________________________________\xb3\n");
	printf("\t\t\t\t\t  <<== Press 1 to Play Again: "); scanf("%d",&back);
   	system("cls");
   	switch(back){
   		case 1:
   			playagain();
   			break;
   		default:
			printf("\n\t\t\t\t\t\xaf\xaf\xaf Invalid! Choose again!");
			system("pause");
			exit();
	}
}

void playagain(){
	system("cls");
	printf("\xdb\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdb\n");
	printf("\xdb   You have one more chance	      \xdb\n");
	printf("\xdb   to play with the same	      \xdb\n");
	printf("\xdb   opponent.            	      \xdb\n");
	printf("\xdb   The score of both players	      \xdb\n");
	printf("\xdb   will continue the score	      \xdb\n");
	printf("\xdb   of the previous match	      \xdb\n");
	printf("\xdb\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdb\n");
	system("pause");
	if(mode==1){
		pvcomp();
		winnerPVC();
		gameover();
	}else if(mode==2){
		counter=1;
		pvp();
		winner();
		gameover();
	}
}

void gameMode(){
	system("color 1f");
	printf("\n\n\n\n\n\n\n");
	printf("\t\t _________________________________________________________________________________ \n");
	printf("\t\t\xb3                                                                                 \xb3\n");
	printf("\t\t\xb3   _______   ______   ___   ___   _____     ___   ___   _____   _____   _____    \xb3\n");
	printf("\t\t\xb3  |  _____| |  __  | |   | |   | |  ___|   |   | |   | |  _  | |  _  | |  ___|   \xb3\n");
	printf("\t\t\xb3  | |  ___  | |  | | |   |_|   | | |___    |   |_|   | | | | | | | | | | |___    \xb3\n");
	printf("\t\t\xb3  | | |_  | | |__| | |  _   _  | |  ___|   |  _   _  | | | | | | | | | |  ___|   \xb3\n");
	printf("\t\t\xb3  | |___| | | |  | | | | | | | | | |___    | | | | | | | |_| | | |_| / | |___    \xb3\n");
	printf("\t\t\xb3  |_______| |_|  |_| |_| |_| |_| |_____|   |_| |_| |_| |_____| |____/  |_____|   \xb3\n");
	printf("\t\t\xb3_________________________________________________________________________________\xb3\n");
	printf("\t\t\xb3         [1] Player vs Computer       \xb3         [2] Player vs player             \xb3\n");
	printf("\t\t\xb3______________________________________\xb3__________________________________________\xb3\n");
	printf("\t\t\xb3                             [3] Back to Main Menu                               \xb3\n");
	printf("\t\t\xb3_________________________________________________________________________________\xb3\n");
	printf("\t\t                                  Pick: "); scanf("%d",&mode);
	system("cls");
	switch(mode){
		case 1:
			getNamesPVComp();
			pvcomp();
			break;
		case 2:
			getNamesPVP();
			pvp();
			break;
		case 3:
			menu();
			break;
		default:
			printf("\n\xaf\xaf\xaf Invalid! Choose again!");
			system("pause");
			gameMode();
	}
}

void boardSize(){
	int size;
	system("cls");
	system("color 3f");
   	printf("\n\n\n\n\n\n\n");
	printf("\t\t _____________________________________________________________________________________ \n");
	printf("\t\t\xb3                                                                                     \xb3\n");
	printf("\t\t\xb3   _______   ______   ___   ___   _____     ______   _____   ______   _____   _____  \xb3\n");
	printf("\t\t\xb3  |  _____| |  __  | |   | |   | |  ___|   |  ___ | |  _  | |  __  | |  ___| |  _  | \xb3\n");
	printf("\t\t\xb3  | |  ___  | |  | | |   |_|   | | |___    | |__/ | | | | | | |  | | | |     | | | | \xb3\n");
	printf("\t\t\xb3  | | |_  | | |__| | |  _   _  | |  ___|   |  ___ / | | | | | |__| | | |     | | | | \xb3\n");
	printf("\t\t\xb3  | |___| | | |  | | | | | | | | | |___    | |__/ | | |_| | | |  | | | |     | |_| / \xb3\n");
	printf("\t\t\xb3  |_______| |_|  |_| |_| |_| |_| |_____|   |______/ |_____| |_|  |_| |_|     |____/  \xb3\n");
	printf("\t\t\xb3_____________________________________________________________________________________\xb3\n");
    printf("\t\t\xb3     [1] Easy Level(3x3)    \xb3    [2] Medium Level(5x5)   \xb3    [3] Hard Level(7x7)    \xb3\n");
    printf("\t\t\xb3____________________________\xb3____________________________\xb3___________________________\xb3\n");
    printf("\t\t\xb3                             Press 0 to Back to Main Menu                            \xb3\n");
    printf("\t\t\xb3_____________________________________________________________________________________\xb3\n");
    printf("\t\t                           Your Pick: "); scanf("%d",&size);
	system("cls");
	switch(size){
		case 0:
			menu();
			break;
		case 1:
			n=3;
			loading();
			break;
		case 2:
			n=5;
			loading();
			break;
		case 3:
			n=7;
			loading();
			break;
		default:
			printf("\t\t\t\tInvalid! Choose again!");
      		system("pause");
      		boardSize();
	}
}

void gotoxy(int x, int y) {
    COORD coord;
     
    coord.X = x;
    coord.Y = y;
     
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void speed(float seconds){
 clock_t endwait;
 endwait=clock()+seconds*CLOCKS_PER_SEC;
 while(clock()<endwait){};
}

void loading(){
	system("color 0c");
	int x = 42; 
	int y = 15; 
	int n;
	//tulisan//
	gotoxy(29, 2); printf("%c", 201);
    for (int i=1;i<=57;i++){
        printf("%c", 205);
    }
    printf ("%c", 187);
    gotoxy(30,4);printf(" ***************     ***************     ***************\n");
    gotoxy(30,5);printf(" ***************     ***************     ***************\n");
    gotoxy(30,6);printf(" ***                 **           **     ***\n");
    gotoxy(30,7);printf(" ***                 **           **     ***\n");
    gotoxy(30,8);printf(" ***                 **           **     ***\n");
    gotoxy(30,9);printf(" ***************     **           **     ***************\n");
    gotoxy(30,10);printf(" ***************     **           **     ***************\n");
    gotoxy(30,11);printf("             ***     **           **                 ***\n");
    gotoxy(30,12);printf("             ***     **           **                 ***\n");
    gotoxy(30,13);printf("             ***     **           **                 ***\n");
    gotoxy(30,14);printf(" ***************     ***************     ***************\n");
    gotoxy(30,15);printf(" ***************     ***************     ***************\n"); 
	
	gotoxy(29,17);printf("%c", 200);
        for (int i=1;i<=57;i++){
                printf("%c", 205);
        }
        printf("%c", 188);
	
	// loading //
	gotoxy(x,18); printf("      Ditunggu Ya Guys Ya");
	gotoxy(x,19); printf("     =====================");
	gotoxy(x,20);printf("     %c                   %c", 186,186);
	gotoxy(x,21); printf("     =====================");
	gotoxy(x,22); printf("       Masih Loading Nih      ");
	for(n=48;n<=66;n++){
		gotoxy(n,20);printf("\xdb");
		speed(0.1);
		
		
	}
	system("cls");
}

void cakep(){
	system("cls");
	system("color 4f");
	printf("\xdb\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdf\xdb\n");
	printf("\xdb   		      \xdb\n");
	printf("\xdb     C A K E P !     \xdb\n");
	printf("\xdb   		      \xdb\n");
	printf("\xdb\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdb\n");
	printf("\xaf\xaf\xaf Congratulations, you take point! Play again!\n");
}

void pvcomp(){
	currentPlayer=0;
	boardSize();
	boardSpace();
	while(!gameDonePVC()) {
		system("cls");
		row = 0; col = 0;
		drawScoreboardPVC();
		drawGameboard();
		if(currentPlayer==0){
			int input = takeInputPVComp();
			if(input){
				int point = ctrlFindSOS();
				if (!point) {
					printf("\xaf\xaf\xaf Sorry, you didn't get point! The turn passed to the computer!\n");
					system("pause");
					currentPlayer = 2;
				}
				else {
					scores[currentPlayer] = scores[currentPlayer] + 1;
					cakep();
					system("pause");
				}
			}
		}
		else if(currentPlayer==2){
			compMove();
		}	
	}
	
}

void pvp(){
	boardSize();
	boardSpace();
	while(counter <= n * n){
		system("cls");
		row = 0; col = 0;
		drawScoreboard();
		drawGameboard();
		int input = takeInput();
		if(input){
			int point = ctrlFindSOS();
			if(!point){
				printf("\xaf\xaf\xaf Sorry, you didn't get point! The turn passed to the other player!");
				system("pause");
				getchar();
				currentPlayer = (currentPlayer + 1) % 2;
			}
			else{
				scores[currentPlayer] = scores[currentPlayer] + 1;
				cakep();
				system("pause");
				getchar();
			}
		counter++;
		}
	}
	
}

void boardSpace(){
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			sos[i][j] = ' ';
}

void getNamesPVP(){
	system("color 0b");
	printf("\n\n");
	printf(" ________________________________________________________________________________________________________________ \n");
	printf("\xb3   ______   ______   _________   ______   ______     _    _   ______     ______   ______   ___   ___   ______   \xb3\n");
	printf("\xb3  |  ____| |      | |___   ___| |  ____| |  ____|   | |  | | |  ____|   |      | |  __  | |   | |   | |  ____|  \xb3\n");
	printf("\xb3  | |____  |  __  |     | |     | |____  | |        | |  | | | |        |  __  | | |  | | |   |_|   | | |____   \xb3\n");
	printf("\xb3  |  ____| | |  | |     | |     |  ____| | |        | |  | | | |        | |  | | | |__| | |  _   _  | |  ____|  \xb3\n");
	printf("\xb3  | |____  | |  | |     | |     | |____  | |        | |__| | | |        | |  | | | |  | | | | | | | | | |____   \xb3\n");
	printf("\xb3  |______| |_|  |_|     |_|     |______| |_|        |______| |_|        |_|  |_| |_|  |_| |_| |_| |_| |______|  \xb3\n");
	printf("\xb3________________________________________________________________________________________________________________\xb3\n");
	printf("\xb3\xaf\xaf Player 1: "); scanf("%s", &name[0][0]);
	printf("\xb3\xaf\xaf Player 2: "); scanf("%s", &name[1][0]);
}

void getNamesPVComp(){
	system("color 0b");
	printf("\n\n");
	printf(" ________________________________________________________________________________________________________________ \n");
	printf("\xb3   ______   ______   _________   ______   ______     _    _   ______     ______   ______   ___   ___   ______   \xb3\n");
	printf("\xb3  |  ____| |      | |___   ___| |  ____| |  ____|   | |  | | |  ____|   |      | |  __  | |   | |   | |  ____|  \xb3\n");
	printf("\xb3  | |____  |  __  |     | |     | |____  | |        | |  | | | |        |  __  | | |  | | |   |_|   | | |____   \xb3\n");
	printf("\xb3  |  ____| | |  | |     | |     |  ____| | |        | |  | | | |        | |  | | | |__| | |  _   _  | |  ____|  \xb3\n");
	printf("\xb3  | |____  | |  | |     | |     | |____  | |        | |__| | | |        | |  | | | |  | | | | | | | | | |____   \xb3\n");
	printf("\xb3  |______| |_|  |_|     |_|     |______| |_|        |______| |_|        |_|  |_| |_|  |_| |_| |_| |_| |______|  \xb3\n");
	printf("\xb3________________________________________________________________________________________________________________\xb3\n");
	printf("\xb3\xaf\xaf Player Name: "); scanf("%s", &name[0][0]);
}

void drawScoreboard(){
	printf("%s %d : %d %s\n\n", name[0], scores[0], scores[1], name[1]);
}

void drawScoreboardPVC(){
	printf("%s %d : %d %s\n\n", name[0], scores[0], scores[2], com);
}

void drawGameboard(){
	int i, j;
	// top line
	system("color 4f");
	for(i = 1; i < (n + 2) * 6 + 2; i++){
		printf("\xdb");
	}
	printf("\n\xdb\xdb ");
	for(i = 0; i <= n; i++){
		if (!i) printf("\xda\xc4\xc4\xc4\xc4\xc4\xc2");
		else if (i == n) printf("\xc4\xc4\xc4\xc4\xc4\xbf");
		else printf("\xc4\xc4\xc4\xc4\xc4\xc2");
	}
	// gameboard
	printf(" \xdb\xdb");
	for(i = 0; i <= n; i++){
		printf("\n\xdb\xdb ");
		for(j = 0; j <= n; j++){
			if (!i && !j) printf("\xb3     ");
			else if (!i && j == n) printf("\xb3 %2d  \xb3", j);
			else if (!i) printf("\xb3 %2d  ", j);
			else if (!j) printf("\xb3 %2d  \xb3", i);
			else if (row && col && row == i && col == j) printf(" \xdb\xdb\xdb \xb3");
			else printf("  %c  \xb3", sos[i - 1][j - 1]);
		}
		printf(" \xdb\xdb\n\xdb\xdb ");
		for(j = 0; j <= n; j++){
			if (i == n && !j) printf("\xc0\xc4\xc4\xc4\xc4\xc4");
			else if (i == n) printf("\xc1\xc4\xc4\xc4\xc4\xc4");
			else if (!j) printf("\xc3\xc4\xc4\xc4\xc4\xc4");
			else printf("\xc5\xc4\xc4\xc4\xc4\xc4");
			if (i == n && j == n) printf("\xd9");
			else if (j == n) printf("\xb4");
		}
		printf(" \xdb\xdb");
	}
	// bottom line
	printf("\n");
	for(i = 1; i < (n + 2) * 6 + 2; i++){
		printf("\xdb");
	}
}

int takeInput(){
	printf("\n\n\xaf Player turn: %s\n", name[currentPlayer]);
	printf("\xaf Row: ");
	scanf("%d", &row);
	printf("\xaf Column: ");
	scanf("%d", &col);
	if(!(row > 0 && row <= n && col > 0 && col <= n)){
		printf("\xaf\xaf Invalid position!!\n\xaf\xaf Click enter to continue!!");
		system("pause");
		return 0;
	}
	switch(sos[row - 1][col - 1]){
		case 'S':
		case 'O':   
			printf("\xaf\xaf Invalid position!!\n\xaf\xaf Click enter to continue!!");
			system("pause");
			return 0;

		default:    
			system("cls");
			drawScoreboard();
			drawGameboard();
			printf("\n\n\xaf Player turn: %s\n\xaf Row: %d\n\xaf Column: %d\n\xaf\xaf S/O? ", name[currentPlayer], row, col);
			char ch;
			scanf(" %c", &ch);
			switch(ch){
				case 's':
				case 'S': sos[row - 1][col - 1] = 'S'; return 1;
				case 'o':
				case 'O': sos[row - 1][col - 1] = 'O'; return 1;
			}
		printf("\xaf\xaf Invalid letter!!\n\xaf\xaf Click enter to continue!!");
		system("pause");
		return 0;
	}
}


int takeInputPVComp(){
	printf("\n\n\xaf Player turn: %s\n", name[currentPlayer]);
	printf("\xaf Row: ");
	scanf("%d", &row);
	printf("\xaf Column: ");
	scanf("%d", &col);
	if(!(row > 0 && row <= n && col > 0 && col <= n)){
		printf("\xaf\xaf Invalid position!!\n\xaf\xaf Click enter to continue!!");
		system("pause");
		return 0;
	}
	switch(sos[row - 1][col - 1]){
		case 'S':
		case 'O':   
			printf("\xaf\xaf Invalid position!!\n\xaf\xaf Click enter to continue!!");
			system("pause");
			return 0;
		default:    
			system("cls");
			drawScoreboard();
			drawGameboard();
			printf("\n\n\xaf Player turn: %s\n\xaf Row: %d\n\xaf Column: %d\n\xaf\xaf S/O? ", name[currentPlayer], row, col);
			char ch;
			scanf(" %c", &ch);
			switch (ch) {
				case 's':
				case 'S': sos[row - 1][col - 1] = 'S'; return 1;
				case 'o':
				case 'O': sos[row - 1][col - 1] = 'O'; return 1;
			}
		printf("\xaf\xaf Invalid letter!!\n\xaf\xaf Click enter to continue!!");
		system("pause");
		return 0;
	}
}


int ctrlFindSOS(){
	if(sos[row - 1][col - 1] == 'S'){
		if (sos[row - 3][col - 3] == 'S' && sos[row - 2][col - 2] == 'O') return 1;
		if (sos[row - 3][col - 1] == 'S' && sos[row - 2][col - 1] == 'O') return 1;
		if (sos[row - 3][col + 1] == 'S' && sos[row - 2][col] == 'O') return 1;
		if (sos[row - 1][col - 3] == 'S' && sos[row - 1][col - 2] == 'O') return 1;
		if (sos[row - 1][col + 1] == 'S' && sos[row - 1][col] == 'O') return 1;
		if (sos[row + 1][col - 3] == 'S' && sos[row][col - 2] == 'O') return 1;
		if (sos[row + 1][col - 1] == 'S' && sos[row][col - 1] == 'O') return 1;
		if (sos[row + 1][col + 1] == 'S' && sos[row][col] == 'O') return 1;
	}
	else{
		if (sos[row - 2][col - 2] == 'S' && sos[row][col] == 'S') return 1;
		if (sos[row - 2][col - 1] == 'S' && sos[row][col - 1] == 'S') return 1;
		if (sos[row - 2][col] == 'S' && sos[row][col - 2] == 'S') return 1;
		if (sos[row - 1][col - 2] == 'S' && sos[row - 1][col] == 'S') return 1;
	}
	return 0;
}


///////////////////////////////////////////
// set alur untuk mode player vs computer//
///////////////////////////////////////////


int positionValidPVC(int square){

  	if(square>0 && square<((n*n)+1)){	
		row = (square-1)/n;
		col = (square-1)%n;

		if (sos[row][col]==' '){
			return 1;
		}
		else {
			return 0;
		} 
	}
  	else{
		return 0;	
  	}
}


int findPosition(){
	int square;
	
	for (square=1; square<((n*n)+1); square++){
		row = (square-1)/n;
		col = (square-1)%n;
		if (sos[row][col] == ' '){
			return square;
		}
	}
	return 0;
}

void compMove(){
	int square;
	char symbol;

  	do{
  		system("cls");
  		drawScoreboardPVC();
    	drawGameboard();
    	if(compFindOS()){
			square = compFindOS();
			symbol = 'S';
		}
		else if(compFindSS()){
			square = compFindSS();
			symbol = 'O';
		}
		else{
			square = findPosition();
			symbol = 'S';
		}
		row = (square-1)/n;
		col = (square-1)%n;
       	
   		sos[row][col] = symbol;
   		if(got==0){
   			if(symbol == 'S'){
   				printf("\n\xaf\xaf I am putting a %c in [%d][%d] \n", symbol, row+1, col+1);
				system("pause");
			}else if(symbol == 'O'){
				printf("\n\xaf\xaf I am putting an %c in [%d][%d] \n", symbol, row+1, col+1);
				system("pause");
			}
		}
		else if(got==1){
			system("cls");
			drawScoreboardPVC();
    		drawGameboard();
    		if(symbol == 'S'){
   				printf("\n\xaf\xaf I am putting a %c in [%d][%d] \n", symbol, row+1, col+1);
   				printf("\xaf\xaf\xaf I get point! \n");
				system("pause");
			}else if(symbol == 'O'){
				printf("\n\xaf\xaf I am putting an %c in [%d][%d] \n", symbol, row+1, col+1);
				printf("\xaf\xaf\xaf I get point! \n");
				system("pause");
			}
		}
   }while(findSOS_PVC(square, 2, symbol) && (!gameDonePVC()));
}

int compFindOS(){
	int square;

	for (int ii=0; ii<n; ii++){
		for(int jj=0; jj<n; jj++){
		   square = ((ii*n) +jj)+1;
			if(positionValidPVC(square)){
				if((sos[ii][jj+1] == 'O') && (sos[ii][jj+2] == 'S')){
					return square;
				}
                if((sos[ii][jj-1] == 'O') && (sos[ii][jj-2] == 'S')){
                    return square;
                        }
				if((sos[ii+1][jj] == 'O') && (sos[ii+2][jj] =='S')){
					return square;
				}
                if((sos[ii-1][jj] == 'O') && (sos[ii-2][jj] =='S')){
                    return square;
                }
				if((sos[ii+1][jj+1] == 'O') && (sos[ii+2][jj+2] == 'S')){
                    return square;
                }
                if((sos[ii-1][jj-1] == 'O') && (sos[ii-2][jj-2] == 'S')){
                    return square;
                }
                if((sos[ii+1][jj-1] == 'O') && (sos[ii+2][jj-2] == 'S')){
                    return square;
                }
                if((sos[ii-1][jj+1] == 'O') && (sos[ii-2][jj+2] == 'S')){
                    return square;
                }
		  	}
		}
	}
	return 0;
}

int compFindSS(){
	int square;
	
    for (int ii=0; ii<n; ii++){
        for(int jj=0; jj<n; jj++){  
        
            square = ((ii*n) +jj)+1;
            if(positionValidPVC(square)){
		        if((sos[ii][jj+1] == 'S') && (sos[ii][jj-1] == 'S')){
                    return square;
            	}
                if ((sos[ii+1][jj] == 'S') && (sos[ii-1][jj] =='S')){
                    return square;
        		}
                if((sos[ii+1][jj+1] == 'S') && (sos[ii-1][jj-1] == 'S')){
                    return square;
                }
                if((sos[ii+1][jj-1] == 'S') && (sos[ii-1][jj+1] == 'S')){
                    return square;
                }
            }
		}
    }
	return 0;
}


int findSOS_PVC (int square, int player, char symbol){
	int get;
	
	row = (square-1)/n;
	col = (square-1)%n;
	get = 0;
	
  	if(symbol == 'S'){
		if ((sos[row][col-2] == 'S') && (sos[row][col-1] == 'O')){
			get++;
		}
		if ((sos[row][col+1]== 'O') && (sos[row][col+2] == 'S')){
			get++;
		}	
		if((sos[row+1][col] == 'O') && (sos[row+2][col] == 'S')){
			get++;
		}
		if((sos[row-1][col] == 'O') && (sos[row-2][col] == 'S')){
			get++;
		}
		if((sos[row+1][col+1] == 'O') && (sos[row+2][col+2] == 'S')){
			get++;
		}
		if((sos[row-1][col-1] == 'O') && (sos[row-2][col-2] == 'S')){
			get++;
		}
		if((sos[row+1][col-1] == 'O') && (sos[row+2][col-2] == 'S')){
			get++;
		}
		if((sos[row-1][col+1] == 'O') && (sos[row-2][col+2] == 'S')){
			get++;
		}
  	}
  	else if(symbol == 'O'){
		if((sos[row+1][col] == 'S') && (sos[row-1][col] == 'S')){
			get++;
		}
		if((sos[row][col+1] == 'S') && (sos[row][col-1] == 'S')){
			get++;
		}
		if((sos[row+1][col+1] == 'S') && (sos[row-1][col-1] == 'S')){
			get++;
		}
		if((sos[row+1][col-1] == 'S') && (sos[row-1][col+1] == 'S')){
			get++;
		}
  	}
    scores[currentPlayer] = scores[currentPlayer] + get;

	if(get>0){
		got=1;
		return 1;
	}
	else{
		currentPlayer=0;
		got=0;
		return 0;
	}
}

int gameDonePVC(){	
	for(row=0; row<n; row++){
		for(col=0; col<n; col++){
			if (sos[row][col] == ' '){
				return 0;
			}
		}
	}
	return 1;
}

