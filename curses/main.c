#include <curses.h>
#include <stdlib.h>
#include <time.h>

// curses.h 是 unix 下的图形编程库，
// 开发围绕终端的GUI command line 程序或者终端游戏。


// WINDOW* initscr()
// 初始化终端屏幕管理，交给curses.h 管理；
// 初始化的 WINDOW 将被记录在 curse.h 的全局变量 stdscr 中。

// start_color()
// 开始管理颜色，之后就可以使用 init_pair 具体配置颜色；

// init_pair(int i, int foregroundColor, int backgroundColor)
// 设置前景色和背景色；
// foregroundColor 是前景色号码，并不是指RGB值，默认情况下，curses.h 中设置了
// 一些标准的颜色，比如 0 表示 黑色；
// backgroundColor 同理 foregroundColor；
// i 表示 前景色和背景色组合的号码，之后使用COLOR_PAIR(i)调用颜色对。

// resizeterm(int lines, int columns)
// 在终端上划分一片面积作为虚拟窗口使用；
// 窗口有 lines 行， columns 列；
// 注意，终端的大小一定要大于这块虚拟窗口，否者窗口显示不全；

// timeout(int val)
// val = 0 时，设置以非阻塞方式读取用户输入；

// cur_set(int val)
// val = 0 时，设置终端上隐藏光标；

// noecho()
// 设置用户输入的内容不显示在终端上；

// box(WINDOW* win, char vchar, char hchar)
// 围绕着虚拟窗口 win 画边框，垂直方向的边用字符 vchar 绘制，
// 水平方向的边用字符 hchar 绘制；

// move(int row, int column)
// 把光标移动到虚拟窗口的第 row 行，第 column 列；
// row = 0 时，光标位于 虚拟窗口的上边框上；
// 在确定好光标位置后，printwc才会知道输出到窗口的内容应该位于哪个位置；

// attron(int attribute)
// 开启窗口的属性，curses.h 提供很多宏，都是用WA_开头，
// WA_REVERSE表示 前景色和背景色交换，COLOR_PAIR(i) 表示使用i标记的颜色对；
// 在设置之后，printw输出的内容才会有颜色；

// attroff(int attribute)
// 关闭窗口的属性；

// refresh()
// printw输出的内容不会立即显示出来，会被缓存到内存中，
// 使用 refresh 进行缓存刷新。

// endwin()
// 关闭虚拟窗口，回到正常的终端

void run_loop() {
    char input = 0;
    int row = 1;
    while((input = getch()) != 'q') {
        row %= 50;
        int color = rand() % 10;
        if (input == 's') {
            move(row++, 0);
            attron(262176 | COLOR_PAIR(color));
            for (int j = 0; j < 20; j++) {
                printw(" ");
            }
            attroff(262176 | COLOR_PAIR(color));
        }
        if (input == 'd') {
            row += 2;
            move(row++, 20);
            // WA_REVERSE 将 前景色和后景色互换，
            // 后景色目前是黑色，在printw 什么字符都不输出时，
            // 打印的就是黑色，看不出什么效果，所以要互换颜色
            attron(WA_REVERSE| COLOR_PAIR(color));
            for (int j = 20; j < 30; j++) { 
                printw("a");
            }
            attroff(WA_REVERSE|  COLOR_PAIR(color));
        }
        refresh();
    }
}

int main() {
    srand(time(0));
    initscr();
    start_color();

    for (int i = 1; i < 10; i++) {
        init_pair(i, i, 0);
    }

    resizeterm(50, 50);
    timeout(0);
    curs_set(0);
    noecho();
    box(stdscr, '+', '+');

    run_loop();

    endwin();

}