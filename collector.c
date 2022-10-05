/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgmira <sgmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:07:04 by sgmira            #+#    #+#             */
/*   Updated: 2022/10/05 11:34:22 by sgmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_free	*ft_newgarbage(void *ptr)
{
	t_free	*trash;

	trash = malloc(sizeof(t_free));
	if (!trash)
		return (NULL);
	trash->ptr = ptr;
	trash->next = NULL;
	return (trash);
}

void	ft_addbackthegarbe(t_free **lst, t_free *nv)
{
	t_free	*head;

	if (*lst)
	{
		head = *lst;
		head = ft_lstgarbage(head);
		head->next = nv;
	}
	else
		(*lst) = nv;
}

t_free	*ft_lstgarbage(t_free *lst)
{
	if (!lst)
		return (NULL);
	if (lst -> next == NULL)
		return (lst);
	return (ft_lstgarbage(lst->next));
}

void	ft_freegarbe(t_free *list)
{
	t_free	*tmp;
	t_free	*to_del;

	tmp = list;
	while (tmp)
	{
		if (tmp->ptr)
			free (tmp->ptr);
		to_del = tmp->next;
		free (tmp);
		tmp = to_del;
	}
}

void	exit_n_free(t_free *list, int exit_code)
{
	ft_freegarbe(list);
	system("leaks cub3d");
	exit(exit_code);
}
