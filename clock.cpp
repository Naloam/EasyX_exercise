#include <graphics.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265359
#define CLOCK_SIZE 200  // 时钟半径

// 绘制时钟表盘
void drawClockFace(int centerX, int centerY, int radius) {
    // 绘制外圆
    setcolor(BLACK);
    setlinestyle(PS_SOLID, 3);
    circle(centerX, centerY, radius);

    // 绘制内圆（中心点）
    setfillcolor(BLACK);
    fillcircle(centerX, centerY, 5);

    // 绘制12个小时刻度
    for (int i = 0; i < 12; i++) {
        double angle = i * PI / 6 - PI / 2;  // 从12点开始
        int x1 = centerX + (radius - 20) * cos(angle);
        int y1 = centerY + (radius - 20) * sin(angle);
        int x2 = centerX + (radius - 10) * cos(angle);
        int y2 = centerY + (radius - 10) * sin(angle);

        setlinestyle(PS_SOLID, 2);
        line(x1, y1, x2, y2);

        // 绘制数字
        TCHAR numStr[3];
        int hour = (i == 0) ? 12 : i;
        _stprintf_s(numStr, _T("%d"), hour);

        int textX = centerX + (radius - 35) * cos(angle) - 10;
        int textY = centerY + (radius - 35) * sin(angle) - 10;
        outtextxy(textX, textY, numStr);
    }

    // 绘制分钟刻度
    setlinestyle(PS_SOLID, 1);
    for (int i = 0; i < 60; i++) {
        if (i % 5 != 0) {  // 跳过小时刻度位置
            double angle = i * PI / 30 - PI / 2;
            int x1 = centerX + (radius - 15) * cos(angle);
            int y1 = centerY + (radius - 15) * sin(angle);
            int x2 = centerX + (radius - 10) * cos(angle);
            int y2 = centerY + (radius - 10) * sin(angle);
            line(x1, y1, x2, y2);
        }
    }
}

// 绘制时针
void drawHourHand(int centerX, int centerY, int hour, int minute) {
    double angle = (hour % 12 + minute / 60.0) * PI / 6 - PI / 2;
    int length = CLOCK_SIZE * 0.5;

    setcolor(BLACK);
    setlinestyle(PS_SOLID, 4);
    line(centerX, centerY,
        centerX + length * cos(angle),
        centerY + length * sin(angle));
}

// 绘制分针
void drawMinuteHand(int centerX, int centerY, int minute, int second) {
    double angle = (minute + second / 60.0) * PI / 30 - PI / 2;
    int length = CLOCK_SIZE * 0.7;

    setcolor(BLUE);
    setlinestyle(PS_SOLID, 3);
    line(centerX, centerY,
        centerX + length * cos(angle),
        centerY + length * sin(angle));
}

// 绘制秒针
void drawSecondHand(int centerX, int centerY, int second) {
    double angle = second * PI / 30 - PI / 2;
    int length = CLOCK_SIZE * 0.8;

    setcolor(RED);
    setlinestyle(PS_SOLID, 1);
    line(centerX, centerY,
        centerX + length * cos(angle),
        centerY + length * sin(angle));
}

// 显示数字时间
void drawDigitalTime(int hour, int minute, int second) {
    TCHAR timeStr[20];
    _stprintf_s(timeStr, _T("%02d:%02d:%02d"), hour, minute, second);

    setcolor(BLACK);
    settextcolor(BLACK);
    setbkcolor(WHITE);

    // 在窗口底部显示数字时间
    outtextxy(270, 460, timeStr);
}

int main() {
    // 初始化图形窗口
    initgraph(600, 500);
    BeginBatchDraw(); // 批量绘图可以解决闪烁问题

    setbkcolor(WHITE);

    int centerX = 300;  // 时钟中心X坐标
    int centerY = 250;  // 时钟中心Y坐标

    while (true) {
        // 清屏
        cleardevice();

        // 获取当前时间
        SYSTEMTIME time;
        GetLocalTime(&time);

        int hour = time.wHour;
        int minute = time.wMinute;
        int second = time.wSecond;

        // 绘制时钟
        drawClockFace(centerX, centerY, CLOCK_SIZE);
        drawHourHand(centerX, centerY, hour, minute);
        drawMinuteHand(centerX, centerY, minute, second);
        drawSecondHand(centerX, centerY, second);
        drawDigitalTime(hour, minute, second);

        // 显示标题
        settextcolor(BLACK);
        setbkcolor(WHITE);
        outtextxy(270, 20, _T("动态时钟"));

        FlushBatchDraw();

        // 刷新显示
        Sleep(1000);  // 每秒更新一次
    }

    // 关闭图形窗口
    EndBatchDraw();
    system("pause");
    closegraph();
    return 0;
}