#include <wchar.h>
#include "ft_printf.h"
#define STRING "|%#*.*d|", 10, 5, 44
// "{% S}", L"(null)"

// "|% -5d|", 0
// "|% 0+5hhx|",
// "|%0#13.12O|", -2147483648
// "%#o", 42
// "|%#5o|", 6
// "|% #1lo|", 0
// "%05o", 42
// "|%0#.4o|", 0

// "|%+-5d|", 0
// "%-+10.5d", 4242
// "{%0-3d}", 0
// "|%0-5.3d|", -25
// "|%0+-5.3hhi|", -5
// "|% +.4hhd|", 0
// "%-10.5d", 42
// "|% -5d|", 0
// "|%+-5d|", 0
int main()
{
    int  res = 0;
    int i;
    i = 0;
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
    printf("\n%d\n", res);
    res = printf(STRING);
    // res = printf(STRING2);
    printf("\n%d\n", res);

   //printf("wchar_t = %lu\n", sizeof(wchar_t));

    // system("leaks ft_printf.out");
    return 0;
}
// || fl->con == 'u' || fl->con == 'O' || fl->con == 'u' || fl->con == 'x' || fl->con == 'X') ? paddings(di, fl, 48)
// 				: ft_strjoin(base
