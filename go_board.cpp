#include <graphics.h>
#include <conio.h>
#include <string>

int main() {
    // 初始化窗口
    const int cell = 30;               // 每格大小
    const int margin = 50;             // 边距
    const int lineCount = 19;          // 棋盘线数
    const int width = margin * 2 + cell * (lineCount - 1);
    const int height = margin * 2 + cell * (lineCount - 1);

    initgraph(width, height);
    setbkcolor(RGB(230, 190, 138));     // 棋盘背景色
    cleardevice();

    // 设置画笔
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 1);

    // 画纵线
    for (int i = 0; i < lineCount; ++i) {
        int x = margin + i * cell;
        line(x, margin, x, margin + cell * (lineCount - 1));
    }

    // 画横线
    for (int i = 0; i < lineCount; ++i) {
        int y = margin + i * cell;
        line(margin, y, margin + cell * (lineCount - 1), y);
    }

    // 设置文字样式
    settextstyle(20, 0, _T("黑体"));
    settextcolor(BLACK);

    // 标注行号（左侧数字 1-19，从上到下）
    for (int i = 0; i < lineCount; ++i) {
        int y = margin + i * cell;
        std::wstring num = std::to_wstring(lineCount - i);
        outtextxy(15, y - 10, num.c_str());
    }

    // 标注列号（底部字母 A-S）
    for (int j = 0; j < lineCount; ++j) {
        int x = margin + j * cell;
        wchar_t ch = L'A' + j;
        wchar_t str[2] = { ch, L'\0' };
        outtextxy(x - 3, height - margin + 10, str);
    }

    // 标出星位（天元和四个角的星位点）
    int starPositions[][2] = {
        {3, 3}, {3, 9}, {3, 15},
        {9, 3}, {9, 9}, {9, 15},
        {15, 3}, {15, 9}, {15, 15}
    };

    const int starRadius = 4;
    setfillcolor(BLACK);

    for (int i = 0; i < 9; ++i) {
        int x = margin + starPositions[i][0] * cell;
        int y = margin + starPositions[i][1] * cell;
        fillcircle(x, y, starRadius); // 注意不要用错成fillellipse
    }

    // 等待按键，关闭图形窗口
    _getch();
    closegraph();
    return 0;
}