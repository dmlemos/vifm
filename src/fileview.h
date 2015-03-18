/* vifm
 * Copyright (C) 2015 xaizek.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef VIFM__FILEVIEW_H__
#define VIFM__FILEVIEW_H__

#include "ui/ui.h"

/* Initialization/termination functions. */

/* Initializes file view unit. */
void fview_init(void);

/* Initializes view once before. */
void fview_view_init(FileView *view);

/* Resets view state partially. */
void fview_view_reset(FileView *view);

/* Appearance related functions. */

void draw_dir_list(FileView *view);

/* Redraws directory list without any extra actions that are performed in
 * draw_dir_list(). */
void draw_dir_list_only(FileView *view);

/* Updates view (maybe postponed) on the screen (redraws file list and
 * cursor) */
void redraw_view(FileView *view);

/* Updates view immediately on the screen (redraws file list and cursor). */
void redraw_view_imm(FileView *view);

/* Updates current view (maybe postponed) on the screen (redraws file list and
 * cursor) */
void redraw_current_view(void);

void erase_current_line_bar(FileView *view);

/* Returns non-zero if redraw is needed. */
int move_curr_line(FileView *view);

/* Redraws cursor of the view on the screen. */
void fview_cursor_redraw(FileView *view);

/* Adds inactive cursor mark to the view. */
void put_inactive_mark(FileView *view);

/* Viewport related functions. */

/* Returns non-zero if all files are visible, so no scrolling is needed. */
int all_files_visible(const FileView *view);

/* Returns index of last visible file in the view.  Value returned may be
 * greater than or equal to number of files in the view, which should be
 * threated correctly. */
size_t get_last_visible_file(const FileView *view);

/* Returns window top position adjusted for 'scrolloff' option. */
size_t get_window_top_pos(const FileView *view);

/* Returns window middle position adjusted for 'scrolloff' option. */
size_t get_window_middle_pos(const FileView *view);

/* Returns window bottom position adjusted for 'scrolloff' option. */
size_t get_window_bottom_pos(const FileView *view);

/* Scrolling related functions. */

/* Returns non-zero in case view can be scrolled up (there are more files). */
int can_scroll_up(const FileView *view);

/* Returns non-zero in case view can be scrolled down (there are more files). */
int can_scroll_down(const FileView *view);

/* Scrolls view up at least by specified number of files.  Updates both top and
 * cursor positions. */
void scroll_up(FileView *view, size_t by);

/* Scrolls view down at least by specified number of files.  Updates both top
 * and cursor positions. */
void scroll_down(FileView *view, size_t by);

/* Returns new list position after making correction for scrolling down. */
int get_corrected_list_pos_down(const FileView *view, size_t pos_delta);

/* Returns new list position after making correction for scrolling up. */
int get_corrected_list_pos_up(const FileView *view, size_t pos_delta);

/* Updates current and top line of a view according to scrolloff option value.
 * Returns non-zero if redraw is needed. */
int consider_scroll_offset(FileView *view);

/* Scrolls view down or up at least by specified number of files.  Updates both
 * top and cursor positions.  A wrapper for scroll_up() and scroll_down()
 * functions. */
void scroll_by_files(FileView *view, ssize_t by);

/* Recalculates difference of two panes scroll positions. */
void update_scroll_bind_offset(void);

/* Layout related functions. */

/* Enables/disables ls-like style of the view. */
void fview_set_lsview(FileView *view, int enabled);

/* Returns number of columns in the view. */
size_t calculate_columns_count(FileView *view);

/* Callback-like function which triggers some view-specific updates after
 * directory of the view changes. */
void fview_dir_updated(FileView *view);

/* Callback-like function which triggers some view-specific updates after list
 * of files changes. */
void fview_list_updated(FileView *view);

/* Callback-like function which triggers some view-specific updates after cursor
 * position in the list changed. */
void fview_position_updated(FileView *view);

/* Callback-like function which triggers some view-specific updates after view
 * sorting changed. */
void fview_sorting_updated(FileView *view);

#endif /* VIFM__FILEVIEW_H__ */

/* vim: set tabstop=2 softtabstop=2 shiftwidth=2 noexpandtab cinoptions-=(0 : */
/* vim: set cinoptions+=t0 : */
