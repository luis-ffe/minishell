/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:08:22 by masoares          #+#    #+#             */
/*   Updated: 2024/04/17 00:08:06 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	switch_sig_function(void)
{
	signal(SIGINT, sig_handler_int);
	signal(SIGQUIT, SIG_IGN);
}


void	switch_sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}


void	handle_sigint_status(void)
{
	signal(SIGINT, update_status_sigint);
	signal(SIGQUIT, update_status_sigquit);
}
