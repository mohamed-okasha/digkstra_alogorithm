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
#include <iomanip>
#include <stack>

#include "map_nodes.h"

using namespace std;

std::vector<Node *> sptSet;
std::vector<Node *> Spt;
std::stack<Node *> sSubPaths;

bool exist_in_spt(Node *node);
bool traverse_map(Node *node);
void show_table(Node *source);

int find_shortest_path_for(Node *node, Node *dis_node) {

	Node *u;
	Node *source = node;

	std::vector<Node *>::iterator i;
	std::list<Node *>::iterator ad;

	int min_dis = 0;

	source->r_distance = 0;
	source->addEntry(source, NULL, NULL, 1);

	traverse_map(node);

	u = node;
	Spt.push_back(u);
	while (Spt.size() < sptSet.size()) {
		cout << u->name << endl;

		for (ad = u->n_nodes.begin(); ad != u->n_nodes.end(); ad++) {

			if ((*ad)->r_distance > (infinite - 1)) { // impossibale distance if visited

				(*ad)->r_distance = u->r_distance
						+ u->getDistanceto((*ad)->name);
				//	cout<<(*ad)->d_node->name<<" rel dist:"<<(*ad)->d_node->r_distance<<endl;
				Node::row *r = source->getEntry(*ad);

				if (r == NULL && source != *ad) {
					cout << "not exist" << endl;
					r = new Node::row;
					source->addEntry(r);
				}
				r->d_node = *ad;
				r->distance = (*ad)->r_distance;
				r->v_path = u;

				std::cout << "new entry:" << r->d_node->name << ":"
						<< r->v_path->name << ":" << r->distance << endl;

			}

		}

		u->visited = true;

		bool initial = false;

		// select node with not visited with minimum relative distance
		for (i = sptSet.begin(); i != sptSet.end(); i++) {

			if ((*i)->visited == false) {
// set initial value to minimum distance
				if (!initial && (*i)->r_distance < (infinite - 1)) {
					min_dis = (*i)->r_distance;
					initial = true;
				}

				if (min_dis >= (*i)->r_distance) {

					min_dis = (*i)->r_distance;
					u = *i;

					//		cout<<"min "<<min_dis<<"  vai path:"<<u->name<<endl;
				}

			}

		}
		Spt.push_back(u);

	}

	int cost = 0;
	sSubPaths.push(dis_node);
	u = dis_node;

	while (source->getEntry(u)->distance) {
		u = source->getEntry(u)->v_path;
		sSubPaths.push(u);
	}
	std::cout << "Fall Path :";
	while (!sSubPaths.empty()) {

		std::cout << sSubPaths.top()->name;
		sSubPaths.pop();
	}

	return (0);

}

int main() {

	Node * A = new Node("A");

	Node *B = new Node("B");

	Node *C = new Node("C");

	Node *D = new Node("D");
	Node *E = new Node("E");
	Node *F = new Node("F");
	Node *G = new Node("G");

	//Node::row *rAB = new Node::row;
	//Node::row *rAC = new Node::row;
	//Node::row *rBE = new Node::row;
	//Node::row *rCE = new Node::row;
	//Node::row *rBD = new Node::row;

	// create map
	A->n_nodes.push_back(B);
	A->addEntry(B, A, 4, 1);
//	(*A->table.begin())->distance = 0; // set distance path source node to zero

	A->n_nodes.push_back(C);
	A->addEntry(C, A, 5, 1);

	B->n_nodes.push_back(F);
	B->addEntry(F, B, 3, 1);

	B->n_nodes.push_back(G);
	B->addEntry(G, B, 1, 1);

	B->n_nodes.push_back(D);
	B->addEntry(D, B, 2, 1);

	C->n_nodes.push_back(D);
	C->addEntry(D, C, 3, 1);

	D->n_nodes.push_back(E);
	D->addEntry(E, D, 3, 1);

	D->n_nodes.push_back(G);
	D->addEntry(G, D, 2, 1);

	F->n_nodes.push_back(E);
	F->addEntry(E, F, 7, 1);

	G->n_nodes.push_back(F);
	G->addEntry(F, G, 2, 1);

// find shortes path for A Node;
	find_shortest_path_for(A, E);
	show_table(A);
//cout<<traverse_map(A);

}

bool exist_in_spt(Node *node) {

	vector<Node *>::iterator i;

	for (i = sptSet.begin(); i != sptSet.end(); i++) {

		if (*i == node) {
			return (true);
		}

	}

	return (false);
}

bool traverse_map(Node *node) {
	std::list<Node *>::iterator i;
	std::list<Node::row *>::iterator r;

	for (i = node->n_nodes.begin(); i != (node->n_nodes).end(); ++i) {

		if (!exist_in_spt(*i))
			sptSet.push_back(*i);
	}
	for (i = node->n_nodes.begin(); i != node->n_nodes.end(); ++i) {

		traverse_map((*i));
	}

	return (false);
}

void show_table(Node *source) {

	list<Node::row *>::iterator i;

	std::cout << setw(10) << "Node" << setw(10) << "Via Node" << setw(10)
			<< "cost" << endl;

	for (i = source->table.begin(); i != source->table.end(); i++) {
		if ((*i)->d_node != NULL)
			std::cout << setw(10) << (*i)->d_node->name;
		else
			std::cout << setw(10) << "-";

		if ((*i)->v_path != NULL)
			cout << setw(10) << (*i)->v_path->name;
		else
			std::cout << setw(10) << "-";

		cout << setw(10) << (*i)->distance << endl;

	}
}
