# define	_BSD_SOURCE

#include	<stdio.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/stat.h>
#include	"my_ls.h"

int		test_before_add(char *param)
{
  struct stat	s;
  DIR		*ptr_dir;

  ptr_dir = 0;
  if (lstat(param, &s) == -1)
    my_mult_putstr(3, "ls: ", param, ": No such file or directory\n");
  else if (S_ISDIR(s.st_mode) && !(ptr_dir = xopendir(param)))
    my_mult_putstr(3, "ls: cannot open directory ", param,
		   ": Permission denied\n");
  else if (S_ISLNK(s.st_mode) && !read_link(param));
  else
    {
      if (ptr_dir)
	closedir(ptr_dir);
      return (1);
    }
  return (0);
}

int		read_file_process(char *dir, t_gen *gen, t_elem *elem)
{
  elem = instance_elem(elem, dir);
  if (lstat(elem->long_name, &(elem->stat)) == 0)
    return (handle_file(gen, elem));
  return (-1);
}
