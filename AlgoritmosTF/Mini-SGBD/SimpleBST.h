#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Dato.h"
using namespace std;

#define max(a, b) (a > b? a : b)
typedef std::function<int(Dato* a, Dato* b)>  COMP;
typedef std::function<int(Dato* a, Dato* b, string tag)>  MATCH;

class SimpleBST {
	struct Node {
		Dato * element;
		Node* left;
		Node* right;
		int height;

		Node(Dato * elem)
			: element(elem), height(0), left(nullptr), right(nullptr) {}
	};
	Node* root;
	MATCH comp;
	string tag;
	int len;
private:
	bool endsWith(const std::string& str, const std::string& suffix);
	bool startsWith(const std::string& str, const std::string& prefix);
	void clear(Node* node);
	//Agregar elemento en un Binary Search Tree
	void add(Node*& node, Dato * elem);
	//Comprobar si se encontró un elemento en un Binary Search Tree
	bool find(Node* node, Dato * elem);
	void findData(Node* node, Dato * elem, MATCH match, vector<Dato*>&vec, string tag);
	void preorder(Node* node, std::function<void(Dato *)> proc);
	void postorder(Node* node, std::function<void(Dato *)> proc);
	void inorder(Node* node, std::function<void(Dato *)> proc);
	//IMPLEMENTAR AQUI METODOS ADICIONALES
	Dato * mayorElemento(Node* node);
	Dato * menorElemento(Node* node);
	void _BSTtoVector(Node* root, vector<Dato*> &vec);
	int height(Node* node);
	string toUpper(string str);
public:
	SimpleBST(MATCH comp, string tag);
	~SimpleBST();
	void clear();
	void add(Dato * elem);
	bool find(Dato * elem);
	void remove(Dato * elem);
	int height();
	void Write(string file);

	void preorder(std::function<void(Dato *)> proc);
	void postorder(std::function<void(Dato *)> proc);
	void inorder(std::function<void(Dato *)> proc);

	void BSTtoVector(vector<Dato*> &vec);
	SimpleBST* VectortoBST(const vector<Dato*> vec);
	vector<Dato*> Filter(Node* root);
	vector<Dato*> Greater(string tag, Dato* dato);
	vector<Dato*> Minor(string tag, Dato* dato);
	vector<Dato*> Equals(string tag, Dato* dato);
	vector<Dato*> Starts(string tag, Dato* dato);
	vector<Dato*> Ends(string tag, Dato* dato);
	vector<Dato*> Inside(string tag, Dato* dato);
	vector<Dato*> NotInside(string tag, Dato* dato);
	//METODOS ADICIONALES
	Dato * mayorElemento();
	Dato * menorElemento();

	void updateHeight(Node* node);
	void RotateLeft(Node*& node);
	void RotateRight(Node*& node);
	void balance(Node*& node);
};