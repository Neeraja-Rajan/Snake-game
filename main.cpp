#include<iostream>
#include<conio.h>
#include<windows.h> 
using namespace std;
bool gameOver;
const int width= 20;
const int height= 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP= 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup()
{
    gameOver= false;
    dir= STOP; //initially it will be in stop condition
    x= width/2; //initially snake will b in the middle
    y= height/2; //snake head will b centered on the map
    fruitX= rand() % width;
    fruitY= rand() % height;
    score= 0; //initially score will b 0
}
void Draw()
{
    system("cls"); //will clear ur console window terminal
    for( int i = 0; i < width+2; i++) //top wall
        cout<<"#";
    cout<< endl;
    
    for( int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if (j == 0)
                cout<<"#";
            if (i == y && j == x)
                cout<<"O";
            else if (i == fruitY && j == fruitX)
                cout<<"F";
            else
            {
                bool print = false;
                for ( int k = 0; k < nTail; k++)
                {
                    if ( tailX[k] == j && tailY[k] == i) // if tailX[k] = xcoordinate n tailY[k] = y coordinate
                    {
                        cout<< "o";
                        print = true;
                    }
                }
                if ( !print)
                    cout << " "; // print blank space
            }
            
            if (j == width-1) //bcoz in for loop, it is j<width. so width-1
                cout<<"#";
        }
        cout<< endl;
    }
    for( int i = 0; i < width+2; i++) //bottom wall
        cout<<"#";
    cout<< endl;
    cout<< "Score: " << score <<endl;

}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x; // to make first element to follow the head
    tailY[0] = y;
    for ( int i = 1; i < nTail; i++)
    {
        prev2X= tailX[i]; // current position of our segment
        prev2Y= tailY[i];
        // now changing them to prevX and prevY
        tailX[i] = prevX;
        tailY[i] = prevY; 
        //next updating prevX to prev2X & prevY to prev2Y
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--; // if moves to left, decrease x-coordinate of snake 
        break;
    case RIGHT:
        x++; // if moves to right, increase x-coordinate
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    
    }
    /* if u hit on map or on tail then the game will over
    
    if ( x > width || x < 0 || y > height || y < 0) // comparing x & y coordinate with height & width of the map so that if snake hit on map game will over.
        gameOver = true;  */

    // here u can exit from any side of map and the game will over only if u hit on the tail
    if ( x >= width ) 
        x = 0;
    else if ( x < 0 )
        x = width-1;
    if ( y >= height )
        y=0;
    else if ( y < 0 )
        y = height-1;
    //
    for ( int i = 0; i < nTail; i++)
    {
        if ( tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if ( x == fruitX && y == fruitY) //checking if we eat food
    {
        score += 10;
        //fruits will randomly arrange on the playground
        fruitX= rand() % width;
        fruitY= rand() % height;
        nTail++; // increase the length of the tail by 1
    }
}
int main()
{
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10); 
    }
    return 0;
}