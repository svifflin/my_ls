#include	"../my_ls.h"

char		*my_strcat(char *dest, char *src)
{
  int		i;
  int		j;

  for (j = 0, i = my_strlen(dest); src[j]; i++, j++)
    dest[i] = src[j];
  dest[i] = '\0';
  return (dest);
}
