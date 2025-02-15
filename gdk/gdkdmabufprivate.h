#pragma once

#include "gdkdmabufformatsbuilderprivate.h"

#define GDK_DMABUF_MAX_PLANES 4

typedef struct _GdkDmabuf GdkDmabuf;
typedef struct _GdkDmabufDownloader GdkDmabufDownloader;

struct _GdkDmabuf
{
  guint32 fourcc;
  guint64 modifier;
  unsigned int n_planes;
  struct {
    int fd;
    unsigned int stride;
    unsigned int offset;
  } planes[GDK_DMABUF_MAX_PLANES];
};

struct _GdkDmabufDownloader
{
  const char *name;
  gboolean              (* add_formats)                         (const GdkDmabufDownloader      *downloader,
                                                                 GdkDisplay                     *display,
                                                                 GdkDmabufFormatsBuilder        *builder);
  gboolean              (* supports)                            (const GdkDmabufDownloader      *downloader,
                                                                 GdkDisplay                     *display,
                                                                 const GdkDmabuf                *dmabuf,
                                                                 gboolean                        premultiplied,
                                                                 GdkMemoryFormat                *out_format,
                                                                 GError                        **error);
  void                  (* download)                            (const GdkDmabufDownloader      *downloader,
                                                                 GdkTexture                     *texture,
                                                                 GdkMemoryFormat                 format,
                                                                 guchar                         *data,
                                                                 gsize                           stride);
};

#ifdef HAVE_DMABUF

const GdkDmabufDownloader * gdk_dmabuf_get_direct_downloader    (void) G_GNUC_CONST;
const GdkDmabufDownloader * gdk_dmabuf_get_egl_downloader       (void) G_GNUC_CONST;

gboolean                    gdk_dmabuf_sanitize                 (GdkDmabuf                      *dest,
                                                                 gsize                           width,
                                                                 gsize                           height,
                                                                 const GdkDmabuf                *src,
                                                                 GError                        **error);

gboolean                    gdk_dmabuf_is_disjoint              (const GdkDmabuf                *dmabuf);

GdkMemoryFormat             gdk_dmabuf_get_memory_format        (GdkDisplay *display,
                                                                 guint32     fourcc,
                                                                 gboolean    premultiplied);

#endif
