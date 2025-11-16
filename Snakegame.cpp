#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
using namespace std;

void gotoxy(int column, int line);

// Kích thước khung chơi
const int LEFT   = 0;
const int TOP    = 0;
const int RIGHT  = 50;
const int BOTTOM = 20;

struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[100];   // thân rắn
    int DoDai;      // độ dài rắn

    CONRAN() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }

    void Ve() {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }
    }

    // Huong: 0 = phải, 1 = xuống, 2 = trái, 3 = lên
    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }

        if (Huong == 0) A[0].x = A[0].x + 1; // phải
        if (Huong == 1) A[0].y = A[0].y + 1; // xuống
        if (Huong == 2) A[0].x = A[0].x - 1; // trái
        if (Huong == 3) A[0].y = A[0].y - 1; // lên
    }
};

// ======== VẼ KHUNG =========
void VeKhung() {
    // cạnh trên & dưới
    for (int x = LEFT; x <= RIGHT; x++) {
        gotoxy(x, TOP);
        cout << "#";
        gotoxy(x, BOTTOM);
        cout << "#";
    }
    // cạnh trái & phải
    for (int y = TOP; y <= BOTTOM; y++) {
        gotoxy(LEFT, y);
        cout << "#";
        gotoxy(RIGHT, y);
        cout << "#";
    }
}

// ======== MỒI =============
Point Food;

void TaoMoi() {
    // random trong vùng bên trong khung
    Food.x = LEFT + 1 + rand() % (RIGHT - LEFT - 1);
    Food.y = TOP  + 1 + rand() % (BOTTOM - TOP - 1);
}

// (optional) kiểm tra rắn đụng tường -> kết thúc game
bool DungTuong(CONRAN &r) {
    if (r.A[0].x <= LEFT || r.A[0].x >= RIGHT ||
        r.A[0].y <= TOP  || r.A[0].y >= BOTTOM) {
        return true;
    }
    return false;
}

int main() {
    CONRAN r;
    int Huong = 0;
    char t;

    srand(time(NULL));
    TaoMoi();

    while (1) {
        // Bắt phím
        if (kbhit()) {
            t = getch();
            if (t == 'a') Huong = 2; // trái
            if (t == 'd') Huong = 0; // phải
            if (t == 'w') Huong = 3; // lên
            if (t == 'x') Huong = 1; // xuống
        }

        system("cls");

        // Vẽ khung
        VeKhung();

        // Vẽ mồi
        gotoxy(Food.x, Food.y);
        cout << "O";

        // Vẽ rắn
        r.Ve();

        // Di chuyển
        r.DiChuyen(Huong);

        // (optional) kiểm tra đụng tường
        if (DungTuong(r)) {
            gotoxy(0, BOTTOM + 2);
            cout << "Game Over!";
            break;
        }

        // ĂN MỒI
        if (r.A[0].x == Food.x && r.A[0].y == Food.y) {
            // Tăng độ dài rắn
            if (r.DoDai < 100) {
                r.DoDai++;
                // gắn thêm 1 đốt ở cuối, trùng với đốt hiện tại
r.A[r.DoDai - 1] = r.A[r.DoDai - 2];
            }
            // Tạo mồi mới
            TaoMoi();
        }

        Sleep(150);
    }

    gotoxy(0, BOTTOM + 4);
    system("pause");
    return 0;
}

// Hàm gotoxy dùng Windows API
void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}