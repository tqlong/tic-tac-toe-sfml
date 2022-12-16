#include "game_state.h"

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

std::vector<GameState::State> GameState::getNextStates(State s)
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
std::pair<int, GameState::State> GameState::getScore(State s, bool isMax, int alpha, int beta)
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
