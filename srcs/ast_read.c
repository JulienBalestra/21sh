/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 18:18:53 by jubalest          #+#    #+#             */
/*   Updated: 2016/01/21 18:18:54 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "../includes/minishell.h"

void	display_op(int op)
{
	if (op == 1)
		ft_putstr("|");
	else if (op == 2)
		ft_putstr(">>");
	else if (op == 3)
		ft_putstr(">");
	else if (op == 4)
		ft_putstr("<<");
	else if (op == 5)
		ft_putstr("<");
	ft_putstr(" ");
}

void	display_command(char **cmd)
{
	while (*cmd)
	{
		ft_putstr(*cmd);
		ft_putstr(" ");
		cmd++;
	}
}

void	ast_read(t_ast *ast)
{
	if (ast->op == -1)
	{
		display_command(ast->cmd);
	}
	else
	{
		ast_read(ast->right);
		display_op(ast->op);
		ast_read(ast->left);
	}
}
