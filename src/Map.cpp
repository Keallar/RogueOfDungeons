#include "Map.h"
#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include <ctime>
#include "UiMain.h"
#include <vector>
#include <iostream>

Map::Map()
{
    TileSet = 0;
    floorLvl = 1;
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            textureLocation[i][j] = 1;
            Location[i][j] = 1;
            Dark[i][j] = 0;
        }
    }
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (i == 0 || i == 21 || j == 0 || j == 31)
            {
                Dark[i][j] = 1;
            }
        }
    }
}

Map::~Map() {

}
void Map::GenerateMap()
{
    floorLvl++;
    srand(time(0));
    if(floorLvl <= 4) {
        TileSet = 0;
        switch(rand()%3) {
        case 0: generateChoose = 0;
            break;
        case 1: generateChoose = 3;
            break;
        case 2: generateChoose = 2;
            break;
        }
    }
    if(floorLvl > 4 && floorLvl <= 8) {
        TileSet = 1;
        switch(rand()%3) {case 0: generateChoose = 0; case 1: generateChoose = 4; break; case 2: generateChoose = 2; break;}
    }
    if(floorLvl > 8 && floorLvl <= 12) {
        TileSet = 2;
        switch(rand()%2) {case 0: generateChoose = 1; break; case 1: generateChoose = 5; break;}
    }
    if(floorLvl > 12 && floorLvl <=16) {
        TileSet = 3;
        switch(rand()%2) {case 0: generateChoose = 1; break; case 1: generateChoose = 5; break;}
    }
    if (floorLvl > 16 && floorLvl <= 20) {
        TileSet = 4;
        switch(rand()%3) {case 0: generateChoose = 1; break; case 1: generateChoose = 5; break; case 2: generateChoose = 7; break;}
    }
    if (floorLvl == 21) {
        TileSet = 4;
        generateChoose = 6;
    }

    switch(generateChoose) {
        case 0: {ChunkGenerationMethod(); break;}
        case 1: {RoomGenerationMethod2(); break;}
        case 2: {ChunkGenerationMethod2(); break;}
        case 3: {BigLabGenerationMethod(); break;}
        case 4: {CaveLabGeneration(); break;}
        case 5: {CastleLabGeneration(); break;}
        case 6: {BossGenerationNethod(); break;}
        case 7: {RingGenerationmethod(); break;}
    }

    for (int i = 0; i < 3; i++) {
        itemsOnLvl[i] = rand() % 4 + 1;
    }
    itemsHave = 2;
}

void Map::CreateChunk(int x, int y) {
    for (int i = x; i < x + 2; i++) {
        for (int j = y; j < y + 4; j++) {
            if ((j <= 31) || (i <= 21) || (j > 0) || (i > 0)) {
                textureLocation[i][j] = 0;
            }
        }
    }
}

void Map::CreateChunk2(int x, int y) {
    for (int i = x; i < x + 2; i++) {
        for (int j = y; j < y + 4; j++) {
            if ((j <= 31) || (i <= 21) || (j > 0) || (i > 0)) {
                textureLocation[i][j] = 1;
            }
        }
    }
}

void Map::WallsAroundLevel() {
    for (int j = 0; j < 32; j++) {
        for (int i = 0; i < 22; i++) {
            //стены вокруг уровня
            if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
                textureLocation[i][j] = 2;
            }
        }
    }
}

int Map::CountingNeighbours(int x, int y, int NeighbourNumber) {
    int count = 0;
    if (this->textureLocation[x][y + 1] == NeighbourNumber) {
        count++;
    }
    if (textureLocation[x + 1][y + 1] == NeighbourNumber) {
        count++;
    }
    if (textureLocation[x + 1][y] == NeighbourNumber) {
        count++;
    }
    if (textureLocation[x + 1][y - 1] == NeighbourNumber) {
        count++;
    }
    if (textureLocation[x][y - 1] == NeighbourNumber) {
        count++;
    }
    if (textureLocation[x - 1][y - 1] == NeighbourNumber) {
        count++;
    }
    if (textureLocation[x - 1][y] == NeighbourNumber) {
        count++;
    }
    if (textureLocation[x - 1][y + 1] == NeighbourNumber) {
        count++;
    }
    return count;
}

void Map::PuttingPortal() {
    portal.x = rand()%20+1;
    portal.y = rand()%30+1;
    while (textureLocation[portal.x][portal.y] != 0) {
        portal.x = rand()%20+1;
        portal.y = rand()%30+1;
    }
    Location[portal.x][portal.y] = 5;
}

void Map::SetWalls1() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 32; j++) {
            if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 4) || (textureLocation[i][j] == 6)) {
                Location[i][j] = 0;
            }
            if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 3) || (textureLocation[i][j] == 5)) {
                Location[i][j] = 1;
            }
            if (textureLocation[i][j] == 2) {
                Location[i][j] = 2;
            }
        }
    }
}

void Map::SetWalls2() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 32; j++) {
            if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 6) || (textureLocation[i][j] == 3) || (textureLocation[i][j] == 4) || (textureLocation[i][j] == 7) || (textureLocation[i][j] == 8)) {
                Location[i][j] = 0;
            }
            if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 5)) {
                Location[i][j] = 1;
            }
            if (textureLocation[i][j] == 2) {
                Location[i][j] = 2;
            }
        }
    }
}

void Map::SetWallsForTileSet() {
    switch(TileSet) {
    case 0:
        SetWalls1();
        break;
    case 1:
        SetWalls1();
        break;
    case 2:
        SetWalls2();
        break;
    case 3:
        SetWalls2();
        break;
    case 4:
        SetWalls2();
        break;
    }
}

//при данном методе генерации карт делится на 8*11 чанков

void Map::ChunkGenerationMethod() {
    for (int j = 0; j < 8; j++) { //делим карту на 8 столбцов по 11 чанков, обрабатываем каждый отдельно
        int i = rand() % 4 + rand() % 3; int count = 0;
        //задумка такая: в каждом столбце создаем какое-то количество пустых чанков (в которых можно хоидть)
        //начиная от какого-то чанка. После того, как мы совместим столбцы, мы получим, так сказать, угловатую пещеру
        //например, в 1 столбце пустые от 4 по 7 чанки, а во 2 стобце от 5 по 9 чанки, представьте в голове
        while (count < (5 + rand() % 3)) { //выбираем кол-во пустых чанков в столбце
            if (i + count < 11) {
                CreateChunk((i + count) * 2, j * 4);
            }
            count++;
        }
    }
    //цикл для сглаживания, превращает угловатую пещеру в нормальную
   //для каждой клетки считаем пустые клетки- соседи. Если их больше 3, делаем клетку пустой
    for (int j = 1; j < 31; j++) {
        for (int i = 1; i < 21; i++) {
            int iteration = 0;
            while (iteration < 50) {
                if (CountingNeighbours(i, j, 0) > 3) {
                    textureLocation[i][j] = 0;
                }
                iteration++;
            }
        }
    }

    //далее рандомно выбираем клетки и меняем им тектурку, чтобы уровень был разнообразнее

    for (int j = 1; j < 31; j++) {
        for (int i = 1; i < 21; i++) {
            if ((!(rand() % 16))) {
                if (CountingNeighbours(i, j, 3) == 0) {
                   textureLocation[i][j] = 3;
                }
            }
            if (textureLocation[i][j] == 1) {
                if (rand() % 2) {
                    textureLocation[i][j] = 5;
                }
            }
            if (textureLocation[i][j] == 0) {
                switch (rand() % 3) {
                case 0:
                    break;
                case 1:
                    textureLocation[i][j] = 4;
                    break;
                case 2:
                    textureLocation[i][j] = 6;
                    break;
                }
            }
        }
    }
    //стены вокруг уровня
    WallsAroundLevel();

    //ставим портал

    PuttingPortal();

    //заполяем массив, которых хранит инфу, где стены, а где можно ходить

    SetWallsForTileSet();

    //ставим сундуки

    for (int i = 0; i < 3; i++) {
        chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
        while (Location[chests[i][0]][chests[i][1]] != 0 || Location[chests[i][0] + 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] + 1] != 0 || Location[chests[i][0] - 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] - 1] != 0 || Location[chests[i][0] - 1][chests[i][1] - 1] != 0 || Location[chests[i][0] - 1][chests[i][1] + 1] != 0 || Location[chests[i][0] + 1][chests[i][1] - 1] != 0 || Location[chests[i][0] + 1][chests[i][1] + 1] != 0) {
            chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
        }
        textureLocation[chests[i][0]][chests[i][1]] = 14;
        Location[chests[i][0]][chests[i][1]] = 3;
    }
}

void Map::LabGeneration() {

    WallsAroundLevel();

    for (int i = 1; i < 19; i++) {
        for (int j = 1; j < 29; j++) {
            if ((i % 2 == 1) && (j % 2 == 1)) {
                textureLocation[i][j] = 0;
                int Way = rand() % 2;
                bool Choosed = false;
                while (Choosed == false) {
                    Choosed = true;
                    switch (Way) {
                    case 0:
                        if (textureLocation[i][j + 1] != 1) {
                            Way = rand() % 4;
                            Choosed = false;
                        }
                        else {
                            textureLocation[i][j + 1] = 0;
                        }
                        break;
                    case 1:
                        if (textureLocation[i+1][j] != 1) {
                            Way = rand() % 4;
                            Choosed = false;
                        }
                        else {
                            textureLocation[i + 1][j] = 0;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1; i < 20; i++) {
        textureLocation[i][29] = 0;
    }
    for (int i = 1; i < 30; i++) {
        textureLocation[19][i] = 0;
    }

    //ставим сундуки

    for(int k = 0; k < 3; k++) {
        int counter = 0;
        bool finder = false;
        while(!finder) {
            for(int i = rand()%19 + 1; i < 21; i++) {
                for(int j = rand()%29+1; j < 31; j++) {
                    if (textureLocation[i][j] == 0) {
                        counter = 0;
                        if (textureLocation[i][j + 1] == 0 || textureLocation[i][j + 1] == 14) {
                            counter++;
                        }
                        if (textureLocation[i][j - 1] == 0 || textureLocation[i][j - 1] == 14) {
                            counter++;
                        }
                        if (textureLocation[i - 1][j] == 0 || textureLocation[i - 1][j] == 14) {
                            counter++;
                        }
                        if (textureLocation[i + 1][j] == 0 || textureLocation[i + 1][j] == 14) {
                            counter++;
                        }
                        if (counter == 1) {
                            textureLocation[i][j] = 14;
                            Location[i][j] = 3;
                            finder = true;
                            break;
                        }
                    }
                }
                if(finder) break;
            }
        }
    }

    //ставим портал

    PuttingPortal();
}

void Map::CaveLabGeneration() {

    LabGeneration();

    for (int j = 0; j < 32; j++) {
        for (int i = 0; i < 22; i++) {
            if (textureLocation[i][j] == 1) {
                if (rand() % 2) {
                    textureLocation[i][j] = 5;
                }
            }
            if (textureLocation[i][j] == 0) {
                switch (rand() % 3) {
                case 0:
                    break;
                case 1:
                    textureLocation[i][j] = 4;
                    break;
                case 2:
                    textureLocation[i][j] = 6;
                    break;
                }
            }
            //стены вокруг уровня
            if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
                textureLocation[i][j] = 2;
            }
        }
    }

    //заполяем массив, которых хранит инфу, где стены, а где можно ходить

    SetWallsForTileSet();
}

void Map::CastleLabGeneration() {

    LabGeneration();

    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 32; j++) {
            if ((textureLocation[i][j] == 1) && (!(rand() % 11))) {
                textureLocation[i][j] = 5;
            }
            if ((textureLocation[i][j] == 0) && (!(rand() % 16))) {
                if (rand() % 2) {
                    textureLocation[i][j] = 3;
                }
                else {
                    textureLocation[i][j] = 4;
                }
            }
            if ((textureLocation[i][j] == 0) && (!(rand() % 4))) {
                if (rand() % 2) {
                    textureLocation[i][j] = 7;
                }
                else {
                    textureLocation[i][j] = 8;
                }
            }
            if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
                textureLocation[i][j] = 2;
            }
        }
    }

    //заполяем массив, которых хранит инфу, где стены, а где можно ходить

    SetWallsForTileSet();
}

//метод для генерации комнат, 2 вариант генерации

//сначала делим карту на 8 чанков, 4 столбца по 2 чанка
//в первом столбце выбираем, какой из чанков будет стартовым
//в строке, в которой есть стартовый чанк, выбираем чанк номер 2 или 3, на котором произойдет поворот дороги
//в последнем столбце выбираем конечный чанк
//главная дорога идет от стартового чанка вправо, поворачивает наверх или вниз на чанке поворота
//(то есть меняет строку), далее дальше вправо до последнего столбца
//в каждом столбце есть дорога, которая соединяет чанки
//чанков 8, но комнат не 8, один из циклов выбирает чанки, в которых не будет комнаты
void Map::RoomGenerationMethod2() {
    int RoomSectors[2][4] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    //выбираем старт чанк
    switch (rand() % 2) {
    case 0:
        RoomSectors[0][0] = 1;
        break;
    case 1:
        RoomSectors[1][0] = 1;
        break;
    }
    //выбираем конечный чанк
    //p.s. в стартовом и конечном чанке всегда есть комната
    switch (rand() % 2) {
    case 0:
        RoomSectors[0][3] = 2;
        break;
    case 1:
        RoomSectors[1][3] = 2;
        break;
    }
    //выбираем чанк поворота. p.s. в нем тоже всегда есть комната
    switch (rand() % 2) {
    case 0:
        if (RoomSectors[0][0] == 1) {
            RoomSectors[0][1] = 3;
            break;
        }
        else {
            RoomSectors[1][1] = 3;
            break;
        }
    case 1:
        if (RoomSectors[0][0] == 1) {
            RoomSectors[0][2] = 3;
            break;
        }
        else {
            RoomSectors[1][2] = 3;
            break;
        }
    }
    //выбираем чанки, в которых не будет комнаты
    int count = 0;
    while (count < 1) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                if ((!(rand() % 4)) && (RoomSectors[i][j] == 0)) {
                    RoomSectors[i][j] = -1;
                    count++;
                    break;
                }
            }
        }
    }
    //...
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << RoomSectors[i][j] << " ";
        }
    }
    //рисуем дороги, судя по инфе про чанки
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (RoomSectors[i][j] == 1) {
                for (int k = 0; k < 8; k++) {
                    textureLocation[11 * i + 5][8 * j + 4 + k] = 0;
                }
            }
            if ((RoomSectors[i][j] == 0) || (RoomSectors[i][j] == -1)) {
                if ((j == 2) && ((RoomSectors[1 - i][1] == 3) || (RoomSectors[1 - i][2] == 3))) {
                    for (int k = 0; k < 8; k++) {
                        textureLocation[11 * i + 5][8 * j + 4 + k] = 0;
                    }
                }
                if ((j == 1) && ((RoomSectors[i][0] == 1) || (RoomSectors[1 - i][j] == 3))) {
                    for (int k = 0; k < 8; k++) {
                        textureLocation[11 * i + 5][8 * j + 4 + k] = 0;
                    }
                }
            }
        }
    }
    //строим дороги между чанками в столюцах
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 11; k++) {
            textureLocation[5 + k][8 * i + 4] = 0;
        }
    }
    //рисуем комнаты
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            int start = rand() % 2;
            int end = rand() % 2;
            if (RoomSectors[i][j] != -1) {
                for (int k = 0; k < 6; k++) {
                    for (int m = 0 + start; m < 7 + end; m++) {
                        textureLocation[11 * i + 1 + m][8 * j + 1 + k] = 0;
                    }
                }
            }
        }
    }
    //меняем текстурку центральных клеток комнат(мелочь, но приятно)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            textureLocation[11 * i + 5][8 * j + 4] = 6;
        }
    }
    //рисуем границы мапы
    WallsAroundLevel();
    //добавляем разнообразие в текстурки
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 32; j++) {
            if ((textureLocation[i][j] == 1) && (!(rand() % 11))) {
                textureLocation[i][j] = 5;
            }
            if ((textureLocation[i][j] == 0) && (!(rand() % 16))) {
                if (rand() % 2) {
                    textureLocation[i][j] = 3;
                }
                else {
                    textureLocation[i][j] = 4;
                }
            }
            if ((textureLocation[i][j] == 0) && (!(rand() % 4))) {
                if (rand() % 2) {
                    textureLocation[i][j] = 7;
                }
                else {
                    textureLocation[i][j] = 8;
                }
            }
        }
    }

    //ставим портал

    PuttingPortal();

    //загружаем инфу о том, где стены, а где можно ходить, в массив

    SetWallsForTileSet();

    //ставим сундуки
    for (int i = 0; i < 3; i++) {
        chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
        while (Location[chests[i][0]][chests[i][1]] != 0 || Location[chests[i][0]+1][chests[i][1]] != 0|| Location[chests[i][0]][chests[i][1]+1] != 0 || Location[chests[i][0]-1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1]-1] != 0 || Location[chests[i][0]- 1][chests[i][1] -1 ] != 0 || Location[chests[i][0]-1][chests[i][1]+1] != 0 || Location[chests[i][0]+1][chests[i][1]-1] != 0 || Location[chests[i][0]+1][chests[i][1]+1] != 0) {
            chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
        }
        textureLocation[chests[i][0]][chests[i][1]] = 14;
        Location[chests[i][0]][chests[i][1]] = 3;
    }

}

void Map::ChunkGenerationMethod2() {
    for (int i = 1; i < 21; i++) {
        for (int j = 1; j < 31; j++) {
            textureLocation[i][j] = 0;
        }
    }
    for (int j = 0; j < 8; j++) { //делим карту на 8 столбцов по 11 чанков, обрабатываем каждый отдельно
        int i = rand() % 4 + rand() % 3; int count = 0;
        //не буду дальше редачить комменты, этот генератор как первый, но он наоборот делает чанки стен, а не пола
        while (count < (5 + rand() % 3)) { //выбираем кол-во пустых чанков в столбце
            if (i + count < 11) {
                CreateChunk2((i + count) * 2, j * 4);
            }
            count++;
        }
    }
    //цикл для сглаживания, превращает угловатую пещеру в нормальную
   //для каждой клетки считаем пустые клетки- соседи. Если их больше 3, делаем клетку пустой
    for (int j = 0; j < 32; j++) {
        for (int i = 0; i < 22; i++) {
            int iteration = 0;
            while (iteration < 50) {
                int count = CountingNeighbours(i, j, 0);
                if (count > 3) {
                    if ((rand() % 3) == 0) {
                        textureLocation[i][j] = 0;
                    }
                }
                if (count > 1) {
                    if ((rand() % 200) == 0) {
                        textureLocation[i][j] = 0;
                    }
                }
                iteration++;
            }
        }
    }
    for (int j = 1; j < 31; j++) {
        textureLocation[1][j] = 0;
        textureLocation[2][j] = 0;
        textureLocation[19][j] = 0;
        textureLocation[20][j] = 0;
    }
    int startTunnel = 0; int rotation = 0;
    switch (rand() % 3) {
    case 0:
        startTunnel = rand() % 10;
        rotation = 1;
        break;
    case 1:
        startTunnel = rand() % 10;
        rotation = 0;
        break;
    case 2:
        startTunnel = rand() % 11 + 10;
        rotation = -1;
        break;
    default:
        break;
    }
    for (int i = 0; i < 21; i++) {
        textureLocation[i][startTunnel] = 0;
        textureLocation[i][startTunnel + 1] = 0;
        textureLocation[i][startTunnel + 2] = 0;
        textureLocation[i][startTunnel + 3] = 0;
        textureLocation[i][startTunnel + 4] = 0;
        if ((rand() % 2)==1) {
            textureLocation[i][startTunnel + 5] = 0;
        }
        startTunnel += rotation;
    }

    //далее рандомно выбираем клетки и меняем им тектурку, чтобы уровень был разнообразнее

    for (int j = 1; j < 31; j++) {
        for (int i = 1; i < 31; i++) {
            if ((!(rand() % 16))) {                
                if(CountingNeighbours(i, j, 3) == 0) {
                    textureLocation[i][j] = 3;
                }
            }
            if (textureLocation[i][j] == 1) {
                if (rand() % 2) {
                    textureLocation[i][j] = 5;
                }
            }
            if (textureLocation[i][j] == 0) {
                switch (rand() % 3) {
                case 0:
                    break;
                case 1:
                    textureLocation[i][j] = 4;
                    break;
                case 2:
                    textureLocation[i][j] = 6;
                    break;
                }
            }
        }
    }
    //стены
    WallsAroundLevel();

    //ставим портал

    PuttingPortal();

    //заполяем массив, который хранит инфу, где стены, а где можно ходить

    SetWallsForTileSet();

    //ставим сундуки

    for (int i = 0; i < 3; i++) {
        srand(time(0));
        chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
        while (Location[chests[i][0]][chests[i][1]] != 0 || Location[chests[i][0] + 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] + 1] != 0 || Location[chests[i][0] - 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] - 1] != 0 || Location[chests[i][0] - 1][chests[i][1] - 1] != 0 || Location[chests[i][0] - 1][chests[i][1] + 1] != 0 || Location[chests[i][0] + 1][chests[i][1] - 1] != 0 || Location[chests[i][0] + 1][chests[i][1] + 1] != 0) {
            chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
        }
        textureLocation[chests[i][0]][chests[i][1]] = 14;
        Location[chests[i][0]][chests[i][1]] = 3;
    }
}

void Map::GulagChoose(int LCK) {

    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < 22; j++) {
            textureLocation[j][i] = 1;
            Location[j][i] = 1;
            Dark[j][i] = 1;
        }
    }
    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < 22; j++) {
            if(i == 0 || i == 31 || j == 0 || j == 21) {
                textureLocation[j][i] = 2;
                Location[j][i] = 1;
            }
            if((i >= 10 && i < 17)&&(j >= 10 && j < 17)) {
                textureLocation[j][i] = 0;
                Location[j][i] = 0;
            }
        }
    }
    int count = 0;
    while (count <= 12) {
        if(count < 3) {
            textureLocation[11+count*2][10] = 3;
            Location[11+count*2][10] = 8;
        }
        if(count >= 3 && count < 6) {
            textureLocation[10][11+(count-3)*2] = 3;
            Location[10][11+(count-3)*2] = 8;
        }
        if (count >= 6 && count < 9) {
            textureLocation[16][11+(count-6)*2] = 3;
            Location[16][11+(count-6)*2] = 8;
        }
        if (count >= 9 && count < 12) {
            textureLocation[11+(count-9)*2][16] = 3;
            Location[11+(count-9)*2][16] = 8;
        }
        count++;
        if (count >= (13 - LCK)) break;
    }
}

void Map::CreateSquare(int x, int y, int texture, int size) {
    for(int i = x; i < x+size; i++) {
        for(int j = y; j < y+size; j++) {
            textureLocation[j][i] = texture;
        }
    }
}

void Map::BigLabGenerationMethod() {
    srand(time(0));
    WallsAroundLevel();

    for (int i = 3; i < 21; i+=6) {
        for (int j = 3; j < 31; j+=6) {
            if ((i % 2 == 1) && (j % 2 == 1)) {
                CreateSquare(j, i, 0, 3);
                int Way = rand() % 2;
                bool Choosed = false;
                while (Choosed == false) {
                    Choosed = true;
                    switch (Way) {
                    case 0:
                        if (textureLocation[i][j + 3] != 1) {
                            Way = rand() % 4;
                            Choosed = false;
                        }
                        else {
                            CreateSquare(j + 3, i, 0, 3);
                        }
                        break;
                    case 1:
                        if (textureLocation[i+3][j] != 1) {
                            Way = rand() % 4;
                            Choosed = false;
                        }
                        else {
                            CreateSquare(j, i+3, 0, 3);
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1; i < 21; i++) {
        textureLocation[i][27] = 0;
        textureLocation[i][28] = 0;
        textureLocation[i][29] = 0;
        textureLocation[i][30] = 1;
        textureLocation[i][0] = 1;
        textureLocation[i][1] = 1;
    }
    for (int i = 1; i < 31; i++) {
        textureLocation[18][i] = 0;
        textureLocation[19][i] = 0;
        textureLocation[20][i] = 1;
    }
    for (int j = 1; j < 31; j++) {
        for (int i = 1; i < 21; i++) {
            if (CountingNeighbours(i, j, 0) > 3) {
                if(!(rand()%5)) {
                    textureLocation[i][j] = 0;
                }
            }
        }
    }

    for (int j = 1; j < 31; j++) {
        for (int i = 1; i < 21; i++) {
            if ((!(rand() % 16))) {
                if(CountingNeighbours(i, j, 3) == 0) {
                    textureLocation[i][j] = 3;
                }
            }
            if (textureLocation[i][j] == 1) {
                if (rand() % 2) {
                    textureLocation[i][j] = 5;
                }
            }
            if (textureLocation[i][j] == 0) {
                switch (rand() % 3) {
                case 0:
                    break;
                case 1:
                    textureLocation[i][j] = 4;
                    break;
                case 2:
                    textureLocation[i][j] = 6;
                    break;
                }
            }
        }
    }
    WallsAroundLevel();
    //генерим стены

    SetWallsForTileSet();

    //ставим сундуки

    for (int i = 0; i < 3; i++) {
        srand(time(0));
        chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
        while (Location[chests[i][0]][chests[i][1]] != 0 || Location[chests[i][0] + 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] + 1] != 0 || Location[chests[i][0] - 1][chests[i][1]] != 0 || Location[chests[i][0]][chests[i][1] - 1] != 0) {
            chests[i][0] = rand() % 20 + 1; chests[i][1] = rand() % 30 + 1;
        }
        textureLocation[chests[i][0]][chests[i][1]] = 14;
        Location[chests[i][0]][chests[i][1]] = 3;
    }

    //ставим портал

    PuttingPortal();
}

void Map::BossGenerationNethod() {
    for (int i = 0; i < 22; i++) {
        for(int j = 0; j < 32; j++) {
            textureLocation[i][j] = 0;
        }
    }
    int x = 6; int y = 5; int size = 4;
    CreateSquare(x, y, 1, size);
    CreateSquare(32-x-size,22-y-size, 1, 4);
    CreateSquare(x, 22-y-size, 1, 4);
    CreateSquare(32-x-size, y, 1, 4);
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 32; j++) {
            if ((textureLocation[i][j] == 1) && (!(rand() % 11))) {
                textureLocation[i][j] = 5;
            }
            if ((textureLocation[i][j] == 0) && (!(rand() % 16))) {
                if (rand() % 2) {
                    textureLocation[i][j] = 3;
                }
                else {
                    textureLocation[i][j] = 4;
                }
            }
            if ((textureLocation[i][j] == 0) && (!(rand() % 4))) {
                if (rand() % 2) {
                    textureLocation[i][j] = 7;
                }
                else {
                    textureLocation[i][j] = 8;
                }
            }
        }
    }
    WallsAroundLevel();

    SetWallsForTileSet();
}

void Map::CreateRing(int a, int b, int R) {
    for(int x = 0; x < 32; x++) {
        for(int y = 0; y < 22; y++) {
            if (pow((x-a), 2) + pow((y-b), 2) < pow(R, 2)) {
                textureLocation[y][x] = 0;
            }
        }
    }
}

void Map::RingGenerationmethod() {
    int Ring = rand()%6+6;
    int RingPos = 17 - Ring + 1;
    if (RingPos < 0 + Ring) RingPos = 0 + Ring + 1;
    CreateRing(RingPos, 10, Ring);
    Ring = rand()%6+6;
    RingPos = 17 + Ring;
    if (RingPos > 31 - Ring) RingPos = 31 - Ring;
    CreateRing(RingPos, 10, Ring);
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 32; j++) {
            if ((textureLocation[i][j] == 1) && (!(rand() % 11))) {
                textureLocation[i][j] = 5;
            }
            if ((textureLocation[i][j] == 0) && (!(rand() % 16))) {
                if (rand() % 2) {
                    textureLocation[i][j] = 3;
                }
                else {
                    textureLocation[i][j] = 4;
                }
            }
            if ((textureLocation[i][j] == 0) && (!(rand() % 4))) {
                if (rand() % 2) {
                    textureLocation[i][j] = 7;
                }
                else {
                    textureLocation[i][j] = 8;
                }
            }
        }
    }
    WallsAroundLevel();

    SetWallsForTileSet();

    PuttingPortal();
}
