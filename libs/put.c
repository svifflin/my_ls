#include	<stdarg.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"../my_ls.h"

void		my_putstr(char *s)
{
  int		i;

  for (i = 0; s[i]; ++i)
    my_putchar(s[i]);
}

void		my_mult_putstr(int nb_max, ...)
{
  va_list	ap;
  char		*buf;
  int		i;

  va_start(ap, nb_max);
  for (i = 0; i < nb_max; i++)
    {
      if ((buf = va_arg(ap, char *)))
	my_putstr(buf);
    }
  va_end(ap);
}

void		my_put_nbr(int n)
{
  if (n < 0)
    {
      my_putchar('-');
      n = -n;
    }
  if (n > 9)
    my_put_nbr(n / 10);
  my_putchar('0' + n % 10);
}

void		my_putchar(char c)
{
  write(1, &c, 1);
}
