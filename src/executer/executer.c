/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:24:26 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/25 15:15:16 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Contains the core execution logic for commands (both built-in and external).
 */

// Helper function to check if command exists in PATH
char *check_access(char *command, char **path)
{
    char *command_and_path;
    int  i;

    // If command has full path and is executable, use it directly
    if (access(command, X_OK) == 0)
        return (command);

    i = 0;
    // Try each directory in PATH
    while (path[i])
    {
        command_and_path = ft_strjoin(path[i], command);
        if (!command_and_path)
            return (0);
        // If command found and executable, return full path
        if (access(command_and_path, X_OK) == 0)
            return (command_and_path);
        free(command_and_path);
        i++;
    }
    return (0);
}

// Helper function to execute external command
static int execaux(t_command *instr, t_shell_data *data)
{
    char *comand_and_path;
    char **path;

    // Get PATH from environment
    path = get_path(data->env);
    if (!path)
        return (1);

    // Check if command exists in PATH
    comand_and_path = check_access(instr->argv[0], path);
    free_path(path);
    if (comand_and_path != 0)
    {
        // Execute command
        execve(comand_and_path, instr->argv, data->env);
        return (errno);
    }
    return (127); // 127 = command not found
}

// Function to execute non-builtin commands
static int execute_generic(t_command *instr, t_shell_data *data)
{
    int     result_code;

    // Fork to execute command
    g_sig.pid = fork();
    result_code = 0;

    if (g_sig.pid < 0)
        return (g_sig.pid);

    if (g_sig.pid == 0)
    {
        // Child process executes command
        result_code = execaux(instr, data);
        exit(result_code);
    }
    // Parent waits for child to finish
    waitpid(g_sig.pid, &result_code, 0);
    result_code = decode_error(result_code);
    // Print error if command not found
    if (result_code == 127)
        print_error(instr->argv[0], 0, "command not found", result_code);
    return (result_code);
}

// Function to execute a single command
int execute(t_list *instr, t_shell_data *data)
{
    int         status;
    t_command   *command;

    command = (t_command *) instr->content;
    if (!command->argv || !command->argv[0])
        return (0);

    // Set up input/output redirection
    if (command->fd_in > 0)
        dup2(command->fd_in, STDIN_FILENO);
    if (command->fd_out > 0)
        dup2(command->fd_out, STDOUT_FILENO);
    // Close unused pipe ends
    close_pipes(data, instr);
    // Execute builtin or external command
    if (is_builtin(command->argv[0]))
        status = execute_builtins(command, data);
    else
        status = execute_generic(command, data);
    // Clean up file descriptors
    if (command->fd_out > 0)
        close(command->fd_out);
    if (instr->next)
        close(((t_command *)instr->next->content)->fd_in);
    // Restore standard input/output
    if (command->fd_in > 0)
        dup2(data->dup_stdin, STDIN_FILENO);
    if (command->fd_out > 0)
        dup2(data->dup_stdout, STDOUT_FILENO);
    return (status);
}

// Function to execute a pipeline of commands
int execute_pipex(t_shell_data *data)
{
    int     status;
    int     last_pid;
    int     last_status;
    t_list  *commands;

    commands = data->commands;
    // Fork for each command in pipeline
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
    // Close all pipes in parent
    close_pipes(data, 0);
    commands = data->commands;
    // Wait for all commands to finish
    while (commands)
    {
        if (last_pid == waitpid(-1, &status, 0))
            last_status = decode_error(status);
        commands = commands->next;
    }
    return (last_status);
}
