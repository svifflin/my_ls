#include	"../my_ls.h"

int		my_istrcmp(char *s1, char *s2)
{
  int		i;
  char		c_s1;
  char		c_s2;

  i = 0;
  while (s1[i] && s2[i])
    {
      c_s1 = ((s1[i] >= 'A' && s1[i] <= 'Z') ? (s1[i] + 32) : s1[i]);
      c_s2 = ((s2[i] >= 'A' && s2[i] <= 'Z') ? (s2[i] + 32) : s2[i]);
      if (c_s1 < c_s2)
	return (-1);
      else if (c_s1 > c_s2)
	return (1);
      ++i;
    }
  if (!s1[i] && !s2[i])
    return (0);
  else if (!s1[i])
    return (-1);
  return (1);
}

int		my_strcmp(char *s1, char *s2)
{
  int		i;

  i = 0;
  while (s1[i] && s2[i])
    {
      if (s1[i] < s2[i])
	return (-1);
      else if (s1[i] > s2[i])
	return (1);
      ++i;
    }
  if (!s1[i] && !s2[i])
    return (0);
  else if (!s1[i])
    return (-1);
  return (1);
}
