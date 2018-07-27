#include <stdio.h>
#include "numeric_map.h"

void print(numeric_key k, numeric_map_item v) {
	printf("%s\n", (char*)v);
}

int main(int argc, char* argv[]) {
	numeric_map* nm = numeric_map_new();
	/*
	5
  3   7
        20
	  9
	*/
	numeric_map_put(nm, 5, "Hello");
	numeric_map_put(nm, 3, "Bar");
	numeric_map_put(nm, 7, "Parallel");
	numeric_map_put(nm, 20, "foreacg");
	numeric_map_put(nm, 9, "dummy");
	numeric_map_each(nm, print);
	numeric_map_delete(nm, numeric_map_deleter_null);
	return 0;
}