#include <gtest/gtest.h>
#include "../game_state.h"

class GameStateTest : public ::testing::Test
{
protected:
    // test get final message at the end of the game
    void TestGetFinalMessage() { 
        state.finalScore = 1;
        EXPECT_EQ(state.getFinalMessage(), "X wins");
        state.finalScore = -1;
        EXPECT_EQ(state.getFinalMessage(), "O wins");
        state.finalScore = 0;
        EXPECT_EQ(state.getFinalMessage(), "It is a draw");
        state.finalScore = 2;
        EXPECT_EQ(state.getFinalMessage(), "Unknown");
    }

    // test the initial state of the game
    void TestPlayerTurn() {
        EXPECT_EQ(state.currentPlayer, 'X');
        state.currentPlayer = 'O';
        EXPECT_EQ(state.currentPlayer, 'O');
    }

    // test the initial state of the game
    void TestGameStop() {
        EXPECT_EQ(state.gameStop, false);
        state.gameStop = true;
        EXPECT_EQ(state.gameStop, true);
    }

    // test player turn at the beginning of the game
    void TestPlayAndChangePlayer() {
        GameState state;
        state.playAndChangePlayer(0, 0);
        EXPECT_EQ(state.s[0][0], 'X');
        EXPECT_EQ(state.currentPlayer, 'O');
        state.playAndChangePlayer(0, 1);
        EXPECT_EQ(state.s[0][1], 'O');
        EXPECT_EQ(state.currentPlayer, 'X');
    }

    // test terminal state
    void TestCheckAndProcessFinalState() {
        {
            GameState state;
            state.s[0][0] = 'X'; state.s[0][1] = 'X'; state.s[0][2] = 'X';
            state.s[1][0] = 'O'; state.s[1][1] = 'O'; state.s[1][2] = 'X';
            state.s[2][0] = ' '; state.s[2][1] = ' '; state.s[2][2] = ' ';
            EXPECT_EQ(state.isFinalState(state.s), true);
            state.checkAndProcessFinalState();
            EXPECT_EQ(state.finalScore, 1);
            EXPECT_EQ(state.gameStop, true);
        }

        {
            GameState state;
            state.s[0][0] = 'X'; state.s[0][1] = 'X'; state.s[0][2] = ' ';
            state.s[1][0] = 'O'; state.s[1][1] = 'O'; state.s[1][2] = 'O';
            state.s[2][0] = 'X'; state.s[2][1] = ' '; state.s[2][2] = ' ';
            EXPECT_EQ(state.isFinalState(state.s), true);
            state.checkAndProcessFinalState();
            EXPECT_EQ(state.finalScore, -1);
            EXPECT_EQ(state.gameStop, true);
        }

        {
            GameState state;
            state.s[0][0] = 'X'; state.s[0][1] = 'X'; state.s[0][2] = 'O';
            state.s[1][0] = 'O'; state.s[1][1] = 'O'; state.s[1][2] = 'X';
            state.s[2][0] = 'X'; state.s[2][1] = 'O'; state.s[2][2] = 'X';
            EXPECT_EQ(state.isFinalState(state.s), true);
            state.checkAndProcessFinalState();
            EXPECT_EQ(state.finalScore, 0);
            EXPECT_EQ(state.gameStop, true);
        }
    }

    void TestScreen() {
        GameState state;
        EXPECT_EQ(state.playScreen, GameState::PlayScreen::PlayModeScreen);
        state.playScreen = GameState::PlayScreen::PlayingScreen;
        EXPECT_EQ(state.playScreen, GameState::PlayScreen::PlayingScreen);
    }

private:
    GameState state;
};

TEST_F(GameStateTest, getFinalMessage) {
    TestGetFinalMessage();
}

TEST_F(GameStateTest, playerTurn) {
    TestPlayerTurn();
}

TEST_F(GameStateTest, gameStop) {
    TestGameStop();
}

TEST_F(GameStateTest, playAndChangePlayer) {
    TestPlayAndChangePlayer();
}

TEST_F(GameStateTest, checkAndProcessFinalState) {
    TestCheckAndProcessFinalState();
}

TEST_F(GameStateTest, screen) {
    TestScreen();
}