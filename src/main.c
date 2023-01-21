/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 05:43:21 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/21 12:20:35 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_mainpl(t_data *data)
{
	ft_assert_not_null (data, data);
	ft_addhistory (data, data->line);
	if (ft_minishell_split (data, data->line) && ft_isvalid (data)
		&& ft_assert_finished (data))
	{
		ft_parse (data);
		ft_heredocs (data);
		if (g_heredoc_success)
		{
			ft_toggle_echoctl (data, true);
			ft_signals (SIG_PARENT_EXECUTION);
			ft_execute (data);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (EXIT_FAILURE);
	data = ft_initdata (envp);
	g_heredoc_success = true;
	while (true)
	{
		ft_signals (SIG_PARENT);
		ft_toggle_echoctl (data, false);
		data->line = readline ("\001\033[32;1m\002minishell$ \001\033[0m\002");
		g_heredoc_success = true;
		if (data->line == NULL)
			ft_exit(data, NULL);
		else if (ft_strncmp (data->line, "", 1) != 0)
			ft_mainpl (data);
		ft_destroy_execution (data);
	}
	ft_destroy_data (data);
	exit (EXIT_SUCCESS);
}
