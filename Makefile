NAME	= my_ls

##
## DIRECTORY
##
LIBS	= ./libs/

SRCS	= main.c		\
	  parsing.c		\
	  my_ls.c		\
	  access.c		\
	  error.c		\
	  option_l.c		\
	  showing.c		\
	  linked_list.c		\
	  utils_options.c	\
	  utils_options2.c	\
	  $(LIBS)put.c		\
	  $(LIBS)f_str.c	\
	  $(LIBS)my_strdup.c	\
	  $(LIBS)my_strcpy.c	\
	  $(LIBS)my_strcmp.c	\
	  $(LIBS)my_strcat.c	\
	  $(LIBS)my_getnbr.c	\
	  $(LIBS)fc_utils.c	\
	  $(LIBS)xfunctions.c
OBJS	= $(SRCS:.c=.o)
CC	= gcc
RM	= rm -rf
CFLAGS	= -O2 -W -Wall -Wextra -Wformat-nonliteral -Wpointer-arith -Wmissing-declarations -Winline -Wundef -Wcast-align -Wformat-security -ansi -pedantic

$(NAME)	: $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all	: $(NAME)

clean	:
	$(RM) $(OBJS) *~ *#
	$(RM) $(LIBS)*~ $(LIBS)*#

fclean	: clean
	$(RM) $(NAME)

re	: fclean all
