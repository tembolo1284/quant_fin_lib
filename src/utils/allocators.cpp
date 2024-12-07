#include <cstdlib>
#include <cstring>
#include "quant_fin_lib.h"

struct qf_allocators_s {
    void *(*f_malloc)(size_t) = malloc;
    void *(*f_realloc)(void *, size_t) = realloc;
    void (*f_free)(void *) = free;
};

static struct qf_allocators_s _qf_allocators;

void qf_set_allocators(void *(*f_malloc)(size_t), void *(*f_realloc)(void *, size_t), void (*f_free)(void *)) {
    _qf_allocators.f_malloc = f_malloc;
    _qf_allocators.f_realloc = f_realloc;
    _qf_allocators.f_free = f_free;
}

void *qf_malloc(size_t size) {
    return _qf_allocators.f_malloc(size);
}

void qf_free(void *ptr) {
    _qf_allocators.f_free(ptr);
}

