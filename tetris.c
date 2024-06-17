#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include<stdio.h>


int window=1;

int space[30][20]={0};


void rotate(int* matrix) 
{
    // Transpose the matrix
    for (int i = 0; i < 4; i++) 
    {
        for (int j = i; j < 4; j++) 
        {
            int t = *(matrix + i * 4 + j);
            *(matrix + i * 4 + j) = *(matrix + j * 4 + i);
            *(matrix + j * 4 + i) = t;
        }
    }

    // Reverse each row
    for(int j=0;j<2;j++)
    {
        for(int i=0;i<4;i++)
        {
            int t=*(matrix+i+4*j);
            *(matrix+i+4*j)=*(matrix+i+4*(4-j-1));
            *(matrix+i+4*(4-j-1))=t;
        }
    }
}

void remove_line()
{
    for(int i=28;i>=0;i--)
    {
        int count=0;
        for(int j=0;j<20;j++)
        {
            if(space[i][j]!=0) count=1;
            space[i+1][j]=space[i][j];
        }
        if(count==0) return;
    }
}

int main(void) 
{


    const int screenWidth = 1000;
    const int screenHeight = 900;
    int score=0;

    int O[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    int L[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 1, 1, 1},
        {0, 0, 0, 0}
    };

    int I[4][4] = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    int S[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    int Z[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0}
    };

    int J[4][4] = {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    int T[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    int ** matrix=(int**) malloc(7*sizeof(int*));
        matrix[0]=&O[0][0];
        matrix[1]=&L[0][0];
        matrix[2]=&I[0][0];
        matrix[3]=&J[0][0];
        matrix[4]=&Z[0][0];
        matrix[5]=&T[0][0];
        matrix[6]=&S[0][0];

    

    InitWindow(screenWidth, screenHeight, "Tetris Clone");
    
    SetTargetFPS(20);
    int level=8;

    srand(time(0));
    int x = rand() % 17;
    int space_fill=100;
    bool collide=false;
    
    Texture2D texture[] = {LoadTexture("1.png"),LoadTexture("2.png"),LoadTexture("3.png"),LoadTexture("4.png"),LoadTexture("5.png")};
    
    int y = -120;
    int k = 1;

while (!WindowShouldClose()) {

    if(window==6)
    {
        int lead_y=1;
            ClearBackground(BLACK);
            DrawRectangleLines(5,5,100,30,GREEN);
            DrawText("Back",20,6,30,GREEN);
            char str[100];
            FILE*fp=fopen("file.txt","r");
            BeginDrawing();
            while(!feof(fp))
            {
                fgets(str,100,fp);
                if(str[0]!='\0') DrawText(str,350,50*lead_y,30,WHITE);
                lead_y++;
            }
            fclose(fp);
            EndDrawing();

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX()>=5 && GetMouseX()<=105 && GetMouseY()>=5 && GetMouseY()<=35)
            {
                window=2;
                texture[2]=LoadTexture("3.png");

            }
    }

    else if(window==5)
    {
        ClearBackground(BLACK);
        static bool scan=0;
        BeginDrawing();
        char name[20];
        static int count=0;
        DrawTexture(texture[4],0,0,WHITE);
        if(count>0)
        {
            DrawText(name,275,370,50,BLACK);
        }
        EndDrawing();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if(GetMouseX()>=270 && GetMouseX()<=740 && GetMouseY()>=365 && GetMouseY()<=445)
            {
                scan=1;
            }
            else scan=0;
        }

        if(scan)
        {
            if(IsKeyPressed(KEY_ENTER))
            {
                FILE * fp=fopen("file.txt","a");
                fprintf(fp,"\n%s ",name);
                fclose(fp);
                    UnloadTexture(texture[4]);
                    scan=0;
                    window=3;
                    score=0;
                    level=8;
                    texture[3]=LoadTexture("4.png");
                    count=0;
            }
            int letter=GetKeyPressed();
            if((letter>=64 && letter<=126) || (char) letter == ' ')
            {
                name[count]=(char) letter;
                count++;
                name[count]='\0';
            }

            if(IsKeyPressed(KEY_BACKSPACE))
            {
                count--;
                name[count]='\0';
            }
        }

    }

 else if(window==4)
    {
        BeginDrawing();
        ClearBackground(BLACK);
       DrawTexture(texture[1],0,0,WHITE);
       DrawText(TextFormat("%d",score),565, 312, 100, BLACK);
       EndDrawing();

    if(IsKeyPressed(KEY_ENTER))
    {
     UnloadTexture(texture[1]);
       FILE * fp=fopen("file.txt","a");
       fprintf(fp,"%d",score);
       fclose(fp);
        window=2;
           texture[2]=LoadTexture("3.png");
          }
    }


else if(window==1)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(texture[0],0,0,WHITE);
    EndDrawing();
    if(IsKeyPressed(KEY_ENTER))
        {
            UnloadTexture(texture[0]);
            window=2;
            texture[2]=LoadTexture("3.png");
        }
}


    else if(window==2)
    {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(texture[2],0,0,WHITE);
    EndDrawing();
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if(GetMouseX()>=57 && GetMouseX()<=270 && GetMouseY()>=725 && GetMouseY()<=838)
        {
            window=6;
        }
        else if(GetMouseX()>=296 && GetMouseX()<=567 && GetMouseY()>=400 && GetMouseY()<=519)
        {
            {
                for(int i=0;i<30;i++)
                    {
                        for(int j=0;j<20;j++)
                                    {   
                                        space[i][j]=0;
                                    }
                    }
                    UnloadTexture(texture[2]);
                    window=5;
                    score=0;
                    level=8;
                    texture[4]=LoadTexture("5.png");
            }
        }
    }
    }

    else if(window==3)
    {

        if(IsKeyPressed(KEY_BACKSPACE))
        {
            window=4;
            UnloadTexture(texture[3]);
            texture[1]=LoadTexture("2.png");
            y=-120;
        }
        ClearBackground(BLACK);
        BeginDrawing();
        ClearBackground(BLACK);

    /*
        eikhane score dekhar code add korbi
    */

    for (int i = 29; i >= 0; i--) 
    {
        int flag=0;
        for (int j = 0; j<20; j++) 
        {
            if (space[i][j]!=0) 
            {
                space_fill=i;
                if(space[i][j]==100) DrawRectangle(j * 30 , i * 30, 30, 30, PINK);
                else if(space[i][j]==101) DrawRectangle(j * 30 , i * 30, 30, 30, MAROON);
                else if(space[i][j]==102) DrawRectangle(j * 30 , i * 30, 30, 30, VIOLET);
                else if(space[i][j]==103) DrawRectangle(j * 30 , i * 30, 30, 30, WHITE);
                else if(space[i][j]==104) DrawRectangle(j * 30 , i * 30, 30, 30, BROWN);
                else if(space[i][j]==105) DrawRectangle(j * 30 , i * 30, 30, 30, PURPLE);
                else if(space[i][j]==106) DrawRectangle(j * 30 , i * 30, 30, 30, ORANGE);
                flag++;
            }
        }
        if(flag==0) break;
        else if(flag==20)
        {
            remove_line();
            score++;
            level+=2;
        }
    }

    // Draw grid
        for (int i = 0; i < 20; i++) 
        {
            DrawLine(i * 30, 0, i * 30, 900, DARKGRAY);
        }
        for (int i = 0; i < 30; i++) 
        {
            DrawLine(0, i * 30, 600, i * 30, DARKGRAY);
        }
    DrawTexture(texture[3],600,0,WHITE);
    ClearBackground(BLACK);
    DrawText(TextFormat("%d",score), 600+182, 370, 50, BLACK);
    DrawText(TextFormat("%d",((level-8)/2)*2), 778, 790, 50, BLACK);
    
    int max;
    int max_j=0,min_j=4,max_i,min_i;
    // Draw current Tetrimino
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            if (*(matrix[k] + i * 4 + j)) 
            {
                if(max_j<j) {max_j=j,max_i=i;}
                if(min_j>j) {min_j=j,min_i=i;}
                max=i;
                
                if(k==0) DrawRectangle(x * 30 + j * 30, y + i * 30, 30, 30, PINK);
                else if(k==1) DrawRectangle(x * 30 + j * 30, y + i * 30, 30, 30, MAROON);
                else if(k==2) DrawRectangle(x * 30 + j * 30, y + i * 30, 30, 30, VIOLET);
                else if(k==3) DrawRectangle(x * 30 + j * 30, y + i * 30, 30, 30, WHITE);
                else if(k==4) DrawRectangle(x * 30 + j * 30, y + i * 30, 30, 30, BROWN);
                else if(k==5) DrawRectangle(x * 30 + j * 30, y + i * 30, 30, 30, PURPLE);
                else if(k==6) DrawRectangle(x * 30 + j * 30, y + i * 30, 30, 30, ORANGE);
            }
        }
    }



    y += level;



    // Check for rotation input
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressedRepeat(KEY_SPACE)) 
    {
        rotate(*(matrix+k));
    }

    if(IsKeyPressed(KEY_LEFT)|| IsKeyPressedRepeat(KEY_LEFT))
    {
        if(x+min_j>0 && space[y/30+min_i][x+min_j-1]==0) x-=1;
    }
    if(IsKeyPressed(KEY_RIGHT)|| IsKeyPressedRepeat(KEY_RIGHT))
    {
        if(x+max_j<19 && space[y/30+max_i][x+max_j+1]==0) x+=1;
    }


    if(((y + max * 30 + 30)/30)>=space_fill)
    {
        for(int j=0;j<4;j++)
        {
            int max_i=-1;
            for(int i=3;i>=0;i--)
            {
                if(*(matrix[k] + i * 4 + j))
                {
                    max_i=i;
                    break;
                }
            }

            if(max_i>=0 && space[((y + max_i * 30 + 30)/30)][x+j])
            {
                collide=true;
                break;
            }
        }
    }

    if (y + max * 30 + 30 >= 900 || collide) 
    {
        for (int i = 0; i < 4; i++) \
        {
            for (int j = 0; j < 4; j++) 
            {
                if (*(matrix[k] + i * 4 + j)) 
                {
                    if(((y / 30) + i)<=0) //Game Over
                    {
                        window=4;
                        UnloadTexture(texture[3]);
                        texture[1]=LoadTexture("2.png");
                        break;
                         //eta kete dibi
                        //first e clearBackgroun dibi
                        //then image sound add korbi
                        //tarpor each option er jonno window
                        //er value update korar code likhbi
                    }
                    space[(y / 30) + i][x + j] = k+100;
                }
            }
            if(window==4) break;
        }
        y = -120;
        k = (k + 1) % 7;
        srand(time(0));
        x = rand() % 17;
        if(collide) collide=false;
    }
    EndDrawing();
    }
}
    free(matrix);
    CloseWindow();
    return 0;
}