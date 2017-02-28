#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED



#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>

//#define NDEBUG

//==========DEFINES========
#ifndef NDEBUG
    #define ASSERT(stk) if (!stk.ok()) { DUMP(stk); assert (!"Stack si not OK!!!\n"); }
    #define DUMP(stk) stk.dump(#stk);
#else
    #define ASSERT(stk)
    #define DUMP(stk)
#endif // NDEBUG

typedef int type;

class Stack
{
private:
    const static int INIT_SIZE    = 255;
    const static int COUNT_POISON = -666;
    const static int DATA_POISON  = -666;
    const static int SIZE_POISON  = -666;
    
public:
    explicit Stack(size_t size = INIT_SIZE);
    ~Stack();
    
    bool full ();
    bool empty();
    int  size ();
    
    int  push(type value);
    type pop();
    
private:
    type*  data_;
    int    count_;
    size_t size_;
    
#ifndef NDEBUG
public:
#else
private:
#endif // NDEBUG
    bool ok();
    int  dump(const std::string varName);
    
};



#endif // STACK_H_INCLUDED
