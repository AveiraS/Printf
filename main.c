#include "ft_printf.h"

int main()
{
    ft_printf("%#.5x\n", 21);
    printf("%#.5x\n", 21);
    ft_printf("%08.5x\n", 34);
    printf("%08.5x\n", 34);
    ft_printf("%8.5x\n", 34);
    printf("%8.5x\n", 34);
    ft_printf("%08.5u\n", 34);
    printf("%08.5u\n", 34);
    ft_printf("%8.3u\n", 8375);
    printf("%8.3u\n", 8375);
    ft_printf("% 05i\n", 43);
    printf("% 05i\n", 43);
    ft_printf("% .5i\n", 2);
    printf("% .5i\n", 2);
    ft_printf("% 5i\n", 52625);
    printf("% 5i\n", 52625);
    ft_printf("%0+3.7i\n", 3267);
    printf("%0+3.7i\n", 3267);
    ft_printf("%+i\n", 5);
    printf("%+i\n", 5);
    ft_printf("%+05i\n", 432);
    printf("%+05i\n", 432);
    ft_printf("%+04i\n", 0);
    printf("%+04i\n", 0);
	ft_printf("%c\n", 0);
    ft_printf("%0+8.3i\n", -8473);
    printf("%0+8.3i\n", -8473);
    ft_printf("%+8.3i\n", -8473);
    printf("%+8.3i\n", -8473);
    ft_printf("%03.3i\n", -8462);
    ft_printf("%010.5i\n", -216);
    printf("%010.5i\n", -216);
    ft_printf("%08.5i\n", 34);
    printf("%08.5i\n", 34);
    ft_printf("%8.3i\n", -8473);
    printf("%8.3i\n", -8473);
    ft_printf("%10.5i\n", -216);
    printf("%10.5i\n", -216);
    ft_printf("%8.3i\n", 8375);
    printf("%8.3i\n", 8375);
    ft_printf("%0+10.5i\n", 216);
    printf("%0+10.5i\n", 216);
    ft_printf("%8.5i\n", 34);
    printf("%8.5i\n", 34);
    ft_printf("%03.7i\n", -2375);
    printf("%0+3.7i\n", -2375);
    ft_printf("%0+15.3i\n", 123456);
    printf("%0+15.3i\n", 123456);
return (0);
}
