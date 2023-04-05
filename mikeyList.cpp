#include <iostream>
#include <string>
using namespace std;

template <typename T>
class MikeyList {
public:
    // Constructors //

    // Default empty constructor. Sets LS to 0, PS to 2
    // Init mList to empty
    MikeyList() {
        logicalSize = 0;
        physicalSize = 1000;
    }

    // Array conversion constructor. You can pass in an array and its
    // size to convert it to a MikeyList
    MikeyList(T arr[], int arrSize) {
        logicalSize = 0;
        physicalSize = 1000;
        for (int i = 0; i < arrSize; i++) {
            this->append(arr[i]);
        }
    }

    // Initializer list constructor. This allows you to use the format
    // MikeyList <T> varName = {1, 2, 3, 4 ... n}
    MikeyList(std::initializer_list<T> list) {
        logicalSize = 0;
        physicalSize = 1000;
        for (auto i = list.begin(); i != list.end(); i++) {
            this->append(*i);
        }
    }

    // Copy Constructor //
    MikeyList(MikeyList<T> &original) {
        logicalSize = original.logicalSize;
        physicalSize = original.physicalSize;

        for (int i = 0; i < logicalSize; i++) {
            mList[i] = original.mList[i];
        }
    }

    // Methods //

    // Prints the elements in the list
    void print();
    
    // Returns the logical size of the list
    int length() { return logicalSize; }

    // Returns the physical size of the list
    int getPhysicalSize() { return physicalSize; }
    
    // Similar to vector.push_back. Appends an element to the
    // end of the list
    void append(T val);

    // Returns the index of the first occurrence of a value
    int findIndex(T toFind);

    // Returns the value at the specified index
    T atIndex(int index) { return mList[index]; }

    // Counts the number of times a value occurs in the list
    int count(T val);

    // Removes the element at the specified index from the list
    // and returns the value that and returns the value that is removed
    T pop(int index);

    // Removes an element from the list and does not return it
    void remove(T val);

    // Allows you to copy the elements of an array (dynamic or static)
    // over to a MikeyList.
    void extend(T *arr, int arrSize);

    // Inserts an element at the specified index
    void insert(int index, T val);

    // Allows you to take a slice from a list (lst[x:y:step]) and either
    // return it in place or out of place
    // If you return it in place, the slice will overwrite the calling object
    // If you return it out of place, you must save it to another MikeyList object
    MikeyList<T> slice(int startIndex, int endIndex, int step = 1, bool inPlace = false);

    // Deletes the dynamic array stored at mList and reinitializes the
    // variable with null values.In Python, this method is .delete, but
    // since delete is a keyword in C++, I called it del.
    void clear();

    // Operator Overloading //

    // mL3 = mL1 + mL2 will append the contents of both mL1 and mL2 to mL3
    // In all of these overloads, I use the append method as it has a built in
    // check and resize method. This prevents code redundancy.
    friend MikeyList<T> operator+ (MikeyList<T> &arr1, MikeyList<T> &arr2) {
        MikeyList<T> temp;

        for (int i = 0; i < arr1.logicalSize; i++) {
            temp.append(arr1.mList[i]);
        }

        for (int i = 0; i < arr2.logicalSize; i++) {
            temp.append(arr2.mList[i]);
        }

        return temp;
    }

    // mL1 += mL2 will append the contents of mL2 to mL1;
    MikeyList<T> & operator += (MikeyList<T> &rhsArr) {
        for (int i = 0; i < rhsArr.logicalSize; i++) {
            this->append(rhsArr[i]);
        }
        return *this;
    }

    // mL1 == mL2 will check that the contents in each index are equivalent
    // this could be made more advanced so it checks for equality regardless
    // of position
    friend bool operator == (MikeyList<T> &arr1, MikeyList<T> &arr2) {
        if (arr1.logicalSize != arr2.logicalSize) {
            return false;
        } else {
            for (int i = 0; i < arr1.logicalSize; i++) {
                if (arr1[i] != arr2[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    // This overload allows you to work with a MikeyList like a normal list.
    // You can index using mL[ind] and assign using mL[ind] = val
    T & operator [] (int index) {
        if (index >= logicalSize) {
            cout<<"Error: Index out of range.";
            exit(0);
        } else {
            return mList[index];
        }
    }

    MikeyList<T> operator = (MikeyList<T> &rhsArr) {
        delete [] this->mList;
        this->mList = new int[rhsArr.physicalSize];

        this->logicalSize = rhsArr.logicalSize;
        this->physicalSize = rhsArr.physicalSize;

        for (int i = 0; i <= logicalSize; i++) {
            this->mList[i] = rhsArr.mList[i];
        }

        return *this;
    }

    // Destructor //

    // Deallocates memory used to store mList when a MikeyList object goes
    // out of scope
    ~MikeyList() {
        delete [] mList;
        mList = NULL;
    }
        
private:
    int physicalSize;
    int logicalSize;
    T *mList = new T[1000];
    void resizeMList();
};

// Member function definitions - See above for documentation
// If you're familiar with Python, these should work very similarly
// to Python's list methods

template <typename T> 
void MikeyList<T>::print() {
    cout<<"[ ";
    for (int i = 0; i < logicalSize; i++) {
        cout<<mList[i]<<" ";
    }
    cout<<"]";
    return;
}

template <typename T>
void MikeyList<T>::resizeMList() {
    physicalSize *= 2;
    T *resized = new T[physicalSize];
    
    for (int i = 0; i < logicalSize; i++) {
        resized[i] = mList[i];
    }
    
    delete [] mList;
    
    mList = resized;

    return;
}

template <typename T>
void MikeyList<T>::append(T val) {
    if (logicalSize < physicalSize) {
        mList[logicalSize] = val;
        logicalSize++;
    } else {
        resizeMList();
        mList[logicalSize] = val;
        logicalSize++;
    }
    return;
}

template <typename T>
int MikeyList<T>::findIndex(T toFind) {
    for (int i = 0; i < logicalSize; i++) {
        if (mList[i] == toFind) {
            return i;
        }
    }
    return -1;
}

template <typename T>
int MikeyList<T>::count(T val) {
    int countVar = 0;
    for (int i = 0; i < logicalSize; i++) {
        if (mList[i] == val) {
            countVar++;
        }
    }
    return countVar;
}

template <typename T>
T MikeyList<T>::pop(int index) {
    T toReturn = mList[index];
    for (int i = index; i < logicalSize; i++) {
        mList[i] = mList[i + 1];
    }
    logicalSize -= 1;
    return toReturn;
}

template <typename T>
void MikeyList<T>::remove(T val) {
    int ind = findIndex(val);
    if (ind == -1) {
        cout<<"Item not found"<<endl;
    } else {
        for (int i = ind; i < logicalSize; i++) {
            mList[i] = mList[i + 1];
        }
    }
    logicalSize -= 1;
    return;
}

template <typename T>
void MikeyList<T>::extend(T arr[], int arrSize) {
    int lsCopy = logicalSize;
    for (int i = lsCopy; i < lsCopy + arrSize; i++) {
        if (logicalSize < physicalSize) {
            mList[i] = arr[0];
            arr += 1;
            logicalSize++;
        } else {
            resizeMList();
            mList[logicalSize] = arr[0];
            arr += 1;
            logicalSize ++;
        }
    }
    return;
}

template <typename T>
void MikeyList<T>::insert(int index, T val) {
    if (logicalSize + 1 >= physicalSize) {
        resizeMList();
    }

    if (index <= logicalSize) {
        logicalSize += 1;
        int i = 0;
        for (int i = logicalSize; i >= index; i--) {
            mList[i] = mList[i - 1];
        }
        mList[index] = val;
        return;
    } else {
        cout<<"Error: Index out of range"<<endl;
        return;
    }
}

template <typename T>
MikeyList<T> MikeyList<T>::slice(int startIndex, int endIndex, int step, bool inPlace) {
    if (inPlace == true) {
        MikeyList<T> temp;
        for (int i = startIndex; i < endIndex; i += step) {
            temp.append(this->mList[i]);
        }
        this->clear();
        for (int i = 0; i < temp.logicalSize; i++) {
            this->append(temp[i]);
        }
        return *this;
    } else {
        MikeyList<T> temp;
        for (int i = startIndex; i < endIndex; i += step) {
            temp.append(this->mList[i]);
        }
        return temp;
    }
}
template <typename T>
void MikeyList<T>::clear() {
    delete [] mList;

    mList = new int[1000];
    logicalSize = 0;
    physicalSize = 1000;

    return;
}

int main() {
    return 0;
}