// File: Graph.cpp
//Name: Ujjwal Rehani
// CMSC 341 Spring 2017
//
// cpp file for Graph class
//
#include <iostream>
#include "Graph.h"


Graph::Graph(int n)
{
	AdjListNode *head;
	m_size = n;
	//make sure number of vertices is bigger than 0
	if (n <= 0)
		throw std::out_of_range ("Number must be greater than 0");
	
	m_adjLists = new AdjListNode[m_size];
	for(int i = 0; i< n; i++)
		m_adjLists->head = NULL;
	
	
}

AdjListNode* newNode(int v=-1, AdjListNode *ptr=NULL){
	
	//Creates new node
	AdjListNode* Node = new AdjListNode
	Node->next = NULL;
	return Node;
	
}

Graph::Graph(const Graph& G){
	m_adjLists = new int[n]
	*m_adjLists = *G.m_adjLists;
}

Graph::const Graph& operator= (const Graph& rhs){
	//Check for self assignment
	if(this == &rhs)
		return *this;
	m_adjLists = rhs.m_adjLists;
	
}

Graph::~Graph(){
	
	delete [] m_adjLists;
	
}

//Returns the number of vertices in the graph
int Graph::size(){
	
	return m_size;
}

void addEdge(int u, int v){
	//Bounds checks
		if (u <= 0 || v <= 0)
			throw std::out_of_range ("Edges must be in bounds");
	//Adds an edge between vertices u and v
	AdjListNode* Node = newNode(v);
	Node->next = m_adjLists[u]->head;
	m_adjLists[u] = Node;
	
	Node = newNode(u);
	Node->next = m_adjLists[v]->head;
	m_adjLists[v]->head = Node;
	
}

void Graph::dump(){
	std::cout<<"Dump out graph"<<"Size"<<n<<endl;
	for (int i = 0; i < m; i++)
	{
		AdjListNode* printNode = m_adjLists->head
		std::cout<<i<<endl;
		
		while(printNode{
			std::cout<<"->"<<printNode->v;
			printNode = printNode->next;
			)
	}
}

NbIterator::NbIterator(Graph *Gptr = NULL, int v = -1, bool isEnd = false){
	
}

//compares two EgIterator objects
EgIterator::EgIterator(Graph *Gptr = NULL, bool isEnd = false){
	if isEnd = true{
		m_source = v;
		m_where = NULL;
	}
}
EgIterator::bool operator!= (const EgIterator& rhs){
	
}

EgIterator::void operator++(int dummy){
	
	
}

NbIterator::bool operator!= (const NbIterator& rhs){
	
}

NbIterator::void operator++(int dummy){
	
	
}

NbIterator::int operator*(){
	
	return m_source;
}



