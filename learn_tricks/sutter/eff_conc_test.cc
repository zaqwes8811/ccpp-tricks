// Eff conc.
// http://herbsutter.com/2009/11/11/effective-concurrency-prefer-structured-lifetimes-%E2%80%93-local-nested-bounded-deterministic/

// TODO: The Pillars of Concurrency
// 1. Responsiveness and Isolation via Async Agents
// 2. Throuthput and Scalability via conc. collections
// 3. Consistency via Safely Shared Res.
// http://www.drdobbs.com/parallel/the-pillars-of-concurrency/200001985?pgno=2

// TODO: Use Threads Correctly = Isolation + Asynchronous Messages
// http://www.drdobbs.com/parallel/use-threads-correctly-isolation-asynch/215900465

// TODO: Use Thread Pools Correctly: Keep Tasks Short and Nonblocking
// http://stackoverflow.com/questions/3988128/c-thread-pool - good pool


// TODO: Avoid Exposing Concurrency: Hide It Inside Synchronous Methods
// А как быть со всякими асинхоронными api?
//
// Way: hide it inside sync API

// TODO: Boost.Thread supply
// thread interrurpt - но а если объект потока не доступен?
//
//  Join the thread before destroying or use an scoped thread.
