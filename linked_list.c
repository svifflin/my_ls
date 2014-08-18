#include	<stdlib.h>
#include	"my_ls.h"

t_elem		*init_elem()
{
  t_elem	*elem;

  elem = xmalloc(sizeof(*elem));
  elem->name = NULL;
  elem->long_name = NULL;
  elem->obj = NULL;
  elem->next = NULL;
  elem->prev = NULL;
  return (elem);
}

t_elem		*insert_into_list(t_elem *elem, t_elem *list, char *opts)
{
  int		i;
  t_elem	*current;

  current = list;
  if (!current)
    return (list = elem);
  while ((i = filter_by_option(opts, current, elem)) <= 0 && current->next)
    current = current->next;
  elem->next = (i < 0 ? current->next :
		(current->prev ? current->prev->next : current));
  if (i < 0)
    current->next = elem;
  elem->prev = (i < 0 ? current : current->prev);
  if (i > 0 && current->prev)
    current->prev->next = elem;
  if (i > 0)
    current->prev = elem;
  if (!elem->prev)
    list = elem;
  return (list);
}

t_elem		*free_list(t_elem *elem)
{
  t_elem	*tmp;

  while (elem)
    {
      tmp = elem->next;
      if (*(elem->name))
	free(elem->name);
      if (*(elem->long_name))
	free(elem->long_name);
      free(elem);
      elem = tmp;
    }
  return (elem);
}
