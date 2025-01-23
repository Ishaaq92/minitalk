/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:13:19 by isahmed           #+#    #+#             */
/*   Updated: 2025/01/23 12:23:49 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
volatile	int	g = 0;

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	total;

	i = 0;
	sign = 1;
	total = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i ++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = sign * -1;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		total = (total * 10) + (nptr[i] - 48);
		i ++;
	}
	return (sign * total);
}

// void	send_char(int pid, char c, int i)
// {
// 	if (i == 8)
// 		return ;
// 	send_char(pid, c>>1, i + 1);
// 	usleep(10000);
// 	if (c & 1)
// 	{
// 		kill(pid, SIGUSR1);
// 		ft_printf("1");
// 	}
// 	else
// 	{
// 		kill(pid, SIGUSR2);
// 		ft_printf("0");
// 	}
// 	pause();
// }

void	sig_handler(int sig)
{
	(void)sig;
	g = 1;

}

void	send_char(int pid, char c)
{
	int	i;
	int	j;

	i = 7;
	while (i >= 0)
	{
		g = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		j = 0;
		while (j++ < 100 && !g)
			usleep(100);
		if (j >= 100)
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		i --;
	}
	
}

int	main(int ac, char *av[])
{
	int		pid;
	int		i;
	char	*msg;

	if (ac > 3)
		return (1);
	pid = ft_atoi(av[1]);
	msg = av[2];
	i = 0;
	signal(SIGUSR1, sig_handler);
	ft_printf("client: (%d)\n", pid);
	while (msg[i] != '\0')
	{
		send_char(pid, msg[i]);
		i ++;
	}
	ft_printf("Message Sent Successfully");
	return (0);
}
