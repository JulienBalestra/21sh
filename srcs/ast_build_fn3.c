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

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

void	mock_ps1_by_ps2(t_sh *shell)
{
	ft_strdel(&shell->ps1);
	shell->ps1 = ft_strdup(DEFAULT_PS2);
	shell->len_ps1 = LEN_PS2;
}

char	*join_free_start(char *start, char *end)
{
	char	*tmp;

	tmp = start;
	start = ft_strjoin(start, end);
	ft_strdel(&tmp);
	return (start);
}

int		skip_eof(char *s)
{
	int		i;

	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

void	process_pipe_stderr(char **cut, t_ast *ast, t_sh *shell)
{
	char	*tmp;

	tmp = cut[0];
	cut[0] = ft_strjoin(cut[0], " 2>&1 ");
	ft_strdel(&tmp);
	if (cut[1] && cut[1][0] == '&')
		cut[1][0] = ' ';
	ast->op = 1;
	ast->left = ast_build(cut[0], 0, shell);
	ast->right = ast_build(cut[1], 0, shell);
}

void	process_atoi(t_ast *ast, char *str, size_t k)
{
	ast->from = ft_atoi(str);
	ast->to = ft_atoi(&str[k]);
}
