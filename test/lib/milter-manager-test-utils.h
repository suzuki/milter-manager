/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) 2008  Kouhei Sutou <kou@cozmixng.org>
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __MILTER_MANAGER_TEST_UTILS_H__
#define __MILTER_MANAGER_TEST_UTILS_H__

#include <gcutter.h>

G_BEGIN_DECLS

const gchar *milter_manager_test_get_base_dir (void);

typedef struct _MilterManagerTestHeader
{
    guint index;
    gchar *name;
    gchar *value;
} MilterManagerTestHeader;

MilterManagerTestHeader *milter_manager_test_header_new
                                                (guint index,
                                                 const gchar *name,
                                                 const gchar *value);
void                     milter_manager_test_header_free
                                                (MilterManagerTestHeader *header);
void                     milter_manager_test_header_inspect_without_index
                                                (GString *string,
                                                 MilterManagerTestHeader *header,
                                                 gpointer user_data);
void                     milter_manager_test_header_inspect
                                                (GString *string,
                                                 MilterManagerTestHeader *header,
                                                 gpointer user_data);
gboolean                 milter_manager_test_header_equal
                                                (MilterManagerTestHeader *header_a,
                                                 MilterManagerTestHeader *header_b);
gint                     milter_manager_test_header_compare
                                                (MilterManagerTestHeader *header_a,
                                                 MilterManagerTestHeader *header_b);

typedef struct _MilterManagerTestValueWithParam
{
    gchar *value;
    gchar *param;
} MilterManagerTestValueWithParam;

MilterManagerTestValueWithParam *milter_manager_test_value_with_param_new
                                        (const gchar *value,
                                         const gchar *param);
void                     milter_manager_test_value_with_param_free
                                        (MilterManagerTestValueWithParam *value);
void                     milter_manager_test_value_with_param_inspect_without_index
                                        (GString *string,
                                         MilterManagerTestValueWithParam *value,
                                         gpointer user_data);
void                     milter_manager_test_value_with_param_inspect
                                        (GString *string,
                                         MilterManagerTestValueWithParam *value,
                                         gpointer user_data);
gboolean                 milter_manager_test_value_with_param_equal
                                        (MilterManagerTestValueWithParam *value_a,
                                         MilterManagerTestValueWithParam *value_b);


G_END_DECLS

#endif /* __MILTER_MANAGER_TEST_UTILS_H__ */

/*
vi:ts=4:nowrap:ai:expandtab:sw=4
*/
