/*Hlavičkový soubor pro práci se řetězci
*
**Jaroslav Zikmund leden 2026
*/

/*
* podmíněný překladový příkaz proti vícenásobnému zahrnutí
*/

#ifndef STRINGS_H
#define STRINGS_H

/* ========= pomocné funkce========= */
/* funkce pro délku řetězce */
static int cstrlen(const char *s);

/* funkce pro tisk řetězce */
void str_print(String s);

/* funkce pro tisk řetězce s novým řádkem */
void str_println(String s);

/* ================= String ================= */

typedef struct
{
    char *data;
    int   len;
} String;

/*Následující čtyři funkce manuálně ALOKUJÍ paměť pro datové položky řetězců,
 vytváří tak nové kopie.*/
/*transformace C řetězce na String a zpět*/
String str_clone_from_cstring(char *cstring);
char* str_clone_to_cstring(String *s);

/*vytvoření klonu řetězce*/
String str_clone(String src);

/*pojí řetězce obsažené v poli array (s n prvky) do jednoho, 
 přitom je od sebe oddělí pomocí řetězce sep;*/
String str_join(String array[], int n, String sep);

/*Funkce uvolní vnitřní paměť řetězce a nastaví jej tak,
 aby vypadal jako prázdný řetězec.*/
void str_destroy(String* src);

/*Následující tři funkce NEALOKUJÍ paměť pro `data` řetězce, ale jejich položka `data`
ukazuje do této položky jiného řetězce (nebo na C řetězec).
* POZOR:
 * Některé funkce (str_wrap, str_split, si_next, str_trim)
 * vracejí String, který NEVLASTNÍ paměť.
 * Na takový String se NESMÍ volat str_destroy().
*/

/*Vytvoří String z C řetězce*/
String str_wrap(char* cstring);

/*Rozdělí `src` na části oddělené oddělovačem `sep`, a vrátí je jako pole.
 Jejich počet zapíše do n. */
String* str_split(String src, String sep, int *n);

/*Zepředu a zezadu src odstraní všechny znaky obsažené v cutset
 a výsledný řetězec vrátí jako výsledek.*/
String str_trim(String src, String cutset);

/* ================= String Builder ================= */

typedef struct
{
    char *data;
    int   len;
    int   cap;
} String_Builder;

/*Inicializuje sb. Nealokuje žádnou paměť pro uchovávání obsahu.
Po inicialize SB vypadá, jakoby obsahoval prázdný řetězec.
(Po převodu na String, viz níže, je výsledek prázdný řetězec.)*/
void sb_init(String_Builder* sb);

/*Vytvoří SB jako kopii existujícího řetězce*/
String_Builder sb_from_string(String s);

/*Neuvolňuje žádnou paměť SB, pouze nastaví jeho položky tak, aby obsah
 SB odpovídal prázdnému řetězci.*/
void sb_clear(String_Builder* sb);

/*Uvolní paměť, kterou sb používá pro uchování řetězce.*/
void sb_destroy(String_Builder* sb);

/*Funkce analogická printf ze stdio.h, která tiskne do SB.
  Ve formátovacím řetězci podporuje následující direktivy a typy
  - #i     typ int,
  - #S     řetězec typu String,
  - #s     řetězec typu char*, 
  - #c     znak typu char,
  Dále podporuje speciální znaky '\t', '\n', '\"' jako printf.*/
void sb_printf(String_Builder* sb, String format, ...);

/*Transformuje SB na String, jehož data jsou nově alokována (tj. SB lze pořád používat).*/
String sb_clone_to_string(String_Builder sb);

/* ========= String Builder pomocné funkce ========= */

/*Rezervuje v SB dostatek paměti pro uložení alespoň newcap znaků.
 Pokud je kapacita SB již dostatečná, nedělá nic.*/
static void sb_reserve(String_Builder* sb, int newcap);

/*Přidá do SB data o délce len.*/
static void sb_append(String_Builder* sb, const char *data, int len);


/* ================= Iterator ================= */

typedef struct
{
    String src;
    String delim;
    int    pos;
} String_Iterator;

/*inicializuje iterátor pro řetězec src a oddělovač delimiter.*/
String_Iterator si_create(String src, String delimiter);

/*Vrátí 1 a nastaví slice na další část řetězce. 
Pokud už byly projity všechny části řetězce, vrátí 0.
* POZOR:
 * Některé funkce (str_wrap, str_split, si_next, str_trim)
 * vracejí String, který NEVLASTNÍ paměť.
 * Na takový String se NESMÍ volat str_destroy().
*/
int  si_next(String_Iterator* it, String *slice);

/*Restartuje iterátor na začátek řetězce.*/
void si_restart(String_Iterator* it);

#endif // STRINGS_H