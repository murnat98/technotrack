#ifndef Array_hpp
#define Array_hpp

#include <iostream>
#include <string>
#include <assert.h>

#ifndef NDEBUG

#include <fstream>
#define DUMP(array) array.dump(#array);
#define ASSERT(array) if (!array.ok()) { DUMP(array); assert(!"Array is not ok!"); }

#else

#define DUMP(array)
#define ASSERT(array)

#endif // NDEBUG

class Array
{
public:
    Array();
    explicit Array(int size);
    explicit Array(Array& array);
    ~Array();
    
    void resize(int size);
    
private:
    int * array_;
    int   capacity_;
    int   count_;
    bool  allocated_;
    
    constexpr static const int CAPACITY_POISON = -666;
    constexpr static const int COUNT_POISON    = -6666;
    
#ifndef NDEBUG
public:
#else
private:
#endif // NDEBUG
    bool ok  (                         ) const;
    int  dump(const std::string varName) const;
};

#endif /* Array_hpp */
