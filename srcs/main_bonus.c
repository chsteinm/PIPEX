#include "../includes/pipex_bonus.h"

void	close_fds(t_data *data)
{
	int	i;

	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	i = -1;
	while (data->fildes && data->fildes[++i])
	{
		close(data->fildes[i][0]);
		close(data->fildes[i][1]);
		free(data->fildes[i]);
	}
}

void	close_free_exit(t_data *data, int ret)
{
	close_fds(data);
	ft_free_strings(data->args);
	ft_free_strings(data->path);
	free(data->fildes);
	free(data->pid);
	if (ret)
		exit(ret);
}

void	check_argc(t_data *data, int argc, char **argv)
{
	if (argc == 1)
	{
		ft_dprintf(STDERR_FILENO, "%s have no parameters\n", argv[0]);
		close_free_exit(data, EXIT_FAILURE);
	}
	if (!ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])))
		data->is_here_doc = 1;
	if (argc < 5 + data->is_here_doc)
	{
		ft_dprintf(STDERR_FILENO, "%s have not all parameters\n", argv[0]);
		close_free_exit(data, EXIT_FAILURE);
	}
	if (!((argc + data->is_here_doc) % 2))
	{
		ft_dprintf(STDERR_FILENO, "%s \
		have not a right amount of parameters\n", argv[0]);
		close_free_exit(data, EXIT_FAILURE);
	}
}

void	open_files(t_data *data, char **argv)
{
	data->fd_in = open(argv[1 + data->is_here_doc], O_RDONLY);
	if (data->fd_in == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", argv[1 + data->is_here_doc], \
		strerror(errno));
	}
	data->fd_out = open(argv[4 + data->is_here_doc], \
	O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd_out == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", argv[4 + data->is_here_doc], \
		strerror(errno));
	}
}

char	**ret_path(int *is_env, int *is_path, char **env)
{
	char	*line_ptr;
	size_t	i;

	if (env && *env)
		*is_env = 1;
	else
		return (NULL);
	i = -1;
	line_ptr = NULL;
	while (!line_ptr && env[++i])
		line_ptr = ft_strnstr(env[i], "PATH=", 6);
	if (!line_ptr)
		return (NULL);
	else
		*is_path = 1;
	return (ft_split(line_ptr, ':'));
}

void	set_fildes(t_data *data, int ac)
{
	int	i;

	data->nb_cmd = ac - 1 - data->is_here_doc - 2;
	data->fildes = ft_calloc(data->nb_cmd, sizeof(int *));
	if (!data->fildes)
	{
		perror("malloc");
		close_free_exit(data, EXIT_FAILURE);
	}
	i = -1;
	while (++i < data->nb_cmd - 1)
	{
		data->fildes[i] = ft_calloc(2, sizeof(int));
		if (!data->fildes[i])
		{
			perror("malloc");
			close_free_exit(data, EXIT_FAILURE);
		}
		if (pipe(data->fildes[i]) == -1)
		{
			perror("pipe");
			close_free_exit(data, EXIT_FAILURE);
		}
	}
}

void	set_fork(t_data *data)
{
	int	i;

	data->pid = malloc(data->nb_cmd * sizeof(int));
	if (!data->pid)
	{
		perror("malloc");
		close_free_exit(data, EXIT_FAILURE);
	}
	i = -1;
	while (++i < data->nb_cmd)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
		{
			perror("fork");
			close_free_exit(data, EXIT_FAILURE);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)env;
	ft_bzero((char *)&data, sizeof(t_data));
	check_argc(&data, argc, argv);
	open_files(&data, argv);
	data.argv_ptr = argv + 1 + data.is_here_doc;
	data.env_ptr = env;
	data.path = ret_path(&data.is_env, &data.is_path, env);
	if (!data.path && data.is_env && data.is_path)
	{
		perror("malloc");
		close_free_exit(&data, EXIT_FAILURE);
	}
	set_fildes(&data, argc);
	set_fork(&data);
	while (data.i < data.nb_cmd)
		if (data.pid[data.i] == 0 && (data->i++ || data->fd_in != -1))
			exec_cmd(&data);
	// return (WEXITSTATUS(data.status_last));
	close_free_exit(&data, EXIT_SUCCESS);
	return (0);
}
