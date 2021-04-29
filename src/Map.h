#pragma once


class Map
{
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
public:
    Map();
    ~Map();
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
};
