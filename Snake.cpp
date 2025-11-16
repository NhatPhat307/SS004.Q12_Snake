#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[100];
    int DoDai;

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

        if (Huong == 0) A[0].x = A[0].x + 1;
        if (Huong == 1) A[0].y = A[0].y + 1;
        if (Huong == 2) A[0].x = A[0].x - 1;
        if (Huong == 3) A[0].y = A[0].y - 1;
    }
};

// ====== PHẦN CỦA SV3: MỒI + ĂN MỒI ======
Point Food;

// Tạo mồi random trong vùng 1..78 x 1..22 (tùy ý chỉnh)
void TaoMoi() {
    Food.x = 1 + rand() % 78;
    Food.y = 1 + rand() % 22;
}

int main() {
    CONRAN r;
    int Huong = 0;
    char t;

    srand(time(NULL));  // dùng cho random mồi
    TaoMoi();           // tạo mồi lần đầu

    while (1) {
        // Bắt phím điều khiển
        if (kbhit()) {
            t = getch();
            if (t == 'a') Huong = 2; // trái
            if (t == 'd') Huong = 0; // phải
            if (t == 'w') Huong = 3; // lên
            if (t == 'x') Huong = 1; // xuống
        }

        system("cls");

        // Vẽ mồi
        gotoxy(Food.x, Food.y);
        cout << "O";

        // Vẽ và di chuyển rắn
        r.Ve();
        r.DiChuyen(Huong);

        // ====== SV3: XỬ LÝ ĂN MỒI ======
        if (r.A[0].x == Food.x && r.A[0].y == Food.y) {
            // Rắn ăn mồi -> dài thêm 1 đốt
            if (r.DoDai < 100) {
                r.DoDai++;
                r.A[r.DoDai - 1] = r.A[r.DoDai - 2];
            }
            // Tạo mồi mới
            TaoMoi();
        }

        Sleep(200);
    }

    return 0;
}
