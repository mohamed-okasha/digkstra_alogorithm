/*
 * main.cpp
 *
 *  Created on: May 18, 2016
 *      Author: mohamed
 */
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstring>
#include <malloc.h>
using namespace std;

class Node {

//private:

//private:
	//static vector<Node *>::iterator s_next;
public:

	class row {

	public:
		Node * d_node; // distination
		string v_path; // via path
		int distance = 100000; // set initially infinite
		bool visited = false;

	};

	string name;

	vector<Node *> n_nodes; // nea
	list<row *> table;

	Node(string name) {
		this->name.append(name);

		row *first_row = new row;
		first_row->v_path = "-";
		table.push_front(first_row);

	}

	//vector<Node *>::iterator  next_node=n_nodes.begin();

};

vector<Node *> sptSet;

/*Node * add_next_node(Node * cNode,string Name){

 Node *new_node= new Node(Name);

 cNode->n_nodes.push_back(new_node);

 //cout<<(*cNode->next_node)->name;
 return (new_node);
 }
 */

bool traverse_map(Node *node) {
	vector<Node *>::iterator i;
	list<Node::row *>::iterator r;

	if (!(*node->table.begin())->visited)
		return (true);

	for (i = node->n_nodes.begin(); i != (node->n_nodes).end(); ++i) {

		traverse_map((*i));
	}

	return false;
}

bool exist_in_spt(Node *node, vector<Node *> spt) {

	vector<Node *>::iterator i;

	for (i = spt.begin(); i != spt.end(); i++) {

		if (*i == node) {

			//cout<<(*i)->name<<"::"<<(*i)<<"==";
			//cout<<node->name<<"::"<<node<<"endl";
			return (true);
		}

	}

	return (false);
}
Node::row * get_min(Node *node) {

	vector<Node *>::iterator i;
	list<Node::row *>::iterator r;

	static int min_distance = 10000;
	Node::row *min_node = NULL;
//cout<<"node::"<< node->name;
//cout<<endl<<"Table::"<<endl;

	if (!exist_in_spt(node, sptSet)) {
		//	cout<<node->name;
		// skip first row contain information about itself
		for (r = node->table.begin(), ++r; r != (node->table).end(); ++r) {
			//cout<<node->name<< "->"<<(*r)->d_name<<"::"<<(*r)->distance<<endl;

			if ((*r)->distance < min_distance) {

				min_distance = (*r)->distance;
				min_node = (*r);
				Node::row *new_row = new Node::row;

				// node->table.push_back(new_row);
			}

//	if ( node->name.compare((*r)->v_path)==0){ // it's a neighbor node
			//cout<<node->name.c_str();
// }

		}

	}

	for (i = node->n_nodes.begin(); i != (node->n_nodes).end(); ++i) {
		cout << (*i)->name;
		get_min((*i));
	}
	cout << endl;

	return (min_node);

}
int find_shortest_path_for(Node *node) {

	Node::row *u;

	while (u = get_min(node)) {
		u->visited = true;
		sptSet.push_back(u->d_node);
		cout << u->d_node->name;
		//cout<<endl;

	}
	//cout<<"end";

	return (0);

}
int main() {

	Node * A = new Node("A");

	Node *B = new Node("B");

	Node *C = new Node("C");

	Node *D = new Node("D");
	Node *E = new Node("E");

	Node::row *rAB = new Node::row;
	Node::row *rAC = new Node::row;
	Node::row *rBE = new Node::row;
	Node::row *rCE = new Node::row;
	Node::row *rBD = new Node::row;

	// create map
	A->n_nodes.push_back(B);
	rAB->d_node = B;
	rAB->distance = 5;
	rAB->v_path = A->name.at(0);
	(*A->table.begin())->distance = 0; // set distance path source node to zero
	A->table.push_back(rAB);

	A->n_nodes.push_back(C);
	rAC->d_node = C;
	rAC->distance = 70;
	rAC->v_path = A->name.at(0);
	A->table.push_back(rAC);

	B->n_nodes.push_back(E);
	rBE->d_node = E;
	rBE->distance = 1;
	rBE->v_path = B->name.at(0);
	B->table.push_back(rBE);

	B->n_nodes.push_back(D);
	rBD->d_node = D;
	rBD->distance = 6;
	rBD->v_path = B->name.at(0);
	B->table.push_back(rBD);

	C->n_nodes.push_back(E);
	rCE->d_node = E;
	rCE->distance = 3;
	rCE->v_path = C->name.at(0);
	C->table.push_back(rCE);

// find shortes path for A Node;
	find_shortest_path_for(A);
//cout<<traverse_map(A);

}

