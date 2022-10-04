#include "functions.h"

int main(void)
{
	graph *descriptor = create();
	read(descriptor);
	superLink(descriptor);
	print(descriptor);
	plot(descriptor);
	saveTxt(descriptor);

	return 0;
}