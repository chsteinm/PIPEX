#include "libft.h"

int ft_putnbr_base(size_t nb, char *base, size_t base_len)
{
    int count;

    count = 1;
    if (nb >= base_len)
	  count += ft_putnbr_base(nb / base_len, base, base_len);
	  ft_putchar_fd(base[nb % base_len], 1);
	  return (count);
}