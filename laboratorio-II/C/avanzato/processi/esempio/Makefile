PHONY: clean, bgexe

bgexe: bg
	./bg 5

bg: background.c
	gcc $^ -o $@


clean:
	rm -f bg