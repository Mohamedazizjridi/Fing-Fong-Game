#include <iostream>
#include <raylib.h>
using namespace std;
enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};
GameState currentState = MENU;
int player_score=0;
int cpu_score=0;
int selectedMenuItem = 0;
const int WINNING_SCORE = 5;
class Ball{
    public:
        float x,y;
        int speedx,speedy;
        int radius;

    void draw()
    {
        DrawCircle(x,y,radius,GREEN);
    }
    void update()
    {
        x+=speedx;
        y+=speedy;
        if(y+radius>=GetScreenHeight() || y-radius<=0)
        {
            speedy*=-1;
        }
        if(x+radius>=GetScreenWidth())
        {
            cpu_score++;
            resetball();
        }
        if(x-radius<=0)
        {
            player_score++;
            resetball();
        }
       
    }
    void resetball(){
        x=GetScreenWidth()/2;
        y=GetScreenHeight()/2;

        int speed_choices[2]={-1,1};
        speedx*=speed_choices[GetRandomValue(0,1)];
        speedy*=speed_choices[GetRandomValue(0,1)];

    }



};
class paddel{
    protected : 
    void limitmovement ()
    {
        if(y<=0)
        {
            y=0;
        }
        if(y+height>=GetScreenHeight())
        {
            y=GetScreenHeight()-height;
        }
    }
    public:
     float x,y;
     float width,height;
     int speed;

    void draw()
    {
        DrawRectangle(x ,y,width,height,WHITE);
    }
    void update()
    {
        if(IsKeyDown(KEY_UP))
        {
            y=y-speed;
        }
         if(IsKeyDown(KEY_DOWN))
        {
            y=y+speed;
        }
        limitmovement();
    }
};

class CPupaddel: public paddel{
    public : 
     void update(int ball_y){
        if(y+height/2 > ball_y)
        {
            y=y-speed;
        }
        if(y+height/2<= ball_y)
        {
            y=y+speed;
        }
        limitmovement();
     }
};
void Drawmenu(){
    int screenwidth=GetScreenWidth();
    int screenheight=GetScreenHeight();

    ClearBackground(BLACK);

    const char* title ="PONG GAME";
    int titleWidth = MeasureText(title, 80);
    DrawText(title, screenwidth/2 - titleWidth/2, screenheight/2 - 150, 80, GREEN);

    const char* subtitle = "Classic Arcade Game";
    int subtitleWidth = MeasureText(subtitle, 30);
    DrawText(subtitle, screenwidth/2 - subtitleWidth/2, screenheight/2 - 80, 30, GRAY);

    Color startColor = (selectedMenuItem == 0) ? GREEN : WHITE;
    Color exitColor = (selectedMenuItem == 1) ? GREEN : WHITE;
    const char* startText = "START GAME";
    const char* exitText = "EXIT";
    int startWidth = MeasureText(startText, 40);
    int exitWidth = MeasureText(exitText, 40);
    DrawText(startText, screenwidth/2 - startWidth/2, screenheight/2 + 20, 40, startColor);
    DrawText(exitText, screenwidth/2 - exitWidth/2, screenheight/2 + 80, 40, exitColor);


    const char* controlsText = "Use UP/DOWN arrows to navigate, ENTER to select";
    int controlsWidth = MeasureText(controlsText, 20);
    DrawText(controlsText, screenwidth/2 - controlsWidth/2, screenheight - 100, 20, GRAY);
    
    const char* gameControlsText = "Game Controls: UP/DOWN arrows to move paddle";
    int gameControlsWidth = MeasureText(gameControlsText, 20);
    DrawText(gameControlsText, screenwidth/2 - gameControlsWidth/2, screenheight - 60, 20, GRAY);
}
void HandleMenuInput() {
    if(IsKeyPressed(KEY_UP)) {
        selectedMenuItem = (selectedMenuItem - 1 + 2) % 2;
    }
    if(IsKeyPressed(KEY_DOWN)) {
        selectedMenuItem = (selectedMenuItem + 1) % 2;
    }
    if(IsKeyPressed(KEY_ENTER)) {
        if(selectedMenuItem == 0) {
          
            currentState = PLAYING;
            player_score = 0;
            cpu_score = 0;
        } else {
            exit(0);
        }
    }
}
void drawGameover(){
    int screenwidth = GetScreenWidth();
    int screenheight = GetScreenHeight();
    DrawRectangle(0, 0, screenwidth, screenheight, Fade(BLACK, 0.8f));
    const char* gameOverText = "GAME OVER";
    int gameOverWidth = MeasureText(gameOverText, 60);
    DrawText(gameOverText, screenwidth/2 - gameOverWidth/2, screenheight/2 - 100, 60, RED);
    const char* winnerText;
    if(player_score >= WINNING_SCORE) {
        winnerText = "PLAYER WINS!";
    } else {
        winnerText = "CPU WINS!";
    }
    int winnerwidth = MeasureText(winnerText, 40);
    DrawText(winnerText, screenwidth/2 - winnerwidth/2, screenheight/2 - 30, 40, GREEN);

    const char* instructionText = "Press SPACE to return to menu";
    int instructionWidth = MeasureText(instructionText, 25);
    DrawText(instructionText, screenwidth/2 - instructionWidth/2, screenheight/2 + 50, 25, WHITE);


}
Ball ball;
paddel player;
CPupaddel cpu;
int main (){
    cout<<"starting teh game"<<endl;
    const int width =1280;
    const int height =800;
    InitWindow(width, height, "PONG - Classic Arcade Game");
    SetTargetFPS(60);
    ball.radius=20;
    ball.x=width/2;
    ball.y=height/2;
    ball.speedx=7;
    ball.speedy=7;
    player.width=25;
    player.height=120;
    player.x=width-player.width-10;
    player.y=height/2-player.height/2;
    player.speed=6;
    cpu.height=120;
    cpu.width=25;
    cpu.x=10;
    cpu.y=height/2 - cpu.height/2;
    cpu.speed=6;
    while(WindowShouldClose()==false)
    {
        BeginDrawing();
        //
        switch(currentState){
            case MENU:
            {
                HandleMenuInput();
                Drawmenu();
            }
            break;
            case PLAYING :
            {
                    ball.update();
                    player.update();
                    cpu.update(ball.y);
                    // checking collsion 
                    if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player.x,player.y,player.width,player.height}))
                    {
                        ball.speedx*=-1;
                    }
                    if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x,cpu.y,cpu.width,cpu.height}))
                    {
                        ball.speedx*=-1;
                    }
                    if(player_score >= WINNING_SCORE || cpu_score >= WINNING_SCORE) {
                        currentState = GAME_OVER;
                    }
                    if(IsKeyPressed(KEY_SPACE)) {
                        currentState = PAUSED;
                    }
                    // drawing
                    ClearBackground(BLACK);
                    DrawLine(width/2,0,width/2,height,RED);
                    ball.draw();
                    cpu.draw();
                    player.draw();
                    DrawText(TextFormat("%i",cpu_score),width/4 - 20,20,80,GREEN);
                    DrawText(TextFormat("%i",player_score),3*width/4 - 20,20,80,GREEN);
                    DrawText("Press SPACE to pause", 10, height - 30, 20, GRAY);
            }
            break;
            case PAUSED : {
                ClearBackground(BLACK);
                DrawLine(width/2, 0, width/2, height, RED);
                ball.draw();
                cpu.draw();
                player.draw();
                DrawText(TextFormat("%i", cpu_score), width/4 - 20, 20, 80, GREEN);
                DrawText(TextFormat("%i", player_score), 3*width/4 - 20, 20, 80, GREEN);
                DrawRectangle(0, 0, width, height, Fade(BLACK, 0.7f));
                const char* pauseText = "PAUSED";
                int pauseWidth = MeasureText(pauseText, 60);
                DrawText(pauseText, width/2 - pauseWidth/2, height/2 - 30, 60, WHITE);
                const char* resumeText = "Press SPACE to resume";
                int resumeWidth = MeasureText(resumeText, 25);
                DrawText(resumeText, width/2 - resumeWidth/2, height/2 + 50, 25, GRAY);
                if(IsKeyPressed(KEY_SPACE)) {
                        currentState = PLAYING;
                }
            }
            break;
            case GAME_OVER:{
                ClearBackground(BLACK);
                DrawLine(width/2, 0, width/2, height, RED);
                ball.draw();
                cpu.draw();
                player.draw();
                DrawText(TextFormat("%i", cpu_score), width/4 - 20, 20, 80, GREEN);
                DrawText(TextFormat("%i", player_score), 3*width/4 - 20, 20, 80, GREEN);
                drawGameover();
                if(IsKeyPressed(KEY_SPACE)) {
                        currentState = MENU;
                        ball.resetball();
                    }

            }
            break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}