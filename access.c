# define	_BSD_SOURCE

#include	<sys/types.h>
#include	<sys/stat.h>
#include	"my_ls.h"

t_elem		*instance_elem(t_elem *elem, char *dir)
{
  if (!elem->obj)
    {
      elem->name = my_strdup(dir);
      elem->long_name = my_strdup(dir);
    }
  else
    {
      elem->name = my_strdup(elem->obj->d_name);
      elem->long_name = xmalloc((my_strlen(elem->name) + my_strlen(dir) + 2)
				* sizeof(*(elem->long_name)));
      elem->long_name = my_strcpy(elem->long_name, dir);
      elem->long_name = my_strcat(elem->long_name, "/");
      elem->long_name = my_strcat(elem->long_name, elem->name);
    }
  return (elem);
}

void		try_read_dir(DIR *ptr_dir, char *dir, t_gen *gen)
{
  int		err;
  struct dirent	*obj;
  t_elem	*elem;

  while ((obj = readdir(ptr_dir)))
    {
      elem = init_elem();
      elem->obj = obj;
      if ((err = read_file_process(dir, gen, elem)) <= 0)
	{
	  if (err == -1)
	    my_mult_putstr(3, "\nls: ", elem->name, ": Permission denied");
	  free_list(elem);
	}
    }
}

DIR		*try_open_dir(char *dir, t_gen *gen)
{
  DIR		*ptr_dir;
  t_elem	*elem;
  static int	nb_path = 0;

  ++nb_path;
  if (gen->opts[get_pos_strchr(OPTIONS, 'd')]
      || (!(ptr_dir = xopendir(dir))))
    {
      elem = init_elem();
      if (read_file_process(dir, gen, elem))
	return (NULL);
      exit(EXIT_FAILURE);
     }
  if (gen->opts[get_pos_strchr(OPTIONS, 'R')] ||
      (gen->nb_path > 1 && !gen->opts[get_pos_strchr(OPTIONS, 'R')]))
    my_mult_putstr(3, (nb_path > 1 ? "\n" : ""), dir, ":\n");
  return (ptr_dir);
}
