/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_actions_fn1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:32:29 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:32:34 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

void	ft_putlong_fd(long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		ft_putlong_fd(n / 10, fd);
		ft_putlong_fd(n % 10, fd);
	}
	else
		ft_putchar_fd((char)(48 + n), fd);
}
