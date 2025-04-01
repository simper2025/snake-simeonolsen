//This is a frameword to allow you to focus on the game logic.
//Most of your code will go in three locations. 
//Function decalrations, game logic in runGame, and the function declarations.

#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <chrono>
#include <iostream>
using namespace std;

#define key_UP 72
#define key_DOWN 80
#define key_LEFT 75
#define key_RIGHT 77
#define key_ESCAPE 27

//This is a struct (aka structure) it reduces the number of variables needed.
struct point { int x, y; };

//keypress keeps track of what the last pressed key. It is global, but could be made local.
int keypress = 0;

void runGame();
point keyPressed(point direction);
void gotoxy(int x, int y);
void setcolor(WORD color);
void txtPlot(point item, unsigned char Color);

//Add function declarations here
point moveMouse();


int main() {

    //Uncomment the next four lines to see console color options 0-255
    //for (int i = 0; i < 255; i++) {
    //    setcolor(i);
    //    _cprintf("Color option: %i. Hello, world.\n", i);
    //}

	runGame();
	return 0;
}

void runGame() {

    chrono::time_point<chrono::system_clock> runTime;
    chrono::time_point<chrono::system_clock> currentTime;
    runTime = std::chrono::system_clock::now();
    Sleep(300);
    srand(time(0));

    point playerloc = { 0, 10 };
    point direction = { 1, 0 };
    point mouse = {moveMouse()};
    vector<point> tail;
    int length = 5;

    //Loop to start drawing and playing.
	while (keypress != key_ESCAPE) {
		
        direction = keyPressed(direction);
        
        currentTime = chrono::system_clock::now();

        double elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - runTime).count();
        if (elapsedTime > 0.3 * 1000) {
            runTime = chrono::system_clock::now();

            //Most of your game logic goes here.
            txtPlot(playerloc, 15);

            tail.push_back(playerloc);

            playerloc.x += direction.x;
            playerloc.y += direction.y;
            
            if (playerloc.x > 19 || playerloc.y > 19 || playerloc.x < 0 || playerloc.y < 0) {
                setcolor(15);
                gotoxy(1, 20);
                _cprintf("You are bad");
                keypress = key_ESCAPE;
            }

            if (playerloc.x == mouse.x && playerloc.y == mouse.y) {
                length += 1;
                mouse = moveMouse();

            }

            if (tail.size() > length) {
                point erase = tail[0];
                txtPlot(erase, 15);
                tail.erase(tail.begin());

            }
            for (int i = 0; i < tail.size() - 1; i++) {
                if (playerloc.x == tail[i].x && playerloc.y == tail[i].y) {
                    setcolor(15);
                    gotoxy(1, 20);
                    _cprintf("You are bad");
                    keypress = key_ESCAPE;
                }
            }
            for (int i = 0; i < tail.size(); i++) {
                txtPlot(tail[i], 86);
            }

            txtPlot(mouse, 120);
            txtPlot(playerloc, 31);
            
            setcolor(15);
            gotoxy(1, 21);
            _cprintf("Length: %i", length);


        }

		Sleep(10);
	}
}

//Put function definitions here.
point moveMouse() {
    point temp;

    temp.x = rand() % 20;
    temp.y = rand() % 20;

    return temp;
}



//These are helper funcitons to capture keyboard and draw to the console.
point keyPressed(point direction) {
    if (_kbhit())
    {
        keypress = _getch();
        switch (keypress)
        {
        case key_LEFT:
            direction = { -1, 0 };
            break;

        case key_RIGHT:
            direction = { 1, 0 };
            break;

        case key_UP:
            direction = { 0, -1 };
            break;

        case key_DOWN:
            direction = { 0, 1 };
            break;

        default:

            break;
        }
    }
    return direction;
}

void txtPlot(point item, unsigned char Color)
{
    setcolor(Color);
    gotoxy(item.x*2, item.y); 
    _cprintf("  ");
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x + 1; coord.Y = y + 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}

void setcolor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return;
}

