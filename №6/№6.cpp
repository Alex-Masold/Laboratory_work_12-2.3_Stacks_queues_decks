#include <iostream>
#include <fstream>

using namespace std;

template <typename type>
class Stack
{
public:
	Stack();

	bool Is_empty(); // стек пуст
	void Push_front(type data); // добавение в голову
	void Print(); // вывести стек на экран (для проверки)
	void Pop(); // удалить первый элемент в стеке
	char Get(); // Посмотрет первый элемент в стеке

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
bool Stack<type>::Is_empty()
{
	return head == nullptr;
}

template<typename type>
void Stack<type>::Push_front(type data)
{
	head = new Node<type>(data, head);
	Size++;
}

template<typename type>
void Stack<type>::Print()
{
	if (Is_empty())
	{
		cout << "This stack is empty";
		return;
	}
	else
	{
		Node<type>* current = head;
		while (current != nullptr)
		{
			cout << current->data << ' ';
			current = current->next;
		}
		cout << endl;
	}
}

template<typename type>
void Stack<type>::Pop()
{
	if (head == nullptr) // если стэк пустой, то ни чего не делаем
	{
		return;
	}
	else if (head->next == nullptr) // если в стеке только один элемент
	{
		delete head;
		head = nullptr;
		return;
	}
	// Если стек не пуст и в больше чем один элемент 
	Node<type>* current = head; // добавляем новый элемент и заносим туда данные головы
	head = current->next; // смещаем указатель на голову на один узел
	delete current; // удаляем узел с данными, который раньше был головой
}

template<typename type>
char Stack<type>::Get()
{
	return head->data;
}

int main()
{
	Stack<char> stack;

	ifstream in("input.txt", ios::in);
	string str;
	int n;

	in >> n;

	for (int i = 0; i < n; i++)
	{

		in >> str;

		if (str.length() % 2 != 0)
		{
			cout << "NIL" << endl;
			continue;
		}
		if (str[0] == ')' || str[0] == ']' || str[0] == '}' || str[0] == '>')
		{
			cout << "NIL" << endl;
			continue;

		}
		else
		{
			//cout << 'T';
			for (int i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == '(' || str[i] == '[' || str[i] == '{' || str[i] == '<')
				{
					stack.Push_front(str[i]);
					str.erase(str.find(str[i]), 1);
					i--;
				}
			}
			stack.Print();
			cout << str << endl;
		}
	}

	in.close();
}
