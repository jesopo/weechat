/*
 * relay-info.c - info and infolist hooks for relay plugin
 *
 * Copyright (C) 2003-2018 Sébastien Helleu <flashcode@flashtux.org>
 *
 * This file is part of WeeChat, the extensible chat client.
 *
 * WeeChat is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * WeeChat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WeeChat.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>

#include "../weechat-plugin.h"
#include "relay.h"
#include "relay-client.h"


/*
 * Returns relay info "relay_client_count".
 */

const char *
relay_info_info_relay_client_count_cb (const void *pointer, void *data,
                                       const char *info_name,
                                       const char *arguments)
{
    static char str_count[32];
    int count, status;
    struct t_relay_client *ptr_client;

    /* make C compiler happy */
    (void) pointer;
    (void) data;
    (void) info_name;

    str_count[0] = '\0';
    count = relay_client_count;
    if (arguments && arguments[0])
    {
        status = relay_client_status_search (arguments);
        if (status < 0)
            return NULL;
        count = 0;
        for (ptr_client = relay_clients; ptr_client;
             ptr_client = ptr_client->next_client)
        {
            if ((int)ptr_client->status == status)
                count++;
        }
    }
    snprintf (str_count, sizeof (str_count), "%d", count);
    return str_count;

    return NULL;
}

/*
 * Returns relay infolist "relay".
 */

struct t_infolist *
relay_info_infolist_relay_cb (const void *pointer, void *data,
                              const char *infolist_name,
                              void *obj_pointer, const char *arguments)
{
    struct t_infolist *ptr_infolist;
    struct t_relay_client *ptr_client;

    /* make C compiler happy */
    (void) pointer;
    (void) data;
    (void) infolist_name;
    (void) arguments;

    if (obj_pointer && !relay_client_valid (obj_pointer))
        return NULL;

    ptr_infolist = weechat_infolist_new ();
    if (!ptr_infolist)
        return NULL;

    if (obj_pointer)
    {
        /* build list with only one relay */
        if (!relay_client_add_to_infolist (ptr_infolist, obj_pointer))
        {
            weechat_infolist_free (ptr_infolist);
            return NULL;
        }
        return ptr_infolist;
    }
    else
    {
        /* build list with all relays */
        for (ptr_client = relay_clients; ptr_client;
             ptr_client = ptr_client->next_client)
        {
            if (!relay_client_add_to_infolist (ptr_infolist, ptr_client))
            {
                weechat_infolist_free (ptr_infolist);
                return NULL;
            }
        }
        return ptr_infolist;
    }

    return NULL;
}

/*
 * Hooks infolist for relay plugin.
 */

void
relay_info_init ()
{
    /* info hooks */
    weechat_hook_info (
        "relay_client_count",
        N_("number of clients for relay"),
        /* TRANSLATORS: please do not translate the status names, they must be used in English */
        N_("status name (optional): connecting, waiting_auth, "
           "connected, auth_failed, disconnected"),
        &relay_info_info_relay_client_count_cb, NULL, NULL);

    /* infolist hooks */
    weechat_hook_infolist (
        "relay", N_("list of relay clients"),
        N_("relay pointer (optional)"),
        NULL,
        &relay_info_infolist_relay_cb, NULL, NULL);
}
