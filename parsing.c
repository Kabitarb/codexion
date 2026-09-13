/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krajbans <krajbans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 19:43:16 by krajbans          #+#    #+#             */
/*   Updated: 2026/09/11 21:57:11 by krajbans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <limits.h>

static int	is_positive(char *str)
{
	int	num;
	int	i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (strcmp(str, "2147483647") > 0)
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	num = atoi(str);
	return (num > 0);
}

static int	is_scheduler(char *str)
{
	if (!str)
		return (0);
	return (strcmp(str, "fifo") == 0 || strcmp(str, "edf") == 0);
}

static void	validate(int argcs, char **argvs)
{
	if (argcs != 9)
		fprintf(stderr, "Error: Invalid number of arguments\n");
	else if (is_positive(argvs[1]) == 0)
		fprintf(stderr, "Error: Number of coders is invalid\n");
	else if (is_positive(argvs[2]) == 0)
		fprintf(stderr, "Error: Time to burnout is invalid\n");
	else if (is_positive(argvs[3]) == 0)
		fprintf(stderr, "Error: Time to compile is invalid\n");
	else if (is_positive(argvs[4]) == 0)
		fprintf(stderr, "Error: Time to debug is invalid\n");
	else if (is_positive(argvs[5]) == 0)
		fprintf(stderr, "Error: Time to refactor is invalid\n");
	else if (is_positive(argvs[6]) == 0)
		fprintf(stderr, "Error: Number of compiles required is invalid\n");
	else if (is_positive(argvs[7]) == 0)
		fprintf(stderr, "Error: Time for dongle cooldown is invalid\n");
	else if (is_scheduler(argvs[8]) == 0)
		fprintf(stderr, "Error: Scheduler is invalid\n");
	else
		return ;
	exit(1);
}

void	parsing(int argcs, char **argvs, t_config *config)
{
	validate(argcs, argvs);
	config->num_of_coders = atoi(argvs[1]);
	config->time_to_burnout = atoi(argvs[2]);
	config->time_to_compile = atoi(argvs[3]);
	config->time_to_debug = atoi(argvs[4]);
	config->time_to_refactor = atoi(argvs[5]);
	config->num_of_compiles_required = atoi(argvs[6]);
	config->dongle_cooldown = atoi(argvs[7]);
	config->scheduler = argvs[8];
}
