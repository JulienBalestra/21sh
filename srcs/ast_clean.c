/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 18:21:05 by jubalest          #+#    #+#             */
/*   Updated: 2016/01/21 18:21:07 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"
#include <stdlib.h>

void		ast_clean(t_ast *ast)
{
	if (ast->left)
		ast_clean(ast->left);
	if (ast->right)
		ast_clean(ast->right);
	if (ast->cmd)
		ft_str2del(ast->cmd);
	free(ast);
}
