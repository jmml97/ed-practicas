/**
  * @file queue_max.cpp
  * @brief Fichero de implementación del T.D.A. QueueMax
  *
  */

Element& QueueMax::front()
{
    Stack<Element> aux;
    while(!v.empty())
    {
        aux.push(v.top());
        v.pop();
    }
    v.push(aux.top());
    aux.pop();
    Element& e = v.top();
    while(!aux.empty())
    {
        v.push(aux.top());
        aux.pop();
    }
    return e;
}

/* _________________________________________________________________________ */

const Element& QueueMax::front() const
{
    Stack<Element> aux;
    while(!v.empty())
    {
        aux.push(v.top());
        v.pop();
    }
    v.push(aux.top());
    aux.pop();
    Element& e = v.top();
    while(!aux.empty())
    {
        v.push(aux.top());
        aux.pop();
    }
    return e;
}

/* _________________________________________________________________________ */

void QueueMax::push(int n)
{
    int max = n;
    if (!v.empty() && v.top().max > max)
        max = top().max;
    Element e = {n, max};
    v.push(e);
}

/* _________________________________________________________________________ */

void QueueMax::pop()
{
    Stack<Element> aux;
    while(!v.empty())
    {
        aux.push(v.top());
        v.pop();
    }
    aux.pop();
    while(!aux.empty())
    {
        v.push(aux.top());
        aux.pop();
    }
}

/* _________________________________________________________________________ */

std::ostream& QueueMax::prettyPrint(std::ostream& os) const
{
}

/* _________________________________________________________________________ */

std::istream& operator>>(std::istream& is, QueueMax& q)
{
    return q.loadQueue(is);
}

/* _________________________________________________________________________ */

std::ostream& operator<<(std::ostream& os, const QueueMax& q)
{
    return q.writeStack(os);
}

/* _________________________________________________________________________ */

std::ostream& operator<<(std::ostream& os, const Element& e)
{
    os << e.num << ' ' << e.max;
    return os;
}

/* _________________________________________________________________________ */

/* Fin fichero: queue_max.cpp */
