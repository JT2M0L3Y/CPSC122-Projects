/*
*	CPSC 122
*	Lab Final Exam
*	Fall 2021
*
*	Name: Jonathan Smoley
*
*	Notes: N/A
*
*   Deque or Double Ended Queue is a generalized version of Queue data structure
*   that allows insert and delete at both ends.
*   (pronounced �deck� or �deek�) is a double-ended queue. It is similar to a vector,
*	but allows efficient access to values at both the front and the rear.
*/

// Program header area

#include <iostream>

using namespace std;

class DynamicDeque
{
private:
	// Structure for the deque nodes
	struct DequeNode
	{
		int value;			// Value in a node
		DequeNode* nextPtr;	// Pointer to the next node
		DequeNode* prevPtr;	// Pointer to the prev node
	};

	DequeNode* frontPtr;	// The front of the deque
	DequeNode* rearPtr;		// The rear of the deque

	int numItems;	// Number of items in the deque
	int maxSize;	// Limits the maximum number of items in the deque

public:
	// Default Constructor --> should set maxSize to 0
	DynamicDeque();

	// Destructor
	~DynamicDeque();

	// Deque operations
	void enqueue(int);		// Adds an item to the back of the deque
	void dequeue(int&);		// Removes an item from the front of the deque
	bool isEmpty(void) const;	// Returns true if no items are in the deque
	void clear(void);			// Empties the deque of all nodes

	void enqueueFront(int);	// Adds an item to the front of the deque
	void dequeueBack(int&);	// Removes an item from the back of the deque

	// Note: Must be done using recursion
	void displayForward(void) const;		// Displays all nodes in forward order (front to back)
	void displayForward(DequeNode*) const;	// Overloaded helper function for displayForward

	// Note: Must be done using recursion
	void displayReverse(void) const;		// Displays all nodes in reverse order (back to front)
	void displayReverse(DequeNode*) const;	// Overloaded helper function for displayReverse

	int getNumItems(void) const;	// Returns the current size of the deque (aka number of nodes)

	bool isFull(void) const;	// Returns true if the number of nodes is equal to the maximum size
	void resize(int);			// Increases the maximum number of nodes (cannot decrease)

	// Note: Must be done using recursion -- Position counted from the front
	void printNthValue(int) const;	// Prints the value at the Nth node, e.g., N = 1 prints the 1st node value
	void printNthValue(DequeNode*, int) const;	// Overloaded helper function for printNthValue
};

// Class1
class Generic
{
private:
	// Private member variables
public:
	Generic() {}
	~Generic() {}

	void printAbcMessage(void) const { cout << "I was forced into existence by the abstract base class!" << endl; }

	// use final keyword to make a function that cannot be overriden, has to be virtual to use 'final'
	virtual void cannotBeOverriden(void) final { cout << "I cannot be overriden!" << endl; }

	DynamicDeque deque;
};

// Class2
class Derived : public Generic
{
private:
	// Private member variables
public:
	Derived(int size) { deque.resize(size); }
	~Derived() {}
};

// Program main area
int main(void)
{
	int value = 0;
	int numItems = 0;

	// Declare instance of your Derived class with a size of 5 (this is 1 line of code)
	Derived derivedObject(5);

	// Demonstrate class functions
	derivedObject.printAbcMessage();
	derivedObject.cannotBeOverriden();
	cout << endl;

	// Demonstrate deque functions
	// Attempt to change deque size to 3
	derivedObject.deque.resize(3);

	// Attempt to add 6 values to the deque using enqueue
	// values are 2, 10, 20, 30, 40, 50 in that order
	derivedObject.deque.enqueue(2);
	derivedObject.deque.enqueue(10);
	derivedObject.deque.enqueue(20);
	derivedObject.deque.enqueue(30);
	derivedObject.deque.enqueue(40);
	derivedObject.deque.enqueue(50);

	// Output number of items added successfully and display in forward order (front to back)
	cout << "Added " << derivedObject.deque.getNumItems() << " items to the deque." << endl;
	derivedObject.deque.displayForward();
	cout << endl;

	derivedObject.deque.dequeue(value);
	// Output value removed from FRONT, size of deque, and display in forward order (front to back)
	cout << "Removed a " << value << " from the front of the deque" << endl;
	cout << "The deque now contains " << derivedObject.deque.getNumItems() << " items." << endl;
	derivedObject.deque.displayForward();
	cout << endl;

	derivedObject.deque.dequeueBack(value);
	// Output value removed from BACK, size of deque, and display in forward order (front to back)
	cout << "Removed a " << value << " from the back of the deque" << endl;
	cout << "The deque now contains " << derivedObject.deque.getNumItems() << " items." << endl;
	derivedObject.deque.displayForward();
	cout << endl;
	
	// Display list in reverse order
	cout << "Now displaying the deque in reverse order (back to front) " << endl;
	derivedObject.deque.displayReverse();
	cout << endl;
	
	// Output value added to FRONT, size of deque, and display in forward order (front to back)
	cout << "Now adding a 42 to the front of the deque " << endl;
	cout << "The deque now contains " << derivedObject.deque.getNumItems() << " items." << endl;
	derivedObject.deque.enqueueFront(42);
	derivedObject.deque.displayForward();
	cout << endl;
	
	// Output value added to FRONT, size of deque, and display in forward order (front to back)
	cout << "Now adding a 9001 to the front of the deque " << endl;	
	cout << "The deque now contains " << derivedObject.deque.getNumItems() << " items." << endl;
	derivedObject.deque.enqueueFront(9001);
	derivedObject.deque.displayForward();
	cout << endl;

	// Display list in reverse order
	cout << "Now displaying the deque in reverse order (back to front) " << endl;
	derivedObject.deque.displayReverse();
	cout << endl;
	
	// Display list in forward order
	cout << "The final deque now contains " << derivedObject.deque.getNumItems() << " items." << endl;
	derivedObject.deque.displayForward();
	cout << endl;

	// Demonstrate printNthValue function with positions 3, 2, and 20
	cout << "Demonstrating printNthValue():" << endl;
	derivedObject.deque.printNthValue(3);
	derivedObject.deque.printNthValue(2);
	derivedObject.deque.printNthValue(20);

	return 0;
}

// Function definitions area

//********************************************
// The constructor creates an empty deque.   *
//********************************************
DynamicDeque::DynamicDeque()
{
	frontPtr = nullptr;
	rearPtr = nullptr;
	numItems = 0;
}

//********************************************
// Destructor                                *
//********************************************
DynamicDeque::~DynamicDeque()
{
	clear();
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the deque.                 *
//********************************************
void DynamicDeque::enqueue(int num)
{
	if (isFull())
	{
		cout << "The deque is full, " << num << " not added!" << endl;
		return;
	}

	DequeNode* newNode = nullptr;

	// Create a new node and store num there.
	newNode = new DequeNode;
	newNode->value = num;
	newNode->nextPtr = nullptr;
	newNode->prevPtr = nullptr;

	// Adjust front and rear as necessary.
	if (isEmpty())
	{
		frontPtr = newNode;
		rearPtr = newNode;
	}
	else
	{
		newNode->prevPtr = rearPtr;
		rearPtr->nextPtr = newNode;
		rearPtr = newNode;
	}

	// Update numItems.
	numItems++;
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the deque, and copies it into num. *
//**********************************************
void DynamicDeque::dequeue(int& num)
{
	DequeNode* temp = nullptr;

	if (isEmpty())
	{
		cout << "The deque is empty.\n";
	}
	else
	{
		// Save the front node value in num.
		num = frontPtr->value;

		// Remove the front node and delete it.
		temp = frontPtr;
		frontPtr = frontPtr->nextPtr;

		if (!frontPtr) //One element deque
		{
			rearPtr = nullptr;
		}
		else
		{
			frontPtr->prevPtr = nullptr;
		}

		delete temp;

		// Update numItems.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the deque *
// is empty, and false otherwise.             *
//*********************************************
bool DynamicDeque::isEmpty() const
{
	bool status;

	if (numItems > 0)
		status = false;
	else
		status = true;
	return status;
}

//********************************************
// Function clear dequeues all the elements  *
// in the deque.                             *
//********************************************
void DynamicDeque::clear()
{
	int value;   // Dummy variable for dequeue

	while (!isEmpty())
		dequeue(value);
}

//////////////////////////////////////////////
//		Your implmeneted functions below	//
//////////////////////////////////////////////

//*********************************************
// Function enqueueFront inserts an item at the
// front of the deque.
//*********************************************
void DynamicDeque::enqueueFront(int num)
{
	DequeNode* newNode = nullptr;

	// Create a new node and store num there.
	newNode = new DequeNode;
	newNode->value = num;
	newNode->nextPtr = nullptr;

	// Adjust front and rear as necessary.
	if (isEmpty())
	{
		frontPtr = newNode;
		rearPtr = newNode;
	}
	else
	{
		newNode->nextPtr = frontPtr;
		frontPtr->prevPtr = newNode;
		frontPtr = newNode;
	}

	// Update numItems.
	numItems++;
}

//*********************************************
// Function dequeueBack removes an item from
// the back of the deque.
//*********************************************
void DynamicDeque::dequeueBack(int& num)
{
	DequeNode* node = nullptr;
	num = rearPtr->value;

	// Remove the rear node and delete it.
	node = rearPtr;
	rearPtr = rearPtr->prevPtr;

	if (!rearPtr)
	{
		frontPtr = nullptr;
	}
	else
	{
		rearPtr->nextPtr = nullptr;
	}

	delete node;

	// Update numItems.
	numItems--;
}

//*********************************************
// Function displayForward displays the deque
// recursively in forward order.
//*********************************************
void DynamicDeque::displayForward(void) const
{
	displayForward(frontPtr);
	cout << endl;
}

//*********************************************
// Function displayForward displays the deque
// recursively in reverse order.
//*********************************************
void DynamicDeque::displayForward(DequeNode* nodePtr) const
{
	if(nodePtr != nullptr)
	{
		cout << nodePtr->value << " ";
		displayForward(nodePtr->nextPtr);
	}
}

//*********************************************
// Function displayReverse displays the deque
// recursively in reverse order.
//*********************************************
void DynamicDeque::displayReverse(void) const
{
	displayReverse(frontPtr);
	cout << endl;
}

//*********************************************
// Function displayReverse displays the deque
// recursively in reverse order.
//*********************************************
void DynamicDeque::displayReverse(DequeNode* nodePtr) const
{
	if(nodePtr != nullptr)
	{
		displayReverse(nodePtr->nextPtr);
		cout << nodePtr->value << " ";
	}
}

//*********************************************
// Function getNumItems returns the number of
// items in the deque.
//*********************************************
int DynamicDeque::getNumItems(void) const
{
	return numItems;
}

//*********************************************
// Function isFull returns true if the number
// of nodes is equal to the maximum size.
//*********************************************
bool DynamicDeque::isFull(void) const
{
	if(numItems == maxSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*********************************************
// Function resize increases the max number
// of nodes by the amount specified.
//*********************************************
void DynamicDeque::resize(int size)
{
	if(size < maxSize)
	{
		cout << "Error, new size must be greater than current size." << endl;
	}
	else
	{
		maxSize = size;
	}
}

//*********************************************
// Function printNthValue displays the value
// at the nth position in the deque.
//*********************************************
void DynamicDeque::printNthValue(int ndx) const
{
	printNthValue(frontPtr, ndx);
}

//*********************************************
// Function printNthValue displays the value
// at the nth position in the deque.
//*********************************************
void DynamicDeque::printNthValue(DequeNode* nodePtr, int ndx) const
{
	int count = 0;

   	while(count < ndx)
   	{
      	if(nodePtr->value != ndx)
      	{
			nodePtr = nodePtr->nextPtr;
			// printNthValue(nodePtr->nextPtr, ndx);
         	count++;
      	}
		else
		{
			cout << ndx << " is an invalid position in this deque!" << endl;
			return;
		}
   	}
	cout << "The value at position " << ndx << " is " << nodePtr->prevPtr->value << endl;

	// if(nodePtr->value == ndx - 1)
	// {
	// 	cout << "The value at position " << ndx << " is " << nodePtr->prevPtr->value << endl;
	// }
	// else if(nodePtr == nullptr)
	// {
	// 	cout << ndx << " is an invalid position in this deque!" << endl;
	// }
	// printNthValue(nodePtr->nextPtr, ndx++);
}
