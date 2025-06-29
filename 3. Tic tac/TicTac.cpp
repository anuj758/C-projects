#include <iostream>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <limits>
using namespace std;

class TicTac{
    string player1, player2;
    char marker1, marker2;
    vector<vector<char>> board;

    void initializeBoard(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                board[i][j] = i * 3 + j + '1';
            }
        }
    }

    void displayBoard(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(j != 2)    cout << " " << board[i][j] << " |";
                else cout << " " << board[i][j];
            }
            if(i == 0)    cout << "              " << player1 << "'s marker: " << marker1 << "\n";
            if(i == 1)    cout << "              " << player2 << "'s marker: " << marker2 << "\n";
            if(i != 2) cout << "---|---|---\n";
        }
        cout << "\n";

    }

    void takeInput(){
        cout << "---------------------------------GAME START-----------------------------------------------\n";
        cout << "Enter Player 1 name: ";
        getline(cin, player1);
        cout << "Enter Player 2 name: ";
        getline(cin, player2);
        srand(time(0));
        int x = rand() % 2 + 1;
        if(x == 1){
            cout << player1 << " choose your marker O or X : " ;
            cin >> marker1;
            marker2 = (marker1 == 'X') ? 'O' : 'X';
        }
        else{
            cout << player2 << " choose your marker O or X : " ;
            cin >> marker2;
            marker1 = (marker2 == 'X') ? 'O' : 'X';
        }
        if(!((marker1 == 'X' && marker2 == 'O') || (marker1 == 'O' && marker2 == 'X'))){
            throw invalid_argument("! Invalid marker");
        }
    }

    bool updateBoard(char marker, int place){
        place--;
        int row = place / 3;
        int col = place % 3;
        if(board[row][col] == 'X' || board[row][col] == 'O') return false;
        board[row][col] = marker;
        return true;
    }

    bool checkWin(char marker){
        // checking in columns
        for(int col = 0; col < 3; col++){
            if(board[0][col] == marker && board[1][col] == marker && board[2][col] == marker) return true;
        }
        //checking in row
        for(int row = 0; row < 3; row++){
            if(board[row][0] == marker && board[row][1] == marker && board[row][2] == marker) return true;
        }
        //cheking diagonally
        if(board[0][0] == marker && board[1][1] == marker && board[2][2] == marker) return true;
        if(board[0][2] == marker && board[1][1] == marker && board[2][0] == marker) return true;
        return false;
    }

    void simulateGame(){
        int turn = 0;
        int currPlayer;
        char currMarker;
        int place;
        while(turn < 9){
            displayBoard();
            if(turn == 0){   
                currPlayer = rand() % 2 + 1;
                currMarker = (currPlayer == 1) ? marker1 : marker2;
            }
            
            if(currPlayer == 1){
                cout << player1 << "'s turn, enter your position: ";
                cin >> place;
            }
            else{
                cout << player2 << "'s turn, enter your position: ";
                cin >> place;
            }
            

            if(place < 1 || place > 9){
                cout << "Enter a valid position."<<"\n";
                continue;
            }

            if(!updateBoard(currMarker, place)){
                cout << "Place already occupied." << "\n";
                cout << "Choose another place." << "\n";
                continue;
            }
            if(checkWin(currMarker)){
                displayBoard();
                if(currPlayer == 1) cout << "------------" << player1 << " WON ------------" << "\n";
                else cout << "------------" << player2 << " WON ------------" << "\n";
                return;
            }
            currPlayer = (currPlayer == 1) ? 2 : 1;
            currMarker = (currMarker == 'O') ? 'X' : 'O';
            turn++;
        }
        displayBoard();
        cout << "------------GAME DRAW------------\n";
    }

    public:
    TicTac(){
        board.resize(3, vector<char>(3));
    }
    void game() {
        char choice;
        do {
            takeInput();
            initializeBoard();
            simulateGame();

            cout << "Do you want to play again? (y/n): ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (choice == 'y' || choice == 'Y');
    }

};

int main(){
    TicTac t;
    t.game();
    return 0;
}
