# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flo <flo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 09:46:50 by fkeitel           #+#    #+#              #
#    Updated: 2024/03/21 20:59:27 by flo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FT_PRINTFDIR = ft_printf
GET_NEXT_LINEDIR = get_next_line

# Define source files in the directory
FT_PRINTF = 	$(FT_PRINTFDIR)/ft_printf.c $(FT_PRINTFDIR)/check_datatypes.c \
			$(FT_PRINTFDIR)/printing_functions.c $(FT_PRINTFDIR)/handle_datatypes.c \

GET_NEXT_LINE = $(GET_NEXT_LINEDIR)/get_next_line_utils.c \
			$(GET_NEXT_LINEDIR)/get_next_line.c \

FUNCTIONS	=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_realloc.c\
				ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c\
				ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c\
				ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_striteri.c\
				ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c\
				ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c\
				ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_split.c\
				ft_lstnew.c ft_lstsize.c ft_lstadd_front.c ft_lstadd_back.c\
				ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
				free_two_dimensional_array.c\

OBJECTS	=	$(FUNCTIONS:.c=.o) $(FT_PRINTF:$(FT_PRINTFDIR)/%.c=$(FT_PRINTFDIR)/%.o) \
				$(GET_NEXT_LINE:$(GET_NEXT_LINEDIR)/%.c=$(GET_NEXT_LINEDIR)/%.o) \

CC				= cc -g
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

all:	$(NAME)

$(NAME): $(OBJECTS)
		ar -rcs $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS) all

fclean:	clean
		$(RM) $(NAME)
		rm -f libft

re:		fclean all

.PHONY:			all clean fclean
