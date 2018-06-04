/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 00:22:27 by cfranco            #+#    #+#             */
/*   Updated: 2018/03/12 01:08:48 by cfranco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

void	read_file(char *buf, int fd)
{
	int		ret;

	ret = read(fd, buf, BUF_SIZE);
	buf[ret] = -1;
}

void	init_values(unsigned long long int *coln,
		unsigned long long int *rown, int square_w)
{
	int						r;

	r = 0;
	*coln = 0;
	*rown = 0;
	while (r < square_w)
	{
		*coln <<= square_w;
		*coln += 1;
		*rown <<= 1;
		*rown += 1;
		r++;
	}
}

void	init_array(char *array, int sq_size)
{
	int		i;

	i = 0;
	if (sq_size < 4)
		sq_size = 4;
	while (i < (sq_size * sq_size))
		array[i++] = '.';
}

void	sol_array(unsigned long long int *tet_arr, char *array, int sq_size)
{
	char				letter;
	int					i;
	unsigned long long	n;
	int					pos;
	int					c2;

	i = -1;
	letter = 'A' - 1;
	while (tet_arr[++i])
	{
		letter += 1;
		c2 = sq_size * sq_size;
		if (sq_size <= 4)
			c2 = 16;
		n = (unsigned long long int)1 << (c2 - 1);
		pos = 0;
		while (c2-- > 0)
		{
			if (tet_arr[i] & n)
				array[pos] = letter;
			pos++;
			n = n >> 1;
		}
	}
}

void	print_solution(unsigned long long int *tet_arr, int sq_size)
{
	int					i;
	char				square[sq_size * sq_size];
	int					c2;

	init_array(square, sq_size);
	sol_array(tet_arr, square, sq_size);
	i = 0;
	c2 = -1;
	while (++c2 < (sq_size * sq_size))
	{
		if (c2 && (c2 % sq_size) == 0)
		{
			if (sq_size < 4)
				i += 4 - sq_size;
			write(1, "\n", 1);
		}
		write(1, &(square[i++]), 1);
	}
	write(1, "\n", 1);
}
