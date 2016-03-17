#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char *ft_strrev(char *str)
{
    int i;
    size_t len;
    char *rev;

    i = 0;
    rev = NULL;
    if (str && ((len = ft_strlen(str))))
    {
        if ((rev = (char *)malloc(sizeof(char) * len)))
        {
            len--;
            while (len)
            {
                rev[i] = str[len];
                i++;
                len--;
            }
            rev[i] = '\0';
        }
    }
    return (rev);
}

char *get_prev_chars(t_term *term)
{
    char *buf;
    char *rev;
    int i;

    i = 0;
    if ((buf = ft_strnew(128)))
    {
        term = get_current_cursor(term);
        if (term->c == ' ' && term->prev)
            term = term->prev;
        while (term && i < 128 && term->c != ' ')
        {
            buf[i] = (char)term->c;
            term = term->prev;
            i++;
        }
    }
    rev = ft_strrev(buf);
    free(buf);
    return (rev);
}

void    play_next(t_sh *shell, t_term *term, char *str, char *map_name)
{
    size_t  len;
    char *end;

    ft_putstr_fd("m:", DEBUG_FD);
    ft_putendl_fd(map_name, DEBUG_FD);

    len = ft_strlen(str);
    end = &map_name[len];
    while (end && *end)
    {
        tc_continue_process_key(shell, term, (long)*end);
        end++;
    }
    tc_continue_process_key(shell, term, (long)' ');
}

void    find_next(t_sh *shell, t_term *term, char *str)
{
    t_bin   *map;

    map = shell->map;
    while (map && map->next)
    {
        if (starts_with(str, map->name))
        {
            if (map->prev && starts_with(str, map->prev->name))
            {
              ;
            }
            else if (map->next && starts_with(str, map->next->name))
                ;
            else
            {
                play_next(shell, term, str, map->name);
                return ;
            }
        }
        map = map->next;
    }
}