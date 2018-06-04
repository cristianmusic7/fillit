/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 04:32:47 by cfranco           #+#    #+#             */
/*   Updated: 2018/03/12 11:52:36 by cfranco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUF_SIZE 		1000000000
# define BUF_SIZE_INPUT 4096

void						handle_tet(char *buf, int num);
int							calc_square(unsigned long long int *res,
								int square_w, unsigned long long int sum);
int							num_bits(char *buf);
unsigned short				*to_bits(char *buf, int num);
void						read_file(char *buf, int fd);
int							mv_forward(unsigned long long int *tetrimino,
								int square_w, unsigned long long int sum);
int							handle_corner(unsigned long long int *tetrimino,
								int square_w, unsigned long long int flag,
									unsigned long long int rown);
void						mv_top_left(unsigned short *tetriminos,
								int square_w);
unsigned long long int		*morph(unsigned short *tetriminos, int square_w);
unsigned long long int		*morph_helper(unsigned long long int *m_tet,
								unsigned short *tetriminos, int square_w);
void						init_values(unsigned long long int *coln,
								unsigned long long int *rown, int square_w);
void						print_error(void);
int							check_input(char *buf, int fd);
int							check_input_helper(char *buf, int num);
int							is_valid(unsigned short *n);
unsigned short				*fill_array(void);
void						print_solution(unsigned long long int *tet_arr,
								int sq_size);
void						sol_array(unsigned long long int *tet_arr,
								char *array, int sq_size);
void						init_array(char *array, int sq_size);
int							ft_sqrt_ceil(int nb);
#endif
