
# libexcept

Based on [Exceptions in C with Longjmp and Setjmp](http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html) by Francesco Nidito


## Example

```c
TRY {
	TRY {
		THROW( FOO_EXCEPTION );
	} CATCH( FOO_EXCEPTION ) {
		THROW( FOO_EXCEPTION );
	} FINALLY {
		
	} ETRY;
} CATCH( FOO_EXCEPTION ) {
	
} FINALLY {
	
} ETRY;
```

## Caveats

- Local variables will be reverted during a throw unless declared `volatile`.

