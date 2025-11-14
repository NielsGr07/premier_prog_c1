#include <stdio.h>
#include <math.h>

int main() {
    int choix;
    double wind_angle, wind_speed, fuel, consumption, wing_surface;
    double pressure, temperature, altitude, ias, weight;

    // Menu
    printf("=== MENU DE CALCULS ===\n");
    printf("1. Altitude-pression\n");
    printf("2. Vitesse vraie (TAS)\n");
    printf("3. Vitesse-sol\n");
    printf("4. Distance franchissable\n");
    printf("5. Distance de décollage\n");
    printf("6. Charge alaire\n");
    printf("7. Taux de montée\n");
    printf("8. Point de non-retour\n");
    printf("9. Vitesse de descente\n");
    printf("Choix [1-9] : ");
    scanf("%d", &choix);

    // Saisie des données (valeurs minimales pour éviter les erreurs)
    printf("\n--- SAISIE DES DONNÉES ---\n");

    printf("Altitude [0-19500 ft] : ");
    scanf("%lf", &altitude);

    if (choix >= 2 && choix <= 4) {
        printf("IAS [0-500 kts] : ");
        scanf("%lf", &ias);
    }

    if (choix == 3 || choix == 4 || choix == 5) {
        printf("Angle du vent [-3.14 à 3.14 rad] : ");
        scanf("%lf", &wind_angle);
        printf("Vitesse du vent [0-150 kts] : ");
        scanf("%lf", &wind_speed);
    }

    if (choix == 4 || choix == 8) {
        printf("Carburant [20-350000 L] : ");
        scanf("%lf", &fuel);
    }

    if (choix == 4) {
        printf("Consommation [10-15000 L/h] : ");
        scanf("%lf", &consumption);
    }

    if (choix == 5 || choix == 6) {
        printf("Poids [500-600000 kg] : ");
        scanf("%lf", &weight);
    }

    if (choix == 6) {
        printf("Surface alaire [5-900 m²] : ");
        scanf("%lf", &wing_surface);
    }

    if (choix >= 1 && choix <= 7) {
        printf("Pression [300-1050 hPa] : ");
        scanf("%lf", &pressure);
    }

    if (choix >= 5 && choix <= 7) {
        printf("Température [-50 à 50 °C] : ");
        scanf("%lf", &temperature);
    }

    // Calculs
    double headwind = wind_speed * cos(wind_angle);
    double pressure_altitude = altitude + (1023 - pressure) * 30;
    double tas = ias * (1 + 2 * pressure_altitude / 1000);
    double ground_speed = tas - headwind;
    if (ground_speed <= 0) ground_speed = 1; // protection

    double range = (consumption > 0) ? fuel * ground_speed * 1.852 / consumption : 0;
    double takeoff = 0;
    if (ground_speed > 0 && weight > 0) {
        takeoff = 300 * (1 + pressure_altitude / 1000) *
                  (1 - 0.01 * fmax(0, temperature - 15)) *
                  (1 - headwind / ground_speed) *
                  pow(weight / 1157, 2);
    }
    double wing_loading = (wing_surface > 0) ? weight / wing_surface : 0;
    double rate_of_climb = 700 * (1 - pressure_altitude / 10000) *
                           (1 - 0.01 * fmax(0, temperature - 15));
    double no_return = range / 2;
    double descent_speed = ground_speed * tan(3.0 * 0.017453292519943295); // 3° * (π/180)


    // EFIS cockpit
    int pitch = 5, roll = -10, heading = 12;
    int speed_display = (int)(ias);
    int altitude_display = (int)(altitude);

    printf("\n+=============================== EFIS DASHBOARD ============================+\n");
    printf("| SPD(kts)                                                          ALT(ft) |\n");
    printf("| +--------+           +----------------------------------+        +------+ |\n");

    for (int i = 0; i < 7; i++) {
        int spd = speed_display + 50 * (3 - i);
        int alt = altitude_display + 1000 * (3 - i);

        if (i == 3) printf("|>|%3d.....|<", spd);
        else       printf("| | %3d    | ", spd);

        if (i == 0)      printf("           |              SKY                 |");
        else if (i == 1) printf("           | Pitch:%+3d°             Roll:%+3d° |", pitch, roll);
        else if (i == 2) printf("           |   +10°    ----|----    +10°      |");
        else if (i == 3) printf("           |------------HORIZON---------------|");
        else if (i == 4) printf("           |    -5°     ---|---     -5°       |");
        else if (i == 5) printf("           |   -10°    ----|----    -10°      |");
        else             printf("           |             GROUND               |");

        if (i == 3) printf("       >|%5d.....|<\n", alt);
        else       printf("        |%5d | \n", alt);
    }

    printf("| +--------+           +----------------------------------+        +------+ |\n");
    printf("|                             Heading: %03d° N                               |\n", heading);
    printf("+===========================================================================+\n");

    // Résultat
    printf("\n--- RÉSULTAT ---\n");
    switch (choix) {
        case 1: printf("Altitude-pression : %.2f ft\n", pressure_altitude); break;
        case 2: printf("Vitesse vraie (TAS) : %.2f kts\n", tas); break;
        case 3: printf("Vitesse-sol : %.2f kts\n", ground_speed); break;
        case 4: printf("Distance franchissable : %.2f km\n", range); break;
        case 5: printf("Distance de décollage : %.2f m\n", takeoff); break;
        case 6: printf("Charge alaire : %.2f kg/m²\n", wing_loading); break;
        case 7: printf("Taux de montée : %.2f ft/min\n", rate_of_climb); break;
        case 8: printf("Point de non-retour : %.2f km\n", no_return); break;
        case 9: printf("Vitesse de descente : %.2f kts\n", descent_speed); break;
        default: printf("Choix invalide.\n");
    }

    return 0;
}