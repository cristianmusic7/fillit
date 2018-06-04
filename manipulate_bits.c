/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_bits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 00:21:06 by cfranco            #+#    #+#             */
/*   Updated: 2018/03/12 01:16:00 by cfranco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

unsigned long long int		*morph_helper(unsigned long long int *m_tet,
		unsigned short *tetriminos, int square_w)
{
	int						square_c;
	int						c;
	unsigned long long int	row;

	c = -1;
	square_c = 0;
	while (tetriminos[++c])
	{
		m_tet[c] = 0;
		row = 61440;
		square_c = square_w;
		while (row > 0)
		{
			m_tet[c] += (row & tetriminos[c]);
			m_tet[c] <<= (square_w - 4);
			row >>= 4;
		}
		while (square_c-- > 4)
			m_tet[c] <<= square_w;
	}
	m_tet[c] = 0;
	return (m_tet);
}

unsigned long long int		*morph(unsigned short *tetriminos, int square_w)
{
	unsigned long long int	*m_tet;
	unsigned long long int	coln;
	unsigned long long int	rown;
	int						c;

	c = 0;
	while (tetriminos[c])
		c++;
	m_tet = (unsigned long long int *)ft_memalloc(8 * (c + 1));
	c = -1;
	if (square_w < 4)
	{
		while (tetriminos[++c])
		{
			init_values(&coln, &rown, 4);
			coln <<= (4 - square_w) - 1;
			rown <<= (4 * ((4 - square_w) - 1));
			if ((coln & tetriminos[c]) > 0 || (rown & tetriminos[c]) > 0)
				return (NULL);
			m_tet[c] = tetriminos[c];
		}
	}
	else
		morph_helper(m_tet, tetriminos, square_w);
	return (m_tet);
}

void						mv_top_left(unsigned short *tetriminos,
		int square_w)
{
	unsigned long long int	col1;
	unsigned long long int	rown;
	unsigned long long int	coln;
	int						r;

	r = 0;
	init_values(&coln, &rown, square_w);
	col1 = coln << (square_w - 1);
	rown <<= (square_w * (square_w - 1));
	while (*tetriminos)
	{
		while ((col1 & *tetriminos) == 0 || (rown & *tetriminos) == 0)
		{
			*tetriminos <<= 1;
			while (((col1 >> square_w) & *tetriminos) > 0
					&& (coln & *tetriminos) > 0)
				*tetriminos <<= 1;
		}
		tetriminos++;
	}
}

int							handle_corner(unsigned long long int *tetrimino,
		int square_w, unsigned long long int flag, unsigned long long int rown)
{
	unsigned long long int	corner;

	corner = (unsigned long long int)3 << ((square_w * (square_w - 1)) - 1);
	if (flag)
	{
		if (rown & *tetrimino)
		{
			*tetrimino <<= 1;
			return (0);
		}
		*tetrimino >>= 1;
	}
	while (corner >= ((unsigned long long int)3 << (square_w - 1)))
	{
		if ((corner & *tetrimino) < corner)
			corner >>= square_w;
		else if ((corner & *tetrimino) == corner)
		{
			*tetrimino >>= 1;
			corner = (unsigned long long int)3 <<
				((square_w * (square_w - 1)) - 1);
		}
	}
	return (1);
}

int							mv_forward(unsigned long long int *tetrimino,
		int square_w, unsigned long long int sum)
{
	unsigned long long int	coln;
	unsigned long long int	rown;
	int						flag;

	flag = 0;
	init_values(&coln, &rown, square_w);
	if (square_w < 4)
	{
		flag = 1;
		init_values(&coln, &rown, 4);
		rown <<= (4 * (4 - square_w));
		square_w = 4;
	}
	while ((coln & *tetrimino) == 0 || (rown & *tetrimino) == 0)
	{
		*tetrimino >>= 1;
		if (!(handle_corner(tetrimino, square_w, flag
						&& (coln & *tetrimino), rown)))
			return (0);
		if ((sum & *tetrimino) == 0)
			return (1);
	}
	return (0);
}
