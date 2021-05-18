#pragma once
#include <iostream>
#include <string>

template <typename T>
class List
{
private:

    template <typename T>
	class Node
	{
	public:
		T data;
		Node<T>* lvl_next_[10];

		Node(T data = T(), Node<T>* pNextLvl0 = nullptr)
		{
			this->data = data;
			for (int i = 0; i < 10; i++)
			{
				lvl_next_[i] = nullptr;
			}
			lvl_next_[0] = pNextLvl0;
		}
		~Node() {}
	};

	//fields
	Node<T>* head_;
	Node<T>* back_;
	int Size_;
	int CountOfLvls_;

	//Private methods
	//Lvls fixing functions
	List<T>::Node<T>* getNodeByIndexLvl_0(int index);
	void countsOfLvls();
	void lvlsFixing_pushBack();
    void lvlDeletePointers(int indexOfLvl, Node<T>* node);
    void deletePtrAfter(Node<T>* node);
    void rePtrMod2Index(int index, Node<T>* n_node);
    int smallestSizeLvl();

	//Getting node by index (using all lvls to fast skip incorrect data)
	Node<T>* getNodeByIndex(int index);

	//Sorting functions
	void selectionSort();
    void swapDataInNode(Node<T>* a, Node<T>* b);

	//Removing
    void pop_front();
    void pop_back();

	//find
	Node<T>* find(T data);
    Node<T>* saveFind(T data);

    T& getByIndex(int index);
	
public:
	bool contains(T data);
	T& findData(T data);
	void clear();
	
    //void insert(T data, int index);
    //void push_front(T data);
	void push_back(T data);
    void remove(int index);
    void remove(T data);
	int size();
	T& operator[](const int index);
    void changeData(T old, T fresh);

    T* getAll();

	List();
	~List();
};

template <typename T>
List<T>::List()
{
	this->head_ = nullptr;
	this->back_ = nullptr;
	this->Size_ = 0;
	this->CountOfLvls_ = 1;
}

template <typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::clear()
{
	while (this->Size_)
	{
		this->pop_front();
	}
}

template<typename T>
typename List<T>::template Node<T>* List<T>::getNodeByIndex(int index)
{
	if (this->Size_ <= index || index < 0)
	{
		return NULL;
	}

	Node<T>* curNode = this->head_;
	int cur_i = 0;
	for (int i = this->CountOfLvls_ - 1; i >= 0; i--)
	{
		int offset = pow(smallestSizeLvl(), i);
		while (index >= cur_i + offset)
		{
			cur_i += offset;
			curNode = curNode->lvl_next_[i];
		}
		if (index == cur_i)
		{
			return curNode;
		}
	}
}

template<typename T>
T& List<T>::getByIndex(int index)
{
	return getNodeByIndex(index)->data;
}

template<typename T>
int List<T>::size()
{
	return this->Size_;
}

template<typename T>
T& List<T>::operator[](const int index)
{
	return getByIndex(index);
}

template<typename T>
void List<T>::selectionSort()
{
	if (this->Size_ < 2)
	{
		return;
	}

	for (int i = 0; i < this->Size_; i++)
	{
		int min = i;

		for (int j = i + 1; j < this->Size_; j++)
		{
            if (this->getByIndex(j) < this->getByIndex(min))
			{
				min = j;
			}
		}

		swapDataInNode(this->getNodeByIndex(i), this->getNodeByIndex(min));
	}
}

template<typename T>
inline void List<T>::swapDataInNode(Node<T>* a, Node<T>* b)
{
	T tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

template<typename T>
void List<T>::lvlsFixing_pushBack()
{
	countsOfLvls();

	for (int i = 1; i < this->CountOfLvls_; i++)
	{
		int offset = pow(smallestSizeLvl(), i);
		int j = 0;
		Node<T>* prevInLvl = this->head_;

		while (this->Size_ > j + offset)
		{
			if (!prevInLvl->lvl_next_[i]) 
			{
				prevInLvl->lvl_next_[i] = getNodeByIndexLvl_0(j + offset);
			}
			prevInLvl = prevInLvl->lvl_next_[i];
			j += offset;
		}
	}
}

template<typename T>
void List<T>::remove(int index)
{
    if (index > 0)
    {
        Node<T>* before = getNodeByIndex(index - 1);

        deletePtrAfter(before->lvl_next_[0]);

        Node<T>* del = before->lvl_next_[0];
        before->lvl_next_[0] = del->lvl_next_[0];
        if (index % 2 == 0)
            rePtrMod2Index(index, before->lvl_next_[0]);
        delete del;
        this->Size_--;

        lvlsFixing_pushBack();
    }
    else
        pop_front();
}

template<typename T>
void List<T>::remove(T data)
{
    Node<T>* fNode = find(data);

    if (fNode)
    {
        swapDataInNode(fNode, this->back_);
        pop_back();
        countsOfLvls();
        selectionSort();
    }
}


template<typename T>
void List<T>::deletePtrAfter(Node<T>* node)
{
    if (node)
        for (int i = 1; i < CountOfLvls_; i++)
            lvlDeletePointers(i, node);
}

template<typename T>
void List<T>::lvlDeletePointers(int indexOfLvl, List<T>::Node<T>* node)
{
    if (node->lvl_next_[indexOfLvl] != nullptr)
    {
        lvlDeletePointers(indexOfLvl, node->lvl_next_[indexOfLvl]);
        node->lvl_next_[indexOfLvl] = nullptr;
    }
}

template<typename T>
void List<T>::rePtrMod2Index(int index, Node<T>* n_node)
{
    for (int i = 1; i < CountOfLvls_; i++)
    {
        int i_prev = index - pow(smallestSizeLvl(), i);
        if (i_prev >= 0)
        {
            Node<T>* tmp = getNodeByIndex(i_prev);
            tmp->lvl_next_[i] = n_node;
        }
    }
}


template<typename T>
inline int List<T>::smallestSizeLvl()
{
	return 2;
}

template<typename T>
typename List<T>::template Node<T>* List<T>::getNodeByIndexLvl_0(int index)
{
	Node<T>* cur = head_;

	for (int i = 0; i < index; i++)
	{
		cur = cur->lvl_next_[0];
	}

	return cur;
}

template<typename T>
void List<T>::countsOfLvls()
{
	int needlvl = 1;
	while (this->Size_ >= pow(smallestSizeLvl(), needlvl) && needlvl != 10) { needlvl++; }
	this->CountOfLvls_ = needlvl;
}

template <typename T>
void List<T>::push_back(T data)
{
	if (this->head_ == nullptr)
	{
		this->head_ = new Node<T>(data);
        this->back_ = head_;
	}
	else
	{
        back_->lvl_next_[0] = new Node<T>(data);
        back_ = back_->lvl_next_[0];
	}

	this->Size_++;
	lvlsFixing_pushBack();
	selectionSort();
}

template<typename T>
bool List<T>::contains(T data)
{
    if (Size_ > 0)
    {
        if (saveFind(data))
            return true;
    }
    return false;
}

template<typename T>
typename List<T>::template Node<T>* List<T>::saveFind(T data)
{
    Node<T>* curNode = this->head_;

    while (curNode)
    {
        if (curNode->data == data)
            return curNode;
        curNode = curNode->lvl_next_[0];
    }
    return nullptr;
}

template<typename T>
typename List<T>::template Node<T>* List<T>::find(T data)
{
	Node<T>* curNode;
	int cur_i = 0;

    if (data > this->back_->data)
	{
		return nullptr;
	}

	for (int i = this->CountOfLvls_ - 1; i >= 0; i--)
	{
		int offset = pow(smallestSizeLvl(), i);
        while (data > getByIndex(cur_i))
        {
            if (cur_i + offset >= Size_)
                break;
            cur_i += offset;
        }
        curNode = getNodeByIndex(cur_i);
        if (data == curNode->data)
            return curNode;

        if (data < curNode->data)
            cur_i -= offset;
	}
	return nullptr;
}

template<typename T>
T& List<T>::findData(T data)
{
    if (Size_ > 0)
    {
        Node<T>* find = List<T>::find(data);

        if (find)
        {
            return find->data;
        }
    }
}

template<typename T>
T* List<T>::getAll()
{
    T* mas = new T[this->Size_];
    Node<T>* curNode = this->head_;
    int i = 0;

    while (curNode)
    {
        mas[i++] = curNode->data;
        curNode = curNode->lvl_next_[0];
    }

    return mas;
}

/*unused
template<typename T>
void List<T>::push_front(T data)
{
	this->head_ = new Node<T>(data, this->head_);

	this->Size_++;
	countsOfLvls();
	//lvlFixing();
}
template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
		return;
	}
	Node<T>* previous = getNodeByIndex(index - 1);

	previous->lvl_next_[0] = new Node<T>(data, previous->lvl_next_[0]);

	this->Size_++;

	countsOfLvls();
	//lvlFixing();
}*/

template<typename T>
void List<T>::pop_front()
{
	if (this->Size_ == 0)
	{
		return;
	}

	Node<T>* oldHead = this->head_;
	this->head_ = this->head_->lvl_next_[0];
    delete oldHead; 
    this->Size_--;

    deletePtrAfter(this->head_);
    lvlsFixing_pushBack();
}

template<typename T>
void List<T>::pop_back()
{
    if (this->Size_ == 0)
    {
        return;
    }

    Node<T>* oldBack = this->back_;
    this->Size_--;
    if ((Size_) % 2 == 0)
        rePtrMod2Index(Size_, nullptr);
    delete oldBack;

    if (Size_)
    {
        Node<T>* nBack = getNodeByIndex(Size_ - 1);
        this->back_ = nBack;
        back_->lvl_next_[0] = nullptr;
    }
    else
    {
        this->head_ = nullptr;
        this->back_ = nullptr;
    }

    //lvlsFixing_pushBack();
}

