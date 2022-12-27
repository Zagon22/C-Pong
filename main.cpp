#include <iostream>
#include <windows.h>
#include <conio.h>

#define UP 72
#define DOWN 80
#define ENTER 13
#define y 21
#define x 75

using namespace std;

int option = 0;
string arrow = "-->";

void gotoxy(int a, int b);
void drawmenu(); int move();
void options(int* program_loop);
void start(char area[y][x], int ballX, int ballY, int initP, int endP, int initIA_P2, int endIA_P2);
void border(char area[y][x]);
void racP(char area[y][x], int initP, int endP);
void racIA_P2(char area[y][x], int initIA_P2, int endIA_P2);
void ball(char area[y][x], int ballX, int ballY);
void drawArea(char area[y][x]);
void gameloop(char area[y][x], int ballX, int ballY, int initP, int endP, int initIA_P2, int endIA_P2, int modX, int modY, int modIA, int option);
void imput(char area[y][x], int* ballX, int* ballY, int* initP, int* endP, int* initIA_P2, int* endIA_P2, int* modX, int* modY, int* modIA, int* score, int* scorePlayer, int* scoreIA_P2, int option);
void update(char area[y][x], int ballX, int ballY, int initP, int endP, int initIA_P2, int endIA_P2);
void mark(int score, int scorePlayer, int scoreIA_P2, int* game_loop, int option);

int main() {
    int program_loop = 0;
    do {
        options(&program_loop);
    } while (program_loop == 0);
}

void gotoxy(int a, int b) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = a;
    dwPos.Y = b;
    SetConsoleCursorPosition(hCon, dwPos);
}

void drawmenu() {
    string tittle = "Modo";
    string OpSelect[] = { "P1 Vs PC", "P1 Vs P2", "Salir" };

    // Impresión del menú
    gotoxy(5, 3); cout << tittle;
    for (int i = 0; i < 3; i++) {
        gotoxy(9, 5 + i); cout << OpSelect[i];
    }
}

int move() {
    gotoxy(5, 5 + option); cout << arrow;
    if (_kbhit())
    {
        char key = _getch();
        if (key == DOWN)
        {
            option++;
            if (option < 3)
            {
                gotoxy(5, 5 + option - 1); cout << "   ";
            }
            else
            {
                gotoxy(5, 5 + option - 1); cout << "   ";
                option = 0;
            }
        }
        if (key == UP)
        {
            option--;
            if (option < 0) {
                gotoxy(5, 5 + option + 1); cout << "   ";
                option = 2;
            }
            else {
                gotoxy(5, 5 + option + 1); cout << "   ";
            }
        }
        if (key == ENTER)
            return option;
    }
    Sleep(50);
    move();
}

void options(int* program_loop) {
    int ballX, ballY, initP, endP, initIA_P2, endIA_P2;
    int modX, modY, modIA;
    char area[y][x];
    ballX = 37; ballY = 10;
    initP = 8; endP = 12;
    initIA_P2 = 8; endIA_P2 = 12;
    modX = -1; modY = -1; modIA = -1;
    drawmenu();
    move();
    system("cls");
    switch (option)
    {
        case 0:
            start(area, ballX, ballY, initP, endP, initIA_P2, endIA_P2);
            gameloop(area, ballX, ballY, initP, endP, initIA_P2, endIA_P2, modX, modY, modIA, option);
            system("cls");
            *program_loop = 0;
            break;
        case 1:
            start(area, ballX, ballY, initP, endP, initIA_P2, endIA_P2);
            gameloop(area, ballX, ballY, initP, endP, initIA_P2, endIA_P2, modX, modY, modIA, option);
            system("cls");
            *program_loop = 0;
            break;
        case 2:
            *program_loop = 1;
            break;
    }
}

void start(char area[y][x], int ballX, int ballY, int initP, int endP, int initIA_P2, int endIA_P2) {
    border(area);
    racP(area, initP, endP);
    racIA_P2(area, initIA_P2, endIA_P2);
    ball(area, ballX, ballY);
}

void border(char area[y][x]) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (i == 0 || i == y - 1) {
                area[i][j] = '-';
            }
            else if (j == 0 || j == x - 1) {
                area[i][j] = '|';
            }
            else {
                area[i][j] = ' ';
            }
        }
    }
}

void racP(char area[y][x], int initP, int endP) {
    for (int i = initP; i < endP; i++) {
        for (int j = 2; j < 4; j++) {
            area[i][j] = 'X';
        }
    }
}

void racIA_P2(char area[y][x], int initIA_P2, int endIA_P2) {
    for (int i = initIA_P2; i < endIA_P2; i++) {
        for (int j = x - 4; j < x - 2; j++) {
            area[i][j] = 'X';
        }
    }
}

void ball(char area[y][x], int ballX, int ballY) {
    area[ballY][ballX] = 'O';
}

void gameloop(char area[y][x], int ballX, int ballY, int initP, int endP, int initIA_P2, int endIA_P2, int modX, int modY, int modIA_P2, int option) {
    int score = 0, scorePlayer = 0, scoreIA_P2 = 0, game_loop = 0;
    do {
        drawArea(area);
        imput(area, &ballX, &ballY, &initP, &endP, &initIA_P2, &endIA_P2, &modX, &modY, &modIA_P2, &score, &scorePlayer, &scoreIA_P2, option);
        update(area, ballX, ballY, initP, endP, initIA_P2, endIA_P2);
        mark(score, scorePlayer, scoreIA_P2, &game_loop, option);
        Sleep(1); // Debe variar en función de la velocidad del microprocesador.
    } while (game_loop == 0);
}

void drawArea(char area[y][x]) {
    system("cls");
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            cout << area[i][j];
        }
        cout << endl;
    }
}

void imput(char area[y][x], int* ballX, int* ballY, int* initP, int* endP, int* initIA_P2, int* endIA_P2, int* modX, int* modY, int* modIA, int* score, int* scorePlayer, int* scoreIA_P2, int option) {
    if (*ballY == 1 || *ballY == y - 2) {
        *modY *= -1;
    }
    if (*ballX == 1 || *ballX == x - 2) {
        *score += 1;
        if (*ballX == 1) {
            *scoreIA_P2 += 1;
        }
        if (*ballX == x - 2) {
            *scorePlayer += 1;
        }
        /* Reseteo de las posiciones */
        *ballX = 37; *ballY = 10;
        *initP = 8; *endP = 12;
        *initIA_P2 = 8; *endIA_P2 = 12;
    }
    /* Trayectoria de la pelota al impactar con el jugador */

    /* Colisión lateral */
    if (*ballX == 4) {
        for (int i = *initP; i < *endP; i++) {
            if (i == (*ballY)) {
                *modX *= -1;
            }
        }
    }
    /* Colisiones superior e inferior */
    if ((*ballX == 3 && (*ballY == *endP || *ballY == *initP - 1)) || (*ballX == 2 && (*ballY == *endP || *ballY == *initP - 1))) {
        *modY *= -1;
        *modX *= -1;
    }
    /* Colisiones diagonales */
    if (*ballX == 4 && (*ballY == *endP || *ballY == *initP - 1)) {
        *modY *= -1;
        *modX *= -1;
        if (*ballY == 1 || *ballY == y - 2) {
            *modY *= -1;
        }
    }
    /* Trayectoria de la pelota al impactar con la IA o P2 */

    /* Colisión lateral */
    if (*ballX == x - 5) {
        for (int i = *initIA_P2; i < *endIA_P2; i++) {
            if (i == (*ballY)) {
                *modX *= -1;
            }
        }
    }
    /* Colisiones superior e inferior */
    if ((*ballX == x - 4 && (*ballY == *endIA_P2 || *ballY == *initIA_P2 - 1)) || (*ballX == x - 3 && (*ballY == *endIA_P2 || *ballY == *endIA_P2 - 1))) {
        *modY *= -1;
        *modX *= -1;
    }
    /* Colisiones diagonales */
    if (*ballX == x - 5 && (*ballY == *endIA_P2 || *ballY == *initIA_P2 - 1)) {
        *modY *= -1;
        *modX *= -1;
        if (*ballY == 1 || *ballY == y - 2) {
            *modY *= -1;
        }
    }

    if (*score <= 2) {
        char key;
        *ballX += (*modX);
        *ballY += (*modY);
        if (option == 0) {
            if (*initIA_P2 == 1 || *endIA_P2 == y - 1) {
                *modIA *= -1;
            }
            *initIA_P2 += (*modIA);
            *endIA_P2 += (*modIA);
            if (_kbhit()) {
                key = _getch();
                switch (key) 
                {
                    case 'w':
                        if (*initP != 1) {
                            *initP -= 1;
                            *endP -= 1;
                        }
                        else {
                            break;
                        }
                        break;
                    case 's':
                        if (*endP != y - 1) {
                            *initP += 1;
                            *endP += 1;
                        }
                        else {
                            break;
                        }
                        break;
                }
            }
        }
        else if (option == 1) {
            if (_kbhit()) {
                key = _getch();
                switch (key) 
                {
                    case 'w':
                        if (*initP != 1) {
                            *initP -= 1;
                            *endP -= 1;
                        }
                        else {
                            break;
                        }
                        break;
                    case 's':
                        if (*endP != y - 1) {
                            *initP += 1;
                            *endP += 1;
                        }
                        else {
                            break;
                        }
                        break;
                    case 'i':
                        if (*initIA_P2 != 1) {
                            *initIA_P2 -= 1;
                            *endIA_P2 -= 1;
                        }
                        else {
                            break;
                        }
                        break;
                    case 'k':
                        if (*endIA_P2 != y - 1) {
                            *initIA_P2 += 1;
                            *endIA_P2 += 1;
                        }
                        else {
                            break;
                        }
                        break;
                }
            }
        }
    }
}

void update(char area[y][x], int ballX, int ballY, int initP, int endP, int initIA_P2, int endIA_P2) {
    border(area);
    racP(area, initP, endP);
    racIA_P2(area, initIA_P2, endIA_P2);
    ball(area, ballX, ballY);
}

void mark(int score, int scorePlayer, int scoreIA_P2, int* game_loop, int option) {
    string scoreText[2] = { "Score PC: ", "Score P2: " };
    cout << "Score P1: " << scorePlayer << endl;
    cout << scoreText[option] << scoreIA_P2 << endl;
    if (score > 2 || scorePlayer == 2 || scoreIA_P2 == 2) {
        *game_loop = 1;
    }
}
