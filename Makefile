# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/16 17:16:42 by aait-ihi          #+#    #+#              #
#    Updated: 2022/04/13 16:36:41 by aait-ihi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgui.a
TMPNAME = libguitmp.a

CXX = g++ 

CPPFLAGS = -Wall -Wextra -Werror -std=c++11
CPPFLAGS =  -fsanitize=address -g -O3 -std=c++11
CPPFLAGS =  -O3 -std=c++11

LIBS = libs

MLX_LIB = -lmlx -framework OpenGL -framework AppKit

FT2_LIB_DIR = $(LIBS)/freetype/objs/.libs/ 
FT2_LIB = $(FT2_LIB_DIR)/libfreetype.a
FT2_INCLUDE = -I $(LIBS)/freetype/include/

SRC =	Gui.cpp\
		GuiDrawer.cpp\
		GuiFont.cpp\
		Objects/AGuiObject.cpp\
		Objects/GuiButton.cpp\
		Objects/GuiCheckBox.cpp\
		Objects/GuiImage.cpp\
		Objects/GuiLabel.cpp\
		Objects/GuiView.cpp

INCLUDE =	Gui.hpp\
			GuiDrawer.hpp\
			GuiFont.hpp\
			Objects/AGuiObject.hpp\
			Objects/color.hpp\
			Objects/GuiButton.hpp\
			Objects/GuiCheckBox.hpp\
			Objects/GuiImage.hpp\
			Objects/GuiLabel.hpp\
			Objects/GuiView.hpp\
			Structs.hpp

OBJ_DIR = objs/
OBJS = $(addprefix $(OBJ_DIR),$(SRC:.cpp=.o))

all : $(NAME)

$(NAME): $(TMPNAME) $(FT2_LIB)
	libtool -static -o libgui.a libguitmp.a $(FT2_LIB)

$(TMPNAME): $(OBJS)
	ar rcs $(TMPNAME) $(OBJS) 

$(FT2_LIB):
	make -C $(libs)/freetype

$(OBJ_DIR)%.o : %.cpp $(INCLUDE)
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(FT2_INCLUDE) -c -o $@ $<

clean :
	/bin/rm -rf *.hpp.gch

fclean : clean
	/bin/rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re