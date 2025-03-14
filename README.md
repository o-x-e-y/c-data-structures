# C Data structures

Personal collection of data structures I can use in C projects. They're not header only, they require the rest of the file too. Feel free to use them as you please.

## Available:

* `string_t`, a heap-based string which takes care of reallocation if needed.
* `slice_t`, a string subslice.
* `vec_t`, a non-typesafe generic implementation of a growing vector. Contains a `elem_size` field which makes it less memory efficient as a proper implementation but C is hard.

## Testing

To run tests, simply run `make`.
