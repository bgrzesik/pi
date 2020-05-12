//
// Created by Bartłomiej Grzesik on 08/04/2020.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum VEHICLE_TYPE
{
    VEHICLE_CAR,
    VEHICLE_BUS,
    VEHICLE_TRUCK,
};

enum VEHICLE_CAR_TYPE
{
    VEHICLE_CAR_FUEL,
    VEHICLE_CAR_ELECTRIC,
    VEHICLE_CAR_HYBRID,
};

struct vehicle
{
    enum VEHICLE_TYPE type;
    union
    {
        struct
        {
            int car_seats;
            enum VEHICLE_CAR_TYPE car_type;
        };
        struct
        {
            int bus_seats;
            int bus_standing;
        };
        struct
        {
            int truck_capacity;
            int truck_axis;
        };

    };
};

void print_vehicle(struct vehicle *vehicle)
{
    char *type = "";

    switch (vehicle->type) {
        case VEHICLE_BUS:printf("Autbus(siedzenia: %d, stojace: %d)\n", vehicle->bus_seats, vehicle->bus_standing);
            break;
        case VEHICLE_CAR:
            switch (vehicle->car_type) {
                case VEHICLE_CAR_ELECTRIC:type = "elektryczny";
                    break;
                case VEHICLE_CAR_HYBRID:type = "hybrydowy";
                    break;
                case VEHICLE_CAR_FUEL:type = "spalinowy";
                    break;
            }

            printf("Samochód(siedzenia: %d, napęd: %s)\n", vehicle->car_seats, type);
            break;
        case VEHICLE_TRUCK:
            printf("Pojazd ciężarowy(ladownosc: %d, liczba osi: %d)\n", vehicle->truck_capacity, vehicle->truck_axis);
            break;
    }
}

void read_vehicle(struct vehicle *vehicle)
{
    do {
        fprintf(stdout, "Podaj rozdaj pojazdu \n1\tpojazd osobowy,\n2\tautobus,\n3\tpojazd ciezarowy\n");
        fprintf(stdout, "Rodzaj: ");

        int choice;
        fscanf(stdin, "%d", &choice);

        switch (choice) {
            case 1:
                vehicle->type = VEHICLE_CAR;

                fprintf(stdout, "Podaj liczbe miejsc: ");
                fscanf(stdin, "%d", &choice);
                vehicle->car_seats = choice;

                fprintf(stdout, "Podaj rozdaj napędu \n1\telektryczny,\n2\thybrydowy,\n3\tspalinowy\n");
                fprintf(stdout, "Rodzaj: ");
                fscanf(stdin, "%d", &choice);

                switch (choice) {
                    case 1:
                        vehicle->car_type = VEHICLE_CAR_ELECTRIC;
                        break;
                    case 2:
                        vehicle->car_type = VEHICLE_CAR_HYBRID;
                        break;
                    case 3:
                        vehicle->car_type = VEHICLE_CAR_FUEL;
                        break;
                    default:
                        fprintf(stdout, "Nie poprawne dane\n");
                        continue;

                }
                break;

            case 2:
                vehicle->type = VEHICLE_BUS;

                fprintf(stdout, "Podaj liczbe miejsc siedzących: ");
                fscanf(stdin, "%d", &choice);
                vehicle->bus_standing = choice;

                fprintf(stdout, "Podaj liczbe miejsc stojących: ");
                fscanf(stdin, "%d", &choice);
                vehicle->bus_standing = choice;
                break;

            case 3:
                vehicle->type = VEHICLE_TRUCK;

                fprintf(stdout, "Podaj ladownosc: ");
                fscanf(stdin, "%d", &choice);
                vehicle->truck_capacity = choice;

                fprintf(stdout, "Podaj liczbe osi: ");
                fscanf(stdin, "%d", &choice);
                vehicle->truck_axis = choice;
                break;

            default:
                fprintf(stdout, "Nie poprawne dane\n");
                continue;
        }

        break;
    } while (1);

}

int main(int argc, const char *argv[])
{
    struct vehicle vehicle;
    read_vehicle(&vehicle);
    print_vehicle(&vehicle);

    return EXIT_SUCCESS;
}