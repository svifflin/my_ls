# define	_BSD_SOURCE

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<pwd.h>
#include	<grp.h>
#include	<time.h>
#include	"my_ls.h"

static void	show_type(mode_t const mode)
{
  if (S_ISREG(mode))
    my_putchar('-');
  else if (S_ISDIR(mode))
    my_putchar('d');
  else if (S_ISCHR(mode))
    my_putchar('c');
  else if (S_ISBLK(mode))
    my_putchar('b');
  else if (S_ISFIFO(mode))
    my_putchar('p');
  else if (S_ISLNK(mode))
    my_putchar('l');
  else if (S_ISSOCK(mode))
    my_putchar('s');
  else
    my_putchar('?');
}

static void	show_id_or_name(struct stat st, char *opts)
{
  struct passwd	*user;
  struct group	*group;

  user = getpwuid(st.st_uid);
  group = getgrgid(st.st_gid);
  if (!opts[get_pos_strchr(OPTIONS, 'g')])
    {
      if (opts[get_pos_strchr(OPTIONS, 'n')])
	my_put_nbr(user->pw_uid);
      else
	my_putstr(user->pw_name);
      my_putstr((my_strlen(user->pw_name) >= 4) ? "\t" : "\t\t");
    }
  if (opts[get_pos_strchr(OPTIONS, 'o')]);
  else if (opts[get_pos_strchr(OPTIONS, 'G')]);
  else
    {
      if (opts[get_pos_strchr(OPTIONS, 'n')])
	my_put_nbr(group->gr_gid);
      else
	my_putstr(group->gr_name);
      my_putstr((my_strlen(group->gr_name) > 4) ? "\t" : "\t");
    }
}

static void	show_user_group(struct stat st, char *opts)
{
  (st.st_mode & S_IRUSR) ? my_putchar('r') : my_putchar('-');
  (st.st_mode & S_IWUSR) ? my_putchar('w') : my_putchar('-');
  (st.st_mode & S_IXUSR) ? my_putchar('x') : my_putchar('-');
  (st.st_mode & S_IRGRP) ? my_putchar('r') : my_putchar('-');
  (st.st_mode & S_IWGRP) ? my_putchar('w') : my_putchar('-');
  (st.st_mode & S_IXGRP) ? my_putchar('x') : my_putchar('-');
  (st.st_mode & S_IROTH) ? my_putchar('r') : my_putchar('-');
  (st.st_mode & S_IWOTH) ? my_putchar('w') : my_putchar('-');
  (st.st_mode & S_IXOTH) ? my_putchar('x') : my_putchar('-');
  my_putstr("   ");
  my_put_nbr(st.st_nlink);
  my_putchar(' ');
  show_id_or_name(st, opts);
}

static void	show_modif_time(time_t const date_modif)
{
  char		*infotime;
  char		*year;
  char		*time;

  my_putstr("\t");
  infotime = ctime(&date_modif) + 4;
  infotime[my_strlen(infotime) - 1] = '\0';
  year = infotime + my_strlen(infotime) - 4;
  infotime[my_strlen(infotime) - my_strlen(year) * 2] = '\0';
  time = infotime + my_strlen(infotime) - 5;
  infotime[my_strlen(infotime) - my_strlen(time) - 1] = '\0';
  my_putstr(infotime);
  if (!my_strcmp("2012", year))
    my_mult_putstr(2, " ", time);
  else
    my_mult_putstr(2, "  ", year);
  my_putstr(" ");
}

void		showing_option_l(t_elem *elem, char *opts)
{
  char		*link;

  if (opts[get_pos_strchr(OPTIONS, 'l')] || opts[get_pos_strchr(OPTIONS, 'n')]
       || opts[get_pos_strchr(OPTIONS, 'o')])
    {
      show_type(elem->stat.st_mode);
      show_user_group(elem->stat, opts);
      if (S_ISBLK(elem->stat.st_mode) || S_ISCHR(elem->stat.st_mode))
	{
	  my_putstr(" ");
	  my_put_nbr(elem->stat.st_rdev >> 8);
	  my_putstr(", ");
	  my_put_nbr(elem->stat.st_rdev & 0xff);
	}
      else
	show_human_size((int)elem->stat.st_size, opts);
      show_modif_time(elem->stat.st_mtime);
    }
  enclose_name_double_quote(elem, opts);
  if ((opts[get_pos_strchr(OPTIONS, 'l')] || opts[get_pos_strchr(OPTIONS, 'n')]
       || opts[get_pos_strchr(OPTIONS, 'o')])
      && S_ISLNK(elem->stat.st_mode) && (link = read_link(elem->long_name)))
    my_mult_putstr(2, " -> ", link);
}
