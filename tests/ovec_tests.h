#ifndef __OXEY_VEC_TESTS_H
#define __OXEY_VEC_TESTS_H

#include <assert.h>
#include <stdio.h>
#include "../src/headers/ovec.h"

static void mul_three(void* i) { CAST(i, int) = CAST(i, int) * 3; }

static void test_vec() {
    vec_t vec = new_vec(10, sizeof(int));
    {
        int v = 10;
        push_vec(&vec, &v);
        v = 45;
        push_vec(&vec, &v);
    }

    assert(CAST(first_vec(&vec), int) == 10);
    assert(CAST(get_vec(&vec, 1), int) == 45);
    assert(CAST(get_vec(&vec, 1), int) == CAST(last_vec(&vec), int));
    assert(get_vec(&vec, 100) == NULL);
    assert(len_vec(&vec) == 2);
    assert(capacity_vec(&vec) == 10);
    assert(elem_size_vec(&vec) == sizeof(int));
    
    vec_t clone = clone_vec(&vec);
    
    for (int i = 0; i < 10; ++i) {
        push_vec(&clone, &i);
    }
    
    assert(!eq_vec(&vec, &clone));
    assert(capacity_vec(&clone) != capacity_vec(&vec));
    
    for (int i = 9; i >= 0; --i) {
        assert(CAST(pop_vec(&clone), int) == i);
    }

    assert(pop_vec(&clone));
    assert(pop_vec(&clone));
    
    assert(len_vec(&clone) == 0);
    assert(pop_vec(&clone) == NULL);
    assert(pop_vec(&clone) == NULL);
    
    int v = 5;
    set_vec(&vec, &v, 1);
    
    assert(CAST(get_vec(&vec, 1), int) == v);
    
    free_vec(&clone, NULL);
    vec_t clone2 = clone_vec(&vec);
    
    assert(eq_vec(&vec, &clone2));
    
    insert_vec(&vec, &v, 1);
    
    assert(len_vec(&vec) == 3);
    assert(CAST(get_vec(&vec, 1), int) == CAST(get_vec(&vec, 2), int));
    
    remove_vec(&vec, 1);
    
    assert(len_vec(&vec) == 2);
    assert(eq_vec(&vec, &clone2));
    
    append_vec(&vec, &clone2);
    
    assert(len_vec(&vec) == len_vec(&clone2) * 2);
    assert(CAST(get_vec(&vec, 1), int) == CAST(get_vec(&vec, 3), int));
    
    reserve_vec(&vec, 20);
    
    assert(len_vec(&vec) == 4);
    assert(capacity_vec(&vec) == 20);
    
    resize_vec(&vec, 3);
    
    assert(len_vec(&vec) == 3);
    assert(capacity_vec(&vec) == 3);
    
    resize_vec(&vec, 10);
    
    assert(len_vec(&vec) == 3);
    assert(capacity_vec(&vec) == 10);
    
    push_vec(&vec, &v);
    free_vec(&clone2, NULL);
    vec_t clone3 = clone_vec(&vec);
    
    map_vec(&vec, mul_three);
    
    vec_iter_t iter = iter_from_vec(&vec);
    
    for (int i = 0; i < len_vec(&vec); ++i) {
        assert(CAST(get_vec(&vec, i), int) == CAST(get_vec(&clone3, i), int) * 3);
        assert(CAST(get_vec(&vec, i), int) == CAST(iter_next(&iter), int));
    }
    
    assert(iter_next(&iter) == NULL);
    
    iter = iter_from_vec(&vec);
    
    assert(CAST(iter_peek(&iter), int) == CAST(iter_next(&iter), int));
    assert(CAST(iter_next(&iter), int) != CAST(iter_peek(&iter), int));
    
    clear_vec(&vec);
    
    assert(len_vec(&vec) == 0);
    
    printf("vector tests passed!\n");
}

#endif
