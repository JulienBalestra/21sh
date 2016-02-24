/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:45 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:47 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_ast	**command_from_cli(char **cli, t_sh *shell)
{
	int		i;
	t_ast	**ast;

	i = 0;
	if ((ast = (t_ast **)malloc(sizeof(t_ast *) * (ft_str2len(cli) + 1))))
	{
		while (cli[i])
		{
			ast[i] = ast_build(cli[i], 0, shell);
			i++;
		}
		ast[i] = NULL;
	}
	return (ast);
}

t_ast	**build_command(t_sh *shell)
{
	t_ast	**command;
	char	**multi_cli;

	command = NULL;
	if ((multi_cli = ft_lz_strsplit(shell->stdin_buf, ';')))
	{
		command = command_from_cli(multi_cli, shell);
		free(multi_cli);
		free(shell->stdin_buf);
		shell->stdin_buf = NULL;
	}
	return (command);
}
