#include <stdio.h>
#include "strings.c"
#include "test.h"

/*
Globální počítaddla testů 
test_run - počet spuštěných testů
test_passed - počet úspěšně prošlých testů
test_failed - počet neúspěšných testů
*/

static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

/*================= Makra ====================*/
/*
 * Makro TEST_OK
 *  - použije se v případě, že test proběhl úspěšně
 *  - pouze zvýší počítadlo provedených testů
 */
#define TEST_OK() \
    do { tests_run++; } while (0)

/*
 * Makro TEST_FAIL
 *  - zaznamená selhání testu
 *  - zvýší počítadlo testů i selhání
 *  - vypíše chybové hlášení včetně souboru a řádku
 */
#define TEST_FAIL(msg) \
    do { \
        tests_run++; \
        tests_failed++; \
        printf("❌ TEST FAILED: %s\n   (%s:%d)\n", msg, __FILE__, __LINE__); \
    } while (0)

/*
 * Makro TEST_ASSERT
 *  - základní testovací podmínka
 *  - pokud je podmínka splněna → TEST_OK
 *  - pokud není splněna → TEST_FAIL s vlastním popisem chyby
 */
#define TEST_ASSERT(cond, msg) \
    do { \
        if (cond) TEST_OK(); \
        else TEST_FAIL(msg); \
    } while (0)

/*
 * Makro TEST_ASSERT_EQ_INT
 *  - porovnává dvě celočíselné hodnoty
 *  - vhodné např. pro délky řetězců nebo počty částí
 *  - při chybě vypíše očekávanou a skutečnou hodnotu
 */
#define TEST_ASSERT_EQ_INT(expected, got) \
    do { \
        char _msg[128]; \
        if ((expected) == (got)) TEST_OK(); \
        else { \
            sprintf(_msg, "expected %d, got %d", (expected), (got)); \
            TEST_FAIL(_msg); \
        } \
    } while (0)

/*================= Pomocná funkce ====================*/
/*
* Funkce check_split
* ------------------
 * Pomocná funkce pro testování funkce str_split.
 *
 * Parametry:
 *  - text            : vstupní řetězec, který se má rozdělit
 *  - sep             : oddělovač
 *  - expected_parts  : očekávaný počet částí po rozdělení
 *
 * Funkce:
 *  - vytvoří String objekty ze vstupních C-řetězců
 *  - zavolá str_split
 *  - ověří počet vrácených částí
 *  - uvolní veškerou alokovanou paměť
*/

void check_split(char* text, char* sep, int expected_parts)
{
    String s = str_clone_from_cstring(text);
    String delimiter = str_clone_from_cstring(sep);
    int n;
    String* parts = str_split(s, delimiter, &n);

    TEST_ASSERT_EQ_INT(expected_parts, n);

    // uvolnění paměti
    // for (int i = 0; i < n; i++)
    //     str_destroy(&parts[i]);
    free(parts);
    str_destroy(&s);
    str_destroy(&delimiter);
}

/*================= Hlavní testovací funkce ====================*/
/*
 * Test základního chování funkce str_split.
 * Ověřuje, že:
 *  - řetězec "a--b--" rozdělený podle "--"
 *    vytvoří tři části ("a", "b", "")
 */
static void test_split_basic()
{
    check_split("a--b--", "--", 3);
}

/*
 * Test okrajových případů funkce str_split.
 * Tyto testy ověřují chování při nestandardních vstupech,
 * které často způsobují chyby (off-by-one, prázdné řetězce).
 */
static void test_split_edge_cases()
{
    check_split("", ",", 1);          // prázdný vstupní řetězec
    check_split(",", ",", 2);         // pouze jeden oddělovač
    check_split(",,", ",", 3);        // více oddělovačů za sebou
    check_split("abc", ",", 1);       // žádný oddělovač
    check_split(",a", ",", 2);        // oddělovač na začátku
    check_split("a,", ",", 2);        // oddělovač na konci
    check_split("a", "-----", 1);     // oddělovač delší než text
}

/*
 * Test funkčnosti String_Iteratoru.
 * Ověřuje, že iterátor:
 *  - projde všechny části řetězce
 *  - vrátí správný počet částí
 */
static void test_iterator()
{
    String s = str_clone_from_cstring("x--y--z");
    String d = str_clone_from_cstring("--");

    String_Iterator it = si_create(s, d);
    String part;

    int cnt = 0;
    while (si_next(&it, &part))
        cnt++;

    TEST_ASSERT_EQ_INT(3, cnt);

    str_destroy(&s);
    str_destroy(&d);
}

/*
 * Test funkce si_next.
 * Ověřuje, že:
 *  - jednotlivé části jsou vráceny ve správném pořadí
 *  - po vyčerpání částí iterátor vrací 0
 */
static void test_iterator_next()
{
    String s = str_clone_from_cstring("a,b,c");
    String d = str_clone_from_cstring(",");

    String_Iterator it = si_create(s, d);
    String part;

    TEST_ASSERT(si_next(&it, &part), "expected first part");
    TEST_ASSERT(part.len == 1 && part.data[0] == 'a', "first part != 'a'");

    TEST_ASSERT(si_next(&it, &part), "expected second part");
    TEST_ASSERT(part.len == 1 && part.data[0] == 'b', "second part != 'b'");

    TEST_ASSERT(si_next(&it, &part), "expected third part");
    TEST_ASSERT(part.len == 1 && part.data[0] == 'c', "third part != 'c'");

    TEST_ASSERT(!si_next(&it, &part), "iterator should be finished");

    str_destroy(&s);
    str_destroy(&d);
}

/*
 * Test String_Builderu.
 * Ověřuje, že:
 *  - sb_printf správně přidá formátovaný text
 *  - výsledný String má očekávanou délku
 */
static void test_builder()
{
    String_Builder sb;
    sb_init(&sb);

    sb_printf(&sb, str_wrap("#i #s"), 10, "ok");
    String s = sb_clone_to_string(sb);

    TEST_ASSERT_EQ_INT(5, s.len);

    str_destroy(&s);
    sb_destroy(&sb);
}

/*
 * Test spojování více řetězců pomocí String_Builderu.
 * Simuluje chování funkce join.
 */
static void test_join()
{
    String parts[3];
    parts[0] = str_clone_from_cstring("one");
    parts[1] = str_clone_from_cstring("two");
    parts[2] = str_clone_from_cstring("three");

    String sep = str_clone_from_cstring(", ");

    String_Builder sb;
    sb_init(&sb);

    for (int i = 0; i < 3; i++) {
        sb_append(&sb, parts[i].data, parts[i].len);
        if (i < 2)
            sb_append(&sb, sep.data, sep.len);
    }

    String result = sb_clone_to_string(sb);

    TEST_ASSERT(result.len > 0, "join result is empty");

    for (int i = 0; i < 3; i++)
        str_destroy(&parts[i]);

    str_destroy(&sep);
    sb_destroy(&sb);
    str_destroy(&result);
}

/*=============== Hlavní funkce pro spuštění všech testů =====================*/
/*
 * Funkce run_tests
 *  - spustí všechny testovací funkce
 *  - vypíše souhrn výsledků
 */
void run_tests()
{
    printf("Running tests...\n\n");

    test_split_basic();
    test_split_edge_cases();
    test_builder();
    test_iterator();
    test_iterator_next();
    test_join();

    printf("\n====================\n");
    printf("Tests run:    %d\n", tests_run);
    printf("Tests failed: %d\n", tests_failed);

    if (tests_failed == 0)
        printf("✅ ALL TESTS PASSED\n");
    else
        printf("❌ SOME TESTS FAILED\n");
}

/*=============== Hlavní funkce main ===================*/
int main()
{
    run_tests();
    return 0;
}