# define	_BSD_SOURCE

#include	<sys/stat.h>
#include	"../my_ls.h"

int		get_idx_tab(int tab[], int val)
{
  int		i;

  i = 0;
  while (tab[i] && tab[i] != (val & S_IFMT))
    ++i;
  return (i);
}
