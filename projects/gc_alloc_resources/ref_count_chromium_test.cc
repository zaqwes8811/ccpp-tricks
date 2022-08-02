// dtor is private

// http://www.chromium.org/developers/smart-pointer-guidelines
// "scoped_refptr is used for reference-counted objects, though normally you
// should avoid these (see below"
//
// "Ref-counted objects - use scoped_refptr; but better yet, rethink your
// design.  "
//
// Sean Parent: shared ptr is evil
// FIXME: one shared and weak is better?

// Guide:
//   http://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one
