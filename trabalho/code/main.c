#include "functions.h"

int main(int argc, char **argv)
{
	++argv, --argc;
	graph *descriptor = create();
	read(descriptor);
	superLink(descriptor);
	if (argc <= 0)
	{
		print(descriptor);
	}
	saveTxt(descriptor);
	plot(descriptor);

	return 0;
}