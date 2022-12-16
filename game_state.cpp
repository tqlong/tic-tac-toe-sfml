#include <vector>
#include <string>
#include <algorithm>

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
    thinking = true;
    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE 
        && s[i][j] == ' ' && !gameStop) {
        s[i][j] = currentPlayer;
        togglePlayer();
        checkAndProcessFinalState();

        // If the game is not over and the play mode is HumanVsMachine
        // then play the computer move
        if (!gameStop && playMode == PlayMode::HumanVsMachine) {
            std::pair<int, int> nextMove = getComputerPlay(s);
            s[nextMove.first][nextMove.second] = currentPlayer;
            togglePlayer();
            checkAndProcessFinalState();
        }
    }
    thinking = false;
}

void GameState::togglePlayer()
{
    currentPlayer = (currentPlayer == 'X') ? 'O':'X';
}

void GameState::computerPlayFirst() {
    thinking = true;
    std::pair<int, int> nextMove = getComputerPlay(s);
    s[nextMove.first][nextMove.second] = currentPlayer;
    togglePlayer();
    checkAndProcessFinalState();
    thinking = false;
}

void GameState::setHoveredCell(int i, int j)
{
    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
        hoverI = i;
        hoverJ = j;
    }
}

void GameState::resetGame()
{
    s = State(SIZE, Row(SIZE, ' '));
    gameStop = false;
    currentPlayer = 'X';
    finalScore = -10;
}

// Check if the game is over and update the final score
void GameState::checkAndProcessFinalState() {
    if (isFinalState(s)) {
        finalScore = getScoreFinalState(s);
        gameStop = true;
    }
}

// Check if the game is over
bool GameState::isFinalState(State s)
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
int GameState::getScoreFinalState(State s)
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

char GameState::getNextPlayer(State s)
{
    int countX = 0, countO = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (s[i][j] == 'X') countX++;
            else if (s[i][j] == 'O') countO++;
        }
    }
    if (countX == countO) return 'X';
    else return 'O';
}

State GameState::play(State s, int i, int j, char player)
{
    State newState = State(3, Row(3, ' '));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newState[i][j] = s[i][j];
        }
    }
    newState[i][j] = player;
    return newState;
}

std::vector<State> GameState::getNextStates(State s)
{
    char nextPlayer = getNextPlayer(s);
    std::vector<State> states;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (s[i][j] == ' ') {
                State nextState = play(s, i, j, nextPlayer);
                states.push_back(nextState);
            }
        }
    }
    return states;
}

/// @brief Get the score of the state
/// and the best next state
/// @param s the state
/// @param isMax true if the current player is the maximizing player
/// @param alpha MAX best score
/// @param beta MIN best score
/// @return std::pair<int, State> the score and the best next state
std::pair<int, State> GameState::getScore(State s, bool isMax, int alpha, int beta)
{
    // base case
    if (isFinalState(s)) return make_pair(getScoreFinalState(s), s);

    // get all possible next states
    std::vector<State> states = getNextStates(s);
    
    // store the best score and the best next state
    const int INVALID = -10;
    int bestScore = INVALID;
    State bestState;

    // recursively get the score of the next states
    for (State ns: states) {
        std::pair<int, State> p = getScore(ns, !isMax, alpha, beta);
        int score = p.first;
        // update best score for MAX
        if (isMax) {
            if (bestScore < score || bestScore == INVALID) {
                bestScore = score;
                bestState = ns;
            }
            // prune if bestScore >= best option for MIN
            if (bestScore >= beta) return make_pair(bestScore, bestState);
            alpha = std::max(alpha, bestScore);
        } else { // update best score for MIN
            if (bestScore > score || bestScore == INVALID) {
                bestScore = score;
                bestState = ns;
            }
            // prune if bestScore <= best option for MAX
            if (bestScore <= alpha) return make_pair(bestScore, bestState);
            beta = std::min(beta, bestScore);
        }
    }
    return make_pair(bestScore, bestState);
}

std::pair<int, int> GameState::getComputerPlay(State s)
{
    char player = getNextPlayer(s);
    std::pair<int, State> p = getScore(s, player=='X');
    int score = p.first;
    State newState = p.second;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (newState[i][j] != s[i][j]) return std::make_pair(i, j);
        }
    }
    return std::make_pair(-1, -1);
}