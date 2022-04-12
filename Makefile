# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/16 17:16:42 by aait-ihi          #+#    #+#              #
#    Updated: 2022/04/10 16:31:14 by aait-ihi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gui_test

CXX = g++ 

CPPFLAGS = -Wall -Wextra -Werror -std=c++11
CPPFLAGS =  -fsanitize=address -g -O3 -std=c++11
CPPFLAGS =  -O3 -std=c++11

LIBS = libs

MLX_LIB = -lmlx -framework OpenGL -framework AppKit

FT2_LIB = -lfreetype -L $(LIBS)/freetype/objs/.libs/ 

FT2_INCLUDE = -I $(LIBS)/freetype/include/

SRC = test.cpp


all : $(NAME)

$(NAME) :
	$(CXX) -o $(NAME) $(CPPFLAGS) $(OBJ) $(SRC) $(FT2_INCLUDE) $(FT2_LIB) $(MLX_LIB)

$(NAME) :
	$(CXX) -o $(NAME) $(CPPFLAGS) $(OBJ) $(SRC) $(FT2_INCLUDE) $(FT2_LIB) $(MLX_LIB)

clean :
	/bin/rm -rf *.hpp.gch

fclean : clean
	/bin/rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re