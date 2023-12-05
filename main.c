/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:50:07 by npremont          #+#    #+#             */
/*   Updated: 2023/12/05 15:33:36 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execpid1(char **av, int *fd)
{
	char	*path;
	char	**args;

	args = ft_split(av[2], ' ');
	if (!args)
		exit(2);
	path = ft_strjoin("/bin/", args[0]);
	if (!path)
	{
		ft_free_split(args);
		exit(2);
	}
	printf("path : %s\n", path);
	size_t	i = 0;
	while(args[i])
		printf("arg: %s, ", args[i++]);
	printf("\n");
	if (dup2(fd[1], 1) == -1)
	{
		perror("dup2 1");
		exit(3);
	}
	if (execve(path, args, NULL) == -1)
	{
		perror("execve 1");
		exit(2);
	}
}

void	ft_execpid2(char **av, int *fd)
{
	char	*path;
	char	**args;

	args = ft_split(av[3], ' ');
	if (!args)
		exit(2);
	path = ft_strjoin("/usr/bin/", args[0]);
	if (!path)
	{
		ft_free_split(args);
		exit(2);
	}
	printf("path : %s\n", path);
	size_t	i = 0;
	while(args[i])
		printf("arg: %s, ", args[i++]);
	printf("\n");
	printf("NEW OUT %d" ,fd[0]);
	if(dup2(fd[0], 0) == -1)
	{
		perror("dup2 1");
		exit(3);
	}
	if (execve(path, args, NULL) == -1)
	{
		perror("execve 2");
		exit(2);
	}
}

int	main(int ac, char *av[])
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;

	(void)ac;
	if (pipe(pipe_fd) == -1)
		return (1);
	printf("fd read %d\n", pipe_fd[0]);
	printf("fd write %d\n", pipe_fd[1]);
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
		ft_execpid1(av, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
		return (2);
	if (pid2 == 0)
		ft_execpid2(av, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

// int	main(void)
// {
// 	char *args[] = {"ls", "-la", NULL};
// 	char *path = ft_strjoin("/bin/", args[0]);

// 	printf("%s\n", path);
// 	if (execve(path, args, NULL) == -1)
// 	{
// 		perror("execve");
// 		return (1);
// 	}
// 	return (0);
// }
