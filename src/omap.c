// #include "headers/omap.h"

// #include <assert.h>
// #include <stdlib.h>
// #include <string.h>

// // FNV 1A 64-bit algorithm from wikipedia:
// // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
// size_t value_hash(const map_t* self, const void* key) {
//     uint8_t* p = (uint8_t*)key;
//     size_t h = FNV_OFFSET_BASIS;

//     for (size_t i = 0; i < self->key_size; i++) {
//         h = (h ^ p[i]) * FNV_PRIME;
//     }

//     return h;
// }

// // FNV 1A 64-bit algorithm from wikipedia:
// // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
// // Adapted for use on null-terminated strings
// size_t string_hash(const map_t* self, const void* key) {
//     uint8_t* str = (uint8_t*)key;
//     size_t h = FNV_OFFSET_BASIS;

//     uint8_t p;
//     while ((p = *str++)) {
//         h = (h ^ p) * FNV_PRIME;
//     }

//     return h;
// }

// bool value_eq(const map_t* self, const void* lhs, const void* rhs) {
//     const char* lv = (const char*)lhs;
//     const char* rv = (const char*)rhs;

//     return strncmp(lv, rv, self->key_size) == 0;
// }

// bool string_eq(const map_t* self, const void* lhs, const void* rhs) {
//     const char* lstr = *(const char**)lhs;
//     const char* rstr = *(const char**)rhs;

//     if (lstr == NULL || rstr == NULL) {
//         return false;
//     }

//     return strcmp(lstr, rstr) == 0;
// }

// ref_t get_map(const map_t* map, const void* key, size_t key_len) {
//     return (ref_t){.ptr = 0, .len = 0};
// }

// static bool insert_bucket(const map_t* self, bucket_t* bucket, void* key, void* value) {
//     if (bucket == NULL) {
//         *bucket = (bucket_t) { .key = key, .value = value, .prev = NULL, .next = NULL };
//         return true;
//     }

//     do {
//         if (self->eq(self, bucket->key, key)) {
//             return false;
//         }
//         if (bucket->next == NULL) {
//             bucket_t* new = (bucket_t*)malloc(1 * sizeof(bucket_t));

//             new->key = strndup(key, self->key_size);
//             new->value.ptr = value.ptr;
//             new->prev = bucket;

//             bucket->next = new;
//         }
//     } while((bucket = bucket->next));
// }

// bool insert_map(
//     const map_t* map, const void* key, size_t key_len, const void* value, size_t value_len
// ) {
//     ref_t keyptr = (ref_t) { .ptr = strndup(key, key_len), .len = key_len };
//     ref_t valueptr = (ref_t) { .ptr = strndup(value, value_len), .len = value_len };

//     size_t hash = map->hash(key, key_len);

//     return insert_bucket(&map->buckets[hash % map->capacity], keyptr, valueptr);
// }

// bool remove_map(map_t* map, const void* key) { return false; }

// static void free_bucket(bucket_t* bucket) {
//     assert(bucket != NULL);

//     void* key;
//     bucket_t* current = bucket;
//     while ((key = current->key.ptr) != NULL) {
//         free(current->key.ptr);
//         free(current->value.ptr);

//         current = current->next;
//     }
// }

// void free_map(map_t* map) {
//     assert(map != NULL);

//     for (size_t i = 0; i < map->capacity; ++i) {
//         free_bucket(&map->buckets[i]);
//     }
// }