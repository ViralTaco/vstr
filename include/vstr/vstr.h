#ifndef VT_VSTR_H
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * vstr.h:                                               *
 * Copyright (c) 2020 viraltaco_ (viraltaco@gmx.com)     *
 * https://github.com/ViralTaco                          *
 * SPDX-License-Identifier: MIT                          *
 * <http://www.opensource.org/licenses/MIT>              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define VT_VSTR_H "1.1.2"
#include <stdbool.h> // bool, true, false
#include <iso646.h>  // and, or, not
#include <stddef.h>  // size_t
#include <stdlib.h>  // exit, EXIT_FAILURE
#include <string.h>  // strncmp, strlen
#include <stdio.h>   // puts, printf, perror

#define V_ATTR(...) __attribute__((__VA_ARGS__))
#define V_func extern
typedef char const*  c_str;
typedef char *const* c_ptr;
typedef struct vstr {
        c_str  data;
        c_ptr  begin;
        c_ptr  end;
        size_t length;
} vstr;

V_ATTR(pure) V_func
bool V_eqs(const vstr a, c_str b, const size_t len) {
        return len == a.length
           and strncmp(a.data, b, len) == 0;
}

V_ATTR(always_inline, pure) V_func inline
vstr V_init(c_str s, const size_t len) {
        return (vstr) {
                .data     = s,
                .begin    = (c_ptr) s,
                .end      = (c_ptr) (s + len),
                .length   = len - 1,
        };
}

V_func void V_put(const vstr s) {
        if (puts(s.data) == EOF) {
                perror("Error V_puts(const vstr):\n\t"
                       "puts(s.data)' returned EOF");
                exit(EXIT_FAILURE);
        }
}

#define V_eq(v, s) V_eqs((v), (s), strlen(s))
#define V_s(s) V_init(s, sizeof (s))
#define V_for(x, in)                                                           \
        for (__typeof__(x)* it = (in).begin, (x) = *it;                        \
             it != (in).end;                                                   \
             ++it, (x) = *it)
#define V_puts(str) _Generic((str),                                            \
                vstr:       V_put,                                             \
                default:    puts                                               \
        ) (str)
        
#endif // VT_VSTR_H
