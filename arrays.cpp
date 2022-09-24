#include <iostream>
#include <assert.h>
using namespace std;

enum Direction
{
    left,
    right
};

template <typename T>

class Array
{
private:
    T *A;
    int size;
    int length;

    /// @brief swaps the value of 2 pointers
    /// @param v1 the first pointer
    /// @param v2 the second pointer
    void _swap(T *v1, T *v2)
    {
        T temp = *v1;
        *v1 = *v2;
        *v2 = temp;
    }

    /// @brief compares 2 values and finds the minimum between them.
    /// @param val1 the first value to be compared.
    /// @param val2 the second value to be compared.
    /// @return returns the minimum of both.
    T _min(T val1, T val2)
    {
        return val1 < val2 ? val1 : val2;
    }

public:
    Array()
    {
        this->size = 10;
        this->length = 0;
        this->A = new T[10];
    }
    Array(T *arr, int size, int length)
    {
        assert(size >= length && "size of the array must be greater than or equal to the provided length.");
        this->size = size;
        this->length = length;
        this->A = new T[size];
        for (int i = 0; i < length; i++)
        {
            A[i] = arr[i];
        }
    }
    ~Array()
    {
        delete A;
    }

    /// @brief Display the array.
    void display()
    {
        for (int i = 0; i < length; i++)
        {
            cout << A[i];
            if (i != length - 1)
            {
                cout << " ";
            }
        }
    }

    /// @brief Append a value.
    /// @param val the value which is to be added.
    /// @param treatArrayAsSorted Defaults to false. If this is set to true, The val is added in sorted order else it is added at the end.
    void append(T val, bool treatArrayAsSorted = false)
    {
        if (length + 1 < size)
        {
            if (treatArrayAsSorted == false)
            {
                A[length++] = val;
            }
            else
            {
                int i = length - 1;
                for (; A[i] > val; i--)
                {
                    A[i + 1] = A[i];
                }
                A[i + 1] = val;
                length++;
            }
        }
    }
    /// @brief insert a value at a given index.
    /// @param val the value to be inserted.
    /// @param index index at which the value is supposed to be added.
    void insert(T val, int index)
    {
        if (index >= 0 && index < size && length + 1 < size)
        {
            for (int i = length; i > index; i--)
            {
                A[i] = A[i - 1];
            }
            A[index] = val;
            length++;
        }
    }

    /// @brief insert a value in a sorted array such that it still remains sorted.
    /// @param val the value to be inserted.
    void insertSorted(T val)
    {
        if (length + 1 < size)
        {
            int i = length - 1;
            for (; A[i] > val; i--)
            {
                A[i + 1] = A[i];
            }
            A[i + 1] = val;
            length++;
        }
    }

    /// @brief It checks if the array was sorted.
    /// @return returns true if the array is sorted else return false.
    bool isSorted()
    {
        for (int i = 0; i < length - 1; i++)
        {
            if (A[i + 1] < A[i])
            {
                return false;
            }
        }
        return true;
    }

    /// @brief removes a value from the array if it exists.
    /// @param val the value to be removed.
    void del(T val)
    {
        int index = search(val);
        if (index != -1)
        {
            for (int i = index; i < length; i++)
            {
                A[i] = A[i + 1];
            }
            length--;
        }
    }

    /// @brief Removes the value in the array at the given index.
    /// @param index The index at which the array is supposed to be removed.
    /// @return returns the value which was removed.
    T pop(int index)
    {
        if (index >= 0 && index < length)
        {
            T val = A[index];
            for (int i = index; i < length; i++)
            {
                A[i] = A[i + 1];
            }
            length--;
            return val;
        }
    }

    /// @brief searches for a value in the array and returns the index if found else return -1.
    /// @param val The value to be searched.
    /// @param treatArrayAsSorted if the array is sorted binary search[O(logn)] is applied else linear Search[O(n)] is applied
    /// @return returns the index of the value if found else returns -1.
    int search(T val, bool treatArrayAsSorted = false)
    {
        if (length > 0)
        {
            if (treatArrayAsSorted == false)
            {
                for (int i = 0; i < length; i++)
                {
                    if (A[i] == val)
                    {
                        return i;
                    }
                }
            }
            else
            {
                int low = 0;
                int high = length - 1;
                int mid = (low + high) / 2;
                if (A[high] < val || A[low] > val)
                {
                    return -1;
                }
                while (true)
                {
                    if (A[low] == val)
                    {
                        return low;
                    }
                    else if (A[mid] == val)
                    {
                        return mid;
                    }
                    else if (A[high] == val)
                    {
                        return high;
                    }
                    else if (high - low <= 1)
                    {
                        return -1;
                    }
                    else
                    {
                        if (A[mid] > val)
                        {
                            high = mid - 1;
                            mid = (low + high) / 2;
                        }
                        else
                        {
                            low = mid + 1;
                            mid = (low + high) / 2;
                        }
                    }
                }
            }
        }
        return -1;
    }

    /// @brief Returns the value at the given index from the array.
    /// @param index index at which the value is to be returned.
    /// @return returns the value from the array whose index was provided.
    T getElement(int index)
    {
        if (index >= 0 && index < length)
        {
            return A[index];
        }
        return -1;
    }

    /// @brief returns the length of the array
    /// @return returns the length of the array
    int getLength()
    {
        return length;
    }

    /// @brief replaces the old value with the new value provided at a given index in the array.
    /// @param val the new value to be replaced.
    /// @param index index at which the new value is supposed to be exchanged.
    void set(T val, int index)
    {
        if (index >= 0 && index < length)
        {
            A[index] = val;
        }
    }

    /// @brief finds the maximum in the array.
    /// @param treatArrayAsSorted  if this is set true it returns the last value thus O(1) else it uses linear search[O(n)].
    /// @return returns the maxmimum value from the array.
    T max(bool treatArrayAsSorted = false)
    {
        if (length > 0)
        {
            if (treatArrayAsSorted == false)
            {
                T maxTerm = A[0];
                for (int i = 0; i < length; i++)
                {
                    if (A[i] > maxTerm)
                    {
                        maxTerm = A[i];
                    }
                }
                return maxTerm;
            }
            else
            {
                return A[length - 1];
            }
        }
        return -1;
    }

    /// @brief finds the inimum in the array.
    /// @param treatArrayAsSorted  if this is set true it returns the first value thus O(1) else it uses linear search[O(n)].
    /// @return returns the minimum value from the array.
    T min(bool treatArrayAsSorted = false)
    {
        if (length > 0)
        {
            if (treatArrayAsSorted == false)
            {
                T minTerm = A[0];
                for (int i = 0; i < length; i++)
                {
                    if (A[i] < minTerm)
                    {
                        minTerm = A[i];
                    }
                }
                return minTerm;
            }
            else
            {
                return A[0];
            }
        }
        return -1;
    }

    /// @brief reverses the elemnts of the array.
    void reverse()
    {
        for (int i = 0, j = length - 1; i < j; i++, j--)
        {
            _swap(&A[i], &A[j]);
        }
    }

    /// @brief shifts all the elements of the array in the given Direction.
    /// @param dir if the Direction is set to left, all the elemnts move left and the last element is set to 0 else all the elements move right and the first element is set to 0
    void shift(Direction dir = Direction::left)
    {
        if (length > 0)
        {
            if (dir == Direction::left)
            {
                for (int i = 0; i < length - 1; i++)
                {
                    A[i] = A[i + 1];
                }
                A[length - 1] = 0;
            }
            else
            {
                if (length > 0)
                {
                    for (int i = length - 1; i > 0; i--)
                    {
                        A[i] = A[i - 1];
                    }
                    A[0] = 0;
                }
            }
        }
    }

    /// @brief rotates all the elements of the array in the given Direction.
    /// @param dir the Direction of rotation
    void rotate(Direction dir = Direction::left)
    {
        if (length > 0)
        {
            if (dir == Direction::left)
            {
                T firstVal = A[0];
                for (int i = 0; i < length - 1; i++)
                {
                    A[i] = A[i + 1];
                }
                A[length - 1] = firstVal;
            }
            else
            {
                T firstVal = A[length - 1];
                for (int i = length - 1; i > 0; i--)
                {
                    A[i] = A[i - 1];
                }
                A[0] = firstVal;
            }
        }
    }

    /// @brief moves all the negative numbers to the left side and all the positive number to the right side of the array.
    void moveNegativeToLeft()
    {
        if (length > 0)
        {
            int i = 0;
            int j = length - 1;
            while (i < j)
            {
                while (A[i] < 0)
                    i++;
                while (A[j] >= 0)
                    j--;
                if (i < j)
                {
                    _swap(&A[i], &A[j]);
                }
            }
        }
    }
    /// @brief concats 2 array and the value is stored in the current array. If the size overflows only elements till the size of the current array is concatenated.
    /// @param arr pointer to the 2nd Array object to be concatenated.
    void concat(Array arr)
    {
        int i = 0;
        T *arrElements = arr.A;
        for (; i + length < size && i < arr.length; i++)
        {
            A[i + length] = arrElements[i];
        }
        length += i;
    }
    /// @brief compares another array with itself in lexicographical order.
    /// @param arr the array to be compared.
    /// @param len the length of the array to be compared.
    /// @return if the current array is greater, it returns 1 else if both the arrays are same it returns 0 else if the current array is smaller it returns -1.
    int compare(Array arr)
    {
        T *arrElements = arr.A;
        for (int i = 0; i < _min(length, arr.length); i++)
        {
            if (A[i] > arrElements[i])
            {
                return 1;
            }
            else if (A[i] < arrElements[i])
            {
                return -1;
            }
        }
        if (length > arr.length)
        {
            return 1;
        }
        else if (arr.length > length)
        {
            return -1;
        }
        return 0;
    }

    /// @brief makes a copy of the current array and returns it.
    /// @return returns a new Array object with array values copied;
    Array copy()
    {
        T *tempArr = new T[size];
        for (int i = 0; i < length; i++)
        {
            tempArr[i] = A[i];
        }
        return Array(tempArr, size, length);
    }

    /// @brief finds the sum of all the elements in the given array.
    /// @return returns the sum of all the elements in the given array.
    T sum()
    {
        T sum = 0;
        for (int i = 0; i < length; i++)
            sum += A[i];
        return sum;
    }

    /// @brief merges 2 arrays with duplicates
    /// @param arr the 2nd array
    /// @param treatAsSorted Deafults to false. If set to true the merged array is also sorted.
    /// @return
    Array merge(Array arr, bool treatAsSorted = false)
    {
        if (treatAsSorted = false)
        {
            concat(arr);
            return copy();
        }
        else
        {
            int i = 0, j = 0;
            Array<T> mergedArr = {{}, size + arr.size, 0};
            while (i < length && j < arr.length)
            {
                if (A[i] < arr.A[j])
                {
                    mergedArr.append(getElement(i++));
                }
                else
                {
                    mergedArr.append(arr.getElement(j++));
                }
            }
            while (i < length)
                mergedArr.append(getElement(i++));
            while (j < arr.length)
                mergedArr.append(arr.getElement(j++));
            return mergedArr.copy();
        }
    }

    /// @brief Finds the union of 2 arrays i.e. merges 2 arrays without any duplicates.
    /// @param arr The 2nd array.
    /// @param treatAsSortedArray Defaults to false. If set to true, the resulted array is also sorted[O(n)] else it checks if the the element exists in the 2nd array as well as in the final array [O(n^2)]
    /// @return returns a array after applying union operation.
    Array unionArr(Array arr, bool treatAsSortedArray = false)
    {
        Array unionA = Array({}, size + arr.size, 0);
        if (treatAsSortedArray == false)
        {
            int i = 0;
            T currentElement;
            while (i < arr.length + length)
            {
                if (i < length)
                {
                    currentElement = getElement(i++);
                }
                else
                {
                    currentElement = arr.getElement(i++ - length);
                }
                if (unionA.search(currentElement) == -1)
                {
                    unionA.append(currentElement);
                }
            }
        }
        else
        {
            int i = 0, j = 0;
            T currentElement;
            while (i < length && j < arr.length)
            {
                if (getElement(i) < arr.getElement(j))
                    currentElement = getElement(i++);
                else if (getElement(i) > arr.getElement(j))
                    currentElement = arr.getElement(j++);
                else
                {
                    currentElement = getElement(i++);
                    j++;
                }
                unionA.append(currentElement);
            }
            while (i < length)
                unionA.append(getElement(i++));
            while (j < arr.length)
                unionA.append(arr.getElement(j++));
        }
        return unionA.copy();
    }

    /// @brief finds the intersection of 2 arrays i.e. the items which are common.
    /// @param arr the 2nd array.
    /// @param treatAsSorted Defaults to false. If this is set to true the operation is completed in O(n) instead of O(n^2) since search operation is skipped.
    /// @return performs the intersection operation and returns an Array object.
    Array intersection(Array arr, bool treatAsSorted = false)
    {
        Array intersectionArr = {{}, size + arr.size, 0};
        if (treatAsSorted == false)
        {
            int i = 0;
            T currentElement;
            if (_min(length, arr.length) == length)
            {
                while (i < length)
                {
                    currentElement = getElement(i++);
                    if (arr.search(currentElement) != -1 && intersectionArr.search(currentElement) == -1)
                    {
                        intersectionArr.append(currentElement);
                    }
                }
            }
            else
            {
                while (i < arr.length)
                {
                    currentElement = arr.getElement(i++);
                    if (search(currentElement) != -1 && intersectionArr.search(currentElement) == -1)
                    {
                        intersectionArr.append(currentElement);
                    }
                }
            }
        }
        else
        {
            int i = 0, j = 0;
            T element1, element2;
            while (i < length && j < arr.length)
            {
                element1 = getElement(i);
                element2 = arr.getElement(j);
                if (element1 == element2)
                {
                    intersectionArr.append(element1);
                    i++;
                    j++;
                }
                else if (element1 > element2)
                    j++;
                else
                    i++;
            }
        }
        return intersectionArr.copy();
    }

    /// @brief performs difference operation on 1st array i.e. returns the 1st array without any common element with the second array.
    /// @param arr 2nd array.
    /// @param treatArrayAsSorted
    /// @return returns an array after performing the difference operation on the 1st with respect to 2nd.
    Array difference(Array arr, bool treatArrayAsSorted = false)
    {
        Array differenceArr = {{}, length, 0};
        T currentElement;
        if (treatArrayAsSorted == false)
        {
            for (int i = 0; i < length; i++)
            {
                currentElement = getElement(i);
                if (arr.search(currentElement) == -1)
                {
                    differenceArr.append(currentElement);
                }
            }
        }
        else
        {
            int i = 0, j = 0;
            T element1, element2;
            while (i < length && j < arr.length)
            {
                element1 = getElement(i);
                element2 = arr.getElement(j);
                if (element1 < element2)
                {
                    differenceArr.append(element1);
                    i++;
                }
                else if (element1 == element2)
                {
                    i++;
                    j++;
                }
                else
                    j++;
            }
        }
        return differenceArr.copy();
    }

    /// @brief performs concat operation
    /// @param arr The 2nd array
    /// @tparam T returns an Array Object after performing concat operation;
    Array operator+(const Array arr)
    {
        Array additionArray = copy();
        additionArray.concat(arr);
        return additionArray.copy();
    }

    /// @brief performs difference operation.
    /// @param arr The 2nd array.
    /// @return returns an array after performing difference operation with the first from the second array.
    Array operator-(const Array arr)
    {
        Array differenceArray = copy();
        return differenceArray.difference(arr, true);
    }

    /// @brief compares current array with second array in lexicographical order
    /// @param arr1 1st array
    /// @param arr2 2nd array
    /// @return return true if the current array is greater else returns false
    friend bool operator>(Array &arr1, Array &arr2)
    {
        if (arr1.compare(arr2) == 1)
        {
            return true;
        }
        return false;
    }

    /// @brief compares current array with second array in lexicographical order
    /// @param arr1 1st array
    /// @param arr2 2nd array
    /// @return return true if the current array is smaller else returns false
    friend bool operator<(Array &arr1, Array &arr2)
    {
        if (arr1.compare(arr2) == -1)
        {
            return true;
        }
        return false;
    }

    /// @brief prints the array.
    /// @param os
    /// @return
    friend ostream &operator<<(ostream &os, Array &arr)
    {
        for (int i = 0; i < arr.getLength(); i++)
        {
            os << arr.getElement(i);
            if (i != arr.length - 1)
            {
                os << " ";
            }
        }
        return os;
    }

    /// @brief finds the missing elements
    /// @param treatArrayAsSorted should the array be treated as sorted
    /// @param isOnlyOneElementMissing if it is set true, it is assumed only one element is missing and it finds it in O(1)
    /// @param useLongerMethod if it is set true and array is sorted a longer method is used else hash map is used which is of constant time complexity[O(1)]
    /// @return returns an array of all the missing elements
    Array findMissingElements(bool treatArrayAsSorted = false, bool isOnlyOneElementMissing = false, bool useLongerMethod = false)
    {
        T n = max(treatArrayAsSorted)+1;
        if (isOnlyOneElementMissing == true)
        {
            T tempArr[1] = {n * (n + 1) / 2 - sum()};
            Array arr = {tempArr, 1, 1};
            return arr.copy();
        }
        else
        {
            Array arr = {{}, n, 0};
            if (useLongerMethod == true && treatArrayAsSorted == true)
            {
                T d = getElement(0);
                for (int i = 0; i < length; i++)
                    while (getElement(i) > d + i)
                        arr.append(d++ + i);
            }
            else
            {
                int map[n] = {0};
                for (int i = 0; i < length; i++)
                {
                    map[getElement(i)] = 1;
                }
                for (int i = 1; i <= n; i++)
                {
                    if (map[i] == 0)
                    {
                        arr.append(i);
                    }
                }
            }
            return arr.copy();
        }
    }

    /// @brief prints the number of duplicates in the format value, frequency if frequency is greater than 1.if the array is sorted and use2Pointers is set to true then it uses an algorithm of time complexity O(n) else if treatAsSorted is set to false and use2pointers is set to true algorithm used is of time complexity O(n^2). If use2Pointers is set to false then hasmap is used which of time complexity O(n) but also has space complexity of O(n.)
    /// @param treatArrayAsSorted
    /// @param use2Pointers
    void printDuplicates(bool treatArrayAsSorted = false, bool use2Pointers = true)
    {
        int n = max(treatArrayAsSorted)+1;
        if (use2Pointers == true)
        {
            int i = 0, j = 0;
            if (treatArrayAsSorted == true)
            {
                while (i++ < length)
                {
                    if (A[i] == A[i + 1])
                    {
                        j = i + 1;
                        while (A[j++] == A[i])
                            ;
                        cout << "value: " << A[i] << ", frequency: " << j - i - 1 << endl;
                        i = j - 1;
                    }
                }
            }
            else
            {
                int count = 0;
                while (i++ < length)
                {
                    count = 0;
                    j = i + 1;
                    while (j++ < length)
                    {
                        if (A[i] == A[j])
                        {
                            count++;
                        }
                    }
                    if (count > 0)
                    {
                        cout << "value: " << A[i] << ", frequency: " << count + 1 << endl;
                    }
                }
            }
        }
        else
        {
            int map[n] = {0};
            for (int i = 0; i < length; i++)
            {
                map[i]++;
            }
            for (int i = 0; i < n; i++)
            {
                if (map[i] > 1)
                {
                    cout << "value: " << i << ", frequency: " << map[i] << endl;
                }
            }
        }
    }

    /// @brief finds the sum of a pair = k in the array. if this treatArrayAsSorted is set to true and use2Pointers is also set to true the time complexity is O(n) else if treatArrayAsSorted is true and use2Pointers is set to false then the time complexity is O(n^2) else hashmap will be used which is of time complexity O(n) but also of space complexity O(n).
    /// @param k the sum
    /// @param treatArrayAsSorted treat array as sorted flag.
    /// @param use2Pointers if this is set to true 2 Pointers will be used.
    void findAPairWithSumK(int k, bool treatArrayAsSorted = false, bool use2Pointers = true)
    {
        if (use2Pointers == true)
        {
            Array<T> valuesChecked = {{}, size, 0};
            int i = 0, j = length-1;
            if (treatArrayAsSorted == false)
            {
                while (i < length)
                {
                    j = 0;
                    while (j < length)
                    {
                        if (A[j] + A[i] == k)
                        {
                            if (valuesChecked.search(A[i]) == -1)
                            {
                                cout << A[i] << " + " << A[j] << " = " << k << endl;
                            }
                            valuesChecked.append(A[i]);
                            valuesChecked.append(A[j]);
                            break;
                        }
                        j++;
                    }
                    i++;
                }
            }
            else
            {   
                T s;
                while (i<j) {
                    s = A[i]+A[j];
                    if (s == k) {
                        cout << A[i] << " + " << A[j] << " = " << k << endl;
                        do i++; while (A[i] == A[i+1]);
                        do j--; while (A[j] == A[j-1]);
                    }
                    else if (s<k) do i++; while (A[i] == A[i+1]);
                    else do j--; while(A[j] == A[j-1]);
                }
            }
        } else {
            int map[max(treatArrayAsSorted)+1] = {0};
            for (int i=0; i<length; i++) {
                map[A[i]]++;
            }
            for (int i=0; i<length; i++) {
                if (map[k - A[i]] > 0) {
                    cout << A[i] << " + " <<  k - A[i]<< " = " << k << endl;
                    map[k - A[i]] = -1;
                    map[A[i]] = -1;
                }
            }
        }
    }
};

int main()
{
    int a[10] = {1, 2, 10, 11, 12, 4, 4, 8, 10, };
    Array<int> arr = {a, 14, 9};
    return 0;
}