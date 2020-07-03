#include "AvlTree.h"

bool AvlTree::endsWith(const std::string& str, const std::string& suffix)
{
	return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

bool AvlTree::startsWith(const std::string& str, const std::string& prefix)
{
	return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

AvlTree::AvlTree(MATCH comp, string tag)
{
	this->tag = tag;
	this->comp = comp;
	this->root = nullptr;
	this->len = 0;
}


AvlTree::~AvlTree()
{
	clear(this->root);
}

void AvlTree::clear(Node * node)
{
	if (node != nullptr) {
		clear(node->left);
		clear(node->right);
		delete node;
		node = nullptr;
	}
}

void AvlTree::add(Node *& node, Dato * elem)
{
	if (node == nullptr) {
		node = new Node(elem);
		++len;
	}
	else
	{
		if (comp(node->element, elem, tag) == -1 || comp(node->element, elem, tag) == 0) {
			add(node->left, elem);
		}
		else if (comp(node->element, elem, tag) == 1) {
			add(node->right, elem);
		}
		balance(node);
	}
	
}

bool AvlTree::find(Node * node, Dato * elem)
{
	if (node != nullptr) {
		if (comp(node->element, elem, tag) == 0) {
			return true;
		}
		else if (comp(node->element, elem, tag) == -1) {
			return find(node->left, elem);
		}
		else {
			return find(node->right, elem);
		}
	}
	return false;
}

void AvlTree::findData(Node * node, Dato * elem, MATCH match, vector<Dato*>& vec, string tag)
{
	if (node == nullptr) return;

	findData(node->left, elem, match, vec, tag);
	if (match(node->element, elem, tag) == 1)
		vec.push_back(node->element);
	findData(node->right, elem, match, vec, tag);
	
}




void AvlTree::preorder(Node * node, std::function<void(Dato*)> proc)
{
	if (node != nullptr) {
		proc(node->element);
		preorder(node->left, proc);
		preorder(node->right, proc);
	}
}

void AvlTree::postorder(Node * node, std::function<void(Dato*)> proc)
{
	if (node != nullptr) {
		postorder(node->left, proc);
		postorder(node->right, proc);
		proc(node->element);
	}
}

void AvlTree::inorder(Node * node, std::function<void(Dato*)> proc)
{
	if (node != nullptr) {
		inorder(node->left, proc);
		proc(node->element);
		inorder(node->right, proc);
	}
}

Dato * AvlTree::mayorElemento(Node * node)
{

	while (node->right != nullptr) {
		node = node->right;
	}
	return node->element;
}

Dato * AvlTree::menorElemento(Node * node)
{
	while (node->left != nullptr) {
		node = node->left;
	}
	return node->element;
}

void AvlTree::_BSTtoVector(Node * node, vector<Dato*> &vec)
{
	if (node == nullptr) return;

	_BSTtoVector(node->left, vec);
	vec.push_back(node->element);
	_BSTtoVector(node->right, vec);
}

int AvlTree::height(Node * node)
{
	return node == nullptr ? -1 : node->height;
}

void AvlTree::clear()
{
	clear(this->root);
}

void AvlTree::add(Dato * elem)
{
	add(this->root, elem);
}

bool AvlTree::find(Dato * elem)
{
	return find(this->root, elem);
}

void AvlTree::remove(Dato * elem)
{
	// Encontrar elemento a eliminar;
	Node* aux = this->root;
	Node* auxParent = nullptr;
	bool leftChild;
	while (aux != nullptr) {
		if (elem == aux->element) {
			break;
		}
		else if (elem < aux->element) {
			auxParent = aux;
			leftChild = true;
			aux = aux->left;
		}
		else {
			auxParent = aux;
			leftChild = false;
			aux = aux->right;
		}
	}
	if (aux == nullptr) return;                 // No se encontró el elemento a eliminar

												// Ahora eliminamos en caso no tenga hijo izquierdo
	if (aux->left == nullptr) {                 // No tiene hijo izquierdo, sube el derecho
		if (auxParent == nullptr) {             // El elemento a eliminar es root
			this->root = aux->right;
		}
		else if (leftChild) {                 // El elemento a eliminar es el izq de parent
			auxParent->left = aux->right;
		}
		else {                                // es el derecho de parent
			auxParent->right = aux->right;
		}
		delete aux;
		return;
	}

	// En caso si exista hijo izquierdo, buscamos al mayor de dicho subárbol
	Node* aux2 = aux->left;
	Node* aux2Parent = aux;
	leftChild = true;
	while (aux2->right != nullptr) {
		aux2Parent = aux2;
		leftChild = false;
		aux2 = aux2->right;
	}
	aux->element = aux2->element;               // Reemplazamos al elemento a eliminar
	if (leftChild) {
		aux2Parent->left = aux2->left;
	}
	else {
		aux2Parent->right = aux2->left;
	}
	delete aux2;
}

int AvlTree::height()
{
	return height(this->root);
}

void AvlTree::Write(string file)
{
	vector<Dato*> vec;
	BSTtoVector(vec);
	ofstream fs(file);
	fs.clear();
	for each (string ss in vec[0]->getTags())
	{
		fs << ss << ",";
	}
	fs << endl;

	for each (Dato* var in vec)
	{
		for each (string ss in var->getData())
		{
			fs << ss << ",";
		}
		fs << endl;
	}

	fs.flush();
	fs.close();
}

void AvlTree::preorder(std::function<void(Dato*)> proc)
{
	preorder(this->root, proc);
}

void AvlTree::postorder(std::function<void(Dato*)> proc)
{
	postorder(this->root, proc);
}

void AvlTree::inorder(std::function<void(Dato*)> proc)
{
	inorder(this->root, proc);
}

void AvlTree::BSTtoVector(vector<Dato*> &vec)
{
	_BSTtoVector(this->root, vec);
}

AvlTree * AvlTree::VectortoBST(const vector<Dato*> vec)
{
	AvlTree* bst = new AvlTree(this->comp, this->tag);
	for each (Dato* var in vec)
	{
		bst->add(var);
	}
	return bst;
}

vector<Dato*> AvlTree::Filter(Node * root)
{
	vector<Dato*> vec;
	_BSTtoVector(root, vec);
	return vec;
}

vector<Dato*> AvlTree::Greater(string tag, Dato * dato)
{
	vector<Dato*> vec;
	findData(this->root, dato, [&](Dato* a, Dato* b, string tag)
	{
		if (toUpper(a->findByTag(tag)) > toUpper(b->findByTag(tag)))
			return 1;
		else
			return 0;
	}, vec, tag);
	return vec;
}

vector<Dato*> AvlTree::Minor(string tag, Dato * dato)
{
	vector<Dato*> vec;
	findData(this->root, dato, [&](Dato* a, Dato* b, string tag)
	{
		if (toUpper(a->findByTag(tag)) < toUpper(b->findByTag(tag)))
			return 1;
		else
			return 0;
	}, vec, tag);
	return vec;
}

vector<Dato*> AvlTree::Equals(string tag, Dato * dato)
{
	vector<Dato*> vec;
	findData(this->root, dato, [&](Dato* a, Dato* b, string tag)
	{
		if (toUpper(a->findByTag(tag)) == toUpper(b->findByTag(tag)))
			return 1;
		else
			return 0;
	}, vec, tag);
	return vec;
}

vector<Dato*> AvlTree::Starts(string tag, Dato * dato)
{
	vector<Dato*> vec;
	findData(this->root, dato, [&](Dato* a, Dato* b, string tag)
	{
		if (startsWith(toUpper(a->findByTag(tag)), toUpper(b->findByTag(tag))))
			return 1;
		else
			return 0;
	}, vec, tag);
	return vec;
}

vector<Dato*> AvlTree::Ends(string tag, Dato * dato)
{
	vector<Dato*> vec;
	findData(this->root, dato, [&](Dato* a, Dato* b, string tag)
	{
		if (endsWith(toUpper(a->findByTag(tag)),toUpper(b->findByTag(tag))))
			return 1;
		else
			return 0;
	}, vec, tag);
	return vec;
}

vector<Dato*> AvlTree::Inside(string tag, Dato * dato)
{
	vector<Dato*> vec;
	findData(this->root, dato, [&](Dato* a, Dato* b, string tag)
	{
		if (toUpper(a->findByTag(tag)).find(toUpper(b->findByTag(tag))) != string::npos)
			return 1;
		else
			return 0;
	}, vec, tag);
	return vec;
}

vector<Dato*> AvlTree::NotInside(string tag, Dato * dato)
{
	vector<Dato*> vec;
	findData(this->root, dato, [&](Dato* a, Dato* b, string tag)
	{
		if (toUpper(a->findByTag(tag)).find(toUpper(b->findByTag(tag))) == string::npos)
			return 1;
		else
			return 0;
	}, vec, tag);
	return vec;
}

Dato * AvlTree::mayorElemento()
{
	return mayorElemento(this->root);
}

Dato * AvlTree::menorElemento()
{
	return menorElemento(this->root);
}

void AvlTree::updateHeight(Node * node)
{
	if (node != nullptr) {
		int hl = height(node->left);
		int hr = height(node->right);

		node->height = max(hl, hr) + 1;
	}
}

void AvlTree::RotateLeft(Node *& node)
{
	Node* aux = node->right;
	node->right = aux->left;
	updateHeight(node);
	aux->left = node;
	updateHeight(aux);
	node = aux;
}

void AvlTree::RotateRight(Node *& node)
{
	Node* aux = node->left;
	node->left = aux->right;
	updateHeight(node);
	aux->right = node;
	updateHeight(aux);
	node = aux;
}

void AvlTree::balance(Node *& node)
{
	int hl = height(node->left);
	int hr = height(node->right);

	if (hr - hl < -1) {
		hl = height(node->left->left);
		hr = height(node->left->right);
		if (hr > hl) {
			RotateLeft(node->left);
		}
		RotateRight(node);
	}
	else if (hr - hl > 1) {
		hl = height(node->right->left);
		hr = height(node->right->right);
		if (hl > hr) {
			RotateRight(node->right);
		}
		RotateLeft(node);
	}
	else {
		updateHeight(node);
	}
}

string AvlTree::toUpper(string str)
{
	string ss = str;
	transform(ss.begin(), ss.end(), ss.begin(), ::toupper);
	return ss;
}
