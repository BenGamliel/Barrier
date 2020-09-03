#ifndef BARRIER_H_
#define BARRIER_H_
//#include <core/include/mutex.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <mutex>
class Barrier {//multiuse berrier
unsigned int _num_of_threads;
unsigned int _current_threads_counter=0;
mutex_t* _mutex;
sem_t*  _semaphore;
sem_t* _reuse_semaphore;
public:
   Barrier(unsigned int num_of_threads){
       _num_of_threads=num_of_threads;
       _current_threads_counter=0;
        pthread_cond_init(_mutex,NULL);
        sem_init(_semaphore, 0,0);
        sem_init(_reuse_semaphore, 0,1);

}
   void wait(){
       //check if im the left threads to leave
       //start waking up threads
       //last one wakes a thread and than the woken thread wakes the next one
       pthread_mutex_lock(_mutex);

       _current_threads_counter++;
       if(_current_threads_counter==_num_of_threads) {//am i the last one to eneter
           sem_wait(_reuse_semaphore);
           sem_post(_semaphore);
       }
       pthread_mutex_unlock(_mutex);

       sem_wait(_semaphore);
       sem_post(_semaphore);

       pthread_mutex_lock(_mutex);

       _current_threads_counter--;//are we the last one to leave
       if(_current_threads_counter==0){
           sem_wait(_semaphore);
           sem_post(_reuse_semaphore);
       }
       pthread_mutex_unlock(_mutex);

       sem_wait(_reuse_semaphore);
       sem_post(_reuse_semaphore);
   }

	unsigned int waitingThreads(){
       pthread_mutex_lock(_mutex);
       unsigned int temp=_current_threads_counter;
       pthread_mutex_unlock(_mutex);
       return temp;
   }
   ~Barrier(){
       _mutex_destroy(_mutex);
       sem_destroy(_semaphore);
       sem_destroy(_reuse_semaphore);
   }


#endif // BARRIER_H_
