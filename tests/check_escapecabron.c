#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/escapecabron.h"

/*
START_TEST( test_bit) {
	ck_assert(bit(4,2));
}
END_TEST
*/


Suite *
unoslocos_suite(void) {
	Suite *s = suite_create("Unos locos");

	/* Core test case */
	TCase *tc_core = tcase_create("Core");
//	tcase_add_test(tc_core, test_bit);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void) {
	int number_failed;
	Suite *s = unoslocos_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
