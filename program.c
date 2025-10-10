#include <stdio.h>

int main() {
    // Variables dynamiques
    int speed    = 200;     // en kts
    int altitude = 10000;   // en ft
    int pitch    = 5;       // degrés
    int roll     = -10;     // degrés
    int heading  = 12;      // degrésA
    printf("+=============================== EFIS DASHBOARD ============================+\n");
    printf("| SPD(kts)                                                          ALT(ft) |\n");
    printf("| +--------+           +----------------------------------+        +------+ |\n");
    printf("| | %3d    |           |              SKY                 |        |%5d | |\n", speed + 50, altitude + 1000);
    printf("|>| %3d    |<          | Pitch:%+3d°             Roll:%+3d° |       >|%5d |<|\n", speed, pitch, roll, altitude);
    printf("| | %3d    |           |   +10°    ----|----    +10°      |        |%5d | |\n", speed - 50, altitude - 1000);
    printf("| | %3d    |           |    +5°     ---|---     +5°       |        |%5d | |\n", speed - 100, altitude - 2000);
    printf("| | %3d    |           |------------HORIZON---------------|        |%5d | |\n", speed - 150, altitude - 3000);
    printf("| | %3d    |           |    -5°     ---|---     -5°       |        |%5d | |\n", speed - 200, altitude - 4000);
    printf("| | %3d    |           |   -10°    ----|----    -10°      |        |%5d | |\n", speed - 250, altitude - 5000);
    printf("| +--------+           |             GROUND               |        +------+ |\n");
    printf("|                      +----------------------------------+                 |\n");
    printf("|                                                                           |\n");
    printf("|                                                                           |\n");
    printf("|                             +-----------------+                           |\n");
    printf("|                             |   NW   N   NE   |                           |\n");
    printf("|                             |   W    ^    E   |                           |\n");
    printf("|                             |   SW   S   SE   |                           |\n");
    printf("|                             +-----------------+                           |\n");
    printf("|                             Heading: %03d° N                               |\n", heading);
    printf("+===========================================================================+\n");

    return 0;
}