#include	"../my_ls.h"

char		*my_strcpy(char *dest, char *src)
{
  int		i;

  i = 0;
  if (dest && src)
    {
      while (src[i])
	{
	  dest[i] = src[i];
	  ++i;
	}
      dest[i] = '\0';
    }
  return (dest);
}
