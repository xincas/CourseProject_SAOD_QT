#pragma once
#include <string>
#include <array>
#include <functional>
#include <typeinfo>

template<typename K, typename T>
class Pair
{
public:
    K key;
    T data;

    Pair(K key, T data)
    {
        this->data = data;
        this->key = key;
    };

    Pair()
    {
        this->data = T();
        this->key = K();
    };

    bool operator==(Pair<K, T> a)
    {
        return this->key == a.key && this->data == a.data ? true : false;
    }
};


template<typename K, typename T>
class HashTable
{
private:
    int arrSize;
    int size;
	Pair<K,T>* arr;
	int c1 = 2, c2 = 3;

private:
	int hashFun(K key);
    int myHashFun(std::string key);
	int collisionFix(int i , int n);
	bool isFree(int i);
	void resize();
    int indexOf(K key);
    Pair<K,T> pairByKey(K key);
	//T& getDataByKey(K key);

	
public:
	HashTable();
	~HashTable();

	void clear();
    int getSize() const;
	bool contains(K key);
	void add(K key, T data);
	void removeByKey(K key);
    T& operator[](K key);

    T* getAll();
};

template<typename K, typename T>
HashTable<K, T>::HashTable()
{
    this->arrSize = 10;
    this->arr = new Pair<K, T>[arrSize]();

    for(int i = 0; i < arrSize; i++)
        arr[i] = Pair<K, T>();

    this->size = 0;
}

template<typename K, typename T>
HashTable<K, T>::~HashTable()
{
	delete[] arr;
}

template<typename K, typename T>
void HashTable<K, T>::clear()
{
    for (int i = 0; i < this->arrSize; i++)
		arr[i] = Pair<K,T>();

    this->size = 0;
}

template<typename K, typename T>
int HashTable<K, T>::getSize() const
{
    return this->size;
}

template<typename K, typename T>
Pair<K, T> HashTable<K, T>::pairByKey(K key)
{
    int i = indexOf(key);

    int try_n = 1;
    while (arr[i].key != key && try_n != this->arrSize) {
        i = collisionFix(i, try_n++);
    }
    if (try_n != this->arrSize)
        return arr[i];
    return Pair<K,T>();
}

template<typename K, typename T>
bool HashTable<K, T>::contains(K key)
{
    Pair<K, T> check = pairByKey(key);
    return !(check == Pair<K, T>()) && check.key == key;
}

template<typename K, typename T>
void HashTable<K, T>::add(K key, T data)
{
    if (contains(key))
        return;

    int i = indexOf(key);

	if (isFree(i))
		this->arr[i] = Pair<K, T>(key, data);
	else
	{
		int try_n = 1;
		do 
		{
			i = collisionFix(i, try_n++);
		} while (!isFree(i));

        this->arr[i] = Pair<K, T>(key, data);
	}
    this->size++;
	resize();
}

template<typename K, typename T>
int HashTable<K, T>::indexOf(K key)
{
    const std::type_info& str = typeid (std::string);
    if (typeid(key).name() == str.name())
        return myHashFun(key);
    else
        return hashFun(key);
}

template<typename K, typename T>
void HashTable<K, T>::removeByKey(K key)
{
    int i = indexOf(key);

    int try_n = 1;
    while (arr[i].key != key && try_n != this->arrSize) {
        i = collisionFix(i, try_n++);
    }
    if (try_n != this->arrSize)
    {
        this->arr[i] = Pair<K, T>();
        this->size--;
    }
}

template<typename K, typename T>
int HashTable<K, T>::hashFun(K key)
{
    return std::hash<K>{}(key) % this->arrSize;
}

template<typename K, typename T>
int HashTable<K, T>::myHashFun(std::string key)
{
    unsigned int hash(0);
    int key_size = key.size();

    for (int i = 0; i < key_size; i++)
        key += pow(key.at(i), 2);
    hash *= key.at(5) + key.at(4) - key.at(1);
    hash += key.at(4) + key.at(0) * key.at(3);
    hash += pow(key.at(5), 3) + pow(key.at(2), 2);
    hash += pow(key.at(3), 4) - pow(key.at(4), 3);
    hash -= key.at(0) + key.at(1) * 2 - pow(key.at(2), 2);

    return hash % this->arrSize;
}

template<typename K, typename T>
T& HashTable<K, T>::operator[](K key)
{
    int i = indexOf(key);

    int try_n = 1;
    while (arr[i].key != key && try_n != this->arrSize) {
        i = collisionFix(i, try_n++);
    }
    if (try_n != this->arrSize)
        return arr[i].data;
    T tmp = T();
    return tmp;
}

template<typename K, typename T>
int HashTable<K, T>::collisionFix(int i , int n)
{
	int res = i + c1 * n + c2 * n * n;
    if (res < this->arrSize)
		return res;
	else
        return res % this->arrSize;
}

template<typename K, typename T>
bool HashTable<K, T>::isFree(int i)
{
    return arr[i] == Pair<K, T>();
}

template<typename K, typename T>
void HashTable<K, T>::resize()
{
    if ((double)size / (double)arrSize >= 0.7)
	{
        this->arrSize *= 2;

        Pair<K, T>* arr2 = new Pair<K, T>[arrSize]();
        for (int i = 0; i < arrSize; i++)
            arr2[i] = Pair<K, T>();

        for (int i = 0; i < this->arrSize / 2; i++)
		{
			if (this->arr[i] == Pair<K, T>())
				continue;
			else
            {
                int j = indexOf(arr[i].key);

                if (arr2[j] == Pair<K,T>())
                    arr2[j] = Pair<K, T>(arr[i].key, arr[i].data);
                else
                {
                    int try_n = 1;
                    do
                    {
                        j = collisionFix(j, try_n++);
                    } while (!(arr2[j] == Pair<K,T>()));

                    arr2[j] = Pair<K, T>(arr[i].key, arr[i].data);
                }
            }

		}

		delete[] this->arr;

		this->arr = arr2;
	}
}

template<typename K, typename T>
T* HashTable<K, T>::getAll()
{
    T* mas = new T[this->size];

    int j = 0;
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] == Pair<K,T>())
            continue;
        else
            mas[j++] = arr[i].data;

        if (j == this->size)
            break;
    }

    return mas;
}
