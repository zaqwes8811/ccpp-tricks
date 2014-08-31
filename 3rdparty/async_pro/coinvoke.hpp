//
// coinvoke.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef COINVOKE_HPP
#define COINVOKE_HPP

#include <asio/io_service.hpp>
#include <boost/detail/atomic_count.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/mul.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/type_traits/remove_reference.hpp>

#define ARG_PACK_MAX_ARITY 10
#define ARG_PACKS_MAX_SIZE 5

//------------------------------------------------------------------------------
// The arg_pack struct holds the arguments to be passed to a function with a
// specified signature. It has the following interface:
//
//   template <typename Fn>
//   struct arg_pack
//   {
//     enum { arity = N + 1 };
//
//     typedef ... type0;
//     ...
//     typedef ... typeN;
//
//     struct values_type
//     {
//       typename boost::remove_reference<type0>::type arg0;
//       ...
//       typename boost::remove_reference<typeN>::type argN;
//     };
//
//     void init(type0 a0, ..., typeN aN);
//
//     boost::optional<values_type> values;
//   };
//
// The Fn template parameter must be a function signature (and not a function
// pointer). E.g.:
//
//   arg_pack<void(int, char, float)> pack;
//

template <int Arity>
struct arg_pack_base;

#define ARG_PACK_BASE_TYPEDEFS(z, n, data) \
  typedef typename boost::function_traits<Fn>:: \
    BOOST_PP_CAT(arg, BOOST_PP_CAT(BOOST_PP_INC(n), _type)) \
    BOOST_PP_CAT(type, n);

#define ARG_PACK_BASE_VALUES_TYPE_MEMBERS(z, n, data) \
  typename boost::remove_reference<BOOST_PP_CAT(type, n)>::type \
  BOOST_PP_CAT(arg, n);

#define ARG_PACK_BASE_DEF(z, n, data) \
  template <> \
  struct arg_pack_base<n> \
  { \
    template <typename Fn> \
    struct type \
    { \
      enum { arity = n }; \
      BOOST_PP_REPEAT(n, ARG_PACK_BASE_TYPEDEFS, _) \
      struct values_type \
      { \
        BOOST_PP_REPEAT(n, ARG_PACK_BASE_VALUES_TYPE_MEMBERS, _) \
      }; \
      void init(BOOST_PP_ENUM_BINARY_PARAMS(n, type, a)) \
      { \
        values_type v = { BOOST_PP_ENUM_PARAMS(n, a) }; \
        values = v; \
      } \
      boost::optional<values_type> values; \
    }; \
  };

BOOST_PP_REPEAT_FROM_TO(
    0, BOOST_PP_INC(ARG_PACK_MAX_ARITY),
    ARG_PACK_BASE_DEF, _)

#undef ARG_PACK_BASE_TYPEDEFS
#undef ARG_PACK_BASE_VALUES_TYPE_MEMBERS
#undef ARG_PACK_BASE_DEF

template<typename Fn>
struct arg_pack
  : arg_pack_base<boost::function_traits<Fn>::arity>::template type<Fn>
{
};

template<>
struct arg_pack<void>
{
  enum { arity = 0 };
  void init();
};

//------------------------------------------------------------------------------
// The arg_pack_get struct is used to retrieve a reference to the argument at a
// specified index from an arg_pack. For example:
//
//   typedef arg_pack<void(int, char)> pack_type;
//   pack_type pack;
//   ...
//   int& i = arg_pack_get<0, pack_type>::get(pack);
//

template <int Arg>
struct arg_pack_get_base;

#define ARG_PACK_GET_BASE_DEF( z, n, data ) \
  template <> \
  struct arg_pack_get_base<n> \
  { \
    template <typename Pack> \
    struct type \
    { \
      typedef typename Pack::BOOST_PP_CAT(type, n) arg_type; \
      typedef typename boost::add_reference<arg_type>::type result_type; \
      static result_type get(Pack& pack) \
      { \
        return pack.values->BOOST_PP_CAT(arg, n); \
      } \
    }; \
  };

BOOST_PP_REPEAT_FROM_TO(
    0, ARG_PACK_MAX_ARITY,
    ARG_PACK_GET_BASE_DEF, _)

#undef ARG_PACK_GET_BASE_DEF

template <int Arg, typename Pack>
struct arg_pack_get
  : arg_pack_get_base<Arg>::template type<Pack>
{
};

//------------------------------------------------------------------------------
// The arg_packs struct contains one or more arg_pack objects that correspond to
// one or more functions. The arg_pack objects may be accessed and initialised,
// and individual arguments may be retrieved using a single flat index. The
// arg_packs class has the following interface:
//
//   template <typename Fn0, ..., typename FnN>
//   struct arg_packs
//   {
//     typedef arg_pack<Fn0> type0;
//     ...
//     typedef arg_pack<FnN> typeN;
//
//     enum
//     {
//       offset0 = 0,
//       arity0 = type0::arity,
//       ...
//       offsetN = ...,
//       arityN = typeN::arity,
//       total_arity = ...
//     };
//
//     type0 pack0;
//     ...
//     typeN packN;
//   };
//

#define ARG_PACKS_TYPEDEFS(z, n, data) \
  typedef arg_pack<BOOST_PP_CAT(Fn, n)> BOOST_PP_CAT(type, n);

#define ARG_PACKS_ENUM_MEMBERS(z, n, data) \
  BOOST_PP_CAT(offset, n) = \
    BOOST_PP_CAT(offset, BOOST_PP_DEC(n)) \
    + BOOST_PP_CAT(arity, BOOST_PP_DEC(n)), \
  BOOST_PP_CAT(arity, n) = BOOST_PP_CAT(type, n)::arity

#define ARG_PACKS_MEMBERS(z, n, data) \
  BOOST_PP_CAT(type, n) BOOST_PP_CAT(pack, n);

template <BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
      ARG_PACKS_MAX_SIZE, typename Fn, void)>
struct arg_packs
{
  BOOST_PP_REPEAT(ARG_PACKS_MAX_SIZE, ARG_PACKS_TYPEDEFS, _)

  enum
  {
    offset0 = 0,
    arity0 = type0::arity,
    BOOST_PP_ENUM_SHIFTED(ARG_PACKS_MAX_SIZE, ARG_PACKS_ENUM_MEMBERS, _),
    total_arity = BOOST_PP_CAT(offset, BOOST_PP_DEC(ARG_PACKS_MAX_SIZE))
      + BOOST_PP_CAT(arity, BOOST_PP_DEC(ARG_PACKS_MAX_SIZE))
  };

  BOOST_PP_REPEAT(ARG_PACKS_MAX_SIZE, ARG_PACKS_MEMBERS, _)
};

#undef ARG_PACKS_TYPEDEFS
#undef ARG_PACKS_ENUM_MEMBERS
#undef ARG_PACKS_MEMBERS

//------------------------------------------------------------------------------
// The arg_packs_get_pack struct is used to retrieve a reference to the pack at
// a specified index from an arg_packs object. For example:
//
//   typedef arg_packs<void(int, char), void(float)> packs_type;
//   packs_type packs;
//   ...
//   arg_pack<void(float)>& p = arg_packs_get_pack<1, packs_type>::get(packs);
//

template <int Pack>
struct arg_packs_get_pack_base;

#define ARG_PACKS_GET_PACK_BASE_DEF( z, n, data ) \
  template <> \
  struct arg_packs_get_pack_base<n> \
  { \
    template <typename Packs> \
    struct type \
    { \
      typedef typename Packs::BOOST_PP_CAT(type, n) pack_type; \
      enum { arity = pack_type::arity }; \
      static pack_type& get(Packs& packs) \
      { \
        return packs.BOOST_PP_CAT(pack, n); \
      } \
    }; \
  };

BOOST_PP_REPEAT_FROM_TO(
    0, ARG_PACK_MAX_ARITY,
    ARG_PACKS_GET_PACK_BASE_DEF, _)

#undef ARG_PACKS_GET_PACK_BASE_DEF

template <int Pack, typename Packs>
struct arg_packs_get_pack
  : arg_packs_get_pack_base<Pack>::template type<Packs>
{
};

//------------------------------------------------------------------------------
// The arg_packs_get_arg struct is used to retrieve a reference to the argument
// at a specified index from an arg_packs object. The index space is flat
// across all arg_pack objects contains withing the arg_packs object. For
// example:
//
//   typedef arg_packs<void(int, char), void(float)> packs_type;
//   packs_type packs;
//   ...
//   float& f = arg_packs_get_arg<2, packs_type>::get(packs);
//

#define ARG_PACKS_GET_ARG_PACK_INDEX(z, n, data) \
  (Arg < Packs::BOOST_PP_CAT(offset, n) + Packs::BOOST_PP_CAT(arity, n)) ? n :

#define ARG_PACKS_GET_ARG_ARG_INDEX(z, n, data) \
  (Arg < Packs::BOOST_PP_CAT(offset, n) + Packs::BOOST_PP_CAT(arity, n)) \
  ? (Arg - Packs::BOOST_PP_CAT(offset, n)) :

template <int Arg, typename Packs>
struct arg_packs_get_arg
{
  enum
  {
    pack_index =
      BOOST_PP_REPEAT(
          BOOST_PP_DEC(ARG_PACKS_MAX_SIZE),
          ARG_PACKS_GET_ARG_PACK_INDEX, _)
      BOOST_PP_DEC(ARG_PACKS_MAX_SIZE),
    arg_index =
      BOOST_PP_REPEAT(
          BOOST_PP_DEC(ARG_PACKS_MAX_SIZE),
          ARG_PACKS_GET_ARG_ARG_INDEX, _)
      (Arg - Packs::BOOST_PP_CAT(offset, BOOST_PP_DEC(ARG_PACKS_MAX_SIZE)))
  };

  typedef typename arg_packs_get_pack<pack_index, Packs>::pack_type pack_type;
  typedef typename arg_pack_get<arg_index, pack_type>::result_type result_type;

  static result_type get(Packs& packs)
  {
    return arg_pack_get<arg_index, pack_type>::get(
        arg_packs_get_pack<pack_index, Packs>::get(packs));
  }
};

#undef ARG_PACKS_GET_ARG_PACK_INDEX
#undef ARG_PACKS_GET_ARG_ARG_INDEX

//------------------------------------------------------------------------------
// The arg_packs_invoke struct is used to invoke a function object with all of
// the arguments contained within an arg_packs object. For example:
//
//   typedef arg_packs<void(int, char), void(float)> packs_type;
//   packs_type packs;
//   ...
//   extern void foo(int a, char b, float c);
//   arg_packs_invoke<packs_type::arity>::invoke(foo, packs);
//

template <int Arity>
struct arg_packs_invoke;

#define ARG_PACKS_INVOKE_ARGS(z, n, data) \
  arg_packs_get_arg<n, Packs>::get(packs)

#define ARG_PACKS_INVOKE_DEF(z, n, data) \
  template <> \
  struct arg_packs_invoke<n> \
  { \
    template <typename Fn, typename Packs> \
    static void invoke(Fn fn, Packs& packs) \
    { \
      fn(BOOST_PP_ENUM(n, ARG_PACKS_INVOKE_ARGS, _)); \
    } \
  };

BOOST_PP_REPEAT_FROM_TO(
    0, BOOST_PP_INC(BOOST_PP_MUL(ARG_PACK_MAX_ARITY, ARG_PACKS_MAX_SIZE)),
    ARG_PACKS_INVOKE_DEF, _)

#undef ARG_PACKS_INVOKE_ARGS
#undef ARG_PACKS_INVOKE_DEF

//------------------------------------------------------------------------------
// State shared between sibling coinvoked tasks.
//

template <typename Packs, typename Cont>
struct coinvoke_state
{
  coinvoke_state(asio::io_service& i, long n, Cont c)
    : io_service(i), counter(n), continuation(c) {}
  asio::io_service& io_service;
  boost::detail::atomic_count counter;
  Packs packs;
  Cont continuation;
};

//------------------------------------------------------------------------------
// Function object to invoke the continuation with combined task results.
//

template <typename Packs, typename Cont>
class invoke_continuation
{
public:
  explicit invoke_continuation(
      const boost::shared_ptr<coinvoke_state<Packs, Cont> >& s)
    : state_(s)
  {
  }

  void operator()()
  {
    arg_packs_invoke<Packs::total_arity>::invoke(
        state_->continuation, state_->packs);
  }

private:
  boost::shared_ptr<coinvoke_state<Packs, Cont> > state_;
};

//------------------------------------------------------------------------------
// Function object that acts as the continuation for the a coinvoked task.
//

template <int Arity>
struct task_continuation_base;

#define TASK_CONTINUATION_BASE_DEF(z, n, data) \
  template <> \
  struct task_continuation_base<n> \
  { \
    template <int Pack, typename Packs, typename Cont> \
    class type \
    { \
    public: \
      typedef typename arg_packs_get_pack<Pack, Packs>::pack_type pack_type; \
      explicit type(const boost::shared_ptr<coinvoke_state<Packs, Cont> >& s) \
        : state_(s) \
      { \
      } \
      void operator()( \
          BOOST_PP_ENUM_BINARY_PARAMS(n, typename pack_type::type, a)) \
      { \
        arg_packs_get_pack<Pack, Packs>::get(state_->packs).init( \
            BOOST_PP_ENUM_PARAMS(n, a)); \
        if (--state_->counter == 0) \
        { \
          state_->io_service.dispatch( \
              invoke_continuation<Packs, Cont>(state_)); \
        } \
      } \
    private: \
      boost::shared_ptr<coinvoke_state<Packs, Cont> > state_; \
    }; \
  };

BOOST_PP_REPEAT_FROM_TO(
    0, BOOST_PP_INC(ARG_PACK_MAX_ARITY),
    TASK_CONTINUATION_BASE_DEF, _)

#undef TASK_CONTINUATION_BASE_DEF

template <int Pack, typename Packs, typename Cont>
class task_continuation
  : public task_continuation_base<
        arg_packs_get_pack<Pack, Packs>::arity
      >::template type<Pack, Packs, Cont>
{
public:
  explicit task_continuation(
      const boost::shared_ptr<coinvoke_state<Packs, Cont> >& s)
    : task_continuation_base<
        arg_packs_get_pack<Pack, Packs>::arity
      >::template type<Pack, Packs, Cont>(s)
  {
  }
};

//------------------------------------------------------------------------------

// The coinvoke function is used to initiate tasks to run in parallel. The
// function has the following interfaces:
//
//   template <typename TaskCont0, ..., typename TaskContN,
//       typename Task0, ..., typename TaskN, Cont>
//   void coinvoke(asio::io_service& io_service,
//       Task0 task0, ..., TaskN taskN, Cont cont);
//
// Each task must be a function object with a single argument, where the
// argument is the continuation function object for the task. The TaskContN
// template parameters explicitly specify the function signatures used for each
// of the task continuations. For example:
//
//   coinvoke<void(int), void(int)>(task0, task1, cont);
//
// says that both tasks have a continuation with the signature void(int).
//

#define COINVOKE_POST_TASK(z, n, data) \
  task_continuation<n, packs_type, Cont> BOOST_PP_CAT(task_cont, n)(state); \
  io_service.post(asio::detail::bind_handler( \
        BOOST_PP_CAT(task, n), BOOST_PP_CAT(task_cont, n)));

#define COINVOKE_DEF(z, n, data) \
  template < \
      BOOST_PP_ENUM_PARAMS(n, typename TaskCont), \
      BOOST_PP_ENUM_PARAMS(n, typename Task), \
      typename Cont> \
  void coinvoke(asio::io_service& io_service, \
      BOOST_PP_ENUM_BINARY_PARAMS(n, Task, task), \
      Cont cont) \
  { \
    typedef arg_packs<BOOST_PP_ENUM_PARAMS(n, TaskCont)> packs_type; \
    typedef coinvoke_state<packs_type, Cont> state_type; \
    boost::shared_ptr<state_type> state(new state_type(io_service, n, cont)); \
    BOOST_PP_REPEAT(n, COINVOKE_POST_TASK, _) \
  }

BOOST_PP_REPEAT_FROM_TO(
    2, BOOST_PP_INC(ARG_PACKS_MAX_SIZE),
    COINVOKE_DEF, _)

#undef COINVOKE_POST_TASK
#undef COINVOKE_DEF

#endif // COINVOKE_HPP
