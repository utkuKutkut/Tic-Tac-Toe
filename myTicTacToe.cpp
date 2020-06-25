#include <ctime>    // For time()
#include <cstdlib>
#include <iostream>
using namespace std;
class game{

	private:
		char board[5][5];
		bool gameOver=false;

	public:
		void buildMap(){
			int i,j;
			char n='1';
			char n2='1';
			board[0][0]=' ';
			for(i=0;i<=3;i++){
				for(j=0;j<=3;j++){
                    if(i==0 && j>0){
                        board[0][j]=n;
                        n+=1;
                    }
                    else{
                        board[i][j]=' ';
                    }
				}
				if(i>0){
                 board[i][0]=n2;
                 n2+=1;
				}
			}
		}
		void printMap(){
			for(int i=0;i<=3;i++){
                for(int j=0;j<=3;j++){
                    cout<<board[i][j];
                }
                cout<<"\n";
			}
			cout<<"\n";
		}
		bool valid(int row,int col){
			if((row<0 || row>3 ) || (col<0 || col>3)){
				return 1;
			}
			if(board[row][col]!=' '){
				cout<<"problem is.. its not empty cell!";
				return 1;
			}
			else {
				return 0;
			}
		}
		void putDisc(int row,int col,char playerChar){
			board[row][col]=playerChar;
		}

		int playerMove(char playerChar){
			int row=0;
			int col=0;
			cout<<"Please enter a ROW:"; cin>>row;
			cout<<"Please enter a COLOUMN:"; cin>>col;
			while(valid(row,col)){
				cout<<"You cannot make this move! (enter valid choise)\n";
				cout<<"Please enter a ROW:"; cin>>row;
				cout<<"Please enter a COLOUMN:"; cin>>col;
			}
			putDisc(row,col,playerChar);
			return checkWin();
		}



        int evaluate(char b[5][5], char player) {
            char opponent;
            if(player=='X'){opponent='O';}
            else{opponent='X';}
            // Checking for Rows for X or O victory.
            for (int row = 1; row<=3; row++)
            {
                if (b[row][1]==b[row][2] &&b[row][2]==b[row][3])
                {
                    if (b[row][1]==player){

                        return +10;
                    }
                    else if (b[row][1]==opponent)

                        return -10;
                }
            }

            // Checking for Columns for X or O victory.
            for (int col = 1; col<=3; col++)
            {
                if (b[1][col]==b[2][col] && b[2][col]==b[3][col])
                {
                    if (b[1][col]==player){

                        return +10;
                    }
                    else if (b[1][col]==opponent)

                        return -10;
                }
            }

            // Checking for Diagonals for X or O victory.
            if (b[1][1]==b[2][2] && b[2][2]==b[3][3])
            {
                if (b[1][1]==player){

                    return +10;
                }
                else if (b[1][1]==opponent)

                    return -10;

            }

            if (b[1][3]==b[2][2] && b[2][2]==b[3][1])
            {
                if (b[1][3]==player){

                    return +10;
                }
                else if (b[1][3]==opponent)

                    return -10;
            }



            // Else if none of them have won then return 0
            return 0;
        }





        bool moveLeft(char board[5][5])
        {
            for (int i=1;i<=3; i++)
                for (int j = 1; j<=3; j++)
                    if (board[i][j]==' ')
                        return true;
            return false;
        }





	int minimax(char board[5][5], int depth, bool isMax,char player){

            char opponent;
            if(player=='X'){opponent='O';}
            else{opponent='X';}
            int score = evaluate(board,player);

            // If Maximizer has won the game return his/her
            // evaluated score
            if (score == 10)
                return score;

            // If Minimizer has won the game return his/her
            // evaluated score
            if (score == -10)
                return score;



            // If there are no more moves and no winner then
            // it is a tie
            if (moveLeft(board)==false)
                    return 0;


            if (isMax)
            {
                int best = -1000;

                for (int i=1; i<=3; i++)
                {
                    for (int j=1; j<=3; j++)
                    {
                        if (board[i][j]==' ')
                        {

                            board[i][j]=player;

                            best = max(best, minimax(board,depth+1,!isMax,player) );

                            // Undo the move
                            board[i][j] = ' ';
                        }
                    }
                }
                return best;
            }


            else
            {
                int best = 1000;

                for (int i =1; i<=3; i++)
                {
                    for (int j = 1; j<=3; j++)
                    {
                        // Check if cell is empty
                        if (board[i][j]==' ')
                        {

                            board[i][j] = opponent;

                            // Call minimax recursively and choose
                            // the minimum value
                            best = min(best, minimax(board,depth+1,!isMax,player));


                            board[i][j] = ' ';
                        }
                    }
                }

                return best;
            }



       }







		int *findBestMove(char player)
        {
            srand (time(NULL));
            int bestVal = -1000;
            int *bestMove=new int[3];
            bestMove[0] = -1;
            bestMove[1] = -1;

            for (int i =1; i<=3; i++)
            {
                for (int j = 1; j<=3; j++)
                {
                    // Check if cell is empty
                    if (board[i][j]==' ')
                    {
                        int random;
                        random= rand()%2+1;

                        board[i][j] = player;

                        int moveVal = minimax(board, 10, false,player);


                        board[i][j] = ' ';

                        if (moveVal > bestVal)
                        {

                            bestMove[0]=i;
                            bestMove[1] = j;
                            bestVal = moveVal;
                        }



                        else if(moveVal==bestVal){
                            bestMove[0]=i;
                            bestMove[1] = j;
                        }
                    }

                }
            }

            return bestMove;
        }



		int computerMove(char computerChar){
		    int *best=findBestMove(computerChar);
            putDisc(best[0],best[1],computerChar);
            return checkWin();
		}










		int checkWin(){
			int x=0;
			int o=0;
			for(int i=1;i<=3;i++){
				for(int j=1;j<=3;j++){
                        if(board[i][j]==board[i][j+1] && board[i][j+1]==board[i][j+2] && board[i][j]!=' '){
                            if(board[i][j]=='X')
                                cout<< "\nX WINS!"<<endl;
                            else{
                                cout<<"\nO WINS!"<<endl;
                            }
                            cout<<"\n";
                            printMap();
                            return 1;
                        }
                        else if(board[i][j]==board[i+1][j] && board[i+1][j]==board[i+2][j] && board[i][j]!=' '){
                            gameOver=true;
                            if(board[i][j]=='X')
                                cout<< "\nX WINS!"<<endl;
                            else{
                                cout<<"\nO WINS!"<<endl;
                            }
                            cout<<"\n";
                            printMap();
                            return 1;
                        }
                        else if(board[i][j]==board[i+1][j+1] && board[i+1][j+1]==board[i+2][j+2] && board[i][j]!=' '){
                            gameOver=true;
                            if(board[i][j]=='X')
                                cout<< "\nX WINS!"<<endl;
                            else{
                                cout<<"\nO WINS!"<<endl;
                            }
                            cout<<"\n";
                            printMap();
                            return 1;
                        }
                        else{
                            if(moveLeft(board)==0){
                                cout<<"\nGAME DRAWS!\n"<<endl;
                                printMap();
                                return 1;
                            }
                        }
                }
            }
            return 0;
		}




};

int main(){
	int choise;
	int control=0;
	cout<<"Welcome to interactive Tic Tac Toe game.\n1-Single Player Mode\n2-Two Player Mode\nAnswer:"; cin>>choise;

	if(choise==1){
		game play;
		play.buildMap();
		while(1){
			cout<<endl<<"Player 1's Turn!"<<endl<<endl;
			play.printMap();
			if(play.playerMove('X')==1){
                    break;
			}
			play.printMap();
			cout<<endl;
			cout<<endl<<"Player 1 made his move !"<<endl<<endl<<endl;
			cout<<"Player 2's turn!"<<endl<<endl;
			play.printMap();
			if(play.playerMove('O')==1){
                    break;
			}
			cout<<endl<<"Player 2 made his move !"<<endl<<endl<<endl;
			play.printMap();
		}
	}
	else if(choise==2){
            game play;
            play.buildMap();
            while(1){
                cout<<endl<<"Player 1's Turn!"<<endl<<endl;
                play.printMap();
                if(play.playerMove('X')==1){
                        break;
                }
                cout<<endl;
                cout<<endl<<"Player 1 made his move !"<<endl<<endl<<endl;
                play.printMap();
                cout<<"Player 2's turn!"<<endl<<endl;
                play.printMap();
                if(play.computerMove('O')==1){
                        break;
                }
                cout<<endl<<"Player 2 made his move !"<<endl<<endl<<endl;
                play.printMap();
            }
	}
	else{
        cout<<"Invalid choise!"<<endl;
	}
	return 0;
}
