
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <check.h>

#include "except.h"

#define REGISTER_TEST(s, name, title) \
	TCase * tc_ ## name = tcase_create(title); \
	tcase_add_test(tc_ ## name, name); \
	suite_add_tcase(s, tc_ ## name);

#define FOO_EXCEPTION (1)
#define BAR_EXCEPTION (2)
#define BAZ_EXCEPTION (3)

START_TEST(test_basic)
{
   int caught = 0;
   TRY {
      THROW( BAR_EXCEPTION );
      ck_assert(0);
   } CATCH( BAR_EXCEPTION ) {
      caught = 1;
   } ETRY;

   ck_assert(caught);
}
END_TEST

START_TEST(test_without_throw)
{
   int i = 0;
   TRY {
	i++;
   } CATCH( BAR_EXCEPTION ) {
	ck_assert(0);
   } FINALLY {
	i++;
   } ETRY;

   ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(test_multi)
{
   int caught = 0;
   TRY {
      THROW( BAR_EXCEPTION );
      ck_assert(0);
   } CATCH( FOO_EXCEPTION ) {
      ck_assert(0);
   } CATCH( BAR_EXCEPTION ) {
      caught = 1;
   } CATCH( BAZ_EXCEPTION ) {
      ck_assert(0);
   } ETRY;

   ck_assert(caught);
}
END_TEST

START_TEST(test_finally)
{
   int caught = 0;
   int finally_ran = 0;
   TRY {
      THROW( BAR_EXCEPTION );
      ck_assert(0);
   } CATCH( FOO_EXCEPTION ) {
      ck_assert(0);
   } CATCH( BAR_EXCEPTION ) {
      caught = 1;
   } CATCH( BAZ_EXCEPTION ) {
      ck_assert(0);
   } FINALLY {
   	finally_ran = 1;
   } ETRY;

   ck_assert(caught);
   ck_assert(finally_ran);
}
END_TEST

START_TEST(test_finally_only)
{
   int finally_ran = 0;
   TRY {
      THROW( BAR_EXCEPTION );
      ck_assert(0);
   } FINALLY {
   	finally_ran = 1;
   } ETRY;

   ck_assert(finally_ran);
}
END_TEST

START_TEST(test_nested)
{
	volatile int finally_ran = 0;
	volatile int catch_ran = 0;
	TRY {
		TRY {
			THROW( FOO_EXCEPTION );
			ck_assert(0);
		} CATCH( FOO_EXCEPTION ) {
			catch_ran++;
			THROW( FOO_EXCEPTION );
			ck_assert(0);
		} FINALLY {
			finally_ran++;
		} ETRY;
	} CATCH( FOO_EXCEPTION ) {
		catch_ran++;
	} FINALLY {
		finally_ran++;
	} ETRY;
	ck_assert_int_eq(catch_ran, 2);
	ck_assert_int_eq(finally_ran, 2);
}
END_TEST


Suite * parser_suite(void)
{
    Suite * s = suite_create("libexcept");

    REGISTER_TEST(s, test_basic, "Basic");
    REGISTER_TEST(s, test_without_throw, "Without throw");
    REGISTER_TEST(s, test_multi, "Multi");
    REGISTER_TEST(s, test_finally, "Finally");
    REGISTER_TEST(s, test_finally_only, "Finally Only");
    REGISTER_TEST(s, test_nested, "Nested");

    return s;
}

int main(void)
{
    int number_failed;
    Suite * s = parser_suite();
    SRunner * sr = srunner_create(s);
    srunner_run_all(sr, CK_ENV);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}

