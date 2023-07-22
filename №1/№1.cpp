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
		cout << "This stack is empty\n";
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
	Stack<char> stack;
	string str, result;

	ifstream in("input.txt", ios::in);

	in >> str;

	in.close();

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isalpha(str[i])) //Если символ является буквой, он добавляется в конец строки result
		{
			result += str[i];
			stack.Print();
			cout << result << endl;
		}
		else if (stack.Is_empty()) //Если стек пуст, символ добавляется в начало стека
		{
			stack.Push_front(str[i]);
			stack.Print();
			cout << result << endl;

		}
		else if (str[i] == '(') //Если символ - открывающая скобка '(', он добавляется в начало стека
		{
			stack.Push_front(str[i]);
			stack.Print();
			cout << result << endl;

		}
		//Если символ - закрывающая скобка ')', 
		else if (str[i] == ')')
		{
			// все операции из стека добавляются в конец строки result до тех пор, 
			while (stack.Get() != '(')
				//пока не встретится открывающая скобка, которая удаляется из стека
			{

				result += stack.Get();
				stack.Pop();
				stack.Print();
				cout << result << endl;

			}
			stack.Pop();
		}
		else
		{
			while (!stack.Is_empty() && priority(stack.Get()) >= priority(str[i])) // пока стек не пуст и пока приоритет просматриваемого элемента больше текущего
			{
				// Если символ - оператор, то все операторы из стека с более высоким приоритетом добавляются в конец строки result, 
				result += stack.Get();
				stack.Pop();
				stack.Print();
				cout << result << endl;


			}
			// а затем символ добавляется в начало стека
			stack.Push_front(str[i]);
			stack.Print();
			cout << result << endl;



		}


		while (!stack.Is_empty())
		{
			result += stack.Get();
			stack.Pop();
		}
	}
	cout << result << endl;

	ofstream out("output.txt");
	out << result << endl;
	out.close();
}
