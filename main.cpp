#include <iostream>
#include <vector>
class date
{
public:
    enum type_date{NONE,BIRTH,DEATH};
    date(): _date(0), _type(NONE){}
    date(int day, int month, int year, type_date type )
    {
        this->_date = day + month*100 + year*10000;
        this->_type = type;
    }

    friend std::ostream& operator>>(std::ostream& stream, date value);

    bool operator < (date const& value) const
    {
        return this->_date < value._date;
    }
    bool operator > (date const& value) const
    {
        return this->_date > value._date;
    }
    bool operator >= (date const& value) const
    {
        return this->_date >= value._date;
    }
    bool operator == (date const& value) const
    {
        return this->_date == value._date;
    }
    void set_type(type_date type)
    {
        this->_type = type;
    }
    type_date type(void)
    {
        return this->_type;
    }
    int year(void)
    {
        return (int)(this->_date/10000);
    }
    int month(void)
    {
        return (int)(this->_date/100 % 100);
    }
    int day(void)
    {
        return (int)(this->_date % 100);
    }
    date operator - (const date& value)
    {
        if(value > *this)
            return date(value._date - this->_date,type_date::NONE);
        else
            return date(this->_date - value._date,type_date::NONE);
    }
    date operator + (const date& value)
    {
        return date(value._date + this->_date,type_date::NONE);
    }

    friend std::istream& operator>>(std::istream& stream, date& value);

private:
    date(int value, type_date type)
    {
        this->_date = value;
        this->_type = type;
    }

    int _date;
    type_date _type;

};

std::istream& operator>>(std::istream& stream, date& value)
{
    int day = 0, month = 0, year = 0;
    stream >> day >> month >> year;
    value._date = day + month*100 + year*10000;
    return stream;
}


template <typename T>
void shiftDown(std::vector<T>& a, int index, int n)
{
    int index_max = 0;
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    while (left < n)
    {
        if (left == n - 1)
            index_max = left;
        else
            index_max = (a[left] > a[right]) ? (left) : (right);
        if (a[index] < a[index_max])
        {
            std::swap(a[index], a[index_max]);
            index = index_max;
            left = index * 2 + 1;
            right = index * 2 + 2;
        }
        else
            break;
    }
}

template <typename T>
void heapify(std::vector<T> &a)
{
    for (int i = a.size() - 1; i >= 0; --i)
        shiftDown(a, i, a.size());
}

template <typename T>
void Heap_sort(std::vector<T>& a)
{
    heapify(a);
    for (int n_unsorsed = a.size() - 1; n_unsorsed >= 1; n_unsorsed--)
    {
        std::swap(a[n_unsorsed], a[0]);
        shiftDown(a, 0, n_unsorsed);
    }
}



int main()
{
    int n;
    std::cin >> n;
    std::vector<date> data;
    date birth,death;
    date date_18(0,0,18,date::NONE);
    date date_80(0,0,80,date::NONE);
    for( int i = 0; i<n; ++i)
    {
        date tmp;
        std::cin >> birth >> death;
        if( (birth+date_18) >= death )
            continue;
        else
            tmp = birth+date_18;

        if( (birth+date_80) < death )
            death = birth+date_80;

        tmp.set_type(date::BIRTH);
        death.set_type(date::DEATH);
        data.push_back(tmp);
        data.push_back(death);
    }

    Heap_sort(data);

    int max = 0;
    int k = 0;
    for(auto it = data.begin(); it!=data.end(); ++it)
    {
        if( it->type() == date::BIRTH)
        {
            k++;
            if(k > max)
                max = k;
        }
        else
            k--;
    }
    std::cout<<max;
    return 0;
}
