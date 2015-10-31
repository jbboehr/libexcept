
# libexcept

Based on [Exceptions in C with Longjmp and Setjmp](http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html) by Francesco Nidito


## Caveats

- Local variables will be reverted during a throw unless declared `volatile`.

