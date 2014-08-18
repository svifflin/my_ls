#include	"my_ls.h"

void		enclose_name_double_quote(t_elem *elem, char *opts)
{
  if (opts[get_pos_strchr(OPTIONS, 'Q')])
    my_putchar('"');
  my_putstr(elem->name);
  if (opts[get_pos_strchr(OPTIONS, 'Q')])
    my_putchar('"');
  append_char(elem, opts);
}

void		show_files(t_gen *gen)
{
  t_elem	*elem;

  elem = gen->elem;
  if (!gen->opts[get_pos_strchr(OPTIONS, 'd')] &&
      (gen->opts[get_pos_strchr(OPTIONS, 'l')]
       || gen->opts[get_pos_strchr(OPTIONS, 'n')]
       || gen->opts[get_pos_strchr(OPTIONS, 'o')]))
    show_block_size(elem, gen->opts, 1);
  while (elem)
    {
      if (gen->opts[get_pos_strchr(OPTIONS, 's')])
	show_block_size(elem, gen->opts, 0);
      showing_option_l(elem, gen->opts);
      if (elem->next)
	my_putchar('\n');
      elem = elem->next;
    }
}
