#pragma once


class Map
{
private:
    void LabGeneration();
    void ChunkGenerationMethod();
    void ChunkGenerationMethod2();
    void CaveLabGeneration();
    void CastleLabGeneration();
    void RoomGenerationMethod2();
    void CreateChunk(int x, int y);
    void CreateChunk2(int x, int y);
    int CountingNeighbours(int x, int y, int NeighbourNumber);
    void PuttingPortal();
    void SetWallsForTileSet();
    void SetWalls1();
    void SetWalls2();
    void CreateSquare(int x, int y, int texture, int size);
    void BigLabGenerationMethod();
    void BossGenerationNethod();
    void WallsAroundLevel();
    void RingGenerationmethod();
    void CreateRing(int a, int b, int R);
public:
    Map();
    ~Map();
    struct Portal {
        int x;
        int y;
    } portal;
    int generateChoose;
    int itemsOnLvl[3];
    int itemsHave;
    int chests[3][2];
    int floorLvl;
    int TileSet;
    int textureLocation[22][32];
    int Location[22][32];
    int Dark[22][32];
    void GenerateMap();
    void GulagChoose(int LCK);
};
