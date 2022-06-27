#include <iostream>
#include <Windows.h>

#include "constants.h"

using constants::mapWidth;
using constants::mapHeight;

char maze[mapHeight][mapWidth + 1];
char map[mapHeight][mapWidth + 1];

void init();

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
} player(mapWidth / 2, mapHeight / 2);


Player::Player(int x, int y)
{
    this->x = x;
    this->y = y;
    this->cx = x;
    this->cy = y;
}

void Player::putInMap()
{
    map[this->y][this->x] = '@';
}

void Player::input()
{
    this->cx = this->x;
    this->cy = this->y;

    if (GetKeyState('W') < 0)
        (this->y)--;
    if (GetKeyState('S') < 0)
        (this->y)++;
    if (GetKeyState('A') < 0)
        (this->x)--;
    if (GetKeyState('D') < 0)
        (this->x)++;

    if (maze[this->y][this->x] == '#')
    {
        this->x = cx;
        this->y = cy;
    }
}

void Player::exitCheck(int width, int height)
{
    if ((this->x == width - 1) || (this->x == 0) || (this->y == height - 1) || (this->y == 0))
    {
        this->x = width / 2;
        this->y = height / 2;
        system("cls");
        std::cout << "WIN!" << std::endl;
        Sleep(10000);
        system("cls");

        // arrays must be cleared before new generation
        memset(maze, 0, sizeof(maze));
        memset(map, 0, sizeof(map));

        init();
    }
}

void borderGeneration()
{
    for (int i = 0; i < mapWidth; i++)
        maze[0][i] = '#';

    for (int i = 0; i < mapWidth; i++)
        maze[mapHeight - 1][i] = '#';

    maze[0][mapWidth] = '\0';
    maze[mapHeight - 1][mapWidth] = '\0';

    for (int i = 1; i < mapHeight - 1; i++)
    {
        for (int j = 0; j < mapWidth - 1; j++)
            maze[i][j] = ' ';

        maze[i][0] = '#';
        maze[i][mapWidth - 1] = '#';
        maze[i][mapWidth] = '\0';
    }

    bool exit = false;

    // the loop runs until a pass is generated on one of the sides
    while (1)
    {
        for (int i = 1; i < mapWidth - 2; i++)
        {
            if (rand() % 100 == 0)
            {
                maze[0][i] = ' ';
                exit = true;
                break;
            }
        }

        if (exit) break;

        for (int i = 1; i < mapWidth - 2; i++)
        {
            if (rand() % 100 == 0)
            {
                maze[mapHeight - 1][i] = ' ';
                exit = true;
                break;
            }
        }

        if (exit) break;

        for (int i = 1; i < mapHeight - 2; i++)
        {
            if (rand() % 100 == 0)
            {
                maze[i][0] = ' ';
                exit = true;
                break;
            }
        }

        if (exit) break;

        for (int i = 1; i < mapHeight - 2; i++)
        {
            if (rand() % 100 == 0)
            {
                maze[i][mapWidth - 1] = ' ';
                exit = true;
                break;
            }
        }

        if (exit) break;
    }
}

void frameGeneration()
{
    int borderX = 3;
    int borderY = 2;

    while ((borderX < (mapWidth / 2) - 1) && (borderY < (mapHeight / 2) - 1))
    {
        for (int i = borderX; i < mapWidth - borderX; i++)
        {
            maze[borderY][i] = '#';
            maze[mapHeight - borderY - 1][i] = '#';
        }

        for (int i = borderY; i < mapHeight - borderY; i++)
        {
            maze[i][borderX] = '#';
            maze[i][mapWidth - borderX - 1] = '#';
        }

        borderX += 3;
        borderY += 2;
    }

    bool exit = false;
    borderX = 3;
    borderY = 2;

    while ((borderX < (mapWidth / 2) - 1) && (borderY < (mapHeight / 2) - 1))
    {
        exit = false;

        while (1)
        {
            for (int i = borderX + 1; i < mapWidth - borderX - 1; i++)
            {
                if (rand() % 100 == 0)
                {
                    maze[borderY][i] = ' ';
                    exit = true;
                    break;
                }
            }

            if (exit) break;

            for (int i = borderX + 1; i < mapWidth - borderX - 1; i++)
            {
                if (rand() % 100 == 0)
                {
                    maze[mapHeight - borderY - 1][i] = ' ';
                    exit = true;
                    break;
                }
            }

            if (exit) break;

            for (int i = borderY + 1; i < mapHeight - borderY - 1; i++)
            {
                if (rand() % 100 == 0)
                {
                    maze[i][borderX] = ' ';
                    exit = true;
                    break;
                }
            }

            if (exit) break;

            for (int i = borderY + 1; i < mapHeight - borderY - 1; i++)
            {
                if (rand() % 100 == 0)
                {
                    maze[i][mapWidth - borderX - 1] = ' ';
                    exit = true;
                    break;
                }
            }

            if (exit) break;
        }

        borderX += 3;
        borderY += 2;
    }
}

void neighborGeneration()
{

}

int generationChoice()
{
    std::cout << "0 - frame maze\n";
    std::cout << "Generation choice: ";

    int choice;
    std::cin >> choice;

    // a frame maze is generated by default
    if (choice < 0 || choice > 1)
        return 0;
    else return choice;
}

void init()
{
    int generation = generationChoice();

    switch (generation)
    {
    case 0:
        borderGeneration();
        frameGeneration();
        break;
    }
}

void clearMap()
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            map[i][j] = maze[i][j];
        }
    }
}

void show()
{
    for (int i = 0; i < mapHeight; i++)
        std::cout << map[i] << std::endl;
}

void setCursorToBegin()
{
    COORD c;
    c.X = 0;
    c.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void mazeGenerator()
{
    srand(time(NULL));
    init();

    do
    {
        hideCursor();
        setCursorToBegin();
        clearMap();
        player.input();
        player.putInMap();
        player.exitCheck(mapWidth, mapHeight);

        show();
        Sleep(20);

    } while (GetKeyState(VK_ESCAPE) >= 0);
}


int main()
{
    mazeGenerator();
    return 0;
}
