#include "functions.h"

int main(int argc, char **argv)
{
	++argv, --argc;
	graph *descriptor = create();

	if (argc <= 0)
	{
		readTxt(descriptor);
	}

	else
	{
		readCsv(descriptor);
		superLink(descriptor);
		print(descriptor);
		saveTxt(descriptor);
	}
	plot(descriptor);

	return 0;
}