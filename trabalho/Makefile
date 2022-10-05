clean:
	@gcc code/iris.c code/graph.c code/functions.c code/main.c -lm -Wall -o main
	@.\main
	@sfdp -x -Goverlap=scale -Tsvg data/iris.dot > data/iris.svg