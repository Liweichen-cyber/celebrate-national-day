# Celebrate National Day

一个使用 C 语言编写的命令行国庆庆祝程序。

程序会在终端中依次展示加载进度条、彩色烟花、祝福语和使用字符绘制的五星红旗。

## 效果

程序包含以下阶段：

1. 启动提示
2. 动态加载进度条
3. 彩色烟花动画
4. 国庆祝福语
5. 终端字符版五星红旗

程序使用 ANSI 转义序列控制颜色和光标位置，因此建议在支持 ANSI 控制序列的 macOS 或 Linux 终端中运行。

## 编译与运行

使用 GCC：

```bash
gcc -std=c11 -Wall -Wextra celebrate.c -lm -o celebrate
./celebrate
```

其中 `-lm` 用于链接数学库。

## 文件说明

```text
.
├── celebrate.c
├── README.md
└── .gitignore
```

- `celebrate.c`：程序主体和动画绘制逻辑
- `README.md`：项目说明
- `.gitignore`：Git 忽略规则

## 环境说明

- C11
- GCC 或 Clang
- macOS 或 Linux 终端

Windows 终端对 ANSI 控制序列、字符宽度和 `unistd.h` 的支持可能不同，运行效果可能与 macOS/Linux 不一致。
