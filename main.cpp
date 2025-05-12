#include <iostream>
#include <limits>

using namespace std;

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char current_marker;
int current_player;

void drawBoard() {
    cout << "\nTic-Tac-Toe Board:\n";
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|\n-------------\n";
    }
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return true;
    }
    return false;
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];

    return ' ';
}

void swapPlayerAndMarker() {
    current_marker = (current_marker == 'X') ? 'O' : 'X';
    current_player = (current_player == 1) ? 2 : 1;
}

void resetBoard() {
    char init = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = init++;
        }
    }
}

void playGame() {
    cout << "Player 1, choose your marker (X or O): ";
    cin >> current_marker;
    while (current_marker != 'X' && current_marker != 'O') {
        cout << "Invalid choice. Choose X or O: ";
        cin >> current_marker;
    }
    current_player = 1;

    drawBoard();

    for (int turn = 0; turn < 9; turn++) {
        int slot;
        while (true) {
            cout << "Player " << current_player << ", enter slot (1-9): ";
            cin >> slot;

            if (cin.fail() || slot < 1 || slot > 9) {
                cout << "Invalid input. Enter a number between 1 and 9.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (placeMarker(slot)) break;
            cout << "Slot occupied! Try another.\n";
        }

        drawBoard();
        char winner = checkWinner();
        if (winner != ' ') {
            cout << "Player " << current_player << " wins!\n";
            return;
        }

        swapPlayerAndMarker();
    }
    cout << "It's a draw!\n";
}

int main() {
    char play_again;
    do {
        resetBoard();
        playGame();
        cout << "Do you want to play again? (Y/N): ";
        cin >> play_again;
    } while (play_again == 'Y' || play_again == 'y');

    cout << "Thanks for playing!\n";
    return 0;
}
