/*
STL Containers
(c) 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

// The standard template library (STL) includes several container classes that use templates to manage collections of objects for you.
// This example will cover some, but not all of the basics of these container classes. For more information you can always view the documentation online.



#include <vector>   // A vector is a managed array. Adding things to the end of a vector are speedy, but inserting in the middle of the colleciton is inefficient.
                    // Vectors are nice when you need to access items in the collection quickly at an arbitrary location, because they are stored in a straight line.

#include <list>     // A list (or a linked list) is a collection that tracks objects by keeping them in a chain. This makes it easy to add or remove individual
                    // links in the chain. Unlike with vectors, it's hard to access arbitrary objects, because you need to loop forward or backwards until reaching the target.

#include <stack>    // A stack is a much more restricted list, FILO (First In Last Out). Objects can only be added or removed at one end of the stack.
                    // This means that the stack will always be ordered from newest to oldest.

#include <queue>    // Similar to a stack, but FIFO (First In First Out). Objects in a queue can only be removed in the order they were added.
                    // This means that it will be ordered from oldest to newest.

#include <set>      // A set is a sorted collection of objects. It does this by organizing it's contents into a tree. Every value in the set must be unique.
                    // You don't need to understand the implementation for this example. Just know that sets are slower than lists, but are automatically sorted.

#include <map>      // A map is a collection that uses key-value pairs. An object is stored with a unique secondary value that is used to identify it.
                    // The key can then be used to access an object from the map at any time. Maps use a similar strategy to sets when organizing their information.

// Start of main function
int main() 
{
    {
        // The first example is vector:
        std::vector<int> intVector;     // Vectors are probably the simplest collection you'll use in the STL.
                                        // In terms of complexity, vectors are one step up from arrays.

        intVector.push_back(4);         // Adding objects to a vector is simple. Just call push_back(), passing in the thing you want to add.
        intVector.push_back(5);         
        intVector.push_back(6);


        int element0 = intVector.at(0);     // at() can be used to get an object at a specific index in the vector.
        intVector.at(0) = 1;                // with the power of references, you can also write to the vector with at().


        int element1 = intVector.data()[1]; // alternatively, you can use .data() to get the underlying array that the vector uses.
        // intVector.data = { 1, 2 }  NO!   // This array is const (read only)
        intVector.data()[1] = 2;            // The values inside can still be changed though.

        
        int element2 = intVector[2];        // Using operator overloading magic, we can treat the vector like an array with [].
        intVector[2] = 3;                   // This can be read/write too.


        std::cout << "print out elements from vector:" << std::endl;
        std::cout << element0 << " " << element1 << " " << element2 << std::endl;


        // Just accessing using an index can be dangerous, because you can get an index out of bounds error with the array.
        // If you want to loop over all the elements in the vector, you can use .size() to get the length of the vector. (unsigned int. Vectors don't have negative size!)
        for (unsigned int i = 0; i < intVector.size(); i++)
        {
            std::cout << intVector[i] << std::endl;
            // Note: You can also use a thing called iterators for this, but we'll get to that later.
        }


        // Vector automatically resizes the array when you add and remove things, but it has a few helpful functions related to this:

        // Resize will change the size of the array. This removes objects if it would shrink the array, and adds objects if it grows the array.
        std::cout << "intVector.resize(1);" << std::endl;
        intVector.resize(1);


        std::cout << "intVector.size():" << std::endl;      // size is the number of elements in the vector.
        std::cout << intVector.size() << std::endl;
        std::cout << "intVector.capacity():" << std::endl;  // capacity tells you how much space is available before the internal array will be resized.
        std::cout << intVector.capacity() << std::endl;


        std::cout << "intVector.clear();" << std::endl;     // Clear sets the size of the vector to 0, and destroyes the internal objects.
        intVector.clear();                                  
        std::cout << "intVector.reserve(50);" << std::endl; // Reserve resizes the internal array to make room for a given number of objects.
        intVector.reserve(50);                              // This is useful to avoid multiple resizes when adding a lot of things.

        // Print out size and capacity after changes:
        std::cout << "intVector.size():" << std::endl;
        std::cout << intVector.size() << std::endl;
        std::cout << "intVector.capacity():" << std::endl;
        std::cout << intVector.capacity() << std::endl;


        std::cout << "intVector.resize(10, 5);" << std::endl;   // resize() can take in a second value, which determines the default value for the extra objects created.
        intVector.resize(10, 5);
        std::cout << "intVector.shrink_to_fit();" << std::endl; // shrink_to_fit() decreases the capacity to match the size that is actually used.
        intVector.shrink_to_fit();                    

        // Print out size and capacity after changes:
        std::cout << "intVector.size():" << std::endl;
        std::cout << intVector.size() << std::endl;
        std::cout << "intVector.capacity():" << std::endl;
        std::cout << intVector.capacity() << std::endl;
        std::cout << "intVector[5]: " << intVector[5] << std::endl;

        // That's the basics of using vector, but not everything. Take a look at the documentation for mor info!

        std::cin.get();
    }


    {
        // Next is list.
        // List is nice because you can insert things in the middle of the collection easily.

        std::list<int> intList;

        intList.push_back(3);
        intList.push_back(5);   // many of these class templates have similar functions, so we'll cover them more quickly.
        intList.push_back(6);
        

        // How do we loop over the elements of a list?
        std::cout << "looping over list" << std::endl;

        // This may look a bit funky, but I'll explain how it works.
        // the STL gives us a special object type called an iterator.
        // Iterators a objects that act as pointers with some extra functionality, and help us loop over collections that aren't in a row like vectors are.

        for (auto it = intList.begin(); it != intList.end(); it++)  // first we use auto, because the actual type of the iterator is std::list<int>::iterator.
        {                                                           // we set it to the beginning of the collection, and loop until we reach the end of the colleciton.
            std::cout << *it << std::endl;                          // ++ is an operator overload that makes the iterator point at the next object in the colleciton. 
        }                                                           // * dereferences the pointer to get our object from the iterator, and print it out!

        // This is the basic way that most of the STL collections do loops, so you'll see it all over the place in different C++ code.
        


        // Many of the other functions that make list different from vector are based on iterators, for example:
        // insert takes an iterator, and inserts a value into the list at that location.
        std::cout << "intList.emplace(intList.begin(), 2);" << std::endl;
        intList.insert(intList.begin(), 2);

        // erase removes an element from the list using an iterator location.
        // In this case, we use the second element from the end of the list. (end is actually after the end of the list, so we have to go -- twice.)
        std::cout << "intList.erase(----intList.end());" << std::endl;
        intList.erase(----intList.end());

        // loop over the list and print out the change:
        for (auto it = intList.begin(); it != intList.end(); it++)
        {
            std::cout << *it << std::endl;
        }

        std::cin.get();
    }







    {
        // Stacks and Queues should be easy to cover now that we've seen lists

        // Instead of allowing access anywhere, the stack can be even more efficient by only allowing you to access the newest element at any given time.
        std::stack<int> myStack;

        std::cout << "adding 1, 2, 3 to stack:" << std::endl;
        myStack.push(1);    // push() adds an element to the stack.
        myStack.push(2);
        myStack.push(3);


        std::cout << "reading elements from stack, and then popping them off:" << std::endl;
        while (myStack.size() != 0)
        {
            std::cout << myStack.top() << std::endl;    // top() allows us to read from the top of the stack.
                                                        // This is the only way to read elements from a stack.

            myStack.pop();                              // pop() removes that element from the stack.
                                                        // (top will now read a different element)
        }

    

        // Queues work similarly, but only allow reading from the other end:
        std::queue<int> myQueue;

        std::cout << "Adding 1, 2, 3 to queue:" << std::endl;
        myQueue.push(1);    // queues use the same push function that stacks do.
        myQueue.push(2);
        myQueue.push(3);

        std::cout << "reading elements from queue, and then popping them off:" << std::endl;
        while (myQueue.size() != 0)
        {
            std::cout << myQueue.front() << std::endl;  // front() reads from the front of the queue.

            myQueue.pop();                              // pop() removes from the front of the queue.
        }

        
        std::cin.get();
    }





    return 0;   // End Program.
}