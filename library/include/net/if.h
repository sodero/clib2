#ifdef CLIB2_STUBS

#ifndef _IF_H
#define _IF_H

/* RFC 3493, POSIX.1-2001. */

#warning "STUB: net/if.h"

struct if_nameindex {
    unsigned int if_index;
    char *if_name;
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern unsigned int if_nametoindex(const char *ifname);
extern char *if_indextoname(unsigned int ifindex, char *ifname);
extern struct if_nameindex *if_nameindex(void);
extern void if_freenameindex(struct if_nameindex *ptr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IF_H */

#endif /* CLIB2_STUBS */
