#include "Graph.h"

void Graph::AssignStatusFunction(
	int (*function)()
) {
	this->StatusFunction = function;
}