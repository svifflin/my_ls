#include	"../my_ls.h"

int		my_getnbr(char *str)
{
  int		nbr;

  nbr = 0;
  if (*str == '-')
    return (-my_getnbr(str + 1));
  if (*str == '+')
    return (my_getnbr(str + 1));
  while (*str)
    {
      nbr *= 10;
      nbr += *str - '0';
      str++;
    }
  return (nbr);
}
