#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Funkce pro kontrolu ciselneho vstupu
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
            
            // Zkontrolujeme, zda je číslo kladné
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
    float hrubaMzda, zdravotniPojisteni, socialniPojisteni, dan, cisteMzda;

    while (1)
    {
        // Ziskani hodinove mzdy
        hodinovaMzda = nactiCislo("Zadejte hodinovou mzdu: ");

        // Ziskani odpracovanych hodin
        odpracovaneHodiny = nactiCislo("Zadejte pocet odpracovanych hodin: ");

        // Ziskani hodin u lekare
        hodinyLekar = nactiCislo("Kolik hodin jste byli u lekare: ");

        // Ziskani hodin na dovolene
        hodinyDovolena = nactiCislo("Kolik hodin jste byli na dovolene: ");

        // Vypocet hodinove mzdy snizene o 40%
        float snizenaMzda = hodinovaMzda * 0.6f;

        

        // Pridani bonusu
        bonusy = nactiCislo("Zadejte vysi bonusu: ");

        // Vypocet hrube mzdy
        hrubaMzda = (hodinovaMzda * odpracovaneHodiny) + (hodinyLekar * snizenaMzda) + (hodinyDovolena * snizenaMzda) + bonusy;

        // Naklady na obedy
        obedyPocet = nactiCislo("Kolikrat jste byli na obede: ");
        obedCena = nactiCislo("Kolik stoji jeden obed: ");
        int obedyNaklady = obedyPocet * obedCena;

        // Sleva na poplatnika
        char odpoved[4];
        while (1)
        {
            printf("Chcete uplatnit slevu na poplatnika? (ano/ne): ");
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
                printf("Neplatna odpoved. Zadejte ano nebo ne.\n");
            }
        }

        // Vypocty pojisteni a dane
        zdravotniPojisteni = hrubaMzda * 0.045f;
        socialniPojisteni = hrubaMzda * 0.071f; // Aktualizovano na 7.1%
        dan = hrubaMzda * 0.15f;                // Opraveno: daň 15 % z hrubé mzdy

        if (dan < slevaPoplatnik)
        {
            dan = 0;
        }
        else
        {
            dan -= slevaPoplatnik;
        }

        cisteMzda = hrubaMzda - zdravotniPojisteni - socialniPojisteni - dan - obedyNaklady + bonusy;

        // Vystup vysledku
        printf("\n=== Vysledky ===\n");
        printf("Hruba mzda: %.2f Kc\n", hrubaMzda);
        printf("Zdravotni pojisteni: %.2f Kc\n", zdravotniPojisteni);
        printf("Socialni pojisteni: %.2f Kc\n", socialniPojisteni);
        printf("Dan: %.2f Kc\n", dan);
        printf("Naklady na obedy: %d Kc\n", obedyNaklady);
        printf("Hodiny u lekare: %.2f Kc\n", hodinyLekar * snizenaMzda);
        printf("Hodiny na dovolene: %.2f Kc\n", hodinyDovolena * snizenaMzda);
        printf("Cista mzda: %.2f Kc\n", cisteMzda);

        // Potvrzeni vysledku
        while (1)
        {
            printf("Je vse v poradku? (ano/ne): ");
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
                printf("Neplatna odpoved. Zadejte ano nebo ne.\n");
            }
        }
    }

    return 0;
}
