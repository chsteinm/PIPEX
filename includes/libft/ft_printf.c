#include "libft.h"

int print_c(va_list args)
{
    ft_putchar_fd(va_arg(args, int), 1);
    return (1);
}

int print_convert(va_list args, const char *str)
{
    int     i;

    i = 0;
    if (*str == 'c')
        i += print_c(args);
    else if (*str == 's')
        i += print_str(args);
    else if (*str == 'd' || *str == 'u' || *str == 'i')
        i += print_n_base10(args, *str);
    else if (*str == 'p')
        i += print_p(args);
    else if (*str == 'x')
        i += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", 16);
    else if (*str == 'X')
        i += ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", 16);
    else if (*str == '%')
    {
        write(1, "%%", 1);
        i++;
    }
    else
    {
        ft_putchar_fd(*str, 1);
        i++;
    }
    return (i);
}

int print_printable(const char *str)
{
    int i;

    i = -1;
    while (str[++i] != '%' && str[i])
        ft_putchar_fd(str[i], 1);
    return (i);
}

int ft_printf(const char *str, ...)
{
    va_list args;
    int     count_printed_char;
    int     i;

    if (!str)
		return (-1);
	if (!(*str))
		return (0);
    count_printed_char = 0;
    va_start(args, str);
    while (*str)
    {
        if (*str == '%')
        {
            count_printed_char += print_convert(args, str + 1);
            str += 2;
        }
        i = print_printable(str);
        count_printed_char += i;
        str += i;
    }
    va_end(args);
    return (count_printed_char);
}