#include	<stdlib.h>
#include	<string.h>
#include	"my_ls.h"

int		filter_by_option(char *opts, t_elem *current, t_elem *elem)
{
  int		ret;
  int		cmp;

  ret = 0;
  if (opts[get_pos_strchr(OPTIONS, 't')])
    {
      cmp = elem->stat.st_mtime - current->stat.st_mtime;
      if (cmp < 0 || (!cmp && elem->stat.st_atime < current->stat.st_atime))
	ret = -1;
      else
	ret = 1;
    }
  else if (opts[get_pos_strchr(OPTIONS, 'S')])
    {
      cmp = elem->stat.st_size - current->stat.st_size;
      if (cmp < 0 || (!cmp && my_istrcmp(current->name, elem->name) <= 0))
	ret = -1;
      else
	ret = 1;
    }
  else
    ret = my_istrcmp(current->name, elem->name);
  if (opts[get_pos_strchr(OPTIONS, 'r')])
    return (-ret);
  return (ret);
}

static char	*get_next_params(char **av, char reset)
{
  static int	c = 0;

  if (reset == 1)
    return (av[c = 0]);
  if (av[c])
    return (av[c++]);
  return (NULL);
}

int		get_pos_strchr(char *str, int c)
{
  char		*pch;

  pch = strchr(str, c);
  if (!pch)
    return (-1);
  return (pch - OPTIONS);
}

static void	fill_opts(char *param, char *opts)
{
  int		i;

  for (i = 0; param[i]; ++i)
    {
      if (strchr(OPTIONS, param[i]))
	opts[get_pos_strchr(OPTIONS, param[i])] = 1;
      else
	usage();
    }
}

int		check_opts(char **av, t_gen *gen)
{
  int		verif;
  char		*param;

  get_next_params(av, 1);
  for (verif = 0; (param = get_next_params(av, 0)); )
    {
      if (param[0] == '-')
	fill_opts(param + 1, gen->opts);
      else
	{
	  ++verif;
	  if (test_before_add(param))
	    gen->path[(gen->nb_path)++] = my_strdup(param);
	}
    }
  order_args(gen);
  if (!gen->nb_path && verif)
    return (0);
  return (1);
}
