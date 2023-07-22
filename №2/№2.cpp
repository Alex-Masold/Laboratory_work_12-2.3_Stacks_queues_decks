#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename type>
class Stack
{
public:
	Stack();

	bool is_empty();
	void push_front(type data);
	int Lenght() { return Size; }
	void pop();
	void clear();
	type get();
	type get_and_pop();


private:
	template <typename type>
	class Node
	{
	public:
		Node* next;
		type data;

		Node(type data = type(), Node* next = nullptr)
		{
			this->data = data;
			this->next = next;
		}
	};
	int Size;
	Node<type>* head;

};

template<typename type>
Stack<type>::Stack()
{
	this->head = nullptr;
}

template<typename type>
bool Stack<type>::is_empty()
{
	return head == nullptr;
}

template<typename type>
void Stack<type>::push_front(type data)
{
	head = new Node<type>(data, head);
	Size++;
}

template<typename type>
void Stack<type>::pop()
{
	if (head == nullptr) // если стак пустой, то ничего не делаем
	{
		return;
	}
	else if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
		return;
	}
	Node<type>* current = head;
	head = current->next;
	delete current;
}

template<typename type>
void Stack<type>::clear()
{
	while (head)
	{
		pop();
	}
}

template<typename type>
type Stack<type>::get()
{
	return head->data;
}

template<typename type>
type Stack<type>::get_and_pop()
{
	type received = head->data;
	pop();
	return received;
}

int priority(char c)
{
	switch (c)
	{
	case '*': case '/': return 5;

	case '+': case '-': return 4;

	case ')': return 2;

	case '(': return 1;
	}

	return 0;
}


int main()
{
	Stack<int64_t> stack;
	string str;
	int64_t num = 0, a1, a2;
	int i = 0;
	ifstream in("input.txt", ios::in);
	getline(in, str);
	in.close();



	while (i < str.size())
	{
		if (str[i] == ' ') 
		{
			i++;
		}
		else if (str[i] >= '0') //распознование числа 
		{
			while (str[i] != ' ')
			{
				num = num * 10 + str[i] - '0'; // num типа разряд, код символа - код ноля = число в символе
				i++;
			}
			i++;
			stack.push_front(num); // помещаем в стек
			num = 0;
		}
		else
		{
			a1 = stack.get_and_pop();
			a2 = stack.get_and_pop();
			
			switch (str[i])
			{
			case '+': stack.push_front(a2 + a1); break;
			case '-': stack.push_front(a2 - a1); break;
			case '*': stack.push_front(a2 * a1); break;
			case '/': stack.push_front(a2 / a1); break;
			}
			i += 2;
		}
	}
	cout << stack.get();
	/*ofstream out("output.txt");
	out << stack.get();
	out.close();*/
	stack.clear();
}