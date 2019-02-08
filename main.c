#include "ft_printf.h"
#define STRING "%hd", -32768


int main()
{
    int  res;
    int i;
    i = 42;
    char *s;
    s = "asdas";
    char c;
    c = 'z';
    int g;
    g = -42;
    //printf("printf: %s, %c, [%+d]\n", s, c, g); 
    res = ft_printf(STRING);
    printf("\n%d\n", res);
    res = printf(STRING);
    printf("\n%d\n", res);
    // ft_printf("ft_printf: %s, %c, [%+d]\n", s, c, g);
    // ft_printf("%d %d",1, -2);

    //system("leaks ft_printf.out");
    return 0;
}