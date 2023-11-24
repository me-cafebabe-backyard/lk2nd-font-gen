#include <stdio.h>
#include <limits.h>

#define FONT_X  5
#define FONT_Y  12
#define FONT_Y_HALF  FONT_Y / 2
#define FONT_HALF_SIZE FONT_X * FONT_Y_HALF

/* Blank
//X:1  2  3  4  5     Y:
    0, 0, 0, 0, 0, // 1
    0, 0, 0, 0, 0, // 2
    0, 0, 0, 0, 0, // 3
    0, 0, 0, 0, 0, // 4
    0, 0, 0, 0, 0, // 5
    0, 0, 0, 0, 0, // 6
*/

const unsigned int font_half_1_layout[FONT_HALF_SIZE] = {
//X:1  2  3  4  5     Y:
    0, 0, 0, 0, 0, // 1
    0, 0, 0, 0, 0, // 2
    0, 0, 0, 0, 0, // 3
    0, 1, 1, 0, 0, // 4
    0, 1, 1, 0, 0, // 5
    0, 0, 0, 0, 0, // 6
};

const unsigned int font_half_2_layout[FONT_HALF_SIZE] = {
//X:1  2  3  4  5     Y:
    0, 1, 0, 1, 0, // 1
    1, 0, 0, 0, 1, // 2
    1, 0, 1, 0, 1, // 3
    0, 1, 0, 1, 0, // 4
    0, 0, 0, 0, 0, // 5
    0, 0, 0, 0, 0, // 6
};

void print_border(void)
{
    int x;

    for (x = 0; x < FONT_X + 2; x++) {
        putchar('-');
    }
    putchar('\n');
}

//#define DEBUG_PRINT_BINARY
void print_font_half(unsigned int font_half)
{
    int x = 0, y = 0, shift = 0, display = 0;

    for (y = 0; y < FONT_Y_HALF; y++) {
#ifndef DEBUG_PRINT_BINARY
        putchar('|');
#endif
        for (x = 0; x < FONT_X; x++) {
            display = (font_half >> shift) & 1;
            shift++;

#ifdef DEBUG_PRINT_BINARY
            if (display)
                putchar('1');
            else
                putchar('0');
#else
            if (display)
                putchar('#');
            else
                putchar(' ');
#endif
        }
#ifndef DEBUG_PRINT_BINARY
        putchar('|');
        putchar('\n');
#endif
    }

#ifdef DEBUG_PRINT_BINARY
    putchar('\n');
#endif
}

void make_half_font(const unsigned int layout[], unsigned int *output)
{
    unsigned int x = 0, y = 0, shift = 0, it = 0;
    *output = 0;

    for (y = 0; y < FONT_Y_HALF; y++) {
        for (x = 0; x < FONT_X; x++) {
            it = (FONT_X * y) + x;
            if (layout[it])
                *output |= (1 << shift);
            shift++;
        }
    }
}

int main()
{
    unsigned int output1, output2;

#if 0
    print_font_half(0x084210c0); // 1, left
    print_font_half(0x00071084); // 2, right
    return 0;
#endif

/*
    unsigned int line = 0;
    printf("lib/font/font.h Data:\n");
    for (y = 0; y < FONT_Y; y++) {
        line = 0;
        for (x = 0; x < FONT_X; x++) {
            it = (FONT_X * y) + x;
            if (font_layout[it])
                line |= (1 << x);
        }
        printf("0x%02X, ", line);
    }
*/

    make_half_font(font_half_1_layout, &output1);
    make_half_font(font_half_2_layout, &output2);

    printf("Data:\n");
    printf("    0x%08x, 0x%08x,\n", output1, output2);

    printf("Validate:\n");
    print_border();
    print_font_half(output1);
    print_font_half(output2);
    print_border();

    return 0;
}
