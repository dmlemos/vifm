#include <stic.h>

#include "../../src/cfg/config.h"
#include "../../src/utils/regexp.h"

static int not_osx(void);

TEST(bad_regex_leaves_line_unchanged)
{
	assert_string_equal("barfoobar",
			regexp_replace("barfoobar", "*foo", "z", 1, 0));
}

TEST(no_infinite_loop_on_empty_global_match, IF(not_osx))
{
	/* On OS X, regular expressions which can match empty strings don't
	 * compile. */
	assert_string_equal("zbarfoobar", regexp_replace("barfoobar", "", "z", 1, 0));
}

TEST(substitute_segfault_bug)
{
	/* see #SF3515922 */
	assert_string_equal("barfoobar", regexp_replace("foobar", "^", "bar", 1, 0));
	assert_string_equal("01", regexp_replace("001", "^0", "", 1, 0));
}

TEST(substitute_begin_global)
{
	assert_string_equal("01", regexp_replace("001", "^0", "", 1, 0));
}

TEST(substitute_end_global)
{
	assert_string_equal("10", regexp_replace("100", "0$", "", 1, 0));
}

TEST(back_reference_substitution)
{
	assert_string_equal("barfoobaz",
			regexp_replace("bazfoobar", "(.*)foo(.*)", "\\2foo\\1", 1, 0));

	assert_string_equal("barbaz", regexp_replace("foobaz", "foo", "bar\\", 1, 0));

	assert_string_equal("f0t0tbaz", regexp_replace("foobaz", "o", "0\\t", 1, 0));
}

TEST(case_sequences_are_recognized)
{
	cfg.ignore_case = 1;
	cfg.smart_case = 1;


	assert_true(regexp_should_ignore_case("a\\c"));
	assert_true(regexp_should_ignore_case("A\\c"));

	assert_true(regexp_should_ignore_case("a\\\\c"));
	assert_false(regexp_should_ignore_case("A\\\\c"));

	assert_false(regexp_should_ignore_case("a\\C"));
	assert_false(regexp_should_ignore_case("A\\C"));

	assert_false(regexp_should_ignore_case("a\\\\C"));
	assert_false(regexp_should_ignore_case("A\\\\C"));

	cfg.ignore_case = 0;
	cfg.smart_case = 0;
}

TEST(case_sequences_are_respected)
{
	/* Case is not ignored. */

	assert_string_equal("bArz",
			regexp_replace("bArbar", "bar\\C", "z", /*glob=*/1, /*ignore_case=*/1));

	assert_string_equal("bArz",
			regexp_replace("bArbar", "bar\\C", "z", /*glob=*/1, /*ignore_case=*/0));

	/* Case is ignored. */

	assert_string_equal("zz",
			regexp_replace("bArbar", "bar\\c", "z", /*glob=*/1, /*ignore_case=*/0));

	assert_string_equal("zz",
			regexp_replace("bArbar", "bar\\c", "z", /*glob=*/1, /*ignore_case=*/1));

	/* Not a special sequence. */

	assert_string_equal("zz",
			regexp_replace("bAr\\CbAr\\C", "bAr\\\\C", "z", /*glob=*/1,
				/*ignore_case=*/0));

	assert_string_equal("zbar",
			regexp_replace("bAr\\Cbar", "bar\\\\c", "z", /*glob=*/1,
				/*ignore_case=*/1));
}

static int
not_osx(void)
{
#ifndef __APPLE__
	return 1;
#else
	return 0;
#endif
}

/* vim: set tabstop=2 softtabstop=2 shiftwidth=2 noexpandtab cinoptions-=(0 : */
/* vim: set cinoptions+=t0 filetype=c : */
