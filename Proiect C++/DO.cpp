#include "Iterator.h"
#include "DO.h"

#include <exception>

using namespace std;

//Complexitate : Theta(1)
Node::Node(TElem e, Pnode next, Pnode prev){
    this->e = e;
    this->next = next;
    this->prev = prev;
}

//Complexitate : Theta(1)
TElem Node::element() {
    return e;
}

//Complexitate : Theta(1)
Pnode Node::next_element() {
    return next;
}

//Complexitate : Theta(1)
DO::DO(Relatie r) {
    head = nullptr;
    tail = nullptr;
    relation = r;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
//Complexitate :
// Best case: cheia headului nu este in relatie cu cheia primita => Theta(1)
// Worst case : toate cheile sunt in relatie si elementul trebuie adaugat la final => Theta(n)
// Average case : while se poate executa 1,2,3...n ori => T(n) = 4*(n+1)/2 => Theta(n)
// Overall : O(n)
TValoare DO::adauga(TCheie c, TValoare v) {
    Node* currentNode = head;

    // Cautăm poziția corectă pentru inserarea sau actualizarea cheii
    while (currentNode != tail && relation(currentNode->e.first, c)) {
        if (currentNode->e.first == c) {
            // Cheia există deja, înlocuim valoarea asociată și returnăm vechea valoare
            TValoare oldValue = currentNode->e.second;
            currentNode->e.second = v;
            return oldValue;
        }
        currentNode = currentNode->next;
    }

    //caz pentru tail
    if(currentNode!= nullptr && currentNode->e.first == c){
        TValoare oldValue = currentNode->e.second;
        currentNode->e.second = v;
        return oldValue;
    }

    // Cream o nouă pereche (cheie, valoare)
    TElem newPair;
    newPair.first = c;
    newPair.second = v;
    Node* new_node = new Node(newPair, nullptr, nullptr);

    // Cazul în care lista este goală sau trebuie să inserăm la început
    if (head == nullptr || !relation(head->e.first, c)) {
        new_node->next = head;
        if (head != nullptr) {
            head->prev = new_node;
        }
        head = new_node;
        if (tail == nullptr) {
            tail = new_node;
        }
        return NULL_TVALOARE;
    }

    // Cazul în care trebuie să inserăm la sfârșit
    if(relation(tail->e.first, c)){
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
        return NULL_TVALOARE;
    }


    // cazul in care trebuie sa inseram la mijloc
    Node* prevNode = currentNode->prev;
    new_node->next = currentNode;
    new_node->prev = prevNode;
    prevNode->next = new_node;
    currentNode->prev = new_node;

    return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
//Complexitate:
// Best case : elementul cautat este headul => Theta(1)
// Worst case : elementul nu se afla in dll => Theta(n)
// Average case : T(n)= n+1/2 => Theta(n)
// Overall: O(n)
TValoare DO::cauta(TCheie c) const {
	Node* currentNode = head;
    while(currentNode!= nullptr){
        if(currentNode->e.first==c){
            return currentNode->e.second;
        }
        currentNode = currentNode->next;
    }
	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
// Complexitate:
// Best case : elementul cautat este headul => Theta(1)
// Worst case : elementul nu se afla in dll => Theta(n)
// Average case : T(n)= n+1/2 => Theta(n)
// Overall: O(n)
TValoare DO::sterge(TCheie c) {
	Node* currentNode = head;
    while(currentNode!= nullptr){
        if(currentNode->e.first == c){
            if(currentNode==head){
                TValoare oldValue = currentNode->e.second;
                head = currentNode->next;
                delete currentNode;
                return oldValue;
            }
            if(currentNode==tail){
                TValoare oldValue = currentNode->e.second;
                tail = currentNode->prev;
                currentNode->prev->next = nullptr;
                delete currentNode;
                return oldValue;
            }
         TValoare oldValue = currentNode->e.second;
         currentNode->prev->next = currentNode->next;
         currentNode->next->prev = currentNode->prev;
         delete currentNode;
         return oldValue;
        }
        currentNode = currentNode->next;
    }
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
//complexitate : Theta(n)
int DO::dim() const {
	int count = 0;
    Node* currentNode = head;
    while(currentNode!= nullptr){
        count++;
        currentNode = currentNode->next;
    }
	return count;
}

//verifica daca dictionarul e vid
// complexitate : Theta(1)
bool DO::vid() const {
	return head== nullptr;
}

// complexitate : Theta(1)
Iterator DO::iterator() const {
	return  Iterator(*this);
}

// complexitate : Theta(1)
DO::~DO() {
	while(head!= nullptr){
        Node* new_node = head;
        head = head->next;
        delete new_node;
    }
}

/**
 * functie adaugaInexistente(DO& d)
 *  currentNode:[pointer] Node <- d.head
 *  int count <- 0
 *  CatTimp currentNode != nullptr executa
 *      daca cauta(currentNode->e.first) == NULL_TVALOARE atunci
 *          adauga(currentNode->e.first, currentNode->e.second)
 *          count <- count + 1
 *      sfDaca
 *   currentNode <- currentNode -> next
 *   sfCatTimp
 *   adaugaInexistente <- count
 *   sfFunctie
 *
 *  Complexitate : Theta(n*m), n - dim dictionarului nou, m - dim dictionarului existent
 *
 */
int DO::adaugaInexistente(DO &d) {
    Node* currentNode = d.head;
    int count = 0;
    while(currentNode != nullptr){
        if(cauta(currentNode->e.first)==NULL_TVALOARE) {
            adauga(currentNode->e.first, currentNode->e.second);
            count++;
        }
        currentNode = currentNode -> next;
    }
    return count;
}
