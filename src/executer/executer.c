/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:24:26 by yaperalt          #+#    #+#             */
/*   Updated: 2025/06/08 13:20:41 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to check if a command is accessible via PATH
 * It checks if the command exists and is executable
 * @param command The command to check
 * @param path The PATH split into directories
 * @return char* Returns the full path if accessible, or 0 if not
 */
char	*check_access(char *command, char **path)
{
	char	*command_and_path;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
	i = 0;
	while (path[i])
	{
		command_and_path = ft_strjoin(path[i], command);
		if (!command_and_path)
			return (0);
		if (access(command_and_path, X_OK) == 0)
			return (command_and_path);
		free(command_and_path);
		i++;
	}
	return (0);
}

/**
 * Execute auxiliary function for execve
 * This function checks the access to the command and executes it
 * @param instr The command to execute
 * @param data Pointer to the shell data structure containing env vars
 * @return int Returns the result code of the command execution
 *         Returns 127 if the command is not found
 *         Returns an error code if execve fails
 */
static int	execaux(t_command *instr, t_shell_data *data)
{
	char	*comand_and_path;
	char	**path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = get_path(data->env);
	if (!path)
	{
		if (access(instr->argv[0], X_OK) == 0)
		{
			execve(instr->argv[0], instr->argv, data->env);
			return (errno);
		}
		return (127);
	}
	comand_and_path = check_access(instr->argv[0], path);
	free_path(path);
	if (comand_and_path != 0)
	{
		execve(comand_and_path, instr->argv, data->env);
		return (errno);
	}
	return (127);
}

/**
 * Execute generic command
 * This function forks a new process to execute the command
 * It handles the execution of external commands that are not built-in
 * @param instr The command to execute
 * @param data Pointer to the shell data structure containing env vars
 * @return int Returns the result code of the command execution
 *         Returns 127 if the command is not found
 *         Returns an error code if execve fails
 */
static int	execute_generic(t_command *instr, t_shell_data *data)
{
	int		result_code;
	pid_t	pid;

	pid = fork();
	result_code = 0;
	if (pid < 0)
		return (pid);
	if (pid == 0)
	{
		result_code = execaux(instr, data);
		exit(result_code);
	}
	waitpid(pid, &result_code, 0);
	result_code = decode_error(result_code);
	if (result_code == 127)
		print_error(instr->argv[0], 0, "command not found", result_code);
	return (result_code);
}

/**
 * Function to execute built-in commands
 * It checks the command and calls the appropriate built-in function
 * @param command The command to execute
 * @param data Pointer to the shell data structure containing env vars
 * @return int Returns 0 on success, or an error code
 */
int	execute(t_list *instr, t_shell_data *data)
{
	int			status;
	t_command	*command;

	command = (t_command *)instr->content;
	if (!command->argv || !command->argv[0])
		return (0);
	if (command->fd_in > 0)
		dup2(command->fd_in, STDIN_FILENO);
	if (command->fd_out > 0)
		dup2(command->fd_out, STDOUT_FILENO);
	close_pipes(data, instr);
	if (is_builtin(command->argv[0]))
		status = execute_builtins(command, data);
	else
		status = execute_generic(command, data);
	if (command->fd_out > 0)
		close(command->fd_out);
	if (instr->next)
		close(((t_command *)instr->next->content)->fd_in);
	if (command->fd_in > 0)
		dup2(data->dup_stdin, STDIN_FILENO);
	if (command->fd_out > 0)
		dup2(data->dup_stdout, STDOUT_FILENO);
	return (status);
}

/**
 * Function to execute a pipeline of commands
 * It forks a new process for each command in the pipeline
 * It waits for all commands to finish and returns the last command's status
 * @param data Pointer to the shell data structure containing env vars
 * @return int Returns the last command's exit status
 */
int	execute_pipex(t_shell_data *data)
{
	int		status;
	int		last_pid;
	int		last_status;
	t_list	*commands;

	commands = data->commands;
	while (commands)
	{
		last_pid = fork();
		if (last_pid < 0)
			return (last_pid);
		if (last_pid == 0)
			exit(execute(commands, data));
		commands = commands->next;
	}
	commands = data->commands;
	close_pipes(data, 0);
	commands = data->commands;
	while (commands)
	{
		if (last_pid == waitpid(-1, &status, 0))
			last_status = decode_error(status);
		commands = commands->next;
	}
	return (last_status);
}
