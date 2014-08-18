#include	<stdlib.h>
#include	<dirent.h>
#include	<sys/stat.h>

#ifndef		MY_LS_H
# define	MY_LS_H

# define	OPTIONS "lRrdtaALhsFBgGmnopQS"

typedef struct	s_elem
{
  char		*name;
  char		*long_name;
  struct stat	stat;
  struct dirent	*obj;
  struct s_elem	*next;
  struct s_elem	*prev;
}		t_elem;

typedef	struct	s_gen
{
  char		*opts;
  char		**path;
  int		nb_path;
  t_elem	*elem;
}		t_gen;

void		usage();
int		check_opts(char **, t_gen *);
int		get_pos_strchr(char *, int);
void		main_process(t_gen *);
int		filter_by_option(char *, t_elem *, t_elem *);
int		read_file_process(char *, t_gen *, t_elem *);
t_elem          *instance_elem(t_elem *, char *);
void		show_files(t_gen *);
char		**set_folder_recursive(t_elem *, char *);

/*
** ACCESSIBILITY
*/

int		test_before_add(char *);
char		*read_link(char *);
DIR		*try_open_dir(char *, t_gen *);
void		try_read_dir(DIR *, char *, t_gen *);
int		handle_file(t_gen *, t_elem *);

/*
** OPTIONS AND UTILS OPTIONS
**/
void		show_human_size(int, char *);
void		show_block_size(t_elem *, char *, int);
void		showing_option_l(t_elem *, char *);
int		get_idx_tab(int[], int);
void		order_args(t_gen *);
int		get_file_ending_with_tild(t_elem *);
void		append_char(t_elem *, char *);
void		enclose_name_double_quote(t_elem *, char *);

/*
** LINKED_LIST
*/

t_elem		*init_elem();
t_elem		*insert_into_list(t_elem *, t_elem *, char *);
t_elem		*free_list(t_elem *);

/*
** LIBS
*/

void		my_putchar(char);
void		my_putstr(char *);
void		my_mult_putstr(int, ...);
void		my_put_nbr(int);
int		my_strlen(char *);
char		*my_strdup(char *);
char		*my_strcpy(char *, char *);
int		my_strcmp(char *, char *);
int		my_istrcmp(char *, char *);
char		*my_strcat(char *, char *);
int		my_getnbr(char *);
void		my_bzero(char *, int, char);

/*
** XFUNCTIONS
*/

void		*xmalloc(size_t);
size_t		xread(int, void *, size_t);
DIR		*xopendir(char *);

#endif
