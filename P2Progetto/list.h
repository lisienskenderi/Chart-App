#ifndef LIST_H
#define LIST_H


template<typename T>
class List{
private:
    class Node{
    public:
        T info;
        Node * prev;
        Node * next;
        Node(const T& i, Node* p = nullptr, Node* n = nullptr);
        Node(const Node& n);
    };
    Node * first;
    Node * last;
    int length;

    static void copy_deep(Node* copy, Node*& f, Node*& l);
    static void destroy_deep(Node* n);
    static void destroy_one(Node* n);
public:
    explicit List(Node * p = nullptr, Node * n = nullptr, int l=0);
    List<T>& operator=(const List<T>& l);
    ~List();

    void push_back(const T& i);
    void push_front(const T& i);

    Node* pop_back();
    Node* pop_front();

    Node* get_element(int x) const;
    void insert_element(const T& e,int x);
    void set_value(const T& e, int x);

    void del_element(int x);
    int getLength() const;
};

/*  ________________
    |Implementaione|
    v              v
*/
// Node
//-------------------------

template<typename T>
List<T>::Node::Node(const T& i, Node* p, Node* n) : info(i), prev(p), next(n) {}

template<typename T>
List<T>::Node::Node(const Node& n): info(n.info){
    copy_deep(n, prev, next);
}

template<typename T>
void List<T>::copy_deep(Node* copy, Node*& f, Node*& l){
    if(copy == nullptr){ // Lista copy vuota
        f = nullptr;
        l = nullptr;
    } else { // Lista non vuota
        Node* tmp = copy;
        f = new Node(tmp->info,nullptr,nullptr);
        l = f;

        while(tmp->next != nullptr){
            tmp = tmp->next;
            l->next = new Node(tmp->info,l,nullptr);
            l = l->next;
        }
    }
}

template<typename T>
void List<T>::destroy_deep(Node* n){
    if(n != nullptr){
        destroy_deep(n->next);
        Node * aux = n;
        n = nullptr;
        delete aux;
    }
}

template<typename T>
void List<T>::destroy_one(Node* n){
    if(n == nullptr){
        //N->nullptr
    }else if(n->next == nullptr && n->prev == nullptr){
        delete n;
    }else if(n->prev == nullptr){
        n->next->prev = nullptr;
        n->next = nullptr;
        delete n;
    } else if (n->next == nullptr){
        n->prev->next = nullptr;
        n->prev = nullptr;
        delete n;
    } else {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        n->prev = nullptr;
        n->next = nullptr;
        delete n;
    }
}

// List
//-------------------------------

template<typename T>
List<T>::List(Node * p, Node * n,int l) : first(p), last(n), length(l) {}

template<typename T>
List<T>& List<T>::operator=(const List<T>& l){
    if(this != &l){
        destroy_deep(first);
        copy_deep(l.first,first,last);
    }
    return *this;
}

template<typename T>
List<T>::~List(){
    destroy_deep(first);
}

template<typename T>
void List<T>::push_back(const T& i){
    if(first == nullptr){
        first = new Node(i,nullptr,nullptr);
        last = first;
    } else {
        last->next = new Node(i,last,nullptr);
        last = last->next;
    }
    length++;
}

template<typename T>
void List<T>::push_front(const T& i){
    if(first == nullptr){
        first = new Node(i,nullptr,nullptr);
        last = first;
    } else {
       first->prev = new Node(i,nullptr,first);
       first = first->prev;
    }
    length++;
}

template<typename T>
typename List<T>::Node* List<T>::pop_back(){
    if(first == nullptr){
        return nullptr;
    } else {
        Node* tmp = last;
        if(last->prev == nullptr){
            first = nullptr;
            last = nullptr;
        } else {
            last = last->prev;
            last->next = nullptr;
            tmp->prev = nullptr;
        }
        length--;
        return tmp;
    }
}

template<typename T>
typename List<T>::Node* List<T>::pop_front(){
    if(first == nullptr){
        return nullptr;
    } else {
        Node* tmp = first;
        if(first->next == nullptr){
            first = nullptr;
            last = nullptr;
        } else {
            first = first->next;
            first->prev = nullptr;
            tmp->next = nullptr;
        }
        length--;
        return tmp;
    }
}

template<typename T>
typename List<T>::Node* List<T>::get_element(int x)const{
    if(x == 0){
        return first;
    }
    if(x >= length - 1){
        return last;
    }
    Node * tmp = first;
    while(tmp->next != nullptr && x > 0){
        tmp = tmp->next;
        x--;
    }
    if(tmp != nullptr){
        return tmp;
    }
    return nullptr;
}

template<typename T>
void List<T>::insert_element(const T& e, int x){
    if(x == 0){
        push_front(e);
    } else if(x >= length - 1 && x != 0){
        push_back(e);
    }else{
        Node* tmp = get_element(x);
        Node* n = new Node(e, tmp->prev, tmp);
        tmp->prev->next = n;
        tmp->prev = n;
        length++;
    }
}

template<typename T>
void List<T>::set_value(const T& e, int x){
    if(length == 0){
        insert_element(e, x);
    }
    if(x > length - 1){
        insert_element(e, x);
    }
    
    if(get_element(x)){
        Node* tmp = get_element(x);
        tmp->info = e;
    }
}

template<typename T>
void List<T>::del_element(int x){
    if(x == 0){
        Node * n = pop_front();
        n->next = nullptr;
        delete n;
    }else if(x > length - 1){
        Node * n = pop_back();
        n->prev = nullptr;
        delete n;
    }else{
        Node* n = get_element(x);
        if(length == 1){
            delete n;
        } else {
            destroy_one(n);
        }
        length--;
    }
}

template<typename T>
int List<T>::getLength() const{
    return length;
}



#endif // LIST_H
