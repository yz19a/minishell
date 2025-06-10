/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:00:44 by yaperalt          #+#    #+#             */
/*   Updated: 2025/06/10 19:55:09 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_to_oldpwd(t_shell_data *data)
{
	char	*oldpwd;
	int		status;

	oldpwd = get_env_value(data, "OLDPWD");
	if (!oldpwd || oldpwd[0] == '\0')
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		free(oldpwd);
		return (1);
	}
	status = exec_cd(oldpwd, data);
	if (status == 0)
		printf("%s\n", oldpwd);
	free(oldpwd);
	return (status);
}

void	auxiliar2(t_command *command, t_shell_data *data, int *status,
		char *dest_path)
{
	dest_path = NULL;
	if (command->argv[1][0] == '~')
	{
		dest_path = expand_home(command->argv[1], data);
		*status = exec_cd(dest_path, data);
		free(dest_path);
	}
	else
		*status = exec_cd(command->argv[1], data);
}

char	*expand_home(char *arg, t_shell_data *data)
{
	char	*home;
	char	*expanded;
	size_t	home_len;
	size_t	arg_len;

	if (arg[0] == '~' && (arg[1] == '/' || arg[1] == '\0'))
	{
		home = get_env_value(data, "HOME");
		if (!home)
			return (NULL);
		home_len = ft_strlen(home);
		arg_len = ft_strlen(arg + 1);
		expanded = malloc(home_len + arg_len + 1);
		if (!expanded)
		{
			free(home);
			return (NULL);
		}
		ft_strlcpy(expanded, home, home_len + 1);
		ft_strlcat(expanded, arg + 1, home_len + arg_len + 1);
		free(home);
		return (expanded);
	}
	return (ft_strdup(arg));
}
