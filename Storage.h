#pragma once

template<typename T>
class Storage
{
private:
    T* data[100];
    int count;

public:
    Storage()
    {
        count = 0;
        for (int i = 0; i < 100; i++)
            data[i] = nullptr;
    }

    ~Storage()
    {
        clear();
    }

    bool add(T* item)
    {
        if (!item) return false;
        if (count >= 100) return false;

        for (int i = 0; i < count; i++)
            if (data[i] && data[i]->getID() == item->getID())
                return false;

        data[count] = item;
        count++;
        return true;
    }

    bool remove(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i] && data[i]->getID() == id)
            {
                delete data[i];
                for (int j = i; j < count - 1; j++)
                    data[j] = data[j + 1];
                data[count - 1] = nullptr;
                count--;
                return true;
            }
        }
        return false;
    }

    T* findById(int id) const
    {
        for (int i = 0; i < count; i++)
            if (data[i] && data[i]->getID() == id)
                return data[i];
        return nullptr;
    }

    T* const* getAll() const  // FIXED: line 64
    {
        return data;
    }

    int getCount() const
    {
        return count;
    }

    void clear()
    {
        for (int i = 0; i < count; i++)
            delete data[i];
        count = 0;
    }

private:
    Storage(const Storage& other);
    Storage& operator=(const Storage& other);
};