#ifndef __THREAD__
    #define __THREAD__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <iostream>

    #include <atomic>
    
    #include <thread>
    #include <mutex>
    #include <vector>
    #include <random>

#endif

typedef intptr_t (*threadTypedef)(void *);
//  intptr_t     function point return (callback)
//      threadTypedef
//          void *      void * <- point(but function)!   
using namespace std;
mutex values_mtx;
mutex cout_mtx;
vector<int> values;

int main()
{
    values.push_back(42);

    thread tr1(threadFnc, 1);
    thread tr2(threadFnc, 2);

    tr1.join();
    tr2.join();

    cout << "InPut" \
                     << *values \
                                 << ", Result 1:    " \
                                                        << *(values + 1) \
                                 << ", Result 2:    " \
                                                        << *(values + 2) \
        <<"\n";


    return 1;
}

void threadFnc(int tid)
{

    cout_mtx.lock();
    cout << "Starting thread " \
                                 << tid 
        << ".\n";    
    cout_mtx.unlock();

    values_mtx.lock();
    int val = values[0];
    values_mtx.unlock();

    int rval = randGen(0, 10);
    val += rval;

    cout_mtx.lock();
    cout<< "Thread" \
                     << tid \
                             << "adding" \
                                          << rval \
                                                     << ". NEW value:   " \
                                                                            << val '.'\
        <<"\n";
    cout_mtx.unlock();    

    values_mtx.lock();
    values.push_back(val);
    values_mtx.unlock();

}

int randGen(const int & min, const int & max)
{
    static thread_local mt19937 generator(hash<thread::id>()(this_thread::get_id()));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator)
}