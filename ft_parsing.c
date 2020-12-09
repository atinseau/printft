#include "ft_printf.h"

int ft_parsing(va_list *args, char *s)
{
    int i;
    int count;
    t_options print;

    i = 0;
    count = 0;
    while(s[i])
    {
        if(s[i] == '%' && s[i + 1])
        {
            ft_init(&print);
            ft_get_flag(s + i + 1, &print, &i, args);
            ft_print_flag(print, args, &count);
        }
        else
        {
            ft_putchar(s[i]);
            count++;
        }
        i++;
    }
    return (count);
}


void ft_get_flag(char *str, t_options *print, int *main_loop, va_list *args)
{
    int i;

    i = 0;
    while (str[i])
    {
        if(str[i] == '-')
            print->reverse_padd = true;
        if(str[i] == '+')
            print->get_sign = true;
        if(str[i] == '0' && (ft_isdigit(str[i + 1]) && str[i + 1] != '0'))
            print->padd_char = '0';
        if(ft_isdigit(str[i]) && str[i] != '0')
            digit_getter(str + i, &print->padd_size, &i, args); 
        if(str[i] == '*') {
            int tmp = va_arg(*args, int);
            print->padd_size =  (tmp < 0) ? tmp * -1 : tmp; 
        }
        if(str[i] == '.') {
            digit_getter(str + i + 1, &print->field_size, &i, args);
            print->padd_char = ' ';
        }
        if(is_type(str[i]))
        {
            print->type = str[i];
            i++;
            break;
        }
        i++;
    }
    *main_loop += i;
}

void digit_getter(char *str, int *size, int *main_loop, va_list *args) {
    int i;
    char *temp;

    i = 0;
    if(str[i] == '*')
    {
        *size = va_arg(*args, int);
        *main_loop += 1;
        return;
    } 
    while(ft_isdigit(str[i]))
        i++;
    temp = ft_substr(str, 0, i);
    *size = ft_atoi(temp);
    free(temp);
    *main_loop += i;
}
