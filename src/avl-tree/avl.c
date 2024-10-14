#include <stddef.h>

#include "avl.h"
#include "node.h"

void avl_init(struct AvlTree * const self) {
    self->root = NULL;
}

struct AvlTree avl_create() {
    struct AvlTree self;
    avl_init(&self);
    return self;
}

void avl_insert(struct AvlTree * const self, const size_t data) {
    self->root = node_insert(self->root, data);
}
