struct GameState
{
    bool mainMenu, newGame, loadGame, highScores, options, board, battle, credits;
    GameState();
    int set_gameState();
    void set_mm();
    void set_ng();
    void set_lg();
    void set_hs();
    void set_op();
};
