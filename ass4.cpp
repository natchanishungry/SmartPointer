#include <memory>
#include <string>
#include <iostream>


/*
Question 1:
Research smart pointers provided by the standard library (since C++11). List them
and explain the difference between them.

Smart pointers are defined in the std namespace in the <memory> header file.

Using smart pointers allows you to initialize pointers without using keywords "new"
and "delete", meaning it allows the programmer not to worry about ever having to
delete the pointer.

A smart pointer is a class template that you declare on the stack. You then can
initialize a smart pointer by using a raw pointer that points to a heap-allocated
object. Once the smart pointer is initialized, it "owns" the raw pointer (so it
will be the one responsible for deleting the raw pointer memory). Incidentally,
the smart pointer destructor contains the code that deletes the raw pointer it
was assigned. Once the smart pointer is out of scope, its destructor is called.

Smart pointers are used to help ensure that a program is free of memory leaks
and is exception-safe. If you initialize a raw pointer it is best to pass the
pointer to a smart pointer immediately (unless the raw pointer is used in small
code blocks where performance is critical). Passing the raw pointer to the smart
pointer will clear all confusion about ownership.

Different types of smart pointers are:

UNIQUE POINTERS: unique_ptr
A unique pointer is a scoped pointer, meaning that when that pointer goes out out
of scope, it will get destroyed, so it will call delete. The reason they are called
unique pointers is because they have to be unique; you can't copy a unique pointer.
In fact, the copy constructor and copy assignment operators of
unique_ptr are actually deleted in the standard library.
e.g.:
unique_ptr(const _Myt&) = delete;
_Myt& operator=(const _My&) = delete;

If, hypothetically, you copied a unique pointer, the memory the copy would be pointing
to would be the same as the source. You would have two unique pointers pointing to the
same block of memory, and when one of them is destroyed, it would free that memory,
meaning that the other pointer would be pointing to jibberish freed memory.
A unique pointer is a stack-allocated object, and once it goes out of scope,
the destructor will call delete on that pointer.
The problem with this, is that if you want to copy or "share" that pointer, for instance,
if you want to pass it into a function, you're going to run into a problem, because
you can't copy it. You can use a shared pointer for this.

SHARED POINTERS: shared_ptr
Shared pointers use reference counting. Reference couting is a practice where you
keep track of how many references you have to your pointer. As soon as that reference
counter reaches 0, that's when the raw pointer is officially deleted.
As an example: if I create one shared pointer, I then create another shared pointer
which is a copy of the initial shared pointer, my reference count is now 2. When
one of them dies, my reference count is 1, and once the second one dies, my reference
count is 0, and the memory containing the raw pointer is then freed.
The size of a shared pointer is two pointers; one for the object and one for the
shared control block that contains the reference count.

WEAK POINTERS: weak_ptr
Creating a weak pointer, and assigning it to a shared pointer is kinda the same
as making another new shared pointer, but without increasing the reference count.
So a weak pointer provides access to an object owned by one or more shared_ptr
instances, without participating in reference counting. This is useful when you
want to observe an object, but do not require it to remain alive.

*/

using namespace std;

class SmartPointer{
public:
  SmartPointer()
  {
    secret = new int(0);
  }

  SmartPointer(int x)
  {
    secret = new int(x);
  }

  ~SmartPointer()
  {
    delete secret;
  }

  int getValue()
  {
    return *secret;
  }

  void setValue(int x)
  {
    *secret = x;
  }

private:
  int* secret;
};

int main()
{
  //Testing getValue and setValue
  SmartPointer sPointer(11);
  cout << sPointer.getValue() << endl;
  sPointer.setValue(13);
  cout << sPointer.getValue() << endl;
  return 0;

}
