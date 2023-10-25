IMPLS = $(shell find src -name '*.c')
OBJS = $(IMPLS:src/%.c=build/o/%.o)
HEADERS = $(shell find include/cxl/ -name '*.h')
H_DIRS = $(patsubst include/cxl/%,build/gch/%,$(shell find include/cxl/ -type d))
O_DIRS = $(patsubst src/%,build/o/%,$(shell find src/ -type d))
PCH = $(HEADERS:include/cxl/%.h=build/gch/%.h.gch)

CC = clang
CFLAGS = -g --std=c2x -Iinclude -Wall -pedantic

.PHONY: docs objects headers comp bear

print:
	@echo $(IMPLS)
	@echo $(OBJS)
	@echo $(H_DIRS)
	@echo $(O_DIRS)
	@echo $(HEADERS)
	@echo $(PCH)

bear: CFLAGS = -g --std=c2x -DCXL_TYPE=int -DCXL_SUFFIX=int -Iinclude -Wall -pedantic -fsyntax-only -Wno-gnu-auto-type -Wno-gnu-empty-initializer -Wno-macro-redefined
bear:
	bear -- make CFLAGS='$(CFLAGS)' -B comp

comp: headers objects

headers: $(H_DIRS) $(PCH) 

objects: $(O_DIRS) $(OBJS)

$(PCH): build/gch/%.h.gch: include/cxl/%.h
	$(CC) -xc-header -DCXL_DECL_ONLY=1 $(CFLAGS) $< -o $@

build/gch:
	mkdir -p build/gch

$(OBJS): build/o/%.o: src/%.c
	$(CC) -xc $(CFLAGS) -c $< -o $@

$(H_DIRS):
	mkdir -p $@

$(O_DIRS):
	mkdir -p $@

docs:
	doxygen Doxyfile