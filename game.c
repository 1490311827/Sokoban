//0:空的 1:▆ 3：☆ 4：★ 5：※ 7:⊙ 8：※
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int map[2][7][8] =
    {
        {
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1},
            {1, 3, 1, 0, 1, 1, 3, 1},
            {1, 4, 0, 0, 4, 0, 3, 1},
            {1, 0, 1, 0, 1, 1, 4, 1},
            {1, 0, 0, 5, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1}
        },
        {
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1},
            {1, 3, 1, 0, 1, 1, 3, 1},
            {1, 3, 4, 5, 4, 0, 3, 1},
            {1, 4, 1, 0, 1, 1, 4, 1},
            {1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1}
        }
    };
int cas = 0; //为0表示第一关
//记录每一关的箱子数 或者是项目和目的在一起的总数
int boxSum[] = {3, 4};
//记录上次操作
int last_key[3][4];
//地图绘图
void drawMap()
{
    int i, j;
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (j == 0)
                printf("\t\t");
            switch (map[cas][i][j])
            {
                //	//0:空的 1:▆ :墙
            case 0:
                printf("  ");
                break;
            case 1:
                printf("▆");
                break;
                //3：☆ 4：★  //目的地和箱子
            case 3:
                printf("☆");
                break;
            case 4:
                printf("★");
                break;
                //5：※		  //人
            case 5:
            case 8:
                printf("※");
                break;
            case 7:
                printf("⊙");
                break;
                //7:⊙		  //目的(3)和箱子(4)在一起
                //8：※		  //人(5)和目的(3)在一起
            }
        }
        printf("\n");
    }
}
//按键处理
void keyDown()
{
    //分析按键过程
    //定位人在哪里
    //人有两种情况：第一个是：人，第二个：人站在目的上
    int i, j;
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (map[cas][i][j] == 5 || map[cas][i][j] == 8)
            {
                break;
            }
        }
        if (map[cas][i][j] == 5 || map[cas][i][j] == 8)
        {
            break;
        }
    }

    char ch = _getch(); //看不见的字符输入，+头文件 conio.h
    switch (ch)
    {
        //72 80   75 77
    case 'w':
    case 'W':
    case 72:
        //下一个地方等于空地或者是目的 能走
        if (map[cas][i - 1][j] == 0 || map[cas][i - 1][j] == 3)
        {
            //3+5=8 ：表示目的和人在一起
            //新地方(map[i-1][j])人（5）来了
            last_key[0][0] = cas;
            last_key[0][1] = i - 1;
            last_key[0][2] = j;
            last_key[0][3] = map[cas][i - 1][j];
            map[cas][i - 1][j] += 5;
            //老地方(map[i][j])人（5）走了
            last_key[1][0] = cas;
            last_key[1][1] = i;
            last_key[1][2] = j;
            last_key[1][3] = map[cas][i][j];
            map[cas][i][j] -= 5;
            last_key[2][0] = 0;
            last_key[2][1] = 0;
            last_key[2][2] = 0;
            last_key[2][3] = 0;
        }
        //如果下一个是箱子，要进一步判断能走
        //注意点：箱子两种状态：箱子，箱子和目的在一起
        else if (map[cas][i - 1][j] == 4 || map[cas][i - 1][j] == 7)
        {
            //做箱子的下一个地方判断能不能走
            if (map[cas][i - 2][j] == 0 || map[cas][i - 2][j] == 3)
            {
                //新的地方箱子来了
                last_key[0][0] = cas;
                last_key[0][1] = i - 2;
                last_key[0][2] = j;
                last_key[0][3] = map[cas][i - 2][j];
                map[cas][i - 2][j] += 4;
                //箱子的位置：箱子（-4）走了 人来（+5）
                last_key[1][0] = cas;
                last_key[1][1] = i - 1;
                last_key[1][2] = j;
                last_key[1][3] = map[cas][i - 1][j];
                map[cas][i - 1][j] += 1;
                //原来的地方人走了
                last_key[2][0] = cas;
                last_key[2][1] = i;
                last_key[2][2] = j;
                last_key[2][3] = map[cas][i][j];
                map[cas][i][j] -= 5;
            }
        }

        break;
    case 's':
    case 'S':
    case 80:
        //下一个地方等于空地或者是目的 能走
        if (map[cas][i + 1][j] == 0 || map[cas][i + 1][j] == 3)
        {
            //3+5=8 ：表示目的和人在一起
            //新地方(map[i-1][j])人（5）来了
            last_key[0][0] = cas;
            last_key[0][1] = i + 1;
            last_key[0][2] = j;
            last_key[0][3] = map[cas][i + 1][j];
            map[cas][i + 1][j] += 5;
            //老地方(map[i][j])人（5）走了
            last_key[1][0] = cas;
            last_key[1][1] = i;
            last_key[1][2] = j;
            last_key[1][3] = map[cas][i][j];
            map[cas][i][j] -= 5;
            last_key[2][0] = 0;
            last_key[2][1] = 0;
            last_key[2][2] = 0;
            last_key[2][3] = 0;
        }
        else if (map[cas][i + 1][j] == 4 || map[cas][i + 1][j] == 7)
        {
            //做箱子的下一个地方判断能不能走
            if (map[cas][i + 2][j] == 0 || map[cas][i + 2][j] == 3)
            {
                //新的地方箱子来了
                last_key[0][0] = cas;
                last_key[0][1] = i + 2;
                last_key[0][2] = j;
                last_key[0][3] = map[cas][i + 2][j];
                map[cas][i + 2][j] += 4;
                //箱子的位置：箱子（-4）走了 人来（+5）
                last_key[1][0] = cas;
                last_key[1][1] = i + 1;
                last_key[1][2] = j;
                last_key[1][3] = map[cas][i + 1][j];
                map[cas][i + 1][j] += 1;
                //原来的地方人走了
                last_key[2][0] = cas;
                last_key[2][1] = i;
                last_key[2][2] = j;
                last_key[2][3] = map[cas][i][j];
                map[cas][i][j] -= 5;
            }
        }
        break;

    case 'a':
    case 'A':
    case 75:
        //下一个地方等于空地或者是目的 能走
        if (map[cas][i][j - 1] == 0 || map[cas][i][j - 1] == 3)
        {
            //3+5=8 ：表示目的和人在一起
            //新地方(map[i-1][j])人（5）来了
            last_key[0][0] = cas;
            last_key[0][1] = i;
            last_key[0][2] = j - 1;
            last_key[0][3] = map[cas][i][j - 1];
            map[cas][i][j - 1] = map[cas][i][j - 1] + 5;
            //老地方(map[i][j])人（5）走了
            last_key[1][0] = cas;
            last_key[1][1] = i;
            last_key[1][2] = j;
            last_key[1][3] = map[cas][i][j];
            map[cas][i][j] = map[cas][i][j] - 5;
            last_key[2][0] = 0;
            last_key[2][1] = 0;
            last_key[2][2] = 0;
            last_key[2][3] = 0;
            //j+=5  j=j+5
        }
        else if (map[cas][i][j - 1] == 4 || map[cas][i][j - 1] == 7)
        {
            //做箱子的下一个地方判断能不能走
            if (map[cas][i][j - 2] == 0 || map[cas][i][j - 2] == 3)
            {
                //新的地方箱子来了
                last_key[0][0] = cas;
                last_key[0][1] = i;
                last_key[0][2] = j - 2;
                last_key[0][3] = map[cas][i][j - 2];
                map[cas][i][j - 2] += 4;
                //箱子的位置：箱子（-4）走了 人来（+5）
                last_key[1][0] = cas;
                last_key[1][1] = i;
                last_key[1][2] = j - 1;
                last_key[1][3] = map[cas][i][j - 1];
                map[cas][i][j - 1] += 1;
                //原来的地方人走了
                last_key[2][0] = cas;
                last_key[2][1] = i;
                last_key[2][2] = j;
                last_key[2][3] = map[cas][i][j];
                map[cas][i][j] -= 5;
            }
        }

        break;
    case 'D':
    case 'd':
    case 77:
        //下一个地方等于空地或者是目的 能走
        if (map[cas][i][j + 1] == 0 || map[cas][i][j + 1] == 3)
        {
            //3+5=8 ：表示目的和人在一起
            //新地方(map[i-1][j])人（5）来了
            last_key[0][0] = cas;
            last_key[0][1] = i;
            last_key[0][2] = j + 1;
            last_key[0][3] = map[cas][i][j + 1];
            map[cas][i][j + 1] += 5;
            //老地方(map[i][j])人（5）走了
            last_key[1][0] = cas;
            last_key[1][1] = i;
            last_key[1][2] = j;
            last_key[1][3] = map[cas][i][j];
            map[cas][i][j] -= 5;
            last_key[2][0] = 0;
            last_key[2][1] = 0;
            last_key[2][2] = 0;
            last_key[2][3] = 0;
        }

        //下一个地方是箱子，判断箱子的下一个地方是不是目的和空地
        else if (map[cas][i][j + 1] == 4 || map[cas][i][j + 1] == 7)
        {
            //做箱子的下一个地方判断能不能走
            if (map[cas][i][j + 2] == 0 || map[cas][i][j + 2] == 3)
            {
                //新的地方箱子来了
                last_key[0][0] = cas;
                last_key[0][1] = i;
                last_key[0][2] = j + 2;
                last_key[0][3] = map[cas][i][j + 2];
                map[cas][i][j + 2] += 4;
                //箱子的位置：箱子（-4）走了 人来（+5）
                last_key[1][0] = cas;
                last_key[1][1] = i;
                last_key[1][2] = j + 1;
                last_key[1][3] = map[cas][i][j + 1];
                map[cas][i][j + 1] += 1;
                //原来的地方人走了
                last_key[2][0] = cas;
                last_key[2][1] = i;
                last_key[2][2] = j;
                last_key[2][3] = map[cas][i][j];
                map[cas][i][j] -= 5;
            }
        }
        break;

    case 'b':
    case 'B':
        {
            //返回上次操作
            map[last_key[0][0]][last_key[0][1]][last_key[0][2]] = last_key[0][3];
            map[last_key[1][0]][last_key[1][1]][last_key[1][2]] = last_key[1][3];
            if (last_key[2][0] == 0 && last_key[2][1] == 0 && last_key[2][2] == 0 && last_key[2][3] == 0)
                break;
            else
                map[last_key[2][0]][last_key[2][1]][last_key[2][2]] = last_key[2][3];
        }
        break;
    }
}
//胜负判断
//用什么判断胜负： 箱子到达目的的个数
int gameOver()
{
    int count = 0, i, j;
    //所有的地方找一遍
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (map[cas][i][j] == 7)
                count++;
        }
    }
    return count;
}
//箱子数是零的时候也是胜利
int gameOver2()
{
    int count = 3, i, j;
    //所有的地方找一遍
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (map[cas][i][j] == 3)
                count--;
        }
    }
    return count;
}

//隐藏光标函数
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; //第二个值为0表示隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

int main()
{
    HideCursor();
    while (1)
    {
        system("mode con cols=50 lines=20");
        system("color 70");
        printf("\n\n\t墙:▆  目标地：☆  箱子：★   人：※ \n\t*上下左右控制人移动推箱子;按b撤回一步\n");
        printf("\n\n\t\t   第【%d】关\n", cas + 1);
        drawMap();
        if (gameOver() == boxSum[cas])
        {
            cas++;
            if (cas == (int)(sizeof(boxSum)/sizeof(boxSum[0])))
                break;
            else
                printf("\n\t恭喜通过第%d关,按任意键继续\n", cas);
        }
        keyDown();
        gotoxy(0, 0);
    }
    printf("\n\t已通关, GameOVer!");
    system("pause");
    return 0;
}
