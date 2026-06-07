# Smoke + e2e for experimental custom rules (define_rule, blade-build #829).
load('//suites/custom_rule/gen_rules.bld', 'gen_answer', 'concat')

# e2e: a custom rule generates a header that a cc_test consumes.
gen_answer(name = 'answer')

cc_test(
    name = 'custom_rule_test',
    srcs = ['answer_test.cc'],
    deps = [':answer'],
)

# smoke: a custom rule concatenates inputs into one output.
concat(
    name = 'combined',
    srcs = ['a.txt', 'b.txt'],
)
