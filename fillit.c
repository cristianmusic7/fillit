/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 18:26:42 by cfranco           #+#    #+#             */
/*   Updated: 2018/03/12 11:47:32 by cfranco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

unsigned short	*to_bits(char *buf, int num)
{
	unsigned short	*tetriminos;
	int				c;
	unsigned short	current;
	int				t_counter;

	t_counter = 0;
	current = 0;
	c = -1;
	tetriminos = (unsigned short*)malloc(sizeof(unsigned short) * num + 1);
	while (buf[++c] != -1)
	{
		if (buf[c] != '\n')
		{
			current <<= 1;
			current += (buf[c] == '#');
		}
		else if (buf[c] == '\n' && buf[c - 1] == '\n')
		{
			tetriminos[t_counter++] = current;
			current = 0;
		}
	}
	tetriminos[t_counter++] = current;
	tetriminos[t_counter] = 0;
	return (tetriminos);
}

int				num_bits(char *buf)
{
	int		c;
	int		num;

	c = 0;
	num = 0;
	while (buf[++c] != -1)
	{
		if (buf[c] == '#')
			num++;
	}
	return (num);
}

int				calc_square(unsigned long long int *res,
		int square_w, unsigned long long int sum)
{
	unsigned long long int tmp;

	tmp = *res;
	if ((sum & *res) == 0)
	{
		if (*(res + 1))
		{
			if (calc_square(res + 1, square_w, sum + *res))
				return (1);
		}
		else
			return (1);
	}
	while (mv_forward(res, square_w, sum))
	{
		if (*(res + 1))
		{
			if (calc_square(res + 1, square_w, sum + *res))
				return (1);
		}
		else
			return (1);
	}
	*res = tmp;
	return (0);
}

void			handle_tet(char *buf, int num)
{
	unsigned short			*tetriminos;
	unsigned long long int	*res;
	int						square_w;

	res = 0;
	square_w = ft_sqrt_ceil(num * 4);
	tetriminos = to_bits(buf, num);
	mv_top_left(tetriminos, 4);
	is_valid(tetriminos);
	while (!(res = morph(tetriminos, square_w)))
		square_w++;
	while (!(calc_square(res, square_w, 0)))
	{
		free(res);
		if (++square_w > 8)
			break ;
		else
			res = morph(tetriminos, square_w);
	}
	free(tetriminos);
	print_solution(res, square_w);
	if (res)
		free(res);
}

int				main(int argc, char **argv)
{
	int		fd;
	int		num;
	char	*buf;

	buf = (char*)malloc(sizeof(char) * BUF_SIZE);
	buf[0] = '\0';
	num = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1 || !((num = check_input(buf, fd))))
			print_error();
		else if (num > 26)
			print_error();
		else
			handle_tet(buf, num);
	}
	else
		write(1, "usage: fillit <tetrimino_file>\n",
				ft_strlen("usage: fillit <tetrimino_file>\n"));
	free(buf);
	return (0);
}
