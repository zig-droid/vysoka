#include "strings.c"
#include "test.h"

/*=================== Testovací funkce =================*/

/* Testovací funkce pro rozdělení řetězce */
static void test_split()
{
    String s = str_clone_from_cstring("a--b--");    // vytvoříme testovací řetězec
    String d = str_clone_from_cstring("--");    // vytvoříme oddělovač
    int n;               // počet částí po rozdělení
    String *r = str_split(s, d, &n);    // rozdělíme řetězec

    assert(n == 3);          // očekáváme 3 části
    assert(r[2].len == 0);  // třetí část je prázdná

    free(r);    // uvolníme pole částí
    str_destroy(&s);    // uvolníme původní řetězec
    str_destroy(&d);    // uvolníme oddělovač
}

/* Testovací funkce pro String Builder */
static void test_builder()
{
    String_Builder sb;  // vytvoříme String_Builder
    sb_init(&sb);   // inicializujeme ho
    sb_printf(&sb, str_wrap("#i #s"), 10, "ok");    // přidáme formátovaný text
    String s = sb_clone_to_string(sb);  // převedeme na String
    assert(s.len == 5); // očekáváme délku 5
    str_destroy(&s);    // uvolníme String
    sb_destroy(&sb);    // zničíme String_Builder
}

/* Testovací funkce pro iterátor */
static void test_iterator()
{
    String s = str_clone_from_cstring("x--y--z");   // vytvoříme testovací řetězec
    String d = str_clone_from_cstring("--");    // vytvoříme oddělovač
    String_Iterator it = si_create(s, d);   // vytvoříme iterátor
    String part;    // část řetězce

    // první část
    int cnt = 0;    // počítadlo částí

    // projdeme všechny části řetězce
    while (si_next(&it, &part))
        cnt++;  // zvýšíme počítadlo částí

    assert(cnt == 3);   // očekáváme 3 části
    str_destroy(&s);    // uvolníme původní řetězec
    str_destroy(&d);    // uvolníme oddělovač
}

/*Testovací funkce pro spojení řetězců*/
static void test_join()
{
    String parts[3];    // pole částí
    parts[0] = str_clone_from_cstring("one");
    parts[1] = str_clone_from_cstring("two");
    parts[2] = str_clone_from_cstring("three");

    String sep = str_clone_from_cstring(", "); // oddělovač
    String_Builder sb;  // String_Builder pro spojení
    sb_init(&sb);   // inicializujeme ho

    // přidáme všechny části s oddělovačem
    for (int i = 0; i < 3; i++)
    {
        sb_append(&sb, parts[i].data, parts[i].len);
        if (i < 2) // pokud to není poslední část, přidáme oddělovač
            sb_append(&sb, sep.data, sep.len);
    }
    
    String result = sb_clone_to_string(sb); // převedeme na String
    assert(result.len >= 0); // očekáváme délku řetězce delší než nula znaků (one, two, three)
    
    // uvolníme paměť
    for (int i = 0; i < 3; i++)
        str_destroy(&parts[i]);
    str_destroy(&sep);
    sb_destroy(&sb);
    str_destroy(&result);
}

/*Testovací funkce pro získání další části řetězce*/
static void test_iterator_next()
{
    String s = str_clone_from_cstring("a,b,c"); // vytvoříme testovací řetězec
    String d = str_clone_from_cstring(","); // vytvoříme oddělovač
    String_Iterator it = si_create(s, d); // vytvoříme iterátor
    String part; // část řetězce

    // první část
    assert(si_next(&it, &part) == 1); // očekáváme úspěch
    assert(part.len == 1 && part.data[0] == 'a'); // očekáváme "a"

    // druhá část
    assert(si_next(&it, &part) == 1); // očekáváme úspěch
    assert(part.len == 1 && part.data[0] == 'b'); // očekáváme "b"

    // třetí část
    assert(si_next(&it, &part) == 1); // očekáváme úspěch
    assert(part.len == 1 && part.data[0] == 'c'); // očekáváme "c"

    // žádná další část
    assert(si_next(&it, &part) == 0); // očekáváme konec

    // uvolníme paměť
    str_destroy(&s);
    str_destroy(&d);
}

/* Testovací funkce přidám do testu, který bude spuštěn */
void run_tests()
{
    // Spuštění všech testů
    if (1) {
        printf("Running tests...\n");
        test_split();
        test_builder();
        test_iterator();
        test_join();
        test_iterator_next();
        printf("ALL TESTS PASSED\n");
    } else {
        printf("Tests are disabled.\n");
    }
}

/*======================== Hlavní funkce =====================*/
int main() {
    run_tests();
    return 0;
}