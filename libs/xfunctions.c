#include	<stdio.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	"../my_ls.h"

void		*xmalloc(size_t size)
{
  void		*ptr;

  if ((ptr = malloc(size)) != NULL)
    return (ptr);
  my_mult_putstr(1, "Insufficient memory\n");
  exit(EXIT_FAILURE);
}

size_t		xread(int fd, void *buf, size_t count)
{
  int		size;

  if ((size = read(fd, buf, count)) > -1)
    return (size);
  my_mult_putstr(1, "Read problem\n");
  exit(EXIT_FAILURE);
}

DIR		*xopendir(char *name)
{
  DIR		*dir;

  if ((dir = opendir(name)))
    return (dir);
  return (NULL);
}
