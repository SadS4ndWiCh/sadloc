# 🪝 sadloc

Creating a custom memory allocator with C using the `sbrk` syscall.

## ✨ Functions

```c
void *sadloc(size_t size);
void sadfree(void *block);
void *sadcloc(size_t nmemb, size_t size);
void *sadreloc(void *ptr, size_t size);
```

## 🪅 TODO

- [x] sadloc (malloc)
- [x] sadfree (free)
- [x] sadcloc (calloc)
- [x] sadreloc (realloc)

## 🎠 Tests

```sh
$ make <function>_test
```
> `$ make sadloc_test`

## 📖 References

- [Write a simple memory allocator](https://arjunsreedharan.org/post/148675821737/memory-allocators-101-write-a-simple-memory)