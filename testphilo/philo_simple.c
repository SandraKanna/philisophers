/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandra <sandra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:41:12 by sandra            #+#    #+#             */
/*   Updated: 2024/08/01 20:53:58 by sandra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//odd philos sleep (time_to_sleep /2)
// odd philos take right fork first
// even philosophers start eating
// even take the left fork first
//every philo should have their own flag for death and meals_ok
//an additional thread (watcher) should monitor from the main function
//mutex for forks (left and right) and for printing
//handle the case of only one philo because only one fork
//use a custom sleep/wait function for more precision
//additional protection: if philo is eating it cannot die