#include "headers/str_int_map.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FNV 1A 64-bit algorithm from wikipedia:
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
// Adapted for use on null-terminated strings
size_t inline hash_str(const char* key) {
    uint8_t* str = (uint8_t*)key;
    size_t h = FNV_OFFSET_BASIS;

    uint8_t p;
    while ((p = *str++)) {
        h = (h ^ p) * FNV_PRIME;
    }

    return h;
}

// Just strcmp internally
int inline cmp_str(const char* lhs, const char* rhs) { return strcmp(lhs, rhs); }

map_t inline new_map() {
    return (map_t){
        .capacity = DEFAULT_MAP_CAPACITY,
        .len = 0,
        .buckets = (bucket_t*)calloc(DEFAULT_MAP_CAPACITY, sizeof(bucket_t)),
    };
}

static inline map_t new_map_with_capacity(size_t capacity) {
    return (map_t){
        .capacity = capacity,
        .len = 0,
        .buckets = (bucket_t*)calloc(capacity, sizeof(bucket_t)),
    };
}

static size_t* get_bucket(const bucket_t* bucket, const char* key) {
    if (bucket == NULL) {
        return NULL;
    }

    do {
        if (bucket->key == NULL) {
            printf("key is null while trying to get something\n");
            return NULL;
        }
        if (cmp_str(bucket->key, key) == 0) {
            return (size_t*)&bucket->value;
        }
    } while ((bucket = bucket->next));

    printf("Went through bucket without finding anything\n");
    return NULL;
}

size_t* get_map(const map_t* map, const char* key) {
    size_t idx = hash_str(key) % map->capacity;

    return get_bucket(&map->buckets[idx], key);
}

static bool insert_bucket(bucket_t* bucket, const char* key, size_t value) {
    if (bucket == NULL) {
        *bucket = (bucket_t){.key = strdup(key), .value = value, .prev = NULL, .next = NULL};
        return true;
    }

    do {
        if (bucket->key == NULL) {
            bucket->key = strdup(key);
            bucket->value = value;
            return true;
        }
        if (cmp_str(bucket->key, key) == 0) {
            return false;
        }
        if (bucket->next == NULL) {
            bucket_t* new = (bucket_t*)malloc(1 * sizeof(bucket_t));

            new->key = strdup(key);
            new->value = value;

            new->prev = bucket;
            bucket->next = new;

            return true;
        }
    } while ((bucket = bucket->next));

    // should be unreachable
    exit(1);
}

bool insert_map(map_t* map, const char* key, size_t value) {
    if (map->capacity / 4 * 3 < map->len) {
        map_t new = new_map_with_capacity(map->capacity * 2);

        bucket_t* bucket;
        for (size_t i = 0; i < map->capacity; ++i) {
            bucket = &map->buckets[i];
            do {
                if (bucket->key != NULL) {
                    insert_map(&new, bucket->key, bucket->value);
                }
            } while ((bucket = bucket->next));
        }

        printf("growing\n");

        free_map(map);
        *map = new;
    }

    size_t idx = hash_str(key) % map->capacity;

    if (insert_bucket(&map->buckets[idx], key, value)) {
        map->len++;
        return true;
    }
    return false;
}

static bool remove_bucket(bucket_t* bucket, const char* key) {
    if (bucket == NULL) {
        return false;
    }

    do {
        if (bucket->key == NULL) {
            printf("key is null while trying to remove something\n");
            return false;
        }
        if (cmp_str(bucket->key, key) == 0) {
            free((void*)bucket->key);
            bucket->key = NULL;
            bucket->value = 0;

            if (bucket->prev == NULL) {
                if (bucket->next != NULL) {
                    bucket->key = bucket->next->key;
                    bucket->value = bucket->next->value;
                    bucket->next = bucket->next->next;
                }
            } else {
                // if bucket->prev isn't NULL
                bucket->prev->next = bucket->next;

                if (bucket->next != NULL) {
                    bucket->next->prev = bucket->prev;
                }
            }

            return true;
        }
    } while ((bucket = bucket->next));

    printf("Went through bucket without finding anything\n");
    return false;
}

bool remove_map(map_t* map, const char* key) {
    size_t idx = hash_str(key) % map->capacity;

    return remove_bucket(&map->buckets[idx], key);
}

void clear_map(map_t* map) {
    free_map(map);
    *map = new_map();
}

static void free_bucket(bucket_t* bucket) {
    assert(bucket != NULL);

    do {
        if (bucket->key != NULL) {
            free((void*)bucket->key);
        }
    } while ((bucket = bucket->next));
}

void free_map(map_t* map) {
    assert(map != NULL);

    if (map->buckets == NULL) {
        return;
    }

    for (size_t i = 0; i < map->capacity; ++i) {
        free_bucket(&map->buckets[i]);
    }

    free(map->buckets);
    map = NULL;
}

map_iter_t iter_from_map(const map_t* map) {
    assert(map != NULL);

    const bucket_t* end = &map->buckets[map->capacity - 1];

    return (map_iter_t){
        .ptr = map->buckets,
        .end = end,
        .bucket_idx = 0,
    };
}

kv map_iter_peek(const map_iter_t* iter) {
    assert(iter != NULL);

    bucket_t* ptr = (bucket_t*)iter->ptr;

    while (ptr->key == NULL && ptr != iter->end) {
        ptr++;
    }
    if (ptr == iter->end) {
        return (kv){.key = NULL, .value = 0};
    }
    for (size_t i = 0; i < iter->bucket_idx; ++i) {
        if (ptr->next != NULL) {
            ptr = ptr->next;
        } else {
            printf("BLOW THIS BUILDING UP NOW\n");
            exit(1);
        }
    }
    return (kv){.key = (char*)ptr->key, .value = ptr->value};
}

kv map_iter_next(map_iter_t* iter) {
    assert(iter != NULL);

    // printf("bucket idx: %lu\n", iter->bucket_idx);

    bucket_t* bucketptr = (bucket_t*)iter->ptr;

    while (bucketptr->key == NULL && bucketptr != iter->end) {
        bucketptr++;
    }
    if (bucketptr == iter->end) {
        return (kv){.key = NULL, .value = 0};
    }
    for (size_t i = 0; i < iter->bucket_idx; ++i) {
        if (bucketptr->next != NULL) {
            bucketptr = bucketptr->next;
        } else {
            printf("BLOW THIS BUILDING UP NOW\n");
            exit(1);
        }
    }
    if (bucketptr->next != NULL) {
        // printf("incr bucket idx\n");
        iter->bucket_idx++;
    } else {
        // printf("incr pointer\n");
        iter->bucket_idx = 0;
        iter->ptr++;
    }
    return (kv){.key = bucketptr->key, .value = bucketptr->value};
}
