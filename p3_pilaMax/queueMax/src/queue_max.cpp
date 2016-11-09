/**
  * @file queue_max.cpp
  * @brief Fichero de implementación del T.D.A. QueueMax
  *
  */

T& QueueMax::front()
{
}

/* _________________________________________________________________________ */

const T& QueueMax::front() const
{
}

/* _________________________________________________________________________ */

void QueueMax::push(int n)
{
}

/* _________________________________________________________________________ */

void QueueMax::pop()
{
}

/* _________________________________________________________________________ */

void QueueMax::clear()
{
}

/* _________________________________________________________________________ */

int QueueMax::size() const
{
}

/* _________________________________________________________________________ */

bool QueueMax::empty() const
{
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
