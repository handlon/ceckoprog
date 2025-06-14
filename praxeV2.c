#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int nactiCislo(const char *vyzva)
{
    int cislo;
    char buffer[100];
    while (1)
    {
        printf("%s", vyzva);
        if (fgets(buffer, sizeof(buffer), stdin))
        {
            char *endptr;
            cislo = strtol(buffer, &endptr, 10);

            if (endptr != buffer && *endptr == '\n' && cislo >= 0)
            {
                return cislo;
            }
            else
            {
                printf("Neplatny vstup. Zadejte kladne cislo.\n");
            }
        }
        else
        {
            printf("Neplatny vstup. Zadejte kladne cislo.\n");
        }
    }
}

int main()
{
    int hodinovaMzda, odpracovaneHodiny, hodinyLekar, hodinyDovolena;
    int bonusy, obedyPocet, obedCena, slevaPoplatnik = 0;
    float hrubaMzda, zaklad, zdravotniPojisteni, socialniPojisteni, dan, cisteMzda;

    while (1)
    {
        while (1)
        {
            hodinovaMzda = nactiCislo("Zadejte hodinovou mzdu: ");
            if (hodinovaMzda > 100000)
            {
                printf("\n!!! je zadana moc velka hodinova mzda !!!\n");
                printf("zadejte prosim znovu\n\n");
                hodinovaMzda = 0;
            }
            else
            {
                break;
            }
        }
        while (1)
        {
            odpracovaneHodiny = nactiCislo("Zadejte pocet odpracovanych hodin: ");
            if (odpracovaneHodiny > 175)
            {
                printf("\n!!! byl presazen legalni limit odpracovanych hodin !!!\n");
                printf("zadejte prosim znovu\n\n");
                odpracovaneHodiny = 0;
               
            }
            else
            {
                break;
            }
        }

        hodinyLekar = nactiCislo("Kolik hodin jste byli u lekare: ");
        hodinyDovolena = nactiCislo("Kolik hodin jste byli na dovolene: ");

        float snizenaMzda = hodinovaMzda * 0.6f;
        bonusy = nactiCislo("Zadejte vysi bonusu: ");

        hrubaMzda = (hodinovaMzda * odpracovaneHodiny) + (hodinyLekar * snizenaMzda) + (hodinyDovolena * snizenaMzda) + bonusy;

        hrubaMzda = round(hrubaMzda);

        zaklad = ceil((hrubaMzda / 100)) * 100;

        /*printf("zaklad %f", zaklad);*/

        obedyPocet = nactiCislo("Kolikrat jste byli na obede: ");
        obedCena = nactiCislo("Kolik stoji jeden obed: ");
        int obedyNaklady = obedyPocet * obedCena;

        char odpoved[4];
        while (1)
        {
            printf("Chcete uplatnit slevu na poplatnika? (a/n): ");
            fgets(odpoved, sizeof(odpoved), stdin);
            if (odpoved[0] == 'a' || odpoved[0] == 'A')
            {
                slevaPoplatnik = 2570;
                break;
            }
            else if (odpoved[0] == 'n' || odpoved[0] == 'N')
            {
                slevaPoplatnik = 0;
                break;
            }
            else
            {
                printf("Neplatna odpoved. Zadejte 'a' nebo 'n'.\n");
            }
        }

        zdravotniPojisteni = ceil(hrubaMzda * 0.045f);
        socialniPojisteni = ceil(hrubaMzda * 0.071f);

        socialniPojisteni = (socialniPojisteni);
        if (socialniPojisteni>= 13222){
            socialniPojisteni = 13222;
        }
        zdravotniPojisteni = (zdravotniPojisteni);

        if (zaklad > 139671)
        {
            int cast1 = 139671;
            int cast2 = (int)zaklad - cast1;

            printf("cast 2 %d\n", cast2);

            dan = (cast1 * 0.15f) + (cast2 * 0.23f);
        }
        else
        {

            dan = zaklad * 0.15f;
        }

        if (dan < slevaPoplatnik)
        {
            dan = 0;
        }
        else
        {
            dan -= slevaPoplatnik;
        }

        dan = ceil(dan);

        cisteMzda = hrubaMzda - zdravotniPojisteni - socialniPojisteni - dan - obedyNaklady;

        printf("\n=== Vysledky ===\n");
        printf("Hruba mzda: %.2f Kc\n", hrubaMzda);
        printf("Zdravotni pojisteni: %.2f Kc\n", zdravotniPojisteni);
        printf("Socialni pojisteni: %.2f Kc\n", socialniPojisteni);
        printf("Dan: %.2f Kc\n", dan);
        printf("Naklady na obedy: %d Kc\n", obedyNaklady);
        printf("Hodiny u lekare: %.2f Kc\n", hodinyLekar * snizenaMzda);
        printf("Hodiny na dovolene: %.2f Kc\n", hodinyDovolena * snizenaMzda);
        printf("Cista mzda: %.2f Kc\n", cisteMzda);

        while (1)
        {
            printf("Je vse v poradku? (a/n): ");
            fgets(odpoved, sizeof(odpoved), stdin);
            if (odpoved[0] == 'a' || odpoved[0] == 'A')
            {
                printf("Program ukoncen.\n");
                return 0;
            }
            else if (odpoved[0] == 'n' || odpoved[0] == 'N')
            {
                printf("Program se restartuje.\n");
                break;
            }
            else
            {
                printf("Neplatna odpoved. Zadejte 'a' nebo 'n'.\n");
            }
        }
    }

    return 0;
}
