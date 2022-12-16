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

    bool isHoverOnButtonHvsH = false;
    bool isHoverOnButtonHvsM = false;
    bool isHoverOnButtonMvsH = false;

    bool thinking = false;

    int hoverI = -1;
    int hoverJ = -1;

    enum class PlayScreen {
        PlayModeScreen,
        PlayingScreen,
    };

    enum class PlayMode {
        HumanVsHuman,
        HumanVsMachine,
    };

    PlayScreen playScreen = PlayScreen::PlayModeScreen;
    PlayMode playMode = PlayMode::HumanVsHuman;

    // Get final message to display when game is over
    std::string getFinalMessage() const;

    // Play the game on the given position
    void playAndChangePlayer(int i, int j);

    // Play the game first with AI
    void computerPlayFirst();

    // set the hover cell
    void setHoveredCell(int i, int j);

    // reset the game
    void resetGame();

private:
    // toggle player
    void togglePlayer();

    // Check if the game is over and update the final score
    void checkAndProcessFinalState();

    // Check if the game is over
    bool isFinalState(State s);

    // Get the final score
    // 1: X wins, -1: O wins, 0: draw
    int getScoreFinalState(State s);

    // Get the next player
    char getNextPlayer(State s);

    // Play the game on the given position
    State play(State s, int i, int j, char player);

    // Get the next possible states
    std::vector<State> getNextStates(State s);

    // Get the score of the given state via alpha-beta
    std::pair<int, State> getScore(State s, bool isMaximizingPlayer, int alpha = -100, int beta = 100);

    // Get the computer play (AI)
    std::pair<int, int> getComputerPlay(State s);

    friend class GameStateTest;
};

#endif