#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(int x, int y);
    void putInMap();
    void input();
    void exitCheck(int width, int height);
private:
    int x, y;
    int cx, cy;
};

#endif
