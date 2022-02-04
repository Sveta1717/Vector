#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <ctime>
using namespace std;

class Vector
{
	int size = 0; // текущее количество элементов в массиве
	int capacity = 10; // резерв памяти
	int* data; // указатель на инкапсулированный массив

public:
	Vector() : Vector(10)
	{
		// cout << "C-TOR WITHOUT PARAMS!\n";
	}	

	Vector(int capacity)
	{
		if (capacity < 10)
		{
			capacity = 10;
		}
		if (capacity > 500000000)
		{
			capacity = 500000000;
		}
		this->capacity = capacity;
		data = new int[capacity];
		// cout << "C-TOR WITH PARAMS!\n";
	}

	~Vector()
	{
		// cout << "DESTRUCTOR!\n";
		delete[] data;
	}

private:
	void EnsureCapacity(int count)
	{		
		if (capacity >= count) return;		
		int new_capacity = capacity * 3 / 2 + 1;
		int* temp = new int[new_capacity];

		for (int i = 0; i < capacity; i++)
		{
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;

		capacity = new_capacity;
		cout << "NEW CAP: " << capacity << "\n";
	}
public:

	void SetCapacity()
	{
		if (capacity < 10)
		{
			capacity = 10;
		}
		this->capacity = capacity;
		data = new int[capacity];
	}

	int Getsize()
	{
		return size;
	}

	int GetCapacity()
	{
		return capacity;
	}

	void PushBack(int value)
	{
		EnsureCapacity(size + 1); 
		data[size++] = value;
	}	

	Vector operator+(const Vector& another)
	{
		Vector result;

		result.capacity = this->capacity + another.capacity;
		result.size = this->size + another.size;
		result.data = new int[result.capacity];

		int index = 0;
		for (; index < this->size; index++)
		{
			result.data[index] = this->data[index];
		}

		for (; index < this->size + another.size; index++)
		{
			result.data[index] = another.data[index - this->size];
		}

		return result;
	}


	bool Equals(const Vector& another)const
	{
		if (size == another.size)
		{
			int result = 0;
			for (int i = 0; i < size; i++)
			{
				if (data[i] == another.data[i])
				{
					result++;
				}
			}
			return result == size;
		}

		return false;
	}

	void PushFront(int value)
	{		
		for (int i = size; i > 0; i--)
		{
			data[i] = data[i - 1];
		}
		data[0] = value;
		size++;
	}

	void Insert(int index, int value)
	{
		if (index > 0 || index < size)
		{
			EnsureCapacity(size + 1);
			size++;
			
			for (int i = size - 1; i >= index; i--)
			{
				data[i] = data[i - 1];
			}
			data[index] = value;
		}
		else
		{
			return;
		}		
	}

	void RemoveAt(int index)
	{
		if (index > 0 || index < size)
		{
			for (int i = index; i < size; i++)
			{
				data[i] = data[i + 1];
			}
		}
		else
		{
			return;
		}

		size--;
	}

	void Remove(int value) // не корректно работает
	{
		int i = 0; 		
			while (data[i] == value)
			{
				RemoveAt(i);
				i--;				
			}
	}

	void PopFront()
	{
		RemoveAt(0);
	}

	void PopBack()
	{
		RemoveAt(size - 1);
	}

	Vector(const Vector& original)
	{
		this->size = original.size;
		this->capacity = original.capacity;
		this->data = new int[original.capacity];
		for (int i = 0; i < size; i++)
		{
			this->data[i] = original.data[i];
		}
	}

	void Clear()
	{
		size = 0;
	}

	bool IsEmpty()
	{
		return size == 0;
	}

	void TrimToSize()
	{
		capacity = size;
		int* tmp = new int[capacity];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = data[i];
		}
		delete[] data;
		data = tmp;
	}

	void Print()
	{
		if (IsEmpty())
		{
			cout << "Vector is empty.\n";
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				cout << data[i] << " ";
			}
			cout << endl;
		}
	}

	int IndexOf(int value)
	{
		for (int i = 0; i < size; i++)
		{
			if (this->data[i] == value)
			{
				return i;
			}
		}
		return -1;
	}

	int LastIndexOf(int value)
	{
		for (int i = size - 1; i >= 0; i--)
		{
			if (this->data[i] == value)
			{
				return i;
			}
		}
		return -1;
	}

	void Reverse()
	{
		reverse(data, data + size);		
	}

	void SortAsc()
	{
		sort(data, data + size);
	}
	void SortDesc()
	{
		sort(data, data + size);
		Reverse();
	}

	void Shuffle()
	{
		random_shuffle(data, data + size);
	}

	void  RandomFill()
	{
		//generate(data, data + size, rand() % 10);	// не получается (	
		for (int i = 0; i < size; i++)
		{
			data[i] = (rand() % 10);
		}
	} 

	int GetElementAt(unsigned int index) const
	{
		if (index >= size) throw "Incorrect index!";		
		return data[index];		
	}

	 Vector Clone(const Vector& clone) //переполнение буфера в data 
	{			
		size = clone.size;
		capacity = clone.capacity;
		data = new int[clone.capacity];
		for (int i = 0; i < size; i++)
		{
			data[i] = clone.data[i];
		}		
		return clone;
	}

	 bool operator==(const Vector& another)
	 {		 
		 return Equals(another);
	 }

	 Vector operator=(const Vector& another)
	 {
		return Clone(another);
	 }

	const int& operator[](unsigned int index) const
	{
		if (index >= size) throw "Incorrect index!"; 
		return data[index];
	}
	friend istream& operator>>(istream& is, Vector& original)
	{
		/*size = original.size;
		data = new int[original.capacity];*/
		for (int i = 0; i <= original.size; i++)
		{
			is >> original.data[i];
		}
		return is;
	}
};

ostream& operator<<(ostream& os, Vector& original)
{
	original.Print();
	return os;
}

int main()
{
	srand(time(0));
	Vector ar;
	Vector ar1;
	cout << "Vector 1: \n";
	ar.PushBack(1);
	ar.PushBack(2);
	ar.PushBack(3);
	ar.Print();
	cout << "Index of 3: " << ar.IndexOf(3) << "\n";
	cout << "last index of 5: " << ar.LastIndexOf(5) << "\n";
	cout << "Element at index 2 is : " << ar.GetElementAt(2) << "\n";
	ar.PushFront(4);
	ar.Print();	
	cout << "Insert 1 at index 2: \n";
	ar.Insert(2, 1);
	cout << ar;
	cout << "Delete at index 3: \n";
	ar.RemoveAt (3);
	cout << ar;
	ar.Reverse();
	ar.Print();
	cout << "Ascending sort: \n";
	ar.SortAsc();
	ar.Print();
	cout << "Descending sort: \n";
	ar.SortDesc();
	ar.Print();
	cout << "Shuffle: \n";
	ar.Shuffle();
	ar.Print();
	cout << "Random fill: \n";
	ar.RandomFill();
	ar.Print();
	cout << "Vector 2: \n";
	ar1.PushBack(5);
	ar1.PushBack(6);
	ar1.PushBack(7);
	ar1.Print();
	cout << "Vector 1 = Vector 2? " << ar.operator==(ar1) << "\n";
	cout << "= Vector 2\n";
	ar.operator=(ar1);
	ar.Print();
	cout << "Clone 2: \n";
	ar.Clone(ar1);
	cout << ar;	
	cout << "Insert 5 at index 1: \n";
	ar.Insert(1, 5);
	cout << ar;
	cout << "Delete 5: \n";
	ar.Remove(5);
	cout << ar;
	cout << "Delete first element: \n";
	ar.PopFront();
	cout << ar;
	cout << "Delete last element: \n";
	ar.PopBack();
	cout << ar;
	cout << "Clear all \n";	
	ar.Clear();
	ar.Print();
}
