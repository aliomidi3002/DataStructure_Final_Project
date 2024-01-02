#include<iostream>
#include<initializer_list>

template<typename Object>
class Stack{
private:

	Object* Top;
	Object* Array;
	int size;

public:

	// constructor
	Stack() :Top(-1), Array(new Object[20]), size(20){}
	Stack(std::initializer_list<Object> values);

	void Resize();
	void push(Object element);
	Object pop();
	//void top();
	//void size();
	//void empty();

	//Overloading Operators
	//<<
	friend std::ostream& operator << (std::ostream& os, const Stack<Object>& stack) {

		os << "[";
		int current = 0;
		while (stack.Array[current] != *stack.Top) {
			os << stack.Array[current] << ",";
			current++;
		}
		os << stack.Array[current];
		os << "]";

		return os;
	}
	//[]
	Object& operator [](int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index out of range");
		}
		return Array[index];
	}
};


// initializer_list constructor
template<typename Object>
Stack<Object>::Stack(std::initializer_list<Object> values){

	size = 20;
	Array = new Object[20];

	while (values.size() >= size)
		Resize();

	int current = 0;
	for (auto element : values) {
		Array[current] = element;
		current++;
	}

	Top = &Array[--current];
}

// Double the Size(Resize)
template<typename Object>
void Stack<Object>::Resize(){

	Object *newArray =  new Object[size * 2];
	for (int i = 0; i < size; i++)
		newArray[i] = Array[i];

	delete[] Array;
	Array = newArray;
	size *= 2;
}


//push
template<typename Object>
void Stack<Object>::push(Object element) {

	if (*Top == Array[size-1])
		Resize();

	Top++;
	*Top = element;
}


// pop
template<typename Object>
Object Stack<Object>::pop() {
	if (Top == nullptr) {
		throw std::runtime_error("Pop from empty stack");
	}

	Object topValue = *Top; // Get the value at the top

	if (Top != Array)
		Top--;

	else
		Top = nullptr;

	return topValue; // Return the popped value
}


int main() {
	Stack<int> s = {1,2,3,4,5,6,7,8};
	s.pop();
	s.pop();
	s.pop();
	std::cout << s << std::endl;
}