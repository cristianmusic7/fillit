/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 00:13:10 by cfranco            #+#    #+#             */
/*   Updated: 2018/03/12 00:56:17 by cfranco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

unsigned short	*fill_array(void)
{
	unsigned short int	*a;

	a = (unsigned short *)malloc(sizeof(unsigned short) * 18);
	a[0] = 61440;
	a[1] = 52224;
	a[2] = 51328;
	a[3] = 36352;
	a[4] = 17600;
	a[5] = 57600;
	a[6] = 35968;
	a[7] = 58368;
	a[8] = 19520;
	a[9] = 19968;
	a[10] = 59392;
	a[11] = 35008;
	a[12] = 11776;
	a[13] = 50240;
	a[14] = 50688;
	a[15] = 19584;
	a[16] = 35904;
	a[17] = 34952;
	a[18] = 57856;
	a[19] = 27648;
	a[20] = 0;
	return (a);
}

int				is_valid(unsigned short *n)
{
	unsigned short	*a;
	unsigned short	i;
	unsigned short	j;

	a = fill_array();
	i = -1;
	while (n[++i])
	{
		j = -1;
		while (a[++j])
		{
			if (a[j] == n[i])
			{
				break ;
			}
		}
		if (j == 20)
			print_error();
	}
	return (0);
}

int				check_input_helper(char *buf, int num)
{
	int		c;
	int		i;

	c = -1;
	i = 0;
	while (buf[++c] != -1)
	{
		if (buf[c] != '.' && buf[c] != '#' && buf[c] != '\n')
			print_error();
		if (buf[c] == '#')
			i--;
		i++;
		if (buf[c] == '\n' && buf[c - 1] == '\n')
		{
			if (i != 17)
				print_error();
			i = 0;
			num++;
		}
	}
	if (buf[c - 1] == '\n')
		num += 1;
	if (i != 16)
		print_error();
	return (num);
}

int				check_input(char *buf, int fd)
{
	int		num;

	num = 0;
	read_file(buf, fd);
	num = check_input_helper(buf, num);
	if (close(fd) == -1)
		return (0);
	return (num);
}

void			print_error(void)
{
	ft_putendl("error");
	exit(EXIT_FAILURE);
}
