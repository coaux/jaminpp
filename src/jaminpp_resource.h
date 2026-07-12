// custom header file for generated resource file
// see glib-compile-resources(1)

#ifndef JAMIN_RESOURCE_H
#define JAMIN_RESOURCE_H

#include <glib.h>
#include <gmodule.h>
#include <gio/gio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern G_MODULE_EXPORT
GResource* jaminpp_get_resource(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  // JAMIN_RESOURCE_H
