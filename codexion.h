/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krajbans <krajbans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 19:31:58 by krajbans          #+#    #+#             */
/*   Updated: 2026/09/12 20:12:27 by krajbans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_simulation t_simulation;


typedef enum e_state
{
	WAITING,
	COMPILING,
	DEBUGGING,
	REFACTORING
}					t_state;

typedef struct s_config
{
	int				num_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				num_of_compiles_required;
	int				dongle_cooldown;
	char			*scheduler;
}					t_config;

typedef struct s_request
{
	int				coder_id;
	long			deadline;
	long			arrival_time;
}					t_request;

typedef struct s_dongle
{
	int				dongle_id;
	int				held_by;
	long			cooldown_end_time;
	pthread_mutex_t	mutex;
	pthread_cond_t	condition;
	t_request		*queue;
}					t_dongle;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	long			last_compile_start;
	int				compiles_done;
	t_state			state;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	t_config		*config;
	t_simulation	*simulation;
}					t_coder;

typedef struct s_simulation
{
	t_config		*config;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		monitor_thread;
	int				running;
	pthread_mutex_t	log_mutex;
	long			start_time;
}					t_simulation;

void				parsing(int argcs, char **argvs, t_config *config);

#endif