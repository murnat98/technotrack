#include "Stack.h"

Stack::Stack(size_t size)
{
    assert(this);
    
    data_  = (type*)calloc(size, sizeof(type));
    
    for (int i = 0; i < size; i++)
    {
        data_[i] = DATA_POISON;
    }
    
    size_  = size;
    count_ = 0;
}

Stack::~Stack()
{
    assert(this);
    
    size_ = SIZE_POISON;
    count_ = COUNT_POISON;
    
    free(data_);
    data_ = nullptr;
}

bool Stack::ok()
{
    return  (this != nullptr)       &&
            data_                   &&
            (count_ >= 0)           &&
            size_                   &&
            count_ <= size_;
}

int Stack::dump(const std::string varName)
{
    std::string okText;
	if (ok())
		okText = "ok";
	else
	{
        okText = "ERROR";
		assert(this);
		assert(data_);
	}

    std::ofstream dump("stack.dump", std::ofstream::app);

    dump << "Stack \"" << varName << "\" (" << okText << ") [" << &(*this) << "]\n";
    dump << "{\n\tdata_[" << size_ << "] = [" << data_ << "]\n";
    dump << "\t{\n";

	for (int i = 0; i < count_; i++)
	{
		if (i < count_)
        {
            dump << "\t\t*[" << i << "] = " << data_[i] << "\n";
        }
		else
        {
            dump << "\t\t[" << i << "] = " << data_[i] << "     Poison!\n";
        }
	}

    dump << "\t}\n\tcount_ = " << count_ << "\n";
    dump << "\tsize_ = " << size_ << "\n";
    dump << "}\n";

    dump.close();

	return 0;
}

bool Stack::full()
{
    return count_ >= size_ ? true : false;
}

bool Stack::empty()
{
    return count_ <= 0 ? true : false;
}

int Stack::size()
{
    return count_;
}

int Stack::push(type value)
{
	ASSERT((*this));

	if (full())
	{
        return -1;
	}
    
    data_[count_++] = value;

    ASSERT((*this));

	return 0;
}

type Stack::pop()
{
	ASSERT((*this));

	if (empty())
	{
        return DATA_POISON;
	}

    type ret = data_[--count_];
    data_[count_] = DATA_POISON;

	ASSERT((*this));

	return ret;
}
