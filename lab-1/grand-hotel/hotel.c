#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"

Hotel *init_hotel();
void init_room(Room *r);
void show_room(Hotel *h, int i);
void empty_room(Hotel *h, int i);
void assign_first(Hotel *h, Room *v);
void assign_room(Hotel *h, Room *v);
void copy_room(Room *dest, Room *src);
void free_room(Room *r);
Room get_room();

int main()
{
    Hotel *grandHotel = init_hotel();
    int choice, roomNumber;

    while (1)
    {
        printf("\n--- The Grand Hotel Management System ---\n");
        printf("1. Assign to a new visitor\n");
        printf("2. Assign Room 0 (shift all occupants)\n");
        printf("3. Empty a room (shift occupants to fill the gap)\n");
        printf("4. Display room info\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Room r = get_room();
            assign_room(grandHotel, &r);
            break;

        case 2:
            Room ro = get_room();
            assign_first(grandHotel, &ro);
            break;

        case 3:
            printf("Enter the room number to empty: ");
            scanf("%d", &roomNumber);
            empty_room(grandHotel, roomNumber);
            break;

        case 4:
            printf("Enter the room number (Zero Based): ");
            scanf("%d", &roomNumber);
            show_room(grandHotel, roomNumber);
            break;

        case 5:
            free(grandHotel->rooms);
            exit(0);

        default:
            printf("Invalid\n");
        }
    }

    return 0;
}

void show_room(Hotel *hotel, int index)
{
    if (index >= hotel->occupied_rooms)
        return;

    printf("\nName : %s", hotel->rooms[index].name);
    printf("\nAddr : %s", hotel->rooms[index].addr);
    printf("\nAge : %d", hotel->rooms[index].age);
    return;
}

void empty_room(Hotel *hotel, int index)
{
    if (index >= hotel->occupied_rooms)
        return;

    for (int i = index; i < hotel->occupied_rooms - 1; i++)
    {
        copy_room(&hotel->rooms[i], &hotel->rooms[i + 1]);
    }

    free_room(&hotel->rooms[hotel->occupied_rooms - 1]);
    hotel->occupied_rooms--;
    hotel->rooms = (Room *)realloc(hotel->rooms, sizeof(Room) * (hotel->occupied_rooms));
    return;
}

void assign_first(Hotel *hotel, Room *visitor)
{
    int len = ++hotel->occupied_rooms;
    hotel->rooms = (Room *)realloc(hotel->rooms, sizeof(Room) * len);
    init_room(&hotel->rooms[len - 1]);

    for (int i = len - 1; i > 0; i--)
    {
        copy_room(&hotel->rooms[i], &hotel->rooms[i - 1]);
    }
    copy_room(&hotel->rooms[0], visitor);
}

void assign_room(Hotel *hotel, Room *visitor)
{
    printf("1");
    int len = ++hotel->occupied_rooms;
    hotel->rooms = (Room *)realloc(hotel->rooms, sizeof(Room) * len);

    printf("1");
    init_room(&hotel->rooms[len - 1]);
    copy_room(&hotel->rooms[len - 1], visitor);

    printf("1");
}

Hotel *init_hotel()
{
    Hotel *hotel = (Hotel *)malloc(sizeof(Hotel));

    hotel->name = "Grand Hotel";
    hotel->addr = "NAB";
    hotel->occupied_rooms = 0;

    return hotel;
}

void init_room(Room *room)
{
    room->addr = (char *)calloc(ADDR_SIZE, sizeof(char));
    room->name = (char *)calloc(NAME_SIZE, sizeof(char));
    room->age = 0;
    room->occupied = 0;
}

void copy_room(Room *dest, Room *src)
{
    strcpy(dest->addr, src->addr);
    strcpy(dest->name, src->name);
    dest->age = src->age;
    dest->occupied = src->occupied;
}

Room get_room()
{
    Room *visitor = (Room *)malloc(sizeof(Room));
    init_room(visitor);

    printf("Enter the visitor's name: ");
    getchar();
    fgets(visitor->name, NAME_SIZE, stdin);

    printf("Enter the visitor's address: ");
    fgets(visitor->addr, ADDR_SIZE, stdin);

    printf("Enter the visitor's age: ");
    scanf("%d", &visitor->age);

    visitor->occupied = 1;

    return *visitor;
}

void free_room(Room *r)
{
    free(r->name);
    free(r->addr);
}