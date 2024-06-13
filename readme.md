# Philosophers 42

**Goal:** learn about threads, multi-threading, and mutex (mutual exclusion).

**Thread**:
**Mutex**:
Mutex types:  NORMAL, ERRORCHECK, RECURSIVE, DEFAULT (behavior depends on type)

**Rules:**
* Each philosopher should be a thread.
* There is one fork between each pair of philosophers. 
* If there are several philosophers, each philosopher has a fork on their left side and a fork on their right side.
* If there is only one philosopher, there should be only one fork on the table.
* To prevent philosophers from duplicating forks, each of the forks state should be protected with a mutex.

### Allowed functions:
**Classic:** memset, printf, malloc, free, write.

**New:**
- **usleep**: library: unistd.h. Prototype: int usleep(useconds_t usec); suspends execution of the calling thread for (at
       least) usec (unsigned) microseconds.  The sleep may be lengthened slightly by  any
       system  activity  or  by  the  time spent processing the call or by the
       granularity of system timers. **Returns** 0 on success.  On error, -1 is returned, with errno set to
       indicate the cause of the error.

       **Errors**: EINTR  Interrupted by a signal; EINVAL usec  is  greater  than  or equal to 1000000.


- **gettimeofday**: Library: sys/time.h. Prototype: int gettimeofday(struct timeval *tv, struct timezone *tz); gets time and timezone.
        The tv argument is a struct timeval (as specified in <sys/time.h>): and gives the number of seconds and microseconds since the Epoch
        If either tv or tz is NULL, the corresponding structure is not set or  returned. **Return** 0 for success, or -1 for failure
        Errors:  EFAULT (tv or tz pointing outside accessible addresse space), EINVAL (tv.tv_sec is  negative or outside the range), 
        EPERM (The calling process has insufficient privilege)

**Library: pthread.h**
- **pthread_create**: Protoype: int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg); 
        starts  a  new  thread in the calling process.  The new thread starts execution by invoking start_routine(); arg is passed as the sole  argument
        of start_routine(). It terminates when: It calls pthread_exit(3), specifying an exit status value that is available to another
        thread in the same process that calls pthread_join(3). It returns from start_routine(). It is cancelled with  pthread_cancel. 
        Any  of the threads in the process calls exit(3), or the main thread performs a return from main(). On success, pthread_create() **returns** 0; on error, it returns an error  number,  and  the contents of *thread are undefined. 
        **Errors**: EAGAIN (Insufficient resources to create another thread), EINVAL, EPERM.

- **pthread_join**: Protoype: int pthread_join(pthread_t thread, void **retval); waits for the thread specified by thread to terminate.
        If that thread has already terminated, then pthread_join() returns immediately. The thread specified by thread must be joinable.
        If retval is not NULL, then pthread_join() copies the exit status of the target thread into  the location pointed to by retval.
        If the target thread was canceled, then PTHREAD_CANCELED is placed in the location pointed to by retval.
        If multiple threads simultaneously try to join with the same thread, the results are undefined.
        If the thread calling pthread_join() is canceled, then the target thread will remain joinable.
        On success, pthread_join() **returns** 0; on error, it returns an error number.
        **Errors**: EINVAL (thread not joinable or another thread is alreasy waiting to join), EDEADLK (A deadlock was detected (e.g., two threads tried to join  with  each  other);  or
        thread specifies the calling thread). ESRCH (No thread with the ID thread could be found).

- **pthread_detach**: Protoype: int pthread_detach(pthread_t thread); marks the thread identified by thread as detached.
        When a detached thread terminates, its resources are automatically released back to the  system without the need for another thread to join with the terminated thread.
        Attempting to detach an already detached thread results in unspecified behavior.
        On success, pthread_detach() **returns** 0; on error, it returns an error number.
        **Errors**: EINVAL (thread not joinable). ESRCH (no thread with the ID thread could be found).

- **pthread_mutex_init**: Protoype: int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
        Initializes the mutex referenced by mutex with attributes specified by attr.  If attr is NULL, the default mutex attributes  are  used;
        the  effect  shall  be the same as passing the address of a default mutex attributes object.
        Upon successful initialization, the state of the mutex becomes initialized and unlocked.
        A destroyed mutex object can be reinitialized using pthread_mutex_init(); the results of otherwise referencing the object after it has been destroyed are undefined.
        Attempting to initialize an already initialized mutex results in undefined behavior. **Return** 0 for success and other numbers for error.
        **Errors:** EAGAIN (syst has not enough ressources - other than mem - to initialize mutex). ENOMEM (not enough memory). EPERM (no perm). EINVAL (attr has the robust mutex attribute set without the process-shared attribute being set)

- **pthread_mutex_destroy**: Protoype: int pthread_mutex_destroy(pthread_mutex_t *mutex);
        destroy the mutex object referenced by mutex; the mutex  object  becomes,  in  effect,  uninitialized.
        It shall be safe to destroy an initialized mutex that is unlocked.   Attempting  to  destroy  a  locked mutex,
        or a mutex that another thread is attempting to lock, or a mutex that is being used in a pthread_cond_timedwait() or 
        pthread_cond_wait() call by  another thread, results in undefined behavior. **Return** 0 for success and other numbers for error.
        **Errors:** EAGAIN (syst has not enough ressources - other than mem - to initialize mutex). ENOMEM (not enough memory). EPERM (no perm). EINVAL (attr has the robust mutex attribute set without the process-shared attribute being set)

- **pthread_mutex_lock**: Protoype: int pthread_mutex_lock(pthread_mutex_t *mutex); **returns**  zero  or [EOWNERDEAD]. If the mutex is already locked by another thread,
        the calling thread shall block until the mutex becomes available. This  operation  shall return  with  the  mutex object referenced by mutex in the locked state with the calling
        thread as its owner.

- **pthread_mutex_unlock**: Protoype: int pthread_mutex_unlock(pthread_mutex_t *mutex); release the mutex object referenced by mutex.
       The manner in which a mutex is released is dependent upon the mutex's type attribute.
       If there are threads blocked on the mutex object referenced by mutex when pthread_mutex_unlock() is called, resulting in the mutex becoming available, 
       the scheduling policy shall determine which thread shall acquire the mutex.
       If a signal is delivered to a thread waiting for a mutex, upon return  from  the  signal
       handler the thread shall resume waiting for the mutex as if it was not interrupted.
       If  successful, the pthread_mutex_lock(), pthread_mutex_trylock(), and pthread_mutex_un‐
       lock() functions shall return zero; otherwise, an error number shall be returned to  in‐
       dicate the error.

