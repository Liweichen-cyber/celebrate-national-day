#include <stdio.h>
#include <unistd.h>  // 提供 usleep()
#include <math.h>    // 提供 sqrt() 等数学函数

int inside_star(double x, double y, double cx, double cy, double outer_r)
{
    double px[10], py[10];                                  // 保存五角星10个顶点的x、y坐标
    double inner_r = outer_r * 0.382;                       // 五角星内顶点半径，约为外半径的0.382倍
    double angle;                                           // 当前顶点对应的角度
    int i, j;                                               // 循环变量
    int inside = 0;                                         // 默认认为当前点不在五角星内部

    for (i = 0; i < 10; i++)                                // 依次计算五角星的10个顶点
    {
        angle = -M_PI / 2.0 + i * M_PI / 5.0;              // 第一个尖角朝正上方，之后每次旋转36°

        if (i % 2 == 0)                                     // 偶数顶点属于五个外侧尖角
        {
            px[i] = cx + outer_r * cos(angle);              // 计算外顶点的横坐标
            py[i] = cy + outer_r * sin(angle);              // 计算外顶点的纵坐标
        }
        else                                                // 奇数顶点属于五个内侧凹点
        {
            px[i] = cx + inner_r * cos(angle);              // 计算内顶点的横坐标
            py[i] = cy + inner_r * sin(angle);              // 计算内顶点的纵坐标
        }
    }

    for (i = 0, j = 9; i < 10; j = i++)                    // 判断(x,y)是否位于这个五角星多边形内部
    {
        if (((py[i] > y) != (py[j] > y)) &&
            (x < (px[j] - px[i]) * (y - py[i]) /
            (py[j] - py[i]) + px[i]))
        {
            inside = !inside;                               // 射线每穿过一次边界，就切换“内部/外部”状态
        }
    }

    return inside;                                          // 在五角星内部返回1，否则返回0
}

int main(void){
    //第一步：开启动画

    printf("================================\n");
    printf("       NATIONAL DAY PROJECT\n");
    printf("================================\n\n");

    printf("Press Enter to start...");
    getchar();   // 等待用户输入一个字符；这里我们用 Enter 开始程序


    // ---------- Loading ----------
    printf("\nLoading...\n\n");

    //第二步：展示动态进度条

    int i, j;
    for (i = 1; i <= 100; i++)
    {
        printf("\r[");
        // \r：回到当前行开头，但不换行
        // 因此每一次循环都会覆盖、刷新当前的进度条

        // 当前是 i%，就打印 i 个 █
        for (j = 1; j <= i; j++)
        {
            printf("█");
        }

        // 在进度条右侧显示当前百分比
        printf("] %d%%", i);

        // 强制把 printf 的内容立刻显示到终端
        // 否则由于输出缓冲，动画可能不能及时显示
        fflush(stdout);


        usleep(50000);  //暂停0.05秒
    }


    // ---------- Loading 完成 ----------
    // 注意：这里已经在 for 循环外面了！
    // 所以只会在 100% 加载完成后执行一次

    printf("\nLoading complete!\n");

    // 停留 0.5 秒，让用户看到 Loading complete
    usleep(500000);

    // ==================== 第三步：彩色实心圆烟花 ====================

    printf("\n\n");                                          // 与 Loading 区域隔开两行

    int radius;                                              // 当前烟花的半径
    int x, y;                                                // 当前正在检查的位置
    double distance;                                         // 当前位置到烟花圆心的距离


    for (radius = 1; radius <= 10; radius++)                 // 半径从1增加到10，让烟花逐渐向外绽放
    {
        if (radius > 1)
            printf("\033[21A");                              // 光标向上21行，用新的一帧覆盖上一帧


        for (y = -10; y <= 10; y++)                         // 从上到下扫描21行
        {
            for (x = -20; x <= 20; x++)                     // 从左到右扫描41个位置
            {
                distance = sqrt(x * x / 4.0 + y * y);       // 计算当前位置到圆心的距离，并修正字符宽高比例


                if (distance <= radius)                      // 只有当前半径以内的位置属于烟花
                {
                    if (distance <= radius * 0.25)
                        printf("\033[97m*\033[0m");          // 最中心：亮白色，模拟烟花最亮的爆炸核心

                    else if (distance <= radius * 0.55)
                        printf("\033[93m*\033[0m");          // 内圈：亮黄色，模拟金色火焰

                    else if (distance <= radius * 0.80)
                        printf("\033[33m*\033[0m");          // 中外圈：黄色，让颜色产生层次

                    else if ((x + y) % 5 == 0)
                        printf("\033[97m*\033[0m");          // 外缘部分位置加入白色亮点，模拟高亮火花

                    else
                        printf("\033[91m*\033[0m");          // 最外缘：亮红色
                }
                else
                {
                    printf(" ");                             // 烟花之外的位置打印空格
                }
            }

            printf("\n");                                    // 当前一行绘制完成，进入下一行
        }


        fflush(stdout);                                      // 立即显示当前这一帧
        usleep(120000);                                      // 停留0.12秒，再让烟花继续扩大
    }

    // 第四步：展示祝福语
    sleep(1);                                              // 烟花完全绽放后停留1秒
    printf("\n\n                    祝祖国77周年快乐！\n");    // 空两行，并让第一句大致居中
    usleep(500000);                                        // 暂停0.5秒
    printf("                        繁荣昌盛！\n");          // 第二句大致居中

    // ==================== 第五步：绘制五星红旗 ====================

    int row, col;                                               // row表示行，col表示列

    for (row = 1; row <= 20; row++)                             // 从上到下绘制20行
    {
        for (col = 1; col <= 60; col++)                         // 从左到右绘制60列
        {
            double star_x = col / 2.0;                          // 修正终端字符横向比例
            double star_y = row;                                // 当前行作为纵坐标

            if (inside_star(star_x, star_y, 7.5, 6.0, 3.6) ||     // 大五角星
    inside_star(star_x, star_y, 13.0, 3.0, 1.7) ||    // 右上第一颗小星
    inside_star(star_x, star_y, 15.0, 5.0, 1.7) ||    // 右上第二颗小星
    inside_star(star_x, star_y, 15.0, 8.0, 1.7) ||    // 右下第三颗小星
    inside_star(star_x, star_y, 13.0, 10.0, 1.7))     // 右下第四颗小星
            {
                printf("\033[93m█\033[0m");                       // 五颗星所在区域全部打印黄色
            }
            else
            {
                printf("\033[31m█\033[0m");                       // 其他区域保持红色
            }
        }

        printf("\n");                                           // 当前一整行完成后换行
    }

    return 0;
}