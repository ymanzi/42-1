/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:33:23 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/03 13:33:23 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libasm.h"
#include "tests.h"
#include "../debug/notifier.h"

int
	main(void)
{
	if (NOTIFY)
	{
		test_ft_strlen();
		test_ft_strcpy();
		test_ft_strcmp();
		test_ft_write();
		test_ft_read();
		test_ft_strdup();
		test_ft_atoi_base();
		test_ft_list_push_front();
		test_ft_list_size();
		test_ft_list_sort();
	}
	else
	{
		write(1, ft_strdup("This is very long"), strlen("This is very long"));
	}
}
