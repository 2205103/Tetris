#include "raylib.h"
#include <stdlib.h>
#include <time.h>

void rotate(int* matrix) {
    // Transpose the matrix
    for (int i = 0; i < 4; i++) {
        for (int j = i; j < 4; j++) {
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

int main(void) {


    const int screenWidth = 600;
    const int screenHeight = 900;

    int space[30][20]={0};

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
    int level=1;

    srand(time(0));
    int x = rand() % 17;
    

    while (!WindowShouldClose()) {
        // Update logic
        static int y = -120;

        static int k = 1;
        
        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 29; i >= 0; i--) {
            int flag=0;
            for (int j = 0; j<20; j++) {
                if (space[i][j]==1) {
                    DrawRectangle(j * 30 , i * 30, 30, 30, GREEN);
                    flag=1;
                }
            }
            if(flag==0) break;
        }


        // Draw grid
        for (int i = 0; i < 20; i++) {
            DrawLine(i * 30, 0, i * 30, screenHeight, GREEN);
        }
        for (int i = 0; i < 30; i++) {
            DrawLine(0, i * 30, screenWidth, i * 30, GREEN);
        }

       
        int max;
        // Draw current Tetrimino
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (*(matrix[k] + i * 4 + j)) {
                    max=i;
                    DrawRectangle(x * 30 + j * 30, y + i * 30, 30, 30, GREEN);
                }
            }
        }



        y += level;



        // Check for rotation input
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressedRepeat(KEY_SPACE)) {
            rotate(*(matrix+k));
        }

        if(IsKeyPressed(KEY_LEFT))
        {
            x-=1;
        }
        if(IsKeyPressed(KEY_RIGHT))
        {
            x+=1;
        }

        if (y + max * 30 + 30 >= 900) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (*(matrix[k] + i * 4 + j)) {
                        space[(y / 30) + i][x + j] = 1;
                    }
                }
            }
            y = -120;
            k = (k + 1) % 7;
            srand(time(0));
            x = rand() % 17;
        }


        EndDrawing();
    }
    free(matrix);
    CloseWindow();
    return 0;
}