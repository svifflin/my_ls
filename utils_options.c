# define	_BSD_SOURCE

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	"my_ls.h"

void		append_char(t_elem *elem, char *opts)
{
  mode_t	mode;

  mode = elem->stat.st_mode;
  if (opts[get_pos_strchr(OPTIONS, 'F')])
    {
      if (S_ISREG(mode) && ((mode & S_IXUSR) || (mode & S_IXGRP)
			    || (mode & S_IXOTH)))
	my_putchar('*');
      else if (S_ISFIFO(mode))
	my_putchar('|');
      else if (S_ISSOCK(mode))
	my_putchar('=');
    }
  if (opts[get_pos_strchr(OPTIONS, 'F')] || opts[get_pos_strchr(OPTIONS, 'p')])
    if (S_ISDIR(mode))
      my_putchar('/');
  if (!opts[get_pos_strchr(OPTIONS, 'l')] && !opts[get_pos_strchr(OPTIONS, 'n')]
      && !opts[get_pos_strchr(OPTIONS, 'o')])
    {
      if (opts[get_pos_strchr(OPTIONS, 'F')] && S_ISLNK(mode))
	my_putchar('@');
      if (opts[get_pos_strchr(OPTIONS, 'm')])
	my_putchar(',');
    }
}

int		get_file_ending_with_tild(t_elem *elem)
{
  if (elem->name && (elem->name[my_strlen(elem->name) - 1] == '~'))
    return (1);
  return (0);
}

char		*read_link(char *param)
{
  struct stat	s;
  char		*linkname;
  ssize_t	r;

  if (lstat(param, &s) == -1)
    {
      my_mult_putstr(3, "\nls: ", param, ": No such file or directory");
      return (0);
    }
  linkname = xmalloc((s.st_size + 1) * sizeof(*linkname));
  r = readlink(param, linkname, s.st_size + 1);
  if (r < 0)
    {
      my_mult_putstr(3, "\nls: ", param, ": No such file or directory");
      return (0);
    }
  if (r > s.st_size || r > PATH_MAX)
    return (0);
  linkname[s.st_size] = '\0';
  return (linkname);
}

void		show_block_size(t_elem *elem, char *opts, int boucle)
{
  int		total;
  int		blk_size;

  total = 0;
  while (elem)
    {
      blk_size = (int)elem->stat.st_blocks / 2;
      if (opts[get_pos_strchr(OPTIONS, 'h')])
	blk_size *= 1024;
      total += blk_size;
      if (!boucle && opts[get_pos_strchr(OPTIONS, 's')])
	{
	  show_human_size(blk_size, opts);
	  my_putchar(' ');
	}
      if (!boucle)
	return ;
      elem = elem->next;
      blk_size = 1;
    }
  my_putstr("total ");
  show_human_size(total, opts);
  if (total || blk_size)
    my_putchar('\n');
}

void		show_human_size(int size, char *opts)
{
  if (opts[get_pos_strchr(OPTIONS, 'h')])
    if (size >= 1073741824)
      {
	my_put_nbr(size / 1073741824.0);
	my_putchar('G');
      }
    else if (size >= 1048576)
      {
	my_put_nbr(size / 1048576.0);
	my_putchar('M');
      }
    else if (size >= 1024)
      {
	my_put_nbr(size / 1024.0);
	my_putchar('K');
      }
    else
      my_put_nbr(size);
  else
    my_put_nbr(size);
}
