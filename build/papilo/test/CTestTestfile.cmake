# CMake generated Testfile for 
# Source directory: /mnt/d/aMain/4-pre/pre/papilo/test
# Build directory: /mnt/d/aMain/4-pre/pre/build/papilo/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit-test-build "/home/mzy/.local/lib/python3.8/site-packages/cmake/data/bin/cmake" "--build" "/mnt/d/aMain/4-pre/pre/build" "--target" "unit_test")
set_tests_properties(unit-test-build PROPERTIES  RESOURCE_LOCK "unittestbin" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;200;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-accurate-numerical-statistics "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "accurate-numerical-statistics")
set_tests_properties(unit-test-accurate-numerical-statistics PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-matrix-buffer "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "matrix-buffer")
set_tests_properties(unit-test-matrix-buffer PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-vector-comparisons "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "vector-comparisons")
set_tests_properties(unit-test-vector-comparisons PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-matrix-comparisons "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "matrix-comparisons")
set_tests_properties(unit-test-matrix-comparisons PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-replacing-variables-is-postponed-by-flag "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "replacing-variables-is-postponed-by-flag")
set_tests_properties(unit-test-replacing-variables-is-postponed-by-flag PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-replace-variable "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-replace-variable")
set_tests_properties(unit-test-happy-path-replace-variable PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-substitute-matrix-coefficient-into-objective "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-substitute-matrix-coefficient-into-objective")
set_tests_properties(unit-test-happy-path-substitute-matrix-coefficient-into-objective PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-aggregate-free-column "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-aggregate-free-column")
set_tests_properties(unit-test-happy-path-aggregate-free-column PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-presolve-activity-is-updated-correctly-huge-values "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "presolve-activity-is-updated-correctly-huge-values")
set_tests_properties(unit-test-presolve-activity-is-updated-correctly-huge-values PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-trivial-presolve-singleton-row "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "trivial-presolve-singleton-row")
set_tests_properties(unit-test-trivial-presolve-singleton-row PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-trivial-presolve-singleton-row-pt-2 "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "trivial-presolve-singleton-row-pt-2")
set_tests_properties(unit-test-trivial-presolve-singleton-row-pt-2 PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-problem-comparisons "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "problem-comparisons")
set_tests_properties(unit-test-problem-comparisons PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-coefficient-strengthening "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-coefficient-strengthening")
set_tests_properties(unit-test-happy-path-coefficient-strengthening PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-constraint-propagation-happy-path "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "constraint-propagation-happy-path")
set_tests_properties(unit-test-constraint-propagation-happy-path PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-constraint-propagation-no-tightening-for-lp "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "constraint-propagation-no-tightening-for-lp")
set_tests_properties(unit-test-constraint-propagation-no-tightening-for-lp PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-domcol-happy-path "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "domcol-happy-path")
set_tests_properties(unit-test-domcol-happy-path PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-domcol-parallel-columns "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "domcol-parallel-columns")
set_tests_properties(unit-test-domcol-parallel-columns PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-domcol-multiple-parallel-cols-generate_redundant-reductions "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "domcol-multiple-parallel-cols-generate_redundant-reductions")
set_tests_properties(unit-test-domcol-multiple-parallel-cols-generate_redundant-reductions PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-domcol-multiple-column "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "domcol-multiple-column")
set_tests_properties(unit-test-domcol-multiple-column PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-dual-fix-happy-path "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "dual-fix-happy-path")
set_tests_properties(unit-test-dual-fix-happy-path PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-dual-fix-trivial-column-presolve-finds-reduction "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "dual-fix-trivial-column-presolve-finds-reduction")
set_tests_properties(unit-test-dual-fix-trivial-column-presolve-finds-reduction PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-dual-fix-no-dual-substitution-for-lp "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "dual-fix-no-dual-substitution-for-lp")
set_tests_properties(unit-test-dual-fix-no-dual-substitution-for-lp PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-dual-fix-dual-substitution "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "dual-fix-dual-substitution")
set_tests_properties(unit-test-dual-fix-dual-substitution PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-dual-fix-dual-substitution-rounding "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "dual-fix-dual-substitution-rounding")
set_tests_properties(unit-test-dual-fix-dual-substitution-rounding PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-dual-fix-dual-substitution-unbounded-variables "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "dual-fix-dual-substitution-unbounded-variables")
set_tests_properties(unit-test-dual-fix-dual-substitution-unbounded-variables PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-dual-fix-dual-substitution-equation "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "dual-fix-dual-substitution-equation")
set_tests_properties(unit-test-dual-fix-dual-substitution-equation PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-dual-fix-infinity "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "dual-fix-infinity")
set_tests_properties(unit-test-dual-fix-infinity PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-presolve-fix-continuous "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-presolve-fix-continuous")
set_tests_properties(unit-test-happy-path-presolve-fix-continuous PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-no-presolve-fix-continuous "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-no-presolve-fix-continuous")
set_tests_properties(unit-test-happy-path-no-presolve-fix-continuous PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-test-free-variable-detection "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-test-free-variable-detection")
set_tests_properties(unit-test-happy-path-test-free-variable-detection PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-implied-integer-detection "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-implied-integer-detection")
set_tests_properties(unit-test-happy-path-implied-integer-detection PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-unchanged "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-unchanged")
set_tests_properties(unit-test-parallel-row-unchanged PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-equations-infeasible-second-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-equations-infeasible-second-row-dominant")
set_tests_properties(unit-test-parallel-row-two-equations-infeasible-second-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-equations-infeasible-first-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-equations-infeasible-first-row-dominant")
set_tests_properties(unit-test-parallel-row-two-equations-infeasible-first-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-equations-feasible-second-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-equations-feasible-second-row-dominant")
set_tests_properties(unit-test-parallel-row-two-equations-feasible-second-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-equations-feasible-first-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-equations-feasible-first-row-dominant")
set_tests_properties(unit-test-parallel-row-two-equations-feasible-first-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-inequalities-redundant-row-second-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-inequalities-redundant-row-second-row-dominant")
set_tests_properties(unit-test-parallel-row-two-inequalities-redundant-row-second-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-inequalities-redundant-row-first-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-inequalities-redundant-row-first-row-dominant")
set_tests_properties(unit-test-parallel-row-two-inequalities-redundant-row-first-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-inequalities-tighten-lower-bound-second-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-inequalities-tighten-lower-bound-second-row-dominant")
set_tests_properties(unit-test-parallel-row-two-inequalities-tighten-lower-bound-second-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-inequalities-tighten-lower-bound-first-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-inequalities-tighten-lower-bound-first-row-dominant")
set_tests_properties(unit-test-parallel-row-two-inequalities-tighten-lower-bound-first-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-inequalities-tighten-upper-bound-second-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-inequalities-tighten-upper-bound-second-row-dominant")
set_tests_properties(unit-test-parallel-row-two-inequalities-tighten-upper-bound-second-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-inequalities-tighten-upper-bound-first-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-inequalities-tighten-upper-bound-first-row-dominant")
set_tests_properties(unit-test-parallel-row-two-inequalities-tighten-upper-bound-first-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-inequalities-infeasible-first-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-inequalities-infeasible-first-row-dominant")
set_tests_properties(unit-test-parallel-row-two-inequalities-infeasible-first-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-inequalities-infeasible-second-row-dominant "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-inequalities-infeasible-second-row-dominant")
set_tests_properties(unit-test-parallel-row-two-inequalities-infeasible-second-row-dominant PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-two-inequalities-tighten-upper-bound-first-row-neg "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-two-inequalities-tighten-upper-bound-first-row-neg")
set_tests_properties(unit-test-parallel-row-two-inequalities-tighten-upper-bound-first-row-neg PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-overwrite-inf-first-row-rhs-inf "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-overwrite-inf-first-row-rhs-inf")
set_tests_properties(unit-test-parallel-row-overwrite-inf-first-row-rhs-inf PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-overwrite-inf-first-row-lhs-inf "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-overwrite-inf-first-row-lhs-inf")
set_tests_properties(unit-test-parallel-row-overwrite-inf-first-row-lhs-inf PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-overwrite-inf-first-row-lhs-inf-neg-factor "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-overwrite-inf-first-row-lhs-inf-neg-factor")
set_tests_properties(unit-test-parallel-row-overwrite-inf-first-row-lhs-inf-neg-factor PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-mixed-infeasible-first-row-equation "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-mixed-infeasible-first-row-equation")
set_tests_properties(unit-test-parallel-row-mixed-infeasible-first-row-equation PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-best-bound-is-used-for-rhs-coeff-not-1 "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-best-bound-is-used-for-rhs-coeff-not-1")
set_tests_properties(unit-test-parallel-row-best-bound-is-used-for-rhs-coeff-not-1 PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-best-bound-is-used-for-rhs-coeff "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-best-bound-is-used-for-rhs-coeff")
set_tests_properties(unit-test-parallel-row-best-bound-is-used-for-rhs-coeff PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-mixed-second-row-equation "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-mixed-second-row-equation")
set_tests_properties(unit-test-parallel-row-mixed-second-row-equation PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-mixed-infeasible-second-row-equation "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-mixed-infeasible-second-row-equation")
set_tests_properties(unit-test-parallel-row-mixed-infeasible-second-row-equation PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel-row-multiple-parallel-rows "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel-row-multiple-parallel-rows")
set_tests_properties(unit-test-parallel-row-multiple-parallel-rows PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_2_integer_columns "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_2_integer_columns")
set_tests_properties(unit-test-parallel_col_detection_2_integer_columns PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_2_continuous_columns "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_2_continuous_columns")
set_tests_properties(unit-test-parallel_col_detection_2_continuous_columns PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_int_cont_merge_possible "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_int_cont_merge_possible")
set_tests_properties(unit-test-parallel_col_detection_int_cont_merge_possible PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_cont_int_merge_possible "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_cont_int_merge_possible")
set_tests_properties(unit-test-parallel_col_detection_cont_int_merge_possible PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_cont_int_merge_failed "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_cont_int_merge_failed")
set_tests_properties(unit-test-parallel_col_detection_cont_int_merge_failed PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_int_cont_merge_failed "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_int_cont_merge_failed")
set_tests_properties(unit-test-parallel_col_detection_int_cont_merge_failed PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_int_merge_failed_hole "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_int_merge_failed_hole")
set_tests_properties(unit-test-parallel_col_detection_int_merge_failed_hole PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_obj_not_parallel "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_obj_not_parallel")
set_tests_properties(unit-test-parallel_col_detection_obj_not_parallel PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_multiple_parallel_columns "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_multiple_parallel_columns")
set_tests_properties(unit-test-parallel_col_detection_multiple_parallel_columns PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-parallel_col_detection_objective_zero "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "parallel_col_detection_objective_zero")
set_tests_properties(unit-test-parallel_col_detection_objective_zero PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-probing "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-probing")
set_tests_properties(unit-test-happy-path-probing PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-failed-path-probing-on-not-binary-variables "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "failed-path-probing-on-not-binary-variables")
set_tests_properties(unit-test-failed-path-probing-on-not-binary-variables PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-singleton-column "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-singleton-column")
set_tests_properties(unit-test-happy-path-singleton-column PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-singleton-column-equation "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-singleton-column-equation")
set_tests_properties(unit-test-happy-path-singleton-column-equation PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-singleton-column-implied-bounds-negative-coeff-pos-bounds "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-singleton-column-implied-bounds-negative-coeff-pos-bounds")
set_tests_properties(unit-test-happy-path-singleton-column-implied-bounds-negative-coeff-pos-bounds PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-singleton-column-implied-bounds-negative-coeff-neg-bounds "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-singleton-column-implied-bounds-negative-coeff-neg-bounds")
set_tests_properties(unit-test-happy-path-singleton-column-implied-bounds-negative-coeff-neg-bounds PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-singleton-column-implied-bounds-positive-coeff-pos-bounds "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-singleton-column-implied-bounds-positive-coeff-pos-bounds")
set_tests_properties(unit-test-happy-path-singleton-column-implied-bounds-positive-coeff-pos-bounds PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-singleton-column-implied-bounds-positive-coeff-neg-bounds "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-singleton-column-implied-bounds-positive-coeff-neg-bounds")
set_tests_properties(unit-test-happy-path-singleton-column-implied-bounds-positive-coeff-neg-bounds PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-singleton-stuffing-make-sure-to-first-set-bounds-to-infinity "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "singleton-stuffing-make-sure-to-first-set-bounds-to-infinity")
set_tests_properties(unit-test-singleton-stuffing-make-sure-to-first-set-bounds-to-infinity PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-simple-probing "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-simple-probing")
set_tests_properties(unit-test-happy-path-simple-probing PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-simple-probing-only-negative-coeff "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-simple-probing-only-negative-coeff")
set_tests_properties(unit-test-happy-path-simple-probing-only-negative-coeff PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-simple-probing-only-binary-negative-coefficient "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-simple-probing-only-binary-negative-coefficient")
set_tests_properties(unit-test-happy-path-simple-probing-only-binary-negative-coefficient PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-simple-probing-only-binary-positive-coefficient "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-simple-probing-only-binary-positive-coefficient")
set_tests_properties(unit-test-happy-path-simple-probing-only-binary-positive-coefficient PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-simple-substitution-for-2-int "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-simple-substitution-for-2-int")
set_tests_properties(unit-test-happy-path-simple-substitution-for-2-int PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-simple-substitution-for-2-continuous "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-simple-substitution-for-2-continuous")
set_tests_properties(unit-test-happy-path-simple-substitution-for-2-continuous PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-simple-substitution-for-continuous-and-integer "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-simple-substitution-for-continuous-and-integer")
set_tests_properties(unit-test-happy-path-simple-substitution-for-continuous-and-integer PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-simple-substitution-for-int-continuous-coeff "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-simple-substitution-for-int-continuous-coeff")
set_tests_properties(unit-test-happy-path-simple-substitution-for-int-continuous-coeff PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-should_return_infeasible_if_gcd_of_coeff_is_in_rhs "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "should_return_infeasible_if_gcd_of_coeff_is_in_rhs")
set_tests_properties(unit-test-should_return_infeasible_if_gcd_of_coeff_is_in_rhs PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-should_return_feasible_if_gcd_of_coeff_is_in_rhs "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "should_return_feasible_if_gcd_of_coeff_is_in_rhs")
set_tests_properties(unit-test-should_return_feasible_if_gcd_of_coeff_is_in_rhs PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-failed-path-simple-substitution-for-2-int "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "failed-path-simple-substitution-for-2-int")
set_tests_properties(unit-test-failed-path-simple-substitution-for-2-int PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-simplify-inequalities-only-greatest-divisor "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-simplify-inequalities-only-greatest-divisor")
set_tests_properties(unit-test-happy-path-simplify-inequalities-only-greatest-divisor PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-simplify_inequ_doesnt_lock_more_rows "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "simplify_inequ_doesnt_lock_more_rows")
set_tests_properties(unit-test-simplify_inequ_doesnt_lock_more_rows PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-simplify_inequ_doesnt_apply_lb_and_ub_on_one_row "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "simplify_inequ_doesnt_apply_lb_and_ub_on_one_row")
set_tests_properties(unit-test-simplify_inequ_doesnt_apply_lb_and_ub_on_one_row PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-sparsify "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-sparsify")
set_tests_properties(unit-test-happy-path-sparsify PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-happy-path-sparsify-two-equalities "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "happy-path-sparsify-two-equalities")
set_tests_properties(unit-test-happy-path-sparsify-two-equalities PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-failed-path-sparsify "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "failed-path-sparsify")
set_tests_properties(unit-test-failed-path-sparsify PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-integration-test-for-flugpl "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "integration-test-for-flugpl")
set_tests_properties(unit-test-integration-test-for-flugpl PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(unit-test-mps-parser-loading-simple-problem "/mnt/d/aMain/4-pre/pre/build/papilo/test/unit_test" "mps-parser-loading-simple-problem")
set_tests_properties(unit-test-mps-parser-loading-simple-problem PROPERTIES  DEPENDS "unit-test-build" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;209;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
add_test(papilo-build "/home/mzy/.local/lib/python3.8/site-packages/cmake/data/bin/cmake" "--build" "/mnt/d/aMain/4-pre/pre/build" "--target" "papilo-executable")
set_tests_properties(papilo-build PROPERTIES  RESOURCE_LOCK "papilobin" _BACKTRACE_TRIPLES "/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;288;add_test;/mnt/d/aMain/4-pre/pre/papilo/test/CMakeLists.txt;0;")
