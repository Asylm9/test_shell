# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 18:06:08 by magoosse          #+#    #+#              #
#    Updated: 2025/001/001 18:58:34 by matthieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors
RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
BOLD = \033[1m
RESET = \033[0m

#Animation
define LOADING_FRAMES
	@printf "$(BLUE)⠋ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(BLUE)⠙ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(BLUE)⠹ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(BLUE)⠸ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(BLUE)⠼ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(BLUE)⠴ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(BLUE)⠦ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(BLUE)⠧ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(BLUE)⠇ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(BLUE)⠏ Compiling$(RESET)"; \
	sleep 0.001; \
	printf "\r$(GREEN)✓ Done!     $(RESET)\n"
endef

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_strlen.c \
	   ft_memset.c \
	   ft_bzero.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strncmp.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_strnstr.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_memmove.c \
	   ft_atol.c \
	   ft_atoi.c \
	   ft_memcpy.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_strtrim.c \
	   ft_split.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   get_next_line.c \
	   get_next_line_utils.c \
	   ft_print_digit.c \
	   ft_print_txt.c \
	   ft_printf.c

BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)

SRCSALL = $(SRCS) $(BONUS)

OBJSALL = $(SRCSALL:.c=.o)

NAME = libft.a

all: $(NAME)
	@echo "$(BLUE)		╔══════════════════════════════╗$(RESET)"
	@echo "$(BLUE)		║        Libft compiled        ║$(RESET)"
	@echo "$(BLUE)		╚══════════════════════════════╝$(RESET)"

$(NAME): $(OBJS)
	@ar -rsc $(NAME) $(OBJS)

%.o: %.c
	$(LOADING_FRAMES)
	@cc $(CFLAGS) -c $< -o $(<:.c=.o)

bonus: $(OBJSALL)
	@ar -rsc $(NAME) $(OBJSALL)
	@echo "$(BLUE)		╔══════════════════════════════╗$(RESET)"
	@echo "$(BLUE)		║        Libft compiled        ║$(RESET)"
	@echo "$(BLUE)		╚══════════════════════════════╝$(RESET)"

clean:
	@rm -f $(OBJSALL)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re bonus
