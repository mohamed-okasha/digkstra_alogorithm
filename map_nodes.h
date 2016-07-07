/*
 * map_nodes.h
 *
 *  Created on: Jul 5, 2016
 *      Author: mohamed
 */

#ifndef MAP_NODES_H_
#define MAP_NODES_H_

#include <list>
#include <string>

const int infinite = 1000000;

class Node {
//private:

//private:
	//static vector<Node *>::iterator s_next;
public:

	class row {

	public:
		Node * d_node; // destination
		Node * v_path; // via path
		int distance; // distance between 2 Neighbors nodes
		bool dir;

	};

	std::string name;
	int r_distance = infinite; // relative distance between source and this node set initially infinite
	bool visited = false;
	std::list<Node *> n_nodes; // neighbors Nodes
	std::list<row *> table;

	Node(std::string name) {
		this->name.append(name);
		//row *first_row = new row;
		//first_row->v_path = "-";
		//table.push_front(first_row);
	}
	int getDistanceto(std::string na);
	int addEntry(Node * d, Node* v_p, int cost, bool dir);
	int addEntry(Node::row * row);

	row * getEntry(Node * d);
	row * getEntry(std::string node_name);

};

int Node::getDistanceto(std::string na) {
	std::list<row *>::iterator i;
	for (i = table.begin(); i != table.end(); i++) {
		if (na.compare((*i)->d_node->name) == 0)
			return ((*i)->distance);
	}
	return (infinite);
}

int Node::addEntry(Node * d, Node* v_p, int cost, bool dir) {

	Node::row *row = new Node::row;

	// create map
	//	n_nodes.push_back(B);
	row->d_node = d;
	row->distance = cost;
	row->v_path = v_p;
	//	(*A->table.begin())->distance = 0; // set distance path source node to zero
	table.push_back(row);
	return (1);
}

int Node::addEntry(Node::row * row) {

	table.push_back(row);
	return (1);
}
Node::row * Node::getEntry(Node * d) {

	std::list<row *>::iterator i;
	for (i = table.begin(); i != table.end(); i++) {
		if ((*i)->d_node == d)
			return (*i);
	}
	return (NULL);

}

Node::row * Node::getEntry(std::string node_name) {

	std::list<row *>::iterator i;
	for (i = table.begin(); i != table.end(); i++) {
		if (node_name.compare((*i)->d_node->name) == 0)
			return (*i);
	}
	return (NULL);

}

#endif /* MAP_NODES_H_ */
