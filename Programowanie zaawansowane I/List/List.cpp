#include "List.h"

// ______________________________________________________________________________________

List::List()
    : first_(nullptr)
    , last_(nullptr)
    , current_(nullptr)
    , number_(0)
    , queue_(nullptr)
    , deleted_(0)

{
// Allocating the data on the heap.
queue_ = new Node [SIZE];
};

// ______________________________________________________________________________________

List::~List()
{
// Clearing the pointers.
first_ = nullptr;
last_ = nullptr;
current_ = nullptr;

// Clearing the memory.
number_ = 0;
deleted_ = 0;
ClearTheQueue();

// Deallocating the list.
delete [] queue_;
};

// ______________________________________________________________________________________

List::List(const List & _rvalue)
    : first_(_rvalue.first_)
    , last_(_rvalue.last_)
    , current_(_rvalue.current_)
    , number_(_rvalue.number_)
    , deleted_(_rvalue.deleted_)

{
// Declarations.
unsigned short int i;

// Allocating the data on the heap.
queue_ = new Node [SIZE];

// Copying 1-to-1.
for (i=0; i<SIZE; i++)
    {
    queue_[i] = _rvalue.queue_[i];
    };
};

// ______________________________________________________________________________________

List & List::operator= (const List & _rvalue)
{
// Declarations.
unsigned short int i;

// Setting the values.
first_ = _rvalue.first_;
last_ = _rvalue.last_;
current_ = _rvalue.current_;
number_ = _rvalue.number_;
deleted_ = _rvalue.deleted_;

// Copying the class Node's queue 1-to-1.
for (i=0; i<number_; i++)
    {
    queue_[i] = _rvalue.queue_[i];
    };

return (*this);
};

// ______________________________________________________________________________________

const char * List::operator[] (unsigned short int _idx)
{
// Declarations.
unsigned short int j;
Node * tmp = current_;

// :: Checking the list bounds.
if ((_idx > 0) && (_idx <= number_))
    {
    // Setting the index at the right place.
    j = deleted_ + _idx - 1;
    tmp = &(queue_[j]);
    };

// Declarations.
// Be caucious with non-static const char * here.
const char * str = tmp->GetData();

return (str);
};

// ______________________________________________________________________________________

const char * const List::operator[] (unsigned short int _idx) const
{
// Declarations.
unsigned short int j;
Node * tmp = current_;

// :: Checking the list bounds.
if ((_idx > 0) && (_idx <= number_))
    {
    // Setting the index at the right place.
    j = deleted_ + _idx - 1;
    tmp = &(queue_[j]);
    };

// Declarations.
// Be caucious with non-static const char * here.
const char * str = tmp->GetData();

return (str);
};

// ______________________________________________________________________________________

void List::SetFirstElement(class Node * const _node)
{
first_ = _node;
};

// ______________________________________________________________________________________

void List::SetLastElement(class Node * const _node)
{
last_ = _node;
};

// ______________________________________________________________________________________

void List::SetCurrentElement(class Node * const _node)
{
current_ = _node;
};

// ______________________________________________________________________________________

void List::SetNumberOfElements(unsigned short int _n)
{
if (_n > 0)
    {
    number_ = _n;
    };
};

// ______________________________________________________________________________________

void List::SetNodeOnTheQueue(unsigned short int _idx, const char * _string, Node * const _prev, Node * const _next)
{
// :: Checking the bounds.
if ((_idx >= 0) && (_idx < SIZE))
    {
    queue_[_idx].SetData(_string);
    queue_[_idx].SetPrevious(_prev);
    queue_[_idx].SetNext(_next);
    if (_prev == nullptr) queue_[_idx].SetANullPointerToPrevious();
    if (_next == nullptr) queue_[_idx].SetANullPointerToNext();
    };
};

// ______________________________________________________________________________________

void List::SetNumberOfDeletedNodes(unsigned short int _n)
{
if (_n > 0)
    {
    deleted_ = _n;
    };
};

// ______________________________________________________________________________________

const class Node * const List::GetFirstElement() const
{
return (first_);
};

// ______________________________________________________________________________________

const class Node * const List::GetLastElement() const
{
return (last_);
};

// ______________________________________________________________________________________

const class Node * const List::GetCurrentElement() const
{
return (current_);
};

// ______________________________________________________________________________________

unsigned short int List::GetNumberOfElements() const
{
return (number_);
};

// ______________________________________________________________________________________

unsigned short int List::GetListSize() const
{
return (SIZE);
};

// ______________________________________________________________________________________

unsigned short int List::GetNumberOfDeletedNodes() const
{
return (deleted_);
};

// ______________________________________________________________________________________

const class Node * const List::GetNodeOnTheQueue(unsigned short int _idx) const
{
// Declarations.
Node * tmp1 = current_;

// :: Checking the bounds.
if ((_idx >= 0) && (_idx < SIZE))
    {
    tmp1 = &(queue_[_idx]);
    };

return (tmp1);
};

// ______________________________________________________________________________________

void List::AddNode(const class Data & _data)
{
// Updating a new node at the queue list nodes chain.
Node * const tmp = &(queue_[number_]);
tmp->SetData(_data.Get());
tmp->SetANullPointerToNext();

// Checking if it is the first element.
if (first_ == nullptr)
    {
    first_ = tmp;
    last_ = tmp;
    current_ = tmp;
    tmp->SetANullPointerToPrevious();
    }
// Handling with the next element.
else
    {
    tmp->SetPrevious(last_);
    last_ = tmp;
    current_ = tmp;
    tmp->SetANullPointerToNext();
    queue_[number_-1].SetNext(tmp);
    };

// Updating the number of elements on the list.
number_++;
};

// ______________________________________________________________________________________

bool List::RemoveNode()
{
// Declarations.
bool op = true;

// :: Checking the elements on the list.
if (number_ == 0)
    {
    op = false;
    }
else
if (number_ == 1)
    {
    // Clearing the removed node.
    first_->SetData(" ");
    first_->SetANullPointerToPrevious();
    first_->SetANullPointerToNext();

    // Updating the list poles.
    first_ = nullptr;
    last_ = nullptr;
    current_ = nullptr;
    number_ = 0;
    deleted_++;
    }
else
    {
    // Retrieving a pointer to the element that should the first now.
    Node * tmp = const_cast<Node *>(first_->GetNext());
    tmp->SetANullPointerToPrevious();

    // Clearing the removed node.
    first_->SetData(" ");
    first_->SetANullPointerToPrevious();
    first_->SetANullPointerToNext();

    // Updating the list poles.
    first_ = tmp;
    current_ = tmp;

    // Updating the number of elements on the list.
    number_--;
    deleted_++;
    };

return (op);
};

// ______________________________________________________________________________________

class Node & List::GetElementDataAt(unsigned short int _idx)
{
// Declarations.
Node * tmp = current_;

// :: Checking the list bounds.
if ((_idx > 0) && (_idx <= SIZE))
    {
    // Giving the right pointer.
    tmp = &(queue_[_idx-1]);
    }
else
if (!_idx)
    {
    tmp = &(queue_[0]);
    };

// A passing through declaration.
Node & tmp2 = *tmp;

return (tmp2);
};

// ______________________________________________________________________________________

class Node * const List::GetPreviousElement()
{
current_ = const_cast<Node *>(current_->GetPrevious());
return (current_);
};

// ______________________________________________________________________________________

class Node * const List::GetNextElement()
{
current_ = const_cast<Node *>(current_->GetNext());
return (current_);
};

// ______________________________________________________________________________________

void List::Rewind()
{
current_ = first_;
};

// ______________________________________________________________________________________

void List::ClearTheQueue()
{
bool rm = RemoveNode();

while (rm)
    {
    RemoveNode();
    };
};

// ______________________________________________________________________________________
