#ifndef HOTEL
#define HOTEL

#define NAME_SIZE 32
#define ADDR_SIZE 64

typedef struct room
{
    char *name;
    char *addr;
    int age;
    int occupied;

} Room;

typedef struct hotel
{
    char *name;
    char *addr;
    int occupied_rooms;
    Room *rooms;
} Hotel;

#endif