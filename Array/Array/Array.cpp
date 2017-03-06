#include "Array.hpp"

Array::Array()
{
    capacity_  = 0;
    count_     = 0;
    array_     = nullptr;
    allocated_ = false;
}

Array::Array(int size)
{
    capacity_  = size;
    count_     = 0;
    array_     = new int[size];
    allocated_ = true;
}

Array::Array(Array& array)
{
    assert(&array);
    
    capacity_  = array.capacity_;
    array_     = new int[capacity_];
    allocated_ = true;
    count_     = 0;
}

Array::~Array()
{
    if (allocated_ == true)
    {
        delete[] array_;
        array_     = nullptr;
        allocated_ = false;
        count_     = COUNT_POISON;
        capacity_  = CAPACITY_POISON;
    }
    
    std::cout << "destruktor" << std::endl;
}

bool Array::ok() const
{
    if (capacity_ > 0)
    {
        return count_ < capacity_ &&
               allocated_ == true &&
               array_ != nullptr;
    }
    else
    {
        return !capacity_           &&
               !count_              &&
               allocated_ == false  &&
               array_ == nullptr;
    }
}

int Array::dump(const std::string varName) const
{
    std::string okText;
    if (ok())
        okText = "ok";
    else
    {
        okText = "ERROR";
        assert(this);
        assert(array_);
    }
    
    std::ofstream dump("array.dump", std::ofstream::app);
    
    dump << "Array \"" << varName << "\" (" << okText << ") [" << &(*this) << "]\n";
    dump << "{\n\tarray_[" << capacity_ << "] = [" << array_ << "]\n";
    dump << "\t{\n";
    
    for (int i = 0; i < capacity_; i++)
    {
        if (i < count_)
        {
            dump << "\t\t*[" << i << "] = " << array_[i] << "\n";
        }
        else
        {
            dump << "\t\t[" << i << "] = " << array_[i] << "     Poison!\n";
        }
    }
    
    dump << "\t}\n\tcount_ = " << count_ << "\n";
    dump << "\tcapacity_ = " << capacity_ << "\n";
    dump << "}\n";
    
    dump.close();
    
    return 0;
}

void Array::resize(int size)
{
    if (size > capacity_)
    {
        array_     = (int *)realloc(array_, sizeof(array_) * size);
        capacity_  = size;
        allocated_ = true;
    }
}
