#include <iostream>
#include <vector>

enum BuildType{
    HOUSE = 1,
    GARAGE,
    BARN,
    BATH,
};

enum RoomType{
    BEDROOM = 1,
    KITCHEN,
    BATHROOM,
    NURSERY,
    LIVING_ROOM
};

struct Room {
    int square = 0;
    RoomType type = LIVING_ROOM;
};

struct Floor {
    int floorHeight = 0;
    std::vector<Room> room;
};

struct PieceOfVillage{
    std::string areaNumber;
    int amountBuildings = 0;

    struct House {
        int square = 0;
        bool pipe = false;
        std::vector<Floor> floor;
    } house;
    struct Garage {
        int square = 0;
    } garage;
    struct Bath {
        int square = 0;
        bool pipe = false;
    } bath;
    struct Barn {
        int square = 0;
    } barn;
};

void fillRoom (Room &room) {
    std::cout << "Input the square of the room:";
    std::cin >> room.square;

    int answer = 0;
    do {
        std::cout << "Choose the type of room:" << std::endl;
        std::cout << BEDROOM << ". Bedroom;" << std::endl;
        std::cout << KITCHEN << ". Kitchen;" << std::endl;
        std::cout << BATHROOM << ". Bathroom;" << std::endl;
        std::cout << NURSERY << ". Nursery;" << std::endl;
        std::cout << LIVING_ROOM << ". Living room." << std::endl;
        std::cin >> answer;

        if (answer > 0 && answer < 6) {
            if (answer == 1) room.type = BEDROOM;
            if (answer == 2) room.type = KITCHEN;
            if (answer == 3) room.type = BATHROOM;
            if (answer == 4) room.type = NURSERY;
            if (answer == 5) room.type = LIVING_ROOM;
        }
        else std::cout << "Incorrect input. Repeat." << std::endl;
    } while (answer < 1 || answer > 5);
}

void fillFloor (Floor &floor) {
    int amountRoom = 0;
    std::cout << "Input the floor height:";
    std::cin >> floor.floorHeight;

    std::cout << "Input the number of rooms:";
    std::cin >> amountRoom;
    floor.room.resize(amountRoom);

    for (int i=0;i < amountRoom;++i) {
        std::cout << "Set parameters for room #" << i+1 << std::endl;
        fillRoom(floor.room[i]);
    }
}

void fillHouse (PieceOfVillage &Village) {
    std::string answer;
    std::cout << "Input the square of the house:";
    std::cin >> Village.house.square;

    do {
        std::cout << "Is there a stove in the house?(yes/no)" << std::endl;
        std::cin >> answer;
        if (answer == "yes") Village.house.pipe = true;
        else if (answer == "no") Village.house.pipe = false;
        else std::cout << "Incorrect answer.Repeat" << std::endl;
    } while (answer != "yes" && answer != "no");

    int amountFloor = 0;
    std::cout << "Input the number of floors";
    std::cin >> amountFloor;
    Village.house.floor.resize(amountFloor);

    for (int i=0;i < amountFloor;++i) {
        std::cout << "Set parameters for floor #" << i+1 << std::endl;
        fillFloor(Village.house.floor[i]);
    }
}

void fillGarage (PieceOfVillage &Village) {
    std::cout << "Input the square of the garage:";
    std::cin >> Village.garage.square;
}

void fillBarn (PieceOfVillage &Village) {
    std::cout << "Input the square of the barn:";
    std::cin >> Village.barn.square;
}

void fillBath (PieceOfVillage &Village) {
    std::string answer;
    std::cout << "Input the square of the bath:";
    std::cin >> Village.bath.square;

    do {
        std::cout << "Is there a stove in the bath?(yes/no)" << std::endl;
        std::cin >> answer;
        if (answer == "yes") Village.bath.pipe = true;
        else if (answer == "no") Village.bath.pipe = false;
        else std::cout << "Incorrect answer.Repeat" << std::endl;
    } while (answer != "yes" && answer != "no");
}

void fillBuildings (PieceOfVillage &Village) {
    int answer;
    for (int i=1;i <= Village.amountBuildings;) {
        std::cout << "Choose the type of building #"<< i << ":" << std::endl;
        std::cout << HOUSE << ". House;" << std::endl;
        std::cout << GARAGE << ". Garage;" << std::endl;
        std::cout << BARN << ". Barn;" << std::endl;
        std::cout << BATH << ". Bath." << std::endl;
        std::cin >> answer;
        if (answer > 0 && answer < 5) {
            if (answer == 1) fillHouse(Village);
            if (answer == 2) fillGarage(Village);
            if (answer == 3) fillBarn(Village);
            if (answer == 4) fillBath(Village);
            ++i;
        }
        else std::cout << "Incorrect input. Repeat." << std::endl;
    }
}

int main() {

    int area;
    std::cout << "Input the number of areas in the village:";
    std::cin >> area;
    std::vector<PieceOfVillage> Village (area);


    for (int i=0;i < area;++i) {
        std::cout << "Input the unique number of area #" << i+1 << ":";
        std::cin >> Village[i].areaNumber;
        std::cout << "Input the number of buildings area #" << i+1 << ":";
        std::cin >> Village[i].amountBuildings;
        fillBuildings (Village[i]);
    }

    int totalSquare = 0;
    for (int i=0;i < area;++i) {
        totalSquare += Village[i].house.square + Village[i].bath.square + Village[i].barn.square + Village[i].garage.square;
    }
    std::cout << "Total area of buildings:" << totalSquare << std::endl;
    return 0;
}
