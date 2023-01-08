/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:40:47 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/08 08:07:32 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_destroy_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = -1;
	while (tab[++i] != NULL)
		free (tab[i]);
	free (tab);
}

static void	ft_destroy_cmds(t_data *data)
{
	int	i;

	if (data == NULL || data->cmds == NULL)
		return ;
	i = -1;
	while (++i < data->cmdsc)
	{
		if (data->cmds[i].name != NULL)
			free (data->cmds[i].name);
		if (data->cmds[i].pathname != NULL)
			free (data->cmds[i].pathname);
		if (data->cmds[i].args != NULL)
			ft_destroy_tab (data->cmds[i].args);
		if (data->cmds[i].args_redir != NULL)
			ft_destroy_tab (data->cmds[i].args_redir);
		if (data->cmds[i].redirs != NULL)
			free (data->cmds[i].redirs);
	}
	free (data->cmds);
}

void	ft_destroy_execution(t_data *data)
{
	if (data->line != NULL)
		free (data->line);
	if (data->tab != NULL)
		ft_destroy_tab (data->tab);
	if (data->cmds != NULL)
		ft_destroy_cmds (data);
	if (data->pipes != NULL)
		free (data->pipes);
	if (data->pids != NULL)
		free (data->pids);
	data->line = NULL;
	data->tab = NULL;
	data->cmds = NULL;
	data->pipes = NULL;
	data->cmdsc = 0;
	data->pids = NULL;
}

void	ft_destroy_data(t_data *data)
{
	if (data == NULL)
		return ;
	ft_destroy_execution (data);
	if (data->path != NULL)
		ft_destroy_tab (data->path);
	free (data);
}
