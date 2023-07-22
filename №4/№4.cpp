#include <iostream>
#include <fstream>
using namespace std;

class QueueOnArray {
public:
    int* arr; // указатель на начало дин массива
    int begin; // индекс начала
    int end; // индекс конца
    int maxSize;
    int size; // текущий размер 
public:
    QueueOnArray(int capacity)
    {
        maxSize = capacity;
        arr = new int[maxSize];
        begin = 0;
        end = -1;
        size = 0;
    }

    ~QueueOnArray() {
        delete[] arr;
    }

    void enqueueFront(int value) // добавить в начало (сверху)
    {
        begin--;
        if (begin < 0) begin = maxSize - 1;
        arr[begin] = value;
        size++;
    }

    void enqueueBack(int value) // добавить снизу
    {
        end = (end + 1) % maxSize;
        arr[end] = value;
        size++;
    }

    int dequeueFront() // удалить сверху
    {
        if (isEmpty())  return 0;
        int value = arr[begin];
        begin = (begin + 1) % maxSize;
        size--;
        return value;
    }

    int dequeueBack() // удалить снизу
    {
        if (isEmpty()) return 0;
        int value = arr[end];
        end--;
        if (end < 0) end = maxSize - 1; // если протасовали всю колоду      
        size--;
        return value;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    bool isFull()
    {
        return size == maxSize;
    }

    void print() // вывод
    {
        int k = begin;
        cout << size << "  ";
        for (int i = 0; i < size; i++) {
            cout << arr[k] << ' ';
            k = (k + 1) % maxSize;
        }
        cout << endl;
    }
};

unsigned short charToInt(char c) // конвертатор
{
    if (c < 'A') return c - '0';
    else return c - 'A' + 10;
}

int main()
{
    ifstream in("input.txt");

    int n, m, num, popLR, pushLR, popUD, pushUD, temp;
    in >> n >> m;

    QueueOnArray left(2 * n + 1);
    QueueOnArray right(2 * n + 1);
    in.get();

    for (int i = 1; i <= n; i++)
    {
        left.enqueueBack(i);
        right.enqueueBack(-i);
    }

    while (m > 0)
    {
        m--;
        num = charToInt(in.get()); // получение операции
        if (num == 0 || num == 5 || num == 10 || num == 15) // проверка на ничего неделание
            continue;
        popLR = (num & 8); // берем биты операции
        popUD = (num & 4);
        pushLR = (num & 2);
        pushUD = (num & 1);

        // проверка на взятие
        if (popLR) // если бит == 1
        {
            if (popUD)
                temp = right.dequeueBack();
            else temp = right.dequeueFront();
        }
        else
        {
            if (popUD)
                temp = left.dequeueBack();
            else
                temp = left.dequeueFront();
        }

        if (temp == 0) // проверка на взятие из пустой колоды
            continue;

        //проверка на кладение карты 
        if (pushLR) // если бит == 1
        {
            if (pushUD)
                right.enqueueBack(temp);
            else right.enqueueFront(temp);
        }
        else
        {
            if (pushUD) left.enqueueBack(temp);
            else left.enqueueFront(temp);
        }
    }
    left.print();
    right.print();
}