Welcome to my first independent C++ project! I had a lot of fun figuring out how to write this, utilizing a lot of the concepts we've been taught in Bridge, as well as researching new techniques to solve problems.

The MikeyList is a C++ data structure that aims to emulate the functionality of a Python list. It uses a template to adapt to and store any built in data type that is passed to it. You can make a ML with strings, doubles, floats, ints, etc. ML is still strongly typed, so you cannot mix datatypes within it like you would be able to in Python. I also opted to not incorporate a .sort() method to give whoever decides to play around with this structure the flexibility to write custom sorting algorithms.

With that said, if you're familiar with Python, many of the following methods present in MikeyList should be familiar with the addition of a couple new/modified ones:

- length()
	- Returns the logical size of the list as an integer

- getPhysicalSize()
	- Returns the physical size (memory allocated) of the list as an integer

- append(val)
	- Takes one argument and appends it to the end of the list. Calls resizeMList() if necessary.

- findIndex(valToFind)
	- Returns the index of the first occurence of a value as an int

- atIndex(index)
	- Returns the value stored at the specified index

- count(val)
	- Counts how many times a value occurs in the list

- pop(index)
	- Removes an element at the specified index and returns it as value of type T

- remove(val)
	- Removes the first occurrence of a value from the first and does not return it

- extend(arr, arrSize)
	- Allows you to copy the elements of an array over to a MikeyList, appending it to the end

- insert(index, val)
	- Allows you to insert an element at the specified index

- slice(startIndex, endIndex, step, inplace)
	- Allows you to take a slice from a list like in Python (lst[x:y:step])
	  You can choose to do this operation inplace or out of place. If you
	  execute inplace, then the slice will overwrite the calling function
	  If you execute out of place, then a MikeyList object will be returned and must be saved to
        a variable of type MikeyList

- copy()
	- Creates a deep copy of the calling object by calling the deep copy constructor with itself

- clear()
	- Deletes the dynamic array stored at this->mList and reinitializes the variable with null values 

The following operators are overloaded:

- +
	- The + operator requires two arguments of type MikeyList. If this is met, then it will copy
	  The contents of the MLs passed to it into the ML on the left of the assignment operator
	  mL3 = mL1 + mL2

- +=
	- The += operator allows you to quickly append the contents of the ML on the righthand side
	  of the operator to the MikeyList on the lefthand side of the operator
	  mL1 += mL2 

- ==
	- mL1 == mL2 will check that the contents in each index are equivalent. This could be made
	  more advanced so it checks for equality regardless of position like in one of our homework
	  assignments

- []
	- The [] operator is my personal favorite. The way the overload is done allows you to work
	  with a MikeyList object the same way you would work with an array/vector/Python list. You
	  can access elements by index using mL1[index] or assign elements using mL1[index] = value

If you're in my Bridge section or are a professor/TA and you decide to give this a test run let me know what you think! Your feedback is always appreciated :)


