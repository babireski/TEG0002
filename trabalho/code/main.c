#include "functions.h"

int main(void)
{
	graph *descriptor = create();
	read(descriptor);
	superlink(descriptor);
	print(descriptor);
	plot(descriptor);
	
	return 0;
}