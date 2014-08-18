# define	_BSD_SOURCE

#include	<sys/stat.h>
#include	<linux/limits.h>
#include	"my_ls.h"

int		handle_file(t_gen *gen, t_elem *elem)
{
  if (gen->opts[get_pos_strchr(OPTIONS, 'B')]
      && get_file_ending_with_tild(elem));
  else if (!gen->opts[get_pos_strchr(OPTIONS, 'd')] && !gen->opts[get_pos_strchr(OPTIONS, 'a')]
	   && !gen->opts[get_pos_strchr(OPTIONS, 'A')]
	   && elem->name[0] == '.');
  else if (!gen->opts[get_pos_strchr(OPTIONS, 'd')] && !gen->opts[get_pos_strchr(OPTIONS, 'a')]
	   && gen->opts[get_pos_strchr(OPTIONS, 'A')]
	   && (!my_strcmp(elem->name, ".") || !my_strcmp(elem->name, "..")));
  else
    {
      gen->elem = insert_into_list(elem, gen->elem, gen->opts);
      return (1);
    }
  return (0);
}

static void	bg_process(char *dir, t_gen *gen)
{
  int		i;
  DIR		*ptr_dir;
  char		**rec;

  rec = NULL;
  if ((ptr_dir = try_open_dir(dir, gen)))
    {
      try_read_dir(ptr_dir, dir, gen);
      closedir(ptr_dir);
    }
  show_files(gen);
  rec = set_folder_recursive(gen->elem, gen->opts);
  gen->elem = free_list(gen->elem);
  my_putchar('\n');
  for (i = 0; rec && rec[i]; i++)
    {
      bg_process(rec[i], gen);
      free(rec[i]);
    }
  if (rec)
    free(rec);
}

void		main_process(t_gen *gen)
{
  int		i;

  if (!gen->nb_path)
    bg_process(".", gen);
  for (i = 0; i < gen->nb_path; ++i)
    bg_process(gen->path[i], gen);
}
