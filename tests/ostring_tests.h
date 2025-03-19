#ifndef __OXEY_STRING_TESTS_H
#define __OXEY_STRING_TESTS_H

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/headers/ostring.h"

static char charToUpper(char c) {
    return toupper(c);
}

static void test_string() {
    string_t str = new_str(10);

    push_str(&str, 'a');

    push_cstr_str(&str, "bc", strlen("bc"));
    
    assert(get_str(&str, 0) == 'a');
    assert(get_str(&str, 2) == 'c');
    assert(get_str(&str, 100) == 0);
    assert(first_str(&str) == get_str(&str, 0));
    assert(last_str(&str) == get_str(&str, len_str(&str) - 1));

    assert(len_str(&str) == 3);
    assert(capacity_str(&str) == 10);
    
    string_t clone = clone_str(&str);
    
    for (int i = 0; i < 10; ++i) {
        push_str(&clone, i + 48);
    }
    
    assert(!eq_str(&str, &clone));
    assert(capacity_str(&clone) != capacity_str(&str));
    assert(eq_cstr(&str, "abc", strlen("abc")));
    
    for (int i = 9; i >= 0; --i) {
        assert(pop_str(&clone) == i + 48);
    }

    assert(pop_str(&clone));
    assert(pop_str(&clone));
    assert(pop_str(&clone));
    
    assert(len_str(&clone) == 0);
    assert(pop_str(&clone) == 0);
    assert(pop_str(&clone) == 0);
    
    char c = 'e';
    set_str(&str, c, 1);
    
    assert(get_str(&str, 1) == c);
    
    free_str(&clone);
    clone = clone_str(&str);
    
    assert(eq_str(&str, &clone));

    insert_str(&str, c, 1);
    
    assert(len_str(&str) == 4);
    assert(get_str(&str, 1) == get_str(&str, 2));
    
    remove_str(&str, 1);
    
    assert(len_str(&str) == 3);
    assert(len_str(&clone) == 3);
    
    assert(eq_str(&str, &clone));
    
    push_str_str(&str, &clone);
    
    assert(len_str(&str) == len_str(&clone) * 2);
    assert(get_str(&str, 1) == get_str(&str, 4));
    
    reserve_str(&str, 20);
    
    assert(len_str(&str) == 6);
    assert(capacity_str(&str) == 20);
    
    resize_str(&str, 4);
    
    assert(len_str(&str) == 4);
    assert(capacity_str(&str) == 4);
    
    resize_str(&str, 10);
    
    assert(len_str(&str) == 4);
    assert(capacity_str(&str) == 10);
    
    push_str(&str, c);
    free_str(&clone);
    clone = clone_str(&str);
    
    map_str(&str, charToUpper);
    
    str_iter_t iter = iter_from_str(&str);
    
    for (int i = 0; i < len_str(&str); ++i) {
        assert(get_str(&str, i) == charToUpper(get_str(&clone, i)));
        assert(get_str(&str, i) == str_iter_next(&iter));
    }
    
    assert(str_iter_next(&iter) == 0);
    
    iter = iter_from_str(&str);
    
    assert(str_iter_peek(&iter) == str_iter_next(&iter));
    assert(str_iter_next(&iter) != str_iter_peek(&iter));
    
    free_str(&clone);
    clone = clone_str(&str);
    
    const char* cstr = as_cstr(&clone);
    char* cstr_clone = (char*)malloc(clone.len + 1);
    memcpy(cstr_clone, cstr, clone.len + 1);
    
    assert(strncmp(as_cstr(&str), cstr, str.len) == 0);
    
    // reverse_str(&str);
    // reverse_cstr(cstr_clone, clone.len);
    
    // assert(strncmp(as_cstr(&str), cstr, str.len) == 0);
    
    // print
    print_str(&str);
    printf("\n");
    
    free_str(&clone);
    clone = clone_str(&str);
    
    str_iter_t iter2 = iter_from_str(&str);
    
    assert(len_str(&clone) == 5);
    
    assert(str_iter_next(&iter2) == *clone.str++);
    assert(str_iter_next(&iter2) == *clone.str++);
    assert(str_iter_next(&iter2) == *clone.str++);
    
    assert(str_iter_peek(&iter2) == *clone.str);
    assert(str_iter_peek(&iter2) == *clone.str);    
    
    clear_str(&str);
    
    assert(len_str(&str) == 0);
    
    printf("string tests passed!\n");
}

#endif