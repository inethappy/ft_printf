#include <wchar.h> 
#include "ft_printf.h"
#define STRING "%#15.4x", 424242
//"{%*3d}", 0, 0

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
   
   char *new;
    // printf("printf: %s, %c, [%+d]\n", s, c, g); 
    res = ft_printf(STRING);
   printf("\n%d\n", res);
    res = printf(STRING);
    printf("\n%d\n", res);
   
   //printf("wchar_t = %lu\n", sizeof(wchar_t));

    // system("leaks ft_printf.out");
    return 0;
}