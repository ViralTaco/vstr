#include "include/vstr/vstr.h"

int main(void) {
    const vstr foo = V_s("Hello, World!");
    c_str bar = "Hello, World!";
    V_puts(foo);
    V_puts(V_eq(foo, bar) ? "Yep." : "Nope");
    exit(EXIT_SUCCESS);
}
