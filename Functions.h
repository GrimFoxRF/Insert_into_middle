#pragma once

struct Node
{
    int value;
    Node* next;
    std::mutex* node_mutex;

    Node(int val) : value(val), next(nullptr), node_mutex(new std::mutex) {}
    ~Node() 
    { 
        delete node_mutex;
    }
};

class FineGrainedQueue
{
private:
    Node* head;
    std::mutex* queue_mutex;

public:
    FineGrainedQueue() : head(nullptr), queue_mutex(new std::mutex) {}

    ~FineGrainedQueue()
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        delete queue_mutex;
    }
    //вставка элемента в очередь
    void insertIntoMiddle(int value, int pos)
    {
        Node* newNode = new Node(value);
        queue_mutex->lock();//блокировка очереди
        Node* curr = head;//текущий узел
        Node* prev = nullptr;//предыдущий узел

        //обработка пустого списка или вставки в начало
        if (!curr || pos <= 0)
        {
            newNode->next = head;
            head = newNode;
            queue_mutex->unlock();//очередь разблокирована
            return;
        }
        //находим нужную позицию
        while (pos > 0 && curr)
        {
            prev = curr;
            curr = curr->next;
            --pos;//цикл работает пока счетчик позиции не станет равен 0
        }
        queue_mutex->unlock();//очередь разблокирована
        //вставка нового узла в очередь
        if (prev)
        {
            prev->node_mutex->lock();//блокируем предыдущий узел
            prev->next = newNode;//указатель на новый узел как next
            newNode->next = curr;//устанавливаем новому узлу указатель на текущий, как на следующий
            prev->node_mutex->unlock();//разблокируем предыдущий узел
        }
        //если предыдущего узла нет, вставляем новый узел в начало
        else
        {
            if (head) { queue_mutex->lock(); }
            newNode->next = head;//указатель next теперь указывает на первый элемент очереди
            head = newNode;//новый узел теперь стал первым элементом
            if (head) { queue_mutex->unlock(); }
        }
    }
    //вывод содержимого очереди на экран
    void showQueue()
    {
        queue_mutex->lock();
        Node* curr = head;

        std::cout << "\nОчередь: ";

        while (curr)
        {
            curr->node_mutex->lock();
            std::cout << curr->value << " ";
            curr->node_mutex->unlock();
            curr = curr->next;
        }

        queue_mutex->unlock();
        std::cout << std::endl;
    }
};
