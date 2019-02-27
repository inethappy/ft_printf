#include <wchar.h> 
#include "ft_printf.h"
#define STRING "%#.f", 42457666.5647477
// "{%#.5x}", 1
// #define STRING2 "%#8x", 42
// "{%*3d}", 0, 0
// "@main_ftprintf: %####0000 33..1..#00d\n", 256
// 

int main()
{
    int  res = 0;
    int i;
    i = 42;
    char *s;
    s = "asdas";
    char c;
    c = 'c';
    int g;
    g = -42;
   char *test_simple_mix;
   char new[100];
   double a = 0.51;
   	unsigned long l;

    // printf("printf: %s, %c, [%+d]\n", s, c, g); 
    res = ft_printf(STRING);
    // res = ft_printf(STRING2);
    printf("\n%d\n", res);
    res = printf(STRING);
    // res = printf(STRING2);
    printf("\n%d\n", res);
   
   //printf("wchar_t = %lu\n", sizeof(wchar_t));

    system("leaks ft_printf.out");
    return 0;
}

