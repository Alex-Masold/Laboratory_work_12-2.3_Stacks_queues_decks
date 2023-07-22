#include <iostream>
#include <fstream>
#include "№3.h"
using namespace std;

class Queue {
private:
    int* arr;
    int begin;
    int end;
    int maxSize;
    int size;
public:
    Queue(int capacity) {
        maxSize = capacity;
        arr = new int[maxSize];
        begin = 0;
        end = -1;
        size = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    /// <summary>
    /// добавление в очередь
    /// </summary>
    void add(int value) 
    { 
        end = (end + 1) % maxSize;
        arr[end] = value;
        size++;
    }

    /// <summary>
    /// удаление из очереди
    /// </summary>
    int pop() {
        int value = arr[begin];
        begin = (begin + 1) % maxSize;
        size--;
        return value;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == maxSize;
    }
};


int main()
{
    ifstream in("input.txt");
    int sizeofarr = 0, requestsize = 0, request = 0, num = 0, sum = 0;
    // длина буф   сколько запросов     запрос    число в запросах
    // если request > 0, записываем в очередь, иначе выводим ср арифм некоторого колва чисел

    bool fine; // проверка на ошибку (переполнение, удаление пустоты)
    in >> sizeofarr >> requestsize;
    Queue cir(sizeofarr);

    while (requestsize > 0)
    {
        in >> request;
        requestsize--;
        fine = true; // жить можно, жизнь прекрасна

        if (request >= 0)
        {
            for (int i = 0; i < request; i++)
            {
                in >> num;
                if (!cir.isFull())
                {
                    cir.add(num); // записали число в очередь
                }
                else
                {
                    fine = false; // иначе что то не так
                }
                requestsize--;
            }
            if (!fine)
                cout << "Memory overflow" << endl; // соо об ошибке
        }
        else
        {
            sum = 0;
            int del = 0;
            while (request < 0)
            {
                if (!cir.isEmpty())
                {
                    sum += cir.pop();
                    del++;
                }
                else
                {
                    fine = false;
                    break;
                }
                request++;
            }
            if (del != 0)
                cout << sum / del << endl;
            if (!fine)
                cout << "Empty queue" << endl;
        }
    }
}