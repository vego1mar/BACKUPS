#include "Node.h"

// ______________________________________________________________________________________

Node::~Node()
{
// Clearing the pointers.
previous_ = nullptr;
next_ = nullptr;
};

// ______________________________________________________________________________________

Node::Node()
    : data_()
    , previous_(nullptr)
    , next_(nullptr)

{
};

// ______________________________________________________________________________________

Node::Node(const Data & _data)
    : data_(_data)
    , previous_(nullptr)
    , next_(nullptr)

{
};

// ______________________________________________________________________________________

Node & Node::operator= (const Node & _rvalue)
{
// Using the copy construction.
data_ = _rvalue.data_;

// Setting the pointers.
previous_ = _rvalue.previous_;
next_ = _rvalue.next_;

return (*this);
};

// ______________________________________________________________________________________

void Node::SetData(const char * _string)
{
data_.Set(_string);
};

// ______________________________________________________________________________________

void Node::SetPrevious(Node * const _n)
{
if (_n != nullptr)
    {
    previous_ = _n;
    };
};

// ______________________________________________________________________________________

void Node::SetANullPointerToPrevious()
{
previous_ = nullptr;
};

// ______________________________________________________________________________________

void Node::SetNext(Node * const _n)
{
if (_n != nullptr)
    {
    next_ = _n;
    };
};

// ______________________________________________________________________________________

void Node::SetANullPointerToNext()
{
next_ = nullptr;
};

// ______________________________________________________________________________________

const char * Node::GetData() const
{
return (data_.Get());
};

// ______________________________________________________________________________________

const Node * const Node::GetPrevious() const
{
return (previous_);
};

// ______________________________________________________________________________________

const Node * const Node::GetNext() const
{
return (next_);
};

// ______________________________________________________________________________________
