/*
*Program pro práci s řetězci v jazyce C
*
* Jaroslav Zikmund leden 2026
*/
/*
* systémovvé hlavičkové soubory
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/*
* vlastní hlavičkové soubory
*/
#include "strings.h"

/* ========= pomocné funkce========= */

/* funkce pro délku řetězce */
static int cstrlen(const char *s)
{
    int i = 0;  // počítá znaky
    while (s[i]) i++; // počítá znaky až do nulového znaku
    return i;  // vrací délku řetězce
}

/* funkce pro tisk řetězce */
void str_print(String s)
{
    for (int i = 0; i < s.len; i++)
        printf("%c", s.data[i]);
}

/* funkce pro tisk řetězce s novým řádkem */
void str_println(String s)
{
    str_print(s);
    printf("\n");
}

/* ========= String Builder pomocné funkce ========= */

/* funkce pro rezervaci paměti */
static void sb_reserve(String_Builder* sb, int needed)
{
    if (sb->cap >= needed) return;  // už je dostatek paměti

    int newcap = sb->cap ? sb->cap * 2 : 32;    // začínáme s kapacitou 32
    while (newcap < needed) newcap *= 2;    // zdvojnásobujeme kapacitu, dokud není dostatečná

    char *n = malloc(newcap); // alokujeme novou paměť
    if (sb->data)   // pokud už nějaká data existují, zkopírujeme je
        memcpy(n, sb->data, sb->len);   // kopírujeme stará data do nové paměti
    free(sb->data); // uvolníme starou paměť

    sb->data = n;   // nastavíme novou paměť
    sb->cap = newcap;   // aktualizujeme kapacitu
}

/* funkce pro přidání dat do String_Builderu */
static void sb_append(String_Builder* sb, const char *data, int len)
{
    sb_reserve(sb, sb->len + len + 1);  // rezervujeme dostatek paměti
    memcpy(sb->data + sb->len, data, len);  // kopírujeme nová data na konec
    sb->len += len; // aktualizujeme délku
    sb->data[sb->len] = 0;  // přidáme nulový znak na konec
}

/* ========= String ========= */

// funkce pro klonování C-řetězce do Stringu
String str_clone_from_cstring(char *cstring)
{
    String s;   
    s.len = cstrlen(cstring);   // získáme délku C-řetězce
    s.data = malloc(s.len + 1); // alokujeme paměť pro String
    memcpy(s.data, cstring, s.len + 1); // kopírujeme data včetně nulového znaku
    return s;   
}

// funkce pro klonování Stringu do C-řetězce
char* str_clone_to_cstring(String *s)
{
    char *c = malloc(s->len + 1);   // alokujeme paměť pro C-řetězec
    memcpy(c, s->data, s->len); // kopírujeme data
    c[s->len] = 0;  // přidáme nulový znak na konec
    return c;
}

// funkce pro klonování Stringu
String str_clone(String src)
{
    String s;
    s.len = src.len;    // nastavíme délku
    s.data = malloc(s.len + 1); // alokujeme paměť pro data
    memcpy(s.data, src.data, s.len);    // kopírujeme data
    s.data[s.len] = 0;  // přidáme nulový znak na konec
    return s;
}

// funkce pro spojení pole Stringů do jednoho Stringu s oddělovačem
String str_join(String array[], int n, String sep)
{
    // vypočítáme celkovou délku výsledného řetězce
    int len = 0;
    for (int i = 0; i < n; i++)
        len += array[i].len + (i ? sep.len : 0);

    // vytvoříme výsledný String
    String r;
    r.len = len;
    r.data = malloc(len + 1);

    // naplníme výsledný String
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
        if (i)  // přidáme oddělovač mezi řetězce
        {
            memcpy(r.data + pos, sep.data, sep.len);    // kopírujeme oddělovač
            pos += sep.len; // aktualizujeme pozici
        }
        memcpy(r.data + pos, array[i].data, array[i].len);  // kopírujeme řetězec
        pos += array[i].len;    // aktualizujeme pozici
    }
    r.data[len] = 0;    // přidáme nulový znak na konec
    return r;
}

// funkce pro uvolnění paměti Stringu
void str_destroy(String* src)
{
    assert(src -> data!= NULL); // kontrola platnosti ukazatele
    free(src->data);    // uvolníme paměť
    src->data = NULL;   // nastavíme ukazatel na NULL
    src->len = 0;   // nastavíme délku na 0
}

// funkce pro obalení C-řetězce do Stringu
String str_wrap(char* cstring)
{
    String s;
    s.data = cstring;   // nastavíme data na C-řetězec
    s.len = cstrlen(cstring);   // získáme délku C-řetězce
    return s;
}

// funkce pro oříznutí znaků z obou stran Stringu
String str_trim(String src, String cut)
{
    int b = 0, e = src.len; // počáteční a koncový index

    // oříznutí zleva
    while (b < e)
    {
        int ok = 0; // příznak, zda byl znak nalezen v cutsetu
        for (int i = 0; i < cut.len; i++)   
            if (src.data[b] == cut.data[i]) ok = 1; // znak je v cutsetu
        if (!ok) break;
        b++;
    }

    // oříznutí zprava
    while (e > b)
    {
        int ok = 0; // příznak, zda byl znak nalezen v cutsetu
        for (int i = 0; i < cut.len; i++)
            if (src.data[e-1] == cut.data[i]) ok = 1;   // znak je v cutsetu
        if (!ok) break;
        e--;
    }

    String r;
    r.data = src.data + b;  // nastavíme data na začátek oříznutého řetězce
    r.len = e - b;  // nastavíme délku oříznutého řetězce
    return r;
}

// funkce pro rozdělení Stringu podle oddělovače
String* str_split(String src, String sep, int *n)
{
    // spočítáme počet částí
    int count = 1;
    for (int i = 0; i + sep.len <= src.len; )
    {
        if (!memcmp(src.data + i, sep.data, sep.len))
        {
            count++;
            i += sep.len;
        }
        else i++;
    }

    // vytvoříme pole částí
    String *arr = malloc(sizeof(String) * count);
    *n = count;

    // naplníme pole částí
    int pos = 0, idx = 0;   // aktuální pozice a index části
    for (int i = 0; i <= src.len; )
    {
        // hledáme oddělovač nebo konec řetězce
        if (i == src.len ||
            (i + sep.len <= src.len &&
             !memcmp(src.data + i, sep.data, sep.len))) // našli jsme oddělovač nebo konec řetězce
        {
            arr[idx].data = src.data + pos; // nastavíme začátek části
            arr[idx].len = i - pos; // nastavíme délku části
            idx++;  // přejdeme na další část
            i += sep.len;   // přeskočíme oddělovač
            pos = i;    // aktualizujeme pozici začátku další části
        }
        else i++;
    }
    return arr; // vrátíme pole částí
}

/* ========= String Builder ========= */

// funkce pro inicializaci String_Builderu
void sb_init(String_Builder* sb)
{
    sb->data = NULL;    // inicializujeme data na NULL
    sb->len = 0;    // inicializujeme délku na 0
    sb->cap = 0;    // inicializujeme kapacitu na 0
}

// funkce pro vytvoření String_Builderu ze Stringu
String_Builder sb_from_string(String s)
{
    String_Builder sb;  // vytvoříme nový String_Builder
    sb_init(&sb);   // inicializujeme ho
    sb_append(&sb, s.data, s.len);  // přidáme data ze Stringu
    return sb;  // vrátíme String_Builder
}

// funkce pro vyčištění String_Builderu
void sb_clear(String_Builder* sb)
{
    // jednoduše nastavíme délku na 0
    sb->len = 0;
    if (sb->data)
        sb->data[0] = 0;
}

// funkce pro zničení String_Builderu, uvolnění paměti
void sb_destroy(String_Builder* sb)
{
    // uvolníme paměť a znovu inicializujeme String_Builder
    free(sb->data);
    sb_init(sb);
}

// funkce pro formátovaný zápis do String_Builderu
void sb_printf(String_Builder* sb, String fmt, ...)
{
    va_list ap;         // inicializace seznamu argumentů
    va_start(ap, fmt);  // začátek zpracování argumentů

    // procházení formátovacího řetězce
    for (int i = 0; i < fmt.len; i++)
    {
        // zpracování direktiv
        if (fmt.data[i] == '#' && i+1 < fmt.len)
        {
            i++;
            if (fmt.data[i] == 'i')
            {
                int v = va_arg(ap, int);
                char buf[32];
                int l = snprintf(buf, 32, "%d", v);
                sb_append(sb, buf, l);
            }
            else if (fmt.data[i] == 's')
            {
                char *c = va_arg(ap, char*);
                sb_append(sb, c, cstrlen(c));
            }
            else if (fmt.data[i] == 'S')
            {
                String s = va_arg(ap, String);
                sb_append(sb, s.data, s.len);
            }
            else if (fmt.data[i] == 'c')
            {
                char c = (char)va_arg(ap, int);
                sb_append(sb, &c, 1);
            }
        }
        // zpracování speciálních znaků
        else if (fmt.data[i] == '\\' && i+1 < fmt.len)
        {
            i++;
            char c = fmt.data[i] == 'n' ? '\n' :
                     fmt.data[i] == 't' ? '\t' :
                     fmt.data[i];
            sb_append(sb, &c, 1);
        }
        else
            // běžný znak
            sb_append(sb, &fmt.data[i], 1);
    }
    va_end(ap);
}

// funkce pro klonování String_Builderu do Stringu
String sb_clone_to_string(String_Builder sb)
{
    String s;
    s.len = sb.len;   // nastavíme délku
    s.data = malloc(sb.len + 1);    // alokujeme paměť pro data
    memcpy(s.data, sb.data, sb.len);    // kopírujeme data
    s.data[s.len] = 0;  // přidáme nulový znak na konec
    return s;   // vrátíme String
}

/* ========= Iterator ========= */

// funkce pro vytvoření String_Iteratoru
String_Iterator si_create(String src, String delimiter)
{
    String_Iterator it; // vytvoříme nový iterátor
    it.src = src;   // nastavíme zdrojový řetězec
    it.delim = delimiter;   // nastavíme oddělovač
    it.pos = 0;  // inicializujeme pozici na začátek
    return it;  // vrátíme iterátor
}

// funkce pro získání další části řetězce
int si_next(String_Iterator* it, String *slice)
{   
    // pokud jsme na konci řetězce, vrátíme 0
    if (it->pos > it->src.len) return 0;

    // hledáme další výskyt oddělovače
    int start = it->pos;
    for (int i = it->pos; i <= it->src.len; i++)
    {
        // našli jsme oddělovač nebo konec řetězce
        if (i == it->src.len ||
            (i + it->delim.len <= it->src.len &&
             !memcmp(it->src.data + i, it->delim.data, it->delim.len))) // našli jsme oddělovač nebo konec řetězce
        {
            slice->data = it->src.data + start; // nastavíme začátek části
            slice->len = i - start; // nastavíme délku části
            it->pos = i + it->delim.len;    // aktualizujeme pozici pro další volání
            return 1;   // vrátíme 1, že jsme našli další část
        }
    }
    return 0;   // neměli bychom se sem dostat
}

// funkce pro restartování iterátoru
void si_restart(String_Iterator* it)
{
    it->pos = 0;    // nastavíme pozici na začátek řetězce
}
