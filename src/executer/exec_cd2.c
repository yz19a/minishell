/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:00:44 by yaperalt          #+#    #+#             */
/*   Updated: 2025/06/10 17:01:03 by yaperalt         ###   ########.fr       */
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
