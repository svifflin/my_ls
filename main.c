# define	_BSD_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/stat.h>
#include	"my_ls.h"

void		usage()
{
  my_putstr("USAGE: ./my_ls [-lRrdtaALhsFBgGmnopQS] [path ...]\n");
  exit(EXIT_FAILURE);
}

void		order_args(t_gen *gen)
{
  int		i;
  int		j;
  char		*tmp;
  static int	ref[8] = {S_IFSOCK, S_IFBLK, S_IFCHR, S_IFIFO, S_IFREG,
			  S_IFDIR, S_IFLNK, 0};
  struct stat	s;
  struct stat	s_next;

  if ((i = gen->nb_path) <= 1)
    return ;
  while (i--)
    for (j = 0; j < gen->nb_path; j++)
      {
	lstat(gen->path[j], &s);
	if (j + 1 >= gen->nb_path)
	  continue ;
	lstat(gen->path[j + 1], &s_next);
	if (get_idx_tab(ref, s.st_mode) > get_idx_tab(ref, s_next.st_mode))
	  {
	    tmp = gen->path[j];
	    gen->path[j] = gen->path[j + 1];
	    gen->path[j + 1] = tmp;
	  }
      }
}

static void	initialize_gen(int nb_param, t_gen *gen)
{
  gen->opts = my_strdup(OPTIONS);
  my_bzero(gen->opts, my_strlen(OPTIONS), 0);
  gen->path = xmalloc(nb_param * sizeof(gen->path));
  gen->nb_path = 0;
  gen->elem = NULL;
}

int		main(__attribute__((unused))int ac, char **av)
{
  t_gen		gen;

  initialize_gen(ac - 1, &gen);
  if (check_opts(av + 1, &gen))
    main_process(&gen);
  free(gen.opts);
  free(gen.path);
  return (0);
}
