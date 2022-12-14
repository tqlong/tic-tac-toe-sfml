#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <string>

typedef std::vector<char> Row;
typedef std::vector<Row> State;
const int SIZE=3;

/**
 * @brief GameState class
 * This class is responsible for storing the state of the game
 * and providing the logic to play the game.
 */
struct GameState
{
    State s = State(SIZE, Row(SIZE, ' '));
    bool gameStop = false;
    char currentPlayer = 'X';
    int finalScore = -10;

    // Get final message to display when game is over
    std::string getFinalMessage() const;

    // Play the game on the given position
    void playAndChangePlayer(int i, int j);

private:
    // Check if the game is over and update the final score
    void checkAndProcessFinalState();

    // Check if the game is over
    bool isFinalState();

    // Get the final score
    // 1: X wins, -1: O wins, 0: draw
    int getScoreFinalState();

    friend class GameStateTest;
};

#endif