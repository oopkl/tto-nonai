#include <iostream>
#include <vector>

using namespace std;

vector<int> board = {0, 2, 2, 2, 2, 2, 2, 2, 2, 2}; // 2 represents empty, 3 represents X, 5 represents O

//Function to check if any player has won
bool checkWin(int player) {
    for (int i = 1; i <= 9; i += 3) {
        if (board[i] == player && board[i + 1] == player && board[i + 2] == player) {
            return true; // Win in a row
        }
    }

    for (int i = 1; i <= 3; i++) {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player) {
            return true; // Win in a column
        }
    }

    if (board[1] == player && board[5] == player && board[9] == player) {
        return true; // Win in the main diagonal
    }

    if (board[3] == player && board[5] == player && board[7] == player) {
        return true; // Win in the other diagonal
    }

    return false; // No win yet
}

// Function to check the possibility of winning for a player or machine
int posswin(int p) {
    int pos;

    for (int i = 1; i <= 9; i += 3) { // Check rows
        pos = i;
        if (board[pos] * board[pos + 1] * board[pos + 2] == p * p * 2) {
            if (board[pos] == 2)
                return pos; //return the winning (which is currently empty) position
            if (board[pos + 1] == 2)
                return pos + 1; //return the winning (which is currently empty) position
            if (board[pos + 2] == 2)
                return pos + 2; //return the winning (which is currently empty) position
        }
    }


    for (int i = 1; i <= 3; i++) { // Check columns
        pos = i;
        if (board[pos] * board[pos + 3] * board[pos + 6] == p * p * 2) {
            if (board[pos] == 2)
                return pos;
            if (board[pos + 3] == 2)
                return pos + 3;
            if (board[pos + 6] == 2)
                return pos + 6;
        }
    }


    pos = 1; //check 1-5-9 diag and return winning pos
    if (board[pos] * board[pos + 4] * board[pos + 8] == p * p * 2) {
        if (board[pos] == 2)
            return pos;
        if (board[pos + 4] == 2)
            return pos + 4;
        if (board[pos + 8] == 2)
            return pos + 8;
    }

    pos = 3; //check 3-5-7 diag and return winning pos
    if (board[pos] * board[pos + 2] * board[pos + 4] == p * p * 2) {
        if (board[pos] == 2)
            return pos;
        if (board[pos + 2] == 2)
            return pos + 2;
        if (board[pos + 4] == 2)
            return pos + 4;
    }

    return 0; //no winning pos
}

void makemove(int player) {
    if (board[5] == 2) {
        board[5] = player;
        return;
    }

    int winningMove = posswin(player);
    if (winningMove != 0 && board[winningMove] == 2) {
        board[winningMove] = player;
        return;
    }

    int blockingMove = posswin(player == 3 ? 5 : 3);
    if (blockingMove != 0 && board[blockingMove] == 2) {
        board[blockingMove] = player;
        return;
    }

    vector<int> corners = {1, 3, 7, 9}; //strategic corner moves
    for (int i = 0; i < 4; ++i) {
        if (board[corners[i]] == 2) {
            board[corners[i]] = player;
            return;
        }
    }

    for (int i = 1; i <= 9; ++i) { //if no winning move/no blocking move/no strategic corner move
        if (board[i] == 2) {
            board[i] = player;
            return;
        }
    }
}

void displayBoard() {
    cout << endl;

    for (int i = 1; i <= 9; i++) {
        if (board[i] == 2) {
            cout << "_";
        } else if (board[i] == 3) {
            cout << "X";
        } else {
            cout << "O";
        }

        if (i % 3 == 0) {
            cout << endl;
        } else {
            cout << " | ";
        }
    }

    cout << endl;
}

//Function to check if game is over
int gameover() {
    if (checkWin(3)) {
        displayBoard();
        cout << "Game Over. You win!" << endl;
        return 1;
    }

    if (checkWin(5)) {
        displayBoard();
        cout << "Game Over. You lose!" << endl;
        return 1;
    }

    for (int i = 1; i <= 9; i++) {
        if (board[i] == 2) {
            return 0; // Game is not over yet
        }
    }

    displayBoard();
    cout << "Game Over. It's a draw!" << endl;
    return 1;
}

int main() {
    cout << "Welcome to Tic Tac Toe!" << endl;

    while (true) {
        displayBoard();

        int playerMove;
        cout << "Enter your move (1-9): ";
        cin >> playerMove;

        if (playerMove < 1 || playerMove > 9 || board[playerMove] != 2) {
            cout << "Invalid move. Please choose a valid empty position." << endl;
            continue;
        }
        
        board[playerMove] = 3;

        if (gameover() == 1) {
            break;
        }

        makemove(5);

        if (gameover() == 1) {
            break;
        }
    }

    return 0;
}
