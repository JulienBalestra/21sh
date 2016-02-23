/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 18:08:12 by jubalest          #+#    #+#             */
/*   Updated: 2016/01/21 18:08:13 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

int			is_operand(char *s, int i)
{
	if (s[i] == '|' && s[i + 1] != '&')
		return (1);
	if (s[i] == '|' && s[i + 1] == '&')
		return (11);
	if (s[i] == '>')
	{
		if (s[i - 1] == '>')
			return (2);
		if (s[i + 1] && s[i + 1] != '&')
			return (3);
	}
	if (s[i] == '<')
	{
		if (s[i - 1] == '<')
			return (4);
		return (5);
	}
	return (0);
}

void		find_operand(char *input, int *tuple)
{
	size_t	len;
	int		ret;

	tuple[0] = -1;
	tuple[1] = -1;
	if (! input)
		return ;
	len = ft_strlen(input) - 1;
	while (len)
	{
		ret = is_operand(input, (int)len);
		if (ret)
		{
			tuple[0] = ret;
			tuple[1] = (int)len;
			break ;
		}
		len--;
	}
}

char		**cut_input(char *input, int *tuple)
{
	char	**cut;

	if ((cut = (char **)malloc(sizeof(char *) * 3)))
	{
		if (tuple[0] == 2 || tuple[0] == 4)
			cut[0] = ft_strndup(input, (size_t)tuple[1] - 1);
		else
			cut[0] = ft_strndup(input, (size_t)tuple[1]);
		cut[1] = ft_strdup(&input[tuple[1] + 1]);
		cut[2] = NULL;
	}
	return (cut);
}

t_ast		*ast_build(char *input, int eof, t_sh *shell)
{
	t_ast	*ast;
	int		tuple[2];

	if ((ast = (t_ast *)malloc(sizeof(t_ast))))
	{
		find_operand(input, tuple);
		ast->op = tuple[0];
		ast->stdin = 0;
		ast->stdout = 1;
		ast->stderr = 2;
		ast->from = -2;
		ast->to = -2;
		if (ast->op == -1)
			trigger_command(ast, input, eof);
		else
			trigger_operator_with_recurse(ast, input, tuple, shell);
	}
	free(input);
	return (ast);
}
