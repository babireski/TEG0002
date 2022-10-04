clean:
	@gcc code/iris.c code/graph.c code/functions.c code/main.c -lm -Wall -o main
	@./main 1
	@sfdp -x -Goverlap=scale -Tpng data/iris.dot > data/graph.png
