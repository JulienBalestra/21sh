#include "../libft/includes/libft.h"

void	ft_putlong_fd(long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = - n;
	}
	if (n > 9)
	{
		ft_putlong_fd(n / 10, fd);
		ft_putlong_fd(n % 10, fd);
	}
	else
		ft_putchar_fd((char)(48 + n), fd);
}