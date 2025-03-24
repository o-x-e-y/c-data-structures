// #ifndef __OXEY_MAP_H
// #define __OXEY_MAP_H

// #include <stdbool.h>
// #include <stdlib.h>
// #include <string.h>

// #include "util.h"

// #define FNV_OFFSET_BASIS 0xcbf29ce484222325ULL
// #define FNV_PRIME 0x100000001b3ULL

// typedef struct ref_t {
//     void* ptr;
//     size_t len;
// } ref_t;

// typedef struct key_value_t {
//     void* key;
//     void* value;
// } key_value_t;

// typedef struct bucket_t {
//     void* key;
//     void* value;
//     struct bucket_t* prev;
//     struct bucket_t* next;
// } bucket_t;

// typedef struct map_t {
//     size_t key_size;
//     size_t value_size;
//     size_t capacity;
//     size_t len;
//     size_t (*hash)(const struct map_t*, const void*);
//     bool (*eq)(const struct map_t*, const void*, const void*);
//     bucket_t* buckets;
// } map_t;

// typedef struct map_iter_t {
//     bucket_t* ptr;
//     const bucket_t* end;
// } map_iter_t;

// // FNV 1A 64-bit algorithm from wikipedia:
// // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
// size_t value_hash(const map_t* self, const void* key);

// // FNV 1A 64-bit algorithm from wikipedia:
// // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
// // Adapted for use on null-terminated strings
// size_t string_hash(const map_t* self, const void* key);

// bool value_eq(const map_t* self, const void* lhs, const void* rhs);
// bool string_eq(const map_t* self, const void* lhs, const void* rhs);

// #define new_map(key_type, value_type)                                                             \
//     (map_t) {                                                                                     \
//         .key_size = sizeof(key_type), .value_size = sizeof(value_type), .capacity = 32, .len = 0, \
//         .hash = value_hash, .eq = value_eq, .buckets = (bucket_t*)calloc(32, sizeof(bucket_t))                \
//     }

// size_t inline capacity_map(const map_t* map) { return map->capacity; }
// size_t inline len_map(const map_t* map) { return map->len; }

// ref_t get_map(const map_t* map, const void* key, size_t key_len);
// bool insert_map(const map_t* map, const void* key, size_t key_len, const void* value,
//                 size_t value_len);
// bool remove_map(map_t* map, const void* key);
// void clear_map(map_t* map);
// void free_map(map_t* map);

// #endif
