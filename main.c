#include <wchar.h>
#include "ft_printf.h"
#define STRING "%.150p", &l
// "{% S}", L"(null)"

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
    printf("\n%d\n", res);
    res = printf(STRING);
    // res = printf(STRING2);
    printf("\n%d\n", res);

   //printf("wchar_t = %lu\n", sizeof(wchar_t));

    // system("leaks ft_printf.out");
    return 0;
}

