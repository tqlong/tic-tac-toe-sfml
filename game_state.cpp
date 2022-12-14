#include <vector>
#include <string>

#include "game_state.h"

// Get final message to display when game is over
std::string GameState::getFinalMessage() const
{
    switch (finalScore) {
        case 1: return "X wins";
        case -1: return "O wins";
        case 0: return "It is a draw";
        default: return "Unknown";
    }
}

// Play the game on the given position
void GameState::playAndChangePlayer(int i, int j) {
    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE 
        && s[i][j] == ' ' && !gameStop) {
        s[i][j] = currentPlayer;
        currentPlayer = (currentPlayer == 'X') ? 'O':'X';
        checkAndProcessFinalState();
    }
}

// Check if the game is over and update the final score
void GameState::checkAndProcessFinalState() {
    if (isFinalState()) {
        finalScore = getScoreFinalState();
        gameStop = true;
    }
}

// Check if the game is over
bool GameState::isFinalState()
{
    // check rows
    for (int i = 0; i < SIZE; i++)
        if (s[i][0] == s[i][1] && s[i][0] == s[i][2] && s[i][0] != ' ') return true;
    // check cols
    for (int i = 0; i < SIZE; i++)
        if (s[0][i] == s[1][i] && s[0][i] == s[2][i] && s[0][i] != ' ') return true;
    // check diagonals
    if (s[0][0] == s[1][1] && s[0][0] == s[2][2] && s[0][0] != ' ') return true;
    if (s[0][2] == s[1][1] && s[0][2] == s[2][0] && s[0][2] != ' ') return true;
    // check full
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (s[i][j] == ' ') return false;
        }
    }
    return true;
}

// Get the final score
// 1: X wins, -1: O wins, 0: draw
int GameState::getScoreFinalState()
{
    // check rows
    for (int i = 0; i < SIZE; i++)
        if (s[i][0] == s[i][1] && s[i][0] == s[i][2] && s[i][0] != ' ') 
            return s[i][0] == 'X' ? 1 : -1;
    // check cols
    for (int i = 0; i < SIZE; i++)
        if (s[0][i] == s[1][i] && s[0][i] == s[2][i] && s[0][i] != ' ')
            return s[0][i] == 'X' ? 1 : -1;
    if (s[0][0] == s[1][1] && s[0][0] == s[2][2] && s[0][0] != ' ')
        return s[0][0] == 'X' ? 1 : -1;
    if (s[0][2] == s[1][1] && s[0][2] == s[2][0] && s[0][2] != ' ')
        return s[0][2] == 'X' ? 1 : -1;;
    return 0;
}
