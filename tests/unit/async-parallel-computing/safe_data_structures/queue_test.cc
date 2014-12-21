/**
  \brief
  Concurent core info:
  http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2406.html

  coupled - Queue
  https://www.quantnet.com/threads/c-multithreading-in-boost.10028/
  http://stackoverflow.com/questions/10139251/shared-queue-in-c

  concurent queue
  http://stackoverflow.com/questions/16275112/boost-c-lock-free-queue-vs-shared-queue
  http://www.alexey-martynov.pp.ru/index.php?data=articles&article=mt-queue
  http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
  http://stackoverflow.com/questions/6959023/c-producer-consumer-queue-with-very-fast-and-reliable-handover
  http://blog.ruslans.com/2013/08/introduction-to-high-level.html

  Finded tut.:
    https://computing.llnl.gov/tutorials/pthreads/
     https://computing.llnl.gov/tutorials/parallel_comp/


  Concurent code style
    http://www.codingstandard.com/section/18-concurrency/

  http://www.quora.com/What-are-the-most-commonly-used-thread-safe-queue-implementations-in-C++

  http://theboostcpplibraries.com/boost.lockfree - boost loock free

  http://www.boost.org/doc/libs/1_57_0/doc/html/lockfree.html
  http://www.boost.org/doc/libs/1_57_0/doc/html/thread/sds.html#thread.sds.synchronized_queues

  // Troubles
  http://stackoverflow.com/questions/1164023/is-there-a-production-ready-lock-free-queue-or-hash-implementation-in-c
*/

#include <gtest/gtest.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
//#include <boost/thread/concurrent_queues/  // experimental
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/lock_algorithms.hpp>
#include <boost/noncopyable.hpp>

#include <list>
#include <ostream>
#include <queue>

#if __cplusplus > 199711L
#  include <mutex>
#  include <thread>
#endif

#include <pthread.h>

#if __cplusplus > 199711L

#else
using boost::mutex;
using boost::lock_guard;
#endif
using std::list;

namespace interfaces_mt_ds {
/// Существующие интерфейсы
// Boost - lookfree ds
// TBB - best but...
// С++11 - потокобезопасные контейнеры - таких там нет
//   http://stackoverflow.com/questions/15278343/c11-thread-safe-queue

// Intel TBB
template <typename T>
class concurent_queue {
public:
  concurent_queue() {}
  
  void push(const T& source);
  bool try_pop(T& destination);
  
  bool empty() const;  // may not be precist cos pending 
private:
  concurent_queue(const concurent_queue&);
  concurent_queue& operator=(const concurent_queue&);
};

template <typename T>
class concurent_bounded_queue {
public:
  concurent_bounded_queue() {}
  
  void push(const T& source);
  bool try_pop(T& destination);
  
  bool empty() const;
private:
  concurent_bounded_queue(const concurent_bounded_queue&);
  concurent_bounded_queue& operator=(const concurent_bounded_queue&);
};
}

// TODO: очередь от Шена
// http://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning
//
// В вопросах кто-то не лестно отозвался о реализации, но что он сказал?
template <typename T>
class concurent_queue 
{
  mutex mutex_;
  list<T> q_;
public:
  void enqueue(T x) {
    // allocation here
    list<T> tmp;
    tmp.push_back(move(x));
    
    // threading
    {
      lock_guard<mutex> lock(mutex_);
      // вроде бы константное время
      q_.splice(end(q_), tmp);
      
      // для вектора может неожиданно потреб. реаллокация
    }
  }
  
  // ...
};


// TODO: из толков от яндекса
// https://tech.yandex.ru/events/yagosti/cpp-user-group/talks/1798/
// Для контейнеров нужна внешняя синхронизация.
//
// ref base and value base - похоже не то же самое что смартпоинтеры в контейнерах
//
// Нельзя зывать чужой код под "замком"!!
/*

// кстати в плане исключений все было норм.
void push(const T& t){
  //node* p_node = new node(t);  // TODO: сделать безопасным в плане искл.
  // http://www.gotw.ca/publications/using_auto_ptr_effectively.htm
  auto_ptr<node> p_node(new node(t));
  lock_guard lck(mtx);
  
  p_node->next = head;
  
  head = p_node.release();  // not get!!
}
// когда забираем из стека, то тоже можно захватить auto_ptr'ом
*/

TEST(DS, TBBAssignTest) {
  
}

namespace fix_extern_space {
/** Pro
   http://stackoverflow.com/questions/20488854/implementation-of-a-bounded-blocking-queue-using-c

 https://www.threadingbuildingblocks.org/docs/help/reference/containers_overview/concurrent_bounded_queue_cls.htm
 Assume all includes are there

  http://www.boost.org/doc/libs/1_35_0/doc/html/thread/synchronization.html#thread.synchronization.condvar_ref.condition_variable_any
*/
struct BoundedBlockingQueueTerminateException
    : virtual std::exception,
      virtual boost::exception { };

// http://stackoverflow.com/questions/5018783/c-pthread-blocking-queue-deadlock-i-think
template<typename T>
class bounded_blocking_queue : public boost::noncopyable {
private:
  std::queue<T> m_q;  // FIXME: to list
  boost::mutex mtx;
  boost::
  //mutex::
  condition_variable_any cond1; // q.empty() condition
  boost::
  //mutex::
  condition_variable_any cond2; // q.size() == size condition
  int nblocked1;
  int nblocked2;
  bool stopped;
  int m_size;

public:
  // types
  typedef T value_type;
  //typedef A allocator_type;
  typedef T& reference;
  typedef const T& const_reference;

  bounded_blocking_queue(int size)
      : m_size(size), nblocked1(0), nblocked2(0), stopped(false) {
    if (m_size < 1){
        // BOOST_THROW_EXCEPTION
    }
  }

  ~bounded_blocking_queue() {
    stop(true);
  }

  bool empty() {
    boost::mutex::scoped_lock lock(mtx);
    return m_q.empty();
  }

  std::size_t size() {
    boost::mutex::scoped_lock lock(mtx);
    return m_q.size();
  }

  bool try_push(const T& item) {
    boost::mutex::scoped_lock lock(mtx);
    if (m_q.size() == size)
        return false;

    m_q.push(item);
    lock.unlock();
    cond1.notify_one();
    return true;
  }

private:
  void push(const T& item) {
    boost::mutex::scoped_lock lock(mtx);

    ++nblocked2;
    while (!stopped && m_q.size() == size)
      cond2.wait(lock);
    --nblocked2;

    if (stopped) {
      cond2.notify_all();
      BOOST_THROW_EXCEPTION(BoundedBlockingQueueTerminateException());
    }

    m_q.push(item);
    //lock.unlock(mtx);  // why?
    cond1.notify_one();
  }

public:
  bool try_pop(T& popped) {
      boost::mutex::scoped_lock lock(mtx);
      if (m_q.empty())
          return false;

      popped = m_q.front();
      m_q.pop();
      //lock.unlock(mtx);  // why?
      cond2.notify_one();
      return true;
  }

  /**
    \brief blocked call
  */
private:
  void pop(T& popped) {
      boost::mutex::scoped_lock lock(mtx);

      ++nblocked1;
      while (!stopped && m_q.empty())
          cond1.wait(lock);
      --nblocked1;

      if (stopped) {
          cond1.notify_all();
          BOOST_THROW_EXCEPTION(BoundedBlockingQueueTerminateException());
      }

      popped = m_q.front();
      m_q.pop();
      cond2.notify_one();
  }

public:
  void stop(bool wait) {
    boost::mutex::scoped_lock lock(mtx);
    stopped = true;
    cond1.notify_all();
    cond2.notify_all();

    if (wait) {
      while (nblocked1)
        cond1.wait(lock);
      while (nblocked2)
        cond2.wait(lock);
    }
  }
};
}

