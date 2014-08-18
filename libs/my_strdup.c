#include	<stdlib.h>
#include	"../my_ls.h"

char		*my_strdup(char *str)
{
  char		*new;

  new = xmalloc((my_strlen(str) + 1) * sizeof(*str));
  new = my_strcpy(new, str);
  return (new);
}
