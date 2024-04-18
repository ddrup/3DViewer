#include "test_affine_transformation.h"
#include "test_help_func.h"
#include "test_parse_obj_file.h"

#define ASSERT_DECIMAL_EQ(RESULT, EXPECTED)                                  \
  for (size_t i = 0; i < 4; i++) {                                           \
    ck_assert_msg(RESULT.bits[i] == EXPECTED.bits[i], "[%zu] %#x != %#x", i, \
                  RESULT.bits[i], EXPECTED.bits[i]);                         \
  }

Suite *example_suite_create(void) {
  Suite *suite = suite_create("Example");
  TCase *tcase_core = tcase_create("Core of example");
  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, create_matrix_test1);

  tcase_add_test(tcase_core, calloc_matrix_test1);

  tcase_add_test(tcase_core, atof_test1);
  tcase_add_test(tcase_core, atof_test2);
  tcase_add_test(tcase_core, atoi_test1);

  tcase_add_test(tcase_core, vectors_test1);
  tcase_add_test(tcase_core, extractPolygon_test1);
  tcase_add_test(tcase_core, extractPolygon_test2);
  tcase_add_test(tcase_core, extractPolygon_test3);

  tcase_add_test(tcase_core, extractCoordinates_test1);
  tcase_add_test(tcase_core, extractCoordinates_test2);
  tcase_add_test(tcase_core, extractCoordinates_test3);
  tcase_add_test(tcase_core, extractCoordinates_test4);

  tcase_add_test(tcase_core, parseObjFile_test1);
  tcase_add_test(tcase_core, parseObjFile_test2);
  tcase_add_test(tcase_core, parseObjFile_test3);
  tcase_add_test(tcase_core, parseObjFile_test4);

  tcase_add_test(tcase_core, callocMatrix_test);
  tcase_add_test(tcase_core, rellocPoligon_test);
  tcase_add_test(tcase_core, Test_vector);

  tcase_add_test(tcase_core, test_affine_transformation_1);
  tcase_add_test(tcase_core, test_affine_transformation_2);
  tcase_add_test(tcase_core, test_affine_transformation_3);
  tcase_add_test(tcase_core, test_affine_transformation_4);
  tcase_add_test(tcase_core, test_affine_transformation_5);
  tcase_add_test(tcase_core, test_affine_transformation_6);
  tcase_add_test(tcase_core, test_affine_transformation_7);
  tcase_add_test(tcase_core, test_affine_transformation_8);
  tcase_add_test(tcase_core, test_affine_transformation_9);
  tcase_add_test(tcase_core, test_affine_transformation_10);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = example_suite_create();
  SRunner *suite_runner = srunner_create(suite);
  enum fork_status forkStatus = CK_NOFORK;
  srunner_set_fork_status(suite_runner, forkStatus);
  srunner_run_all(suite_runner, CK_NORMAL);
  // Получаем количество проваленных тестов.
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  if (failed_count != 0) {
    // Сигнализируем о том, что тестирование прошло неудачно.
    return 1;
  }

  return 0;
}
