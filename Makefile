executable := c-data-structures
build-path := ./build
exec-path := $(build-path)/$(executable)

src := ./src
headers := ./src/headers

debug-flags := -g -O0 -Wall -Wpedantic -lm
release-flags := -O3 -lm
valgrind-flags := --leak-check=yes --track-origins=yes -s

src_files := $(wildcard $(src)/*.c)
header_files := $(wildcard $(headers)/*.h)

.PHONY: release
release: $(src_files)
	cc $(release-flags) $(src_files) -o $(exec-path) && $(exec-path) $(ARGS)
	
.PHONY: build
build: $(src_files)
	cc $(debug-flags) $(src_files) -o $(exec-path)

.PHONY: build-release
build-release: $(src_files)
	cc $(src_files) $(release-flags) -o $(exec-path)

.PHONY: debug
debug: $(src_files)
	cc $(debug-flags) $(src_files) -o $(exec-path) && $(exec-path)

%:
	@:

.PHONY: valgrind
valgrind: $(exec-path)
	valgrind $(valgrind-flags) $(exec-path) $(ARGS)

.PHONY: fmt
fmt:
	clang-format -i -style=file $(wildcard $(src)/*.c) $(wildcard $(headers)/*.h)

#aliases

.PHONY: r
r: release

.PHONY: b
b: build

.PHONY: br
br: build-release

.PHONY: d
d: debug

.PHONY: v
v: valgrind

.PHONY: bv
bv: build valgrind
