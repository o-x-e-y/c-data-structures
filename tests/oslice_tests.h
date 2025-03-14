#ifndef __OXEY_SLICE_TESTS_H
#define __OXEY_SLICE_TESTS_H

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/headers/oslice.h"

static void test_slice() {
    const char* cstr = "WHAT";
    
    slice_t slice = from_cstr_slice(cstr, strlen(cstr));
    string_t str = from_cstr_str(cstr, strlen(cstr)); 
    slice_t slice2 = from_str_slice(&str);
    slice_t slice3 = copy_slice(&slice);
    
    assert(eq_slice(&slice, &slice2));
    assert(eq_slice(&slice, &slice3));
    assert(eq_str_slice(&slice, &str));
    assert(eq_cstr_slice(&slice, cstr, strlen(cstr)));
    
    assert(len_slice(&slice) == slice.len);
    
    assert(first_slice(&slice) == cstr[0]);
    assert(last_slice(&slice) == cstr[strlen(cstr) - 1]);
    
    printf("slice tests passed!\n");
}

#endif
