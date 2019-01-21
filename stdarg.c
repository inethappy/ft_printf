#include <stdio.h>
#include <stdarg.h>

void foo(char *fmt, ...)
{
	va_list ap;
	int d;
	char c, *p, *s, X;
	va_start(ap, fmt);
	while (*fmt)
			switch (*fmt++) {
		case 's':                       
        	s = va_arg(ap, char *);
            printf("строка %s\n", s);
            break;
        case 'd':                       
			d = va_arg(ap, int);
            printf("целое %d\n", d);
            break;
        case 'c':             
             c = (char)va_arg(ap, int);
             printf("символ %c\n", c);
             break;
    	case 'X':             
             X = va_arg(ap, int);
             printf("символ %X\n", X);
             break;
			 }
        va_end(ap);
}
/*
int sumnum(int num, ...)
{
	int sum = 0;
	va_list ap;
	va_start(ap, num);
	int c = 0;
	while (c < num)
	{
		sum += va_arg(ap, int);		
		c++;
	}
	va_end(ap);
	return sum;
}

void pr_str(int num, ...)
{
	int c = 0;
	char *ptr;
	va_list ap;
	va_start(ap, num);
	while (c < num)
	{
		ptr = va_arg(ap, char *);
		printf("ptr = %s\n", ptr);
		c++;
	}
	va_end(ap);
}
*/
int main(int argc, char *argv[])
{
	/*int total;
	total = sumnum(6, 3, 5, 7, 6, 4);
	printf("total = %d\n", total);
	pr_str(3, "one", "two", "three");
	*/
	char *s;
	s = "sdcX";
	foo(s);
	
	return (0);
}
