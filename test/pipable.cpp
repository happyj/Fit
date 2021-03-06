#include <fit/pipable.hpp>
#include <fit/static.hpp>
#include "test.hpp"

static constexpr fit::static_<fit::pipable_adaptor<binary_class> > binary_pipable = {};

static constexpr fit::static_<fit::pipable_adaptor<unary_class> > unary_pipable = {};

static constexpr fit::static_<fit::pipable_adaptor<mutable_class> > mutable_pipable = {};

static constexpr fit::static_<fit::pipable_adaptor<void_class> > void_pipable = {};

static constexpr fit::static_<fit::pipable_adaptor<mono_class> > mono_pipable = {};

static constexpr fit::static_<fit::pipable_adaptor<move_class> > move_pipable = {};

constexpr fit::pipable_adaptor<void_class> void_pipable_constexpr = {};

constexpr fit::pipable_adaptor<binary_class> binary_pipable_constexpr = {};

constexpr fit::pipable_adaptor<unary_class> unary_pipable_constexpr = {};

#if FIT_HAS_NOEXCEPT_DEDUCTION
FIT_TEST_CASE()
{
    static_assert(noexcept(1 | binary_pipable(2)), "noexcept pipable");
    static_assert(noexcept(binary_pipable(1, 2)), "noexcept pipable");
}
#endif

FIT_TEST_CASE()
{
    void_pipable(1);
    1 | void_pipable;
    FIT_TEST_CHECK(3 == (1 | binary_pipable(2)));
    FIT_TEST_CHECK(3 == (binary_pipable(1, 2)));
    FIT_TEST_CHECK(3 == (3 | unary_pipable));
    FIT_TEST_CHECK(3 == (3 | unary_pipable()));
    FIT_TEST_CHECK(3 == (unary_pipable(3)));
    int i1 = 1;
    FIT_TEST_CHECK(3 == (2 | binary_pipable(i1)));
    FIT_TEST_CHECK(3 == (i1 | mutable_pipable(2)));
    FIT_TEST_CHECK(3 == (i1));
    int i2 = 1;
    FIT_TEST_CHECK(3 == (mutable_pipable(i2, 2)));
    FIT_TEST_CHECK(3 == (i2));
    FIT_TEST_CHECK(3 == (mono_pipable(2)));
    FIT_TEST_CHECK(3 == (2| mono_pipable));
}

FIT_TEST_CASE()
{
    FIT_TEST_CHECK(3 == (move_class()(1, 2)));
    FIT_TEST_CHECK(3 == (move_pipable(1, 2)));
    FIT_TEST_CHECK(3 == (1 | move_pipable(2)));
    FIT_TEST_CHECK(3 == (1 | fit::pipable(move_class())(2)));
    FIT_TEST_CHECK(3 == (fit::pipable(move_class())(1, 2)));
}

FIT_TEST_CASE()
{
    void_pipable_constexpr(1);
    1 | void_pipable_constexpr;
    FIT_STATIC_TEST_CHECK(3 == (1 | binary_pipable_constexpr(2)));
    FIT_STATIC_TEST_CHECK(3 == (binary_pipable_constexpr(1, 2)));
    FIT_STATIC_TEST_CHECK(3 == (3 | unary_pipable_constexpr));
    FIT_STATIC_TEST_CHECK(3 == (3 | unary_pipable_constexpr()));
    FIT_STATIC_TEST_CHECK(3 == (unary_pipable_constexpr(3)));
}

FIT_TEST_CASE()
{
    FIT_TEST_CHECK(3 == fit::limit_c<2>(binary_pipable_constexpr)(1, 2));
    FIT_STATIC_TEST_CHECK(3 == fit::limit_c<2>(binary_pipable_constexpr)(1, 2));
}

FIT_TEST_CASE()
{
    auto f = fit::pipable(fit::limit_c<2>(binary_class()));
    static_assert(fit::is_callable<decltype(f), int, int>::value, "Passing the limit is not callable");
    static_assert(!fit::is_callable<decltype(f), int, int, int>::value, "Passing the limit is not callable");
    static_assert(!fit::is_callable<decltype(f), int, int, int, int>::value, "Passing the limit is not callable");
}
