//
// Created by zaqwes on 27.08.2022.
//

/*

 // https://www.youtube.com/watch?v=A8eCGOqgvH4&ab_channel=toalexsmail
 - Optim. Races, and Mem model
 - Ordering - What: acquire and Release
 - Ordering - how: mutexes, atomics and or Fences
 - other restriction an compile and hw (bugs)
 - code get & perf
 - relaxed atomis
 - coda: volatile

Direct Core_j <-> Ram - likable model
 interleaving

Real model - L_j cache

 Key feature and assumption:
 maintain full coherent caches[!]

 The talk in one slide
 Don't write a race cond or use non-default(relaxed?) atomics and your code will do what you think.


 Does yout computer exece prog you write? No

 Two key concepts
 Sequenctial consistence(SC)
 Race condition

 Transformations
 Source code -> ... -> Actual exec - Only care abolut

Transformation at all level are equivalde => can reaseon about all transform. as reordering ouf souce code load and stores

 Dekker and Peterson Algoritn
 Even Seq Cons.
 Store Buffer - diff vars - IRIW

 Optivization now
 - single thread opt
 - compile doesn't know about sharing => mutex and atomisc

 Fact of life
 Sc for data-race-free programs[!]

 Mem mode == contract

 How to think about races? Release debug
 asm - isn't true

 Key general concept: Transaction
 atomic - all or nothing

 Key rule: Con't can't move out
 But code can safly moved in - next stage - can't move out

 Function calls

 can;t acured/reease interleave - seq consistent

 Ac/Rel
 Don't write fences by hand
 lock
 std::atomic

 Multiply
 Transitivity/causuality
 who came first

 controlling Reordering #2: std::atomic
 ordered atomics
CAS - weak/strong
 Controllint reordering #3: Fendes & order apis

 */

/*

 Part II
 Other restrictions on compiler and hw bugs
 packed

 */

/*

LFree P I

 ACID
 atomic - member of object
 publish

 consitency isomation durability

 Key tool/ The ordered atomic variables
 */

/*

LFree P II

 */