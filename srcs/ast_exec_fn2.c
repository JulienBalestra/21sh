/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec_fn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 18:12:59 by jubalest          #+#    #+#             */
/*   Updated: 2016/01/21 18:13:01 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../includes/minishell.h"

void	change_fd(t_ast *ast)
{
	if (ast->from != -2 && ast->to != -2)
	{
		if (ast->to != -1)
		{
			dup2(ast->to, ast->from);
		}
		else
			close(ast->from);
	}
}
