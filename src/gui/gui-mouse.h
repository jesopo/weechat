/*
 * Copyright (C) 2011 Sebastien Helleu <flashcode@flashtux.org>
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

#ifndef __WEECHAT_GUI_MOUSE_H
#define __WEECHAT_GUI_MOUSE_H 1

/* mouse variables */

extern int gui_mouse_enabled;
extern int gui_mouse_debug;
extern int gui_mouse_grab;
extern int gui_mouse_event_index;
extern int gui_mouse_event_x[2];
extern int gui_mouse_event_y[2];
extern char gui_mouse_event_button;

/* mouse functions */

extern void gui_mouse_debug_toggle ();
extern void gui_mouse_reset_event ();

/* mouse functions (GUI dependent) */

extern void gui_mouse_enable ();
extern void gui_mouse_disable ();
extern void gui_mouse_display_state ();
extern void gui_mouse_grab_init ();
extern const char *gui_mouse_grab_code2key (const char *code);
extern void gui_mouse_grab_end ();

#endif /* __WEECHAT_GUI_MOUSE_H */
