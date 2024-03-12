#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include "get_next_line_bonus.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define ERR_CNF "%s: command not found\n"
# define ERR_M_OR_L "Malloc failed or no limiter found on here_doc\n"

typedef struct s_data
{
	int		fd_in;
	int		fd_out;
	int		nb_cmd;
	int		**fildes;
	pid_t	*pid;
	int		status;
	char	**args;
	char	**argv_ptr;
	char	*limiter;
	char	**env_ptr;
	char	**path;
	int		is_env;
	int		is_path;
	int		is_here_doc;
	int		fildes_hd[2];
	int		i;
}					t_data;

void	set(t_data *data, int argc, char **argv, char **env);
void	here_doc_manage(t_data *data);
int		close_n_exit(t_data *data, int ret);
void	close_free_exit(t_data *data, int ret);
void	close_fds(t_data *data);
void	exec_cmd(t_data *data);

#endif
