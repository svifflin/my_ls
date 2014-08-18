#include	<strings.h>
#include	"../my_ls.h"

int		my_strlen(char *s)
{
  int		i;

  for (i = 0; s[i]; ++i);
  return (i);
}

void		my_bzero(char *s, int n, char c)
{
  int		i;

  if (s)
    for (i = 0; i < n; ++i)
      s[i] = c;
}
