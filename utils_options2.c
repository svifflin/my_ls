#include	"my_ls.h"

static int	count_folder_in_list(t_elem *elem)
{
  int		i;
  DIR		*ptr_dir;

  i = 0;
  while (elem)
    {
      if (my_strcmp(elem->name, ".") && my_strcmp(elem->name, "..")
	  && S_ISDIR(elem->stat.st_mode)
	  && (ptr_dir = xopendir(elem->long_name)))
	{
	  closedir(ptr_dir);
	  ++i;
	}
      elem = elem->next;
    }
  return (i);
}

char		**set_folder_recursive(t_elem *elem, char *opts)
{
  int		i;
  char		**rec;
  DIR		*ptr_dir;

  i = 0;
  if (opts[get_pos_strchr(OPTIONS, 'd')]
      || !opts[get_pos_strchr(OPTIONS, 'R')])
    return (NULL);
  rec = xmalloc((count_folder_in_list(elem) + 1) * sizeof(*rec));
  while (elem)
    {
      if (my_strcmp(elem->name, ".") && my_strcmp(elem->name, "..")
	  && S_ISDIR(elem->stat.st_mode)
	  && (ptr_dir = xopendir(elem->long_name)))
	{
	  closedir(ptr_dir);
	  rec[i++] = my_strdup(elem->long_name);
	}
      elem = elem->next;
    }
  rec[i] = 0;
  return (rec);
}
