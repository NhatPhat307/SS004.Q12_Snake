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
