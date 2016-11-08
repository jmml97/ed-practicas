/**
 * @file list.cpp
 * @brief Implementación del T.D.A. List
 *
 */

List(const List& list)
{
    Node<T>* p = list.head();
    Node<T>* actual = head;

    if (p)
        do
        {
            push_back(p->element);
            p = p->next;
        } while(p);
    else
        head = tail = 0;
}

/* _________________________________________________________________________ */

List& operator =(const List& list)
{
    List aux(list);
    clear();
    Node<T>* p = aux.head();

    if (p)
        do
        {
            push_back(p->element);
            p = p->next;
        } while(p);

    return *this;
}

/* _________________________________________________________________________ */

int size() const
{
    int n = 0;
    for (Node<T>* aux = head; aux; aux = aux->next, ++n);
    return n;
}

/* _________________________________________________________________________ */

void push_back(const T& e)
{
    Node<T>* aux = new Node<T>;
    aux->element = e;

    if (head)
        tail->next = aux;
    else
        head = aux;

    tail = aux;
}

/* _________________________________________________________________________ */

void pop_back()
{
    for (Node<T>* i = head; i->next != tail; i = i->next;)
    delete tail;
    tail = i;
    i->next = 0;
}

/* _________________________________________________________________________ */

void clear()
{
    Node<T>* i = head;
    while (i)
    {
        Node<T>* aux = i->next;
        delete i;
        i = aux;
    }
    head = tail = 0;
}

// No se incluye el .hpp

/* Fin fichero: list.cpp */
