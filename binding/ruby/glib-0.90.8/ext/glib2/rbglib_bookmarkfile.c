/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbglib_bookmarkfile.c -

  $Author: sakai $
  $Date: 2007/07/07 08:25:33 $

  Copyright (C) 2006 Masao Mutoh
************************************************/

#include "rbgprivate.h"

#if GLIB_CHECK_VERSION(2,12,0)
/************************************************/
static GBookmarkFile*
bookmarkfile_copy(const GBookmarkFile* file)
{
/*
  GBookmarkFile* new_file;
  g_return_val_if_fail (file != NULL, NULL);
  new_file = g_key_file_new();
  *new_file = (GBookmarkFile*)*file;
  return new_file;
*/
    return (GBookmarkFile*)file;
}


GType
g_bookmark_file_get_type(void)
{
    static GType our_type = 0;
    if (our_type == 0)
        our_type = g_boxed_type_register_static("GBookmarkFile",
                                                (GBoxedCopyFunc)bookmarkfile_copy,
                                                (GBoxedFreeFunc)g_bookmark_file_free);
    return our_type;
}
/************************************************/

#define G_TYPE_BOOKMARK_FILE (g_bookmark_file_get_type())
#define _SELF(self) ((GBookmarkFile*)(RVAL2BOXED(self, G_TYPE_BOOKMARK_FILE)))

static VALUE
bf_initialize(VALUE self)
{
    G_INITIALIZE(self, g_bookmark_file_new());
    return Qnil;
}

static VALUE
bf_load_from_file(VALUE self, VALUE filename)
{
    GError* error = NULL;
    gboolean ret = g_bookmark_file_load_from_file(_SELF(self),
                                                  RVAL2CSTRFILENAME(filename),
                                                  &error);
    if (!ret) RAISE_GERROR(error);
    return self;
}

static VALUE
bf_load_from_data(VALUE self, VALUE data)
{
    GError *error = NULL;

    StringValue(data);
    if (!g_bookmark_file_load_from_data(_SELF(self),
					RSTRING_PTR(data),
					RSTRING_LEN(data),
					&error))
	RAISE_GERROR(error);

    return Qnil;
}

static VALUE
bf_load_from_data_dirs(VALUE self, VALUE file)
{
    GError* error = NULL;
    gboolean ret;
    gchar* full_path;

    ret = g_bookmark_file_load_from_data_dirs(_SELF(self), 
                                              (const gchar*)RVAL2CSTR(file),
                                              &full_path, &error);

    if (! ret) RAISE_GERROR(error);

    return full_path ? CSTR2RVAL(full_path) : Qnil;
}

static VALUE
bf_to_data(VALUE self)
{
    GError* error = NULL;
    gchar* data = g_bookmark_file_to_data(_SELF(self), NULL, &error);

    if (error) RAISE_GERROR(error);
    
    return CSTR2RVAL_FREE(data);
}

static VALUE
bf_to_file(VALUE self, VALUE filename)
{
    GError* error = NULL;
    gboolean ret = g_bookmark_file_to_file(_SELF(self),
                                           RVAL2CSTRFILENAME(filename),
                                           &error);
    if (!ret) RAISE_GERROR(error);
    return self;
}

static VALUE
bf_has_item(VALUE self, VALUE uri)
{
    return CBOOL2RVAL(g_bookmark_file_has_item(_SELF(self),
                                               (const gchar *)RVAL2CSTR(uri))); 
}

static VALUE
bf_has_group(VALUE self, VALUE uri, VALUE group)
{
    GError* error = NULL;
    return CBOOL2RVAL(g_bookmark_file_has_group(_SELF(self),
                                                (const gchar *)RVAL2CSTR(uri),
                                                (const gchar *)RVAL2CSTR(group),
                                                &error));
}
	                                           
static VALUE
bf_has_application(VALUE self, VALUE uri, VALUE name)
{
    GError* error = NULL;
    return CBOOL2RVAL(g_bookmark_file_has_application(_SELF(self),
                                                      (const gchar *)RVAL2CSTR(uri),
                                                      (const gchar *)RVAL2CSTR(name),
                                                      &error));
}
	                                           
static VALUE
bf_get_size(VALUE self)
{
    return INT2NUM(g_bookmark_file_get_size(_SELF(self)));
}

static VALUE
bf_get_uris(VALUE self)
{
    int i;
    gsize len;
    VALUE ary = rb_ary_new();
    gchar** ret = g_bookmark_file_get_uris(_SELF(self), &len);
	
    for (i = 0; i < len; i++){
        rb_ary_push(ary, CSTR2RVAL(ret[i]));
    }
	
    g_strfreev(ret);
	
    return ary;
}

static VALUE
bf_get_title(VALUE self, VALUE uri)
{
    GError *error = NULL;
    gchar* ret = g_bookmark_file_get_title(_SELF(self),
                                           (const gchar *)RVAL2CSTR(uri),
                                           &error);
    if (error) RAISE_GERROR(error);
    return CSTR2RVAL_FREE(ret);
}

static VALUE
bf_get_description(VALUE self, VALUE uri)
{
    GError *error = NULL;
    gchar* ret = g_bookmark_file_get_description(_SELF(self),
                                                 (const gchar *)RVAL2CSTR(uri),
                                                 &error);
    if (error) RAISE_GERROR(error);
    return CSTR2RVAL_FREE(ret);
}

static VALUE
bf_get_mime_type(VALUE self, VALUE uri)
{
    GError *error = NULL;
    gchar* ret = g_bookmark_file_get_mime_type(_SELF(self),
                                               (const gchar *)RVAL2CSTR(uri),
                                               &error);
    if (error) RAISE_GERROR(error);
    return CSTR2RVAL_FREE(ret);
}

static VALUE
bf_get_is_private(VALUE self, VALUE uri)
{
    GError *error = NULL;
    gboolean ret = g_bookmark_file_get_is_private(_SELF(self),
                                                  (const gchar *)RVAL2CSTR(uri),
                                                  &error);
    if (error) RAISE_GERROR(error);
    return CBOOL2RVAL(ret);
}

static VALUE
bf_get_icon(VALUE self, VALUE uri)
{
    gchar* href;
    gchar* mime_type;
    GError *error = NULL;
    gboolean ret = g_bookmark_file_get_icon(_SELF(self),
                                            (const gchar *)RVAL2CSTR(uri),
                                            &href, &mime_type,
                                            &error);
    if (!ret){
        if (error) RAISE_GERROR(error);
        return Qnil;
    }
    return rb_assoc_new(CSTR2RVAL_FREE(href), CSTR2RVAL_FREE(mime_type)); 
}

static VALUE
bf_get_added(VALUE self, VALUE uri)
{
    GError *error = NULL;
    time_t ret = g_bookmark_file_get_added(_SELF(self),
                                           (const gchar *)RVAL2CSTR(uri),
                                           &error);
    if (!ret) RAISE_GERROR(error);

    return rb_time_new(ret, 0);
}

static VALUE
bf_get_modified(VALUE self, VALUE uri)
{
    GError *error = NULL;
    time_t ret = g_bookmark_file_get_modified(_SELF(self),
                                              (const gchar *)RVAL2CSTR(uri),
                                              &error);
    if (!ret) RAISE_GERROR(error);

    return rb_time_new(ret, 0);
}

static VALUE
bf_get_visited(VALUE self, VALUE uri)
{
    GError *error = NULL;
    time_t ret = g_bookmark_file_get_visited(_SELF(self),
                                             (const gchar *)RVAL2CSTR(uri),
                                             &error);
    if (!ret) RAISE_GERROR(error);

    return rb_time_new(ret, 0);
}

static VALUE
bf_get_groups(VALUE self, VALUE uri)
{
    gsize length;
    VALUE ary;
    gint i;
    GError* error = NULL;
    gchar** ret = g_bookmark_file_get_groups(_SELF(self),
                                             (const gchar *)RVAL2CSTR(uri),
                                             &length, &error);
    if (error) RAISE_GERROR(error);
  

    ary = rb_ary_new();
    for(i = 0; i < length; i++){
        rb_ary_push(ary, CSTR2RVAL(ret[i]));
    }

    g_strfreev(ret);
    return ary;
}

static VALUE
bf_get_applications(VALUE self, VALUE uri)
{
    gsize length;
    VALUE ary;
    gint i;
    GError* error = NULL;
    gchar** ret = g_bookmark_file_get_applications(_SELF(self),
                                                   (const gchar *)RVAL2CSTR(uri),
                                                   &length, &error);
    if (error) RAISE_GERROR(error);
  

    ary = rb_ary_new();
    for(i = 0; i < length; i++){
        rb_ary_push(ary, CSTR2RVAL(ret[i]));
    }

    g_strfreev(ret);
    return ary;
}
  
static VALUE
bf_get_app_info(VALUE self, VALUE uri, VALUE name)
{
    gchar* exec;
    guint count;
    time_t stamp;
    GError* error = NULL;

    gboolean ret = g_bookmark_file_get_app_info(_SELF(self),
                                                (const gchar *)RVAL2CSTR(uri),
                                                (const gchar *)RVAL2CSTR(name),
                                                &exec, &count, &stamp, &error);
    if (!ret) RAISE_GERROR(error);
    
    return rb_ary_new3(3, CSTR2RVAL(exec), UINT2NUM(count), rb_time_new(stamp, 0));
}

static VALUE
bf_set_title(VALUE self, VALUE uri, VALUE title)
{
    g_bookmark_file_set_title(_SELF(self),
                              (const gchar *)RVAL2CSTR(uri),
                              (const gchar *)RVAL2CSTR(title));
    return self;
}

static VALUE
bf_set_description(VALUE self, VALUE uri, VALUE description)
{
    g_bookmark_file_set_description(_SELF(self),
                                    (const gchar *)RVAL2CSTR(uri),
                                    (const gchar *)RVAL2CSTR(description));
    return self;
}

static VALUE
bf_set_mime_type(VALUE self, VALUE uri, VALUE mime_type)
{
    g_bookmark_file_set_mime_type(_SELF(self),
                                  (const gchar *)RVAL2CSTR(uri),
                                  (const gchar *)RVAL2CSTR(mime_type));
    return self;
}

static VALUE
bf_set_is_private(VALUE self, VALUE uri, VALUE is_private)
{
    g_bookmark_file_set_is_private(_SELF(self),
                                   (const gchar *)RVAL2CSTR(uri),
                                   RVAL2CBOOL(is_private));
    return self;
}

static VALUE
bf_set_icon(VALUE self, VALUE uri, VALUE href, VALUE mime_type)
{
    g_bookmark_file_set_icon(_SELF(self),
                             (const gchar *)RVAL2CSTR(uri),
                             (const gchar *)RVAL2CSTR(href),
                             (const gchar *)RVAL2CSTR(mime_type));
    return self;
}

static VALUE
bf_set_added(VALUE self, VALUE uri, VALUE time)
{
    g_bookmark_file_set_added(_SELF(self), 
                              (const gchar *)RVAL2CSTR(uri),
                              (time_t)NUM2LONG(rb_Integer(time)));
    return self;
}

static VALUE
bf_set_groups(VALUE self, VALUE uri, VALUE groups)
{
    gint len = RARRAY_LEN(groups);
    gchar** glist = ALLOCA_N(gchar*, len);
    gint i;

    for (i = 0; i < len; i++){
        glist[i] = RVAL2CSTR(RARRAY_PTR(groups)[i]);
    }
    
    g_bookmark_file_set_groups(_SELF(self),
                               (const gchar *)RVAL2CSTR(uri),
                               (const gchar **)glist, len);
    return self;
}

static VALUE
bf_set_modified(VALUE self, VALUE uri, VALUE time)
{
    g_bookmark_file_set_modified(_SELF(self), 
                                 (const gchar *)RVAL2CSTR(uri),
                                 (time_t)NUM2LONG(rb_Integer(time)));
    return self;
}

static VALUE
bf_set_visited(VALUE self, VALUE uri, VALUE time)
{
    g_bookmark_file_set_visited(_SELF(self), 
                                (const gchar *)RVAL2CSTR(uri),
                                (time_t)NUM2LONG(rb_Integer(time)));
    return self;
}

static VALUE
bf_set_app_info(VALUE self, VALUE uri, VALUE name, VALUE exec, VALUE count, VALUE stamp)
{
    GError* error = NULL;
    gboolean ret = g_bookmark_file_set_app_info(_SELF(self),
                                                (const gchar *)RVAL2CSTR(uri),
                                                (const gchar *)RVAL2CSTR(name),
                                                (const gchar *)RVAL2CSTR(exec),
                                                NUM2INT(count),
                                                (time_t)NUM2LONG(rb_Integer(stamp)),
                                                &error);
 
    if (! ret) RAISE_GERROR(error);

    return self;
}

static VALUE 
bf_add_group(VALUE self, VALUE uri, VALUE group)
{
    g_bookmark_file_add_group(_SELF(self),
                              (const gchar *)RVAL2CSTR(uri),
                              (const gchar *)RVAL2CSTR(group));
    return self;
}

static VALUE
bf_add_application(VALUE self, VALUE uri, VALUE name, VALUE exec)
{
    g_bookmark_file_add_application(_SELF(self),
                                    (const gchar *)RVAL2CSTR(uri),
                                    (const gchar *)RVAL2CSTR(name),
                                    (const gchar *)RVAL2CSTR(exec));
    return self;
}

static VALUE
bf_remove_group(VALUE self, VALUE uri, VALUE group)
{
    GError* error = NULL;
    gboolean ret = g_bookmark_file_remove_group(_SELF(self),
                                                (const gchar *)RVAL2CSTR(uri),
                                                (const gchar *)RVAL2CSTR(group),
                                                &error);
    if (! ret) RAISE_GERROR(error);

    return self;
}

static VALUE
bf_remove_application(VALUE self, VALUE uri, VALUE name)
{
    GError *error = NULL;
    gboolean ret = g_bookmark_file_remove_application(_SELF(self),
                                                      (const gchar *)RVAL2CSTR(uri),
                                                      (const gchar *)RVAL2CSTR(name),
                                                      &error);
    if (! ret) RAISE_GERROR(error);

    return self;
}


static VALUE
bf_remove_item(VALUE self, VALUE uri)
{
    GError *error = NULL;
    gboolean ret = g_bookmark_file_remove_item(_SELF(self),
                                               (const gchar *)RVAL2CSTR(uri),
                                               &error);
    if (! ret) RAISE_GERROR(error);

    return self;
}

static VALUE
bf_move_item(VALUE self, VALUE old_uri, VALUE new_uri)
{
    GError *error = NULL;
    gboolean ret = g_bookmark_file_move_item(_SELF(self),
                                             (const gchar *)RVAL2CSTR(old_uri),
                                             (const gchar *)RVAL2CSTR(new_uri),
                                             &error);
    if (! ret) RAISE_GERROR(error);

    return self;
}

#endif

void
Init_glib_bookmark_file()
{
#if GLIB_CHECK_VERSION(2,12,0)
    VALUE bf = G_DEF_CLASS(G_TYPE_BOOKMARK_FILE, "BookmarkFile", mGLib);

    G_DEF_ERROR(G_BOOKMARK_FILE_ERROR, "BookmarkFileError", mGLib, 
                rb_eRuntimeError, G_TYPE_BOOKMARK_FILE_ERROR);

    rb_define_method(bf, "initialize", bf_initialize, 0);
    rb_define_method(bf, "load_from_file", bf_load_from_file, 1);
    rb_define_method(bf, "load_from_data", bf_load_from_data, 1);
    rb_define_method(bf, "load_from_data_dirs", bf_load_from_data_dirs, 1);
    rb_define_method(bf, "to_data", bf_to_data, 0);
    rb_define_method(bf, "to_file", bf_to_file, 1);
    rb_define_method(bf, "has_item?", bf_has_item, 1);
    rb_define_method(bf, "has_group?", bf_has_group, 2);
    rb_define_method(bf, "has_application?", bf_has_application, 2);
    rb_define_method(bf, "size", bf_get_size, 0);
    rb_define_method(bf, "uris", bf_get_uris, 0);
    rb_define_method(bf, "get_title", bf_get_title, 1);
    rb_define_method(bf, "get_description", bf_get_description, 1);
    rb_define_method(bf, "get_mime_type", bf_get_mime_type, 1);
    rb_define_method(bf, "private?", bf_get_is_private, 1);
    rb_define_method(bf, "get_icon", bf_get_icon, 1);
    rb_define_method(bf, "get_added", bf_get_added, 1);
    rb_define_method(bf, "get_modified", bf_get_modified, 1);
    rb_define_method(bf, "get_visited", bf_get_visited, 1);
    rb_define_method(bf, "get_groups", bf_get_groups, 1);
    rb_define_method(bf, "get_applications", bf_get_applications, 1);
    rb_define_method(bf, "get_app_info", bf_get_app_info, 2);
    rb_define_method(bf, "set_title", bf_set_title, 2);
    rb_define_method(bf, "set_description", bf_set_description, 2);
    rb_define_method(bf, "set_mime_type", bf_set_mime_type, 2);
    rb_define_method(bf, "set_private", bf_set_is_private, 2);
    rb_define_method(bf, "set_icon", bf_set_icon, 3);
    rb_define_method(bf, "set_added", bf_set_added, 2);
    rb_define_method(bf, "set_groups", bf_set_groups, 2);
    rb_define_method(bf, "set_modified", bf_set_modified, 2);
    rb_define_method(bf, "set_visited", bf_set_visited, 2);
    rb_define_method(bf, "set_app_info", bf_set_app_info, 5);
    rb_define_method(bf, "add_group", bf_add_group, 2);
    rb_define_method(bf, "add_application", bf_add_application, 3);
    rb_define_method(bf, "remove_group", bf_remove_group, 2);
    rb_define_method(bf, "remove_application", bf_remove_application, 2);
    rb_define_method(bf, "remove_item", bf_remove_item, 1);
    rb_define_method(bf, "move_item", bf_move_item, 2);
#endif
}

