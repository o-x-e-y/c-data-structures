#ifndef __OXEY_MAP_TESTS_H
#define __OXEY_MAP_TESTS_H

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/headers/omap.h"
#include "../src/headers/str_int_map.h"

static void print_map(const map_t* map) {
    for (size_t i = 0; i < map->capacity; ++i) {
        bucket_t b = map->buckets[i];
        if (b.key == NULL && i < 10) {
            printf("%lu  NULL\n", i);
        } else if (b.key == NULL && i >= 10) {
            printf("%lu NULL\n", i);
        } else if (i < 10) {
            printf("%lu  '%s': %lu\n", i, b.key, b.value);
        } else {
            printf("%lu '%s': %lu\n", i, b.key, b.value);
        }
        while (b.next != NULL) {
            b = *b.next;
            if (i < 10) {
                printf("  %lu  '%s': %lu\n", i, b.key, b.value);
            } else {
                printf("  %lu '%s': %lu\n", i, b.key, b.value);
            }
        }
    }
}

static void test_map() {
    map_t map = new_map();
    
    assert(insert_map(&map, "string", 123));
    assert(insert_map(&map, "dof", 0));
    assert(insert_map(&map, "bofa", 0));
    assert(insert_map(&map, "oxey", 100));
    assert(insert_map(&map, ":oxey:", 5000));
    assert(insert_map(&map, "dofsmie", 1234));
    assert(!insert_map(&map, "dofsmie", 444));
    
    print_map(&map);
    
    remove_map(&map, "bofa");
    // remove_map(&map, ":oxey:");
    // remove_map(&map, "dofsmie");
    remove_map(&map, "string");
    
    print_map(&map);
    
    printf("'oxey': %lu\n", *get_map(&map, "oxey"));
    
    map_iter_t iter = iter_from_map(&map);
    // kv item = map_iter_peek(&iter);
    
    // assert(item.key != NULL);
    // printf("'%s': %lu\n", item.key, item.value);
    
    // kv item2 = map_iter_next(&iter);
    
    // assert(item2.key != NULL);
    // printf("'%s': %lu\n", item2.key, item2.value);
    
    // kv item3 = map_iter_next(&iter);
    
    // assert(item3.key != NULL);
    // printf("'%s': %lu\n", item3.key, item3.value);
    
    // printf("map tests passed!\n");
}

#endif
