#ifndef BARRIER_H_
#define BARRIER_H_
//#include <core/include/mutex.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <mutex>
//#include <thread>




class Barrier {

unsigned int _num_of_threads;
unsigned int _current_threads_counter;
mutex_t* _mutex;
sem_t*  _semaphore;
sem_t* _reuse_semaphore;
public:
    Barrier(unsigned int num_of_threads);
    void wait();
	unsigned int waitingThreads();
    ~Barrier();

};

#endif // BARRIER_H_



//
//class Barrier {//multiuse berrier
//unsigned int _num_of_threads;
//unsigned int _current_threads_counter=0;
//mutex_t* _mutex;
//sem_t*  _semaphore;
//sem_t* _reuse_semaphore;
//public:
//    Barrier(unsigned int num_of_threads){
//        _num_of_threads=num_of_threads;
//        _current_threads_counter=0;
//         pthread_cond_init(_mutex,NULL);
//         sem_init(_semaphore, 0,0);
//         sem_init(_reuse_semaphore, 0,1);
//
//}
//    void wait(){
//        //check if im the left threads to leave
//        //start waking up threads
//        //last one wakes a thread and than the woken thread wakes the next one
//        pthread_mutex_lock(_mutex);
//
//        _current_threads_counter++;
//        if(_current_threads_counter==_num_of_threads) {//am i the last one to eneter
//            sem_wait(_reuse_semaphore);
//            sem_post(_semaphore);
//        }
//        pthread_mutex_unlock(_mutex);
//
//        sem_wait(_semaphore);
//        sem_post(_semaphore);
//
//        pthread_mutex_lock(_mutex);
//
//        _current_threads_counter--;//are we the last one to leave
//        if(_current_threads_counter==0){
//            sem_wait(_semaphore);
//            sem_post(_reuse_semaphore);
//        }
//        pthread_mutex_unlock(_mutex);
//
//        sem_wait(_reuse_semaphore);
//        sem_post(_reuse_semaphore);
//    }
//
//	unsigned int waitingThreads(){
//        pthread_mutex_lock(_mutex);
//        unsigned int temp=_current_threads_counter;
//        pthread_mutex_unlock(_mutex);
//        return temp;
//    }
//    ~Barrier(){
//        _mutex_destroy(_mutex);
//        sem_destroy(_semaphore);
//        sem_destroy(_reuse_semaphore);
//    }
//
//	// TODO: define the member variables
//	// Remember: you can only use semaphores!
//};
//class Barrier { one time berrier
//unsigned int _num_of_threads;
//unsigned int _current_threads_counter=0;
//mutex_t* _mutex;
//sem_t*  _semaphore;
//public:
//    Barrier(unsigned int num_of_threads):_num_of_threads(num_of_threads){
//        _current_threads_counter=0;
//         pthread_cond_init(_mutex,NULL);
//         sem_init(semaphore, 0,0);
//}
//    void wait(){
//        //check if im the left threads to leave
//        //start waking up threads
//        //last one wakes a thread and than the woken thread wakes the next one
//        pthread_mutex_lock(_mutex);
//        _current_threads_counter++;
//        unsigned int temp=_current_threads_counter;
//        pthread_mutex_unlock(_mutex);
//        if(temp==_num_of_threads){//am i the last one to eneter
//            sem_post(_semaphore);
//        }
//        sem_wait(_semaphore);
//        sem_post(_semaphore);
////        sem_signal(_semaphore);
//    }
//
//	unsigned int waitingThreads(){
//        pthread_mutex_lock(_mutex);
//        unsigned int temp=_current_threads_counter;
//        pthread_mutex_unlock(_mutex);
//        return temp;
//    }
//    ~Barrier(){
//        _mutex_destroy(_mutex);
//        sem_destroy(_semaphore);
//    }
//
//	// TODO: define the member variables
//	// Remember: you can only use semaphores!
//};

#endif // BARRIER_H_

http://man7.org/linux/man-pages/man3/sem_init.3.html
//int sem_init(sem_t *sem, int pshared, unsigned int value);


//https://stackoverflow.com/questions/6331301/implementing-an-n-process-barrier-using-semaphores
//n = the number of threads
//        count = 0
//mutex = Semaphore(1)
//barrier = Semaphore(0)
//
//
//mutex.wait()
//count = count + 1
//mutex.signal()
//
//if count == n: barrier.signal() # unblock ONE thread
//
//        barrier.wait()
//barrier.signal() # once we are unblocked, it's our duty to unblock the next thread

//http://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf

Semaphore initialization syntax:
fred = Semaphore (1)

Semaphore operations
fred . increment ()
fred . decrement ()
fred . signal ()
2 fred . wait ()
1 fred . increment_and_wake_a_waiting_process_if_any ()
2 fred . decrement_and_block_if_the_result_is_negative ()

struct barrier_type
{
    // how many processors have entered the barrier
    // initialize to 0
    int arrive_counter;
    // how many processors have exited the barrier
    // initialize to p
    int leave_counter;
    int flag;
    std::mutex lock;
};

// barrier for p processors
//void barrier(barrier_type* b, int p)
//{
//    b->lock.lock();
//    if (b->leave_counter == p)
//    {
//        if (b->arrive_counter == 0) // no other threads in barrier
//        {
//            b->flag = 0; // first arriver clears flag
//        }
//        else
//        {
//            b->lock.unlock();
//            while (b->leave_counter != p); // wait for all to leave before clearing
//            b->lock.lock();
//            b->flag = 0; // first arriver clears flag
//        }
//    }
//    b->arrive_counter++;
//    int arrived = b->arrive_counter;
//    b->lock.unlock();
//    if (arrived == p) // last arriver sets flag
//    {
//        b->arrive_counter = 0;
//        b->leave_counter = 1;
//        b->flag = 1;
//    }
//    else
//    {
//        while (b->flag == 0); // wait for flag
//        b->lock.lock();
//        b->leave_counter++;
//        b->lock.unlock();
//    }
//}

//struct barrier_type
//{
//    int counter; // initialize to 0
//    int flag; // initialize to 0
//    std::mutex lock;
//};
//
//int local_sense = 0; // private per processor
//
//// barrier for p processors
//void barrier(barrier_type* b, int p)
//{
//    local_sense = 1 - local_sense;
//    b->lock.lock();
//    b->counter++;
//    int arrived = b->counter;
//    if (arrived == p) // last arriver sets flag
//    {
//        b->lock.unlock();
//        b->counter = 0;
//        // memory fence to ensure that the change to counter
//        // is seen before the change to flag
//        b->flag = local_sense;
//    }
//    else
//    {
//        b->lock.unlock();
//        while (b->flag != local_sense); // wait for flag
//    }
//}

//barrier hint
//n = the number of threads
//2 count = 0
//3 mutex = Semaphore (1)
//4 barrier = Semaphore (0)


//berrier non solution
//1 rendezvous
//2
//3 mutex . wait ()
//4 count = count + 1
//5 mutex . signal ()
//6
//7 if count == n: barrier . signal ()
//8
//9 barrier . wait ()
//10
//11 critical point


//berrier working solution
//rendezvous
//2
//3 mutex . wait ()
//4 count = count + 1
//5 mutex . signal ()
//6
//7 if count == n: barrier . signal ()
//8
//9 barrier . wait ()
//10 barrier . signal ()
//11
//12 critical point

//two steps berrier implmetion
//# rendezvous
//2
//3 mutex . wait ()
//4 count += 1
//5 if count == n:
//6 turnstile2 . wait () # lock the second
//7 turnstile . signal () # unlock the first
//8 mutex . signal ()
//9
//10 turnstile . wait () # first turnstile
//11 turnstile . signal ()
//12
//13 # critical point
//14
//15 mutex . wait ()
//16 count -= 1
//17 if count == 0:
//18 turnstile . wait () # lock the first
//19 turnstile2 . signal () # unlock the second
//20 mutex . signal ()
//21
//22 turnstile2 . wait () # second turnstile
//23 turnstile2 . signal ()