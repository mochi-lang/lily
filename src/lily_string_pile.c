#include <string.h>

#include "lily_string_pile.h"

#include "lily_api_alloc.h"

lily_string_pile *lily_new_string_pile(void)
{
    lily_string_pile *sp = lily_malloc(sizeof(lily_string_pile));

    sp->buffer = lily_malloc(64);
    sp->size = 63;

    return sp;
}

void lily_free_string_pile(lily_string_pile *sp)
{
    lily_free(sp->buffer);
    lily_free(sp);
}

void lily_sp_insert(lily_string_pile *sp, char *new_str, uint16_t *pos)
{
    int want_size = *pos + 1 + strlen(new_str);
    if (sp->size < want_size) {
        while (sp->size < want_size)
            sp->size *= 2;

        char *new_buffer = lily_realloc(sp->buffer, sp->size);
        sp->buffer = new_buffer;
    }

    strcpy(sp->buffer + *pos, new_str);
    *pos = want_size;
}

char *lily_sp_get(lily_string_pile *sp, int pos)
{
    return sp->buffer + pos;
}
