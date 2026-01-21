#include "strings.c"

/*=============== Tastovací fce =================*/
int main() {
    printf("Demo použití knihovny strings\n");
    printf("=============================\n");
    printf("Ukázka String Builderu a Iteratoru\n\n");
    printf("Vytvoříme String Builder a zapíšeme do něj formátovaný text:\n");
    
    String_Builder sb;
    sb_init(&sb);

    sb_printf(&sb, str_wrap("#i #i #s\ndalsi radek"), 10, 3, "ahoj svete");
    String first = sb_clone_to_string(sb);

    sb_clear(&sb);
    sb_printf(&sb, str_wrap("predtim bylo #S"), first);
    
    String second = sb_clone_to_string(sb);

    sb_destroy(&sb);


    // 
    // předpokládejme, že funkce str_print vytiskne String
    // Potom následující
    //
    str_print(second);
    printf("\n");

    String foo = str_clone_from_cstring("resim-*-domaci-*-ulohu");
    String delimiter = str_clone_from_cstring("-*-");  // oddělovač

    String_Iterator si = si_create(foo, delimiter);
    String s;
    while( si_next(&si, &s) )
    {
        str_println(s);
    }
    return 0;
}