cmake_minimum_required(VERSION 3.15)
project(fdf)

set(CMAKE_CXX_STANDARD 99)

add_custom_target(fdf
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(.:libft:/usr/local/include)
link_directories(/usr/local/lib)
add_compile_options(-Wall -Wextra -Werror -g3)
find_library(OPEN_GL OpenGl)
find_library(APP_KIT AppKit)
link_libraries(mlx)

add_executable(f
        main.c
        ft_tastr.c
        ft_tastr_holder.c
        ft_tpoint_map.c
        ft_tpoint_map_keeper.c
        fdf_tastr_holder.c
        fdf_tpoint_map.c
        fdf_tpoint_map_keeper.c ft_tmlx.c)

add_library(ft STATIC
        libft/ft_astr_del.c
        libft/ft_astr_new.c
        libft/ft_atou_base.c
        libft/ft_atoi_base.c
        libft/ft_astr_fill_c.c
        libft/ft_atoi.c
        libft/ft_atolu_base.c
        libft/ft_atollu_base.c
        libft/ft_atoll_base.c
        libft/ft_astr_put.c
        libft/ft_atol_base.c
        libft/ft_atox_utils.c
        libft/ft_garbage_collector.c
        libft/ft_bzero.c
        libft/ft_gc_parray.c
        libft/ft_strnequ.c
        libft/ft_striteri.c
        libft/ft_nsym.c
        libft/ft_memchr.c
        libft/ft_isspace.c
        libft/ft_strdel.c
        libft/ft_isprint.c
        libft/ft_strlen.c
        libft/ft_striter.c
        libft/ft_lstiter.c
        libft/ft_strnchri.c
        libft/ft_strjoin.c
        libft/ft_memalloc.c
        libft/ft_strmap.c
        libft/ft_strcmp.c
        libft/ft_lstdel.c
        libft/ft_itoa.c
        libft/ft_memdel.c
        libft/ft_gc_utils.c
        libft/ft_strncpy.c
        libft/ft_strequ.c
        libft/ft_memmove.c
        libft/ft_uintlen.c
        libft/ft_strcat.c
        libft/ft_toupper.c
        libft/ft_strcpy.c
        libft/ft_strclr.c
        libft/ft_memset.c
        libft/ft_islower.c
        libft/ft_strlenc.c
        libft/ft_putendl.c
        libft/ft_isascii.c
        libft/ft_strmapi.c
        libft/ft_lstnew.c
        libft/ft_strncat.c
        libft/ft_ishex.c
        libft/ft_putchar.c
        libft/ft_putchar_fd.c
        libft/ft_strstr.c
        libft/ft_strrchr.c
        libft/ft_strlcat.c
        libft/ft_isdigit.c
        libft/ft_tolower.c
        libft/ft_putstr_fd.c
        libft/ft_isalnum.c
        libft/ft_strdup.c
        libft/ft_putnbr.c
        libft/ft_memcpy.c
        libft/ft_strnstr.c
        libft/ft_strncmp.c
        libft/ft_strnew.c
        libft/ft_memccpy.c
        libft/ft_strtrim.c
        libft/ft_lstadd.c
        libft/ft_strsub.c
        libft/ft_putstr.c
        libft/get_next_line.c
        libft/ft_isalpha.c
        libft/ft_putendl_fd.c
        libft/ft_strnlen.c
        libft/ft_lstdelone.c
        libft/ft_strsplit.c
        libft/ft_memcmp.c
        libft/ft_putnbr_fd.c
        libft/ft_strchr.c
        libft/ft_lstmap.c
        libft/ft_isupper.c)

target_link_libraries(f ft mlx ${OPEN_GL} ${APP_KIT})
