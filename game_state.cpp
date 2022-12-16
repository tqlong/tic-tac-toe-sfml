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

char GameState::getPlay(int i, int j) const
{
    return s[i][j];
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

GameState::State GameState::play(State s, int i, int j, char player)
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