#include "functions.h"

int main(void)
{
	graph *descriptor = create();
	read(descriptor);
	link(descriptor, table(descriptor));
	print(descriptor);
	
	return 0;
}