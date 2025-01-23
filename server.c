/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:24:58 by isahmed           #+#    #+#             */
/*   Updated: 2025/01/23 12:23:48 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// int	to_power(int base, int power)
// {
// 	if (power <= 1)
// 		return (base);
// 	return (to_power(base, power - 1) * base);
// }

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static int		character = 0;
	static int		bit = 0;

	(void)context;
	if (sig == SIGUSR1)
		character |= (1 << (7 - bit));
	bit ++;
	if (bit == 8)
	{
		ft_printf("%c", (char)character);
		bit = 0;
		character = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
