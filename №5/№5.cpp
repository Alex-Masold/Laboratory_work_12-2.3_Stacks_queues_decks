#include <iostream>
#include <string>

using namespace std;


class Node {
public:
    double value;
    Node* next;
public:
    Node(double value) {
        this->value = value;
        this->next = NULL;
    }
};

class ListStack {
public:
    Node* head;
public:
    ListStack() {
        this->head = NULL;
    }

    double pop() {
        if (head == NULL) return 0;

        double current = head->value;
        if (head->next == NULL) {
            delete head;
            head = NULL;
            return current;
        }

        Node* node = head;
        head = head->next;
        delete node;
        return current;
    }

    void push(double data) {
        Node* node = new Node(data);
        node->next = head;
        head = node;
    }

    double get() {
        return head->value;
    }

    double get_and_pop() {
        int c = head->value;
        pop();
        return c;
    }

    bool is_empty() {
        return head == NULL;
    }

    void clear() {
        while (head) pop();
    }
};

int priority(char c)
{
    switch (c)
    {
    case '*': case'/': return 5;
    case '+': case '-': return 4;
    case ')': return 2;
    case '(': return 1;
    }
}

double result(double a, double b, char c)
{
    switch (c)
    {
    case '*': return a * b;
    case'/': return a / b;
    case '+': return a + b;
    case '-': return a - b;
    }

}

int main()
{
    ListStack NumSt, OperSt; // стек для чисел и операторов
    int i = 0, num = 0;
    bool unar = false; // проверка на отриц число - угарный минус
    char former_mark = '(';
    string str;

    getline(cin, str);

    while (i < str.size())
    {
        if (str[i] == ' ') // учет пробелов 
        {
            i++;
            continue;
        }

        if (str[i] >= '0') // если число 
        {
            while (isdigit(str[i]))
            {
                num = num * 10 + str[i] - '0'; // num типа разряд, код символа - код ноля = число в символе
                i++;
            }
            if (unar) // проверка на унарный минус
            {
                num = -num;
                unar = false;
            }
            NumSt.push(num); // помещаем в стек
            former_mark = str[i]; // пред знак 
            num = 0;
        }
        else
        {
            if (str[i] == '-' && former_mark == '(') // если число отриц
            {
                unar = true;
            }

            else if (str[i] == '(')
            {
                if (unar)
                {
                    NumSt.push(-1);
                    OperSt.push('*');
                    unar = false; // обыгрываем отрицательное число (отриц скобку)
                }
                OperSt.push(str[i]); // засосываем скобку
            }
            else if (str[i] == ')')
            {
                while (OperSt.get() != '(')
                {
                    NumSt.push(result(NumSt.pop(), NumSt.pop(), OperSt.pop())); // положить в стек чисел результат вычислений 
                }
                OperSt.pop(); // доставаем вторую скобку.        ^^^^ здесь достаем оператор
            }
            else // если ни число, ни скобочка.
            {
                while (!OperSt.is_empty() && priority(OperSt.get()) >= priority(str[i]))
                {
                    NumSt.push(result(NumSt.pop(), NumSt.pop(), OperSt.pop())); // положить в стек чисел результат вычислений 
                }
                OperSt.push(str[i]); // засувываем знакi
            }
            former_mark = str[i];
            i++;
        }
    }

    while (!OperSt.is_empty()) // выплевываем
    {
        NumSt.push(result(NumSt.pop(), NumSt.pop(), OperSt.pop())); // считаем "остатки"
    }

    printf("%.20lf", NumSt.pop());
}