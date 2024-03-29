#include "Inventory.h"
#include "Managers.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

int Inventory::inventoryFace[INVENTORY_SIZE]; //������ � ���� ��, ��� ������ inventory, �� � static
std::map <int, InventoryItem*> Inventory::ExistingItems;
std::map <int, InventoryItem*>::iterator Inventory::it;
int Inventory::traderFace[TRADING_SIZE];

Inventory::Inventory()
{
    std::ifstream file;
    file.open("data/Items.txt");
    int ItemNumber = 0;
    while (file) {
        std::string Type;
        int DMG;
        int RNG;
        int COST;
        std::string WeapTex;
        std::string Name;
        std::string SpawnTex;
        int CHS;
        int dCHS;
        int DEF;
        int SPL;
        int HEAL;
        magicEl Eltype;
        magicType WpType;
        int MpHEAL;
        int STR;
        int DEX;
        int INT;
        int WSD;
        int PHS;
        int LCK;
        file >> Type;
        if (Type == "weapon")
        {
            file >> DMG;
            file >> RNG;
            file >> COST;
            file >> WeapTex;
            char* Tex = new char[WeapTex.length()+1];
            for (int i = 0; i <= WeapTex.length(); i++)
            {
                Tex[i] = WeapTex[i];
            }
            file >> Name;
            file >> SpawnTex;
            loc SpawnLoc = returnLoc(SpawnTex);
            type ItemType = weapon;
            ExistingItems[ItemNumber] = new meleeWeapon(DMG, RNG, COST, ItemType, Tex, Name, SpawnLoc);
        }
        if (Type == "rWeapon")
        {
            file >> DMG;
            file >> RNG;
            file >> CHS;
            file >> dCHS;
            file >> COST;
            file >> WeapTex;
            char* Tex = new char[WeapTex.length() + 1];
            for (int i = 0; i <= WeapTex.length(); i++)
            {
                Tex[i] = WeapTex[i];
            }
            file >> Name;
            file >> SpawnTex;
            loc SpawnLoc = returnLoc(SpawnTex);
            type ItemType = rWeapon;
            ExistingItems[ItemNumber] = new rangeWeapon(DMG, RNG, CHS, dCHS, COST, ItemType, Tex, Name, SpawnLoc);
        }
        if (Type == "magic")
        {
            file >> DMG;
            file >> RNG;
            file >> SPL;
            std::string tempT;
            file >> tempT;
            if(tempT == "ice") Eltype = magicEl::ice;
            if(tempT == "fire") Eltype = magicEl::fire;
            if(tempT == "thunder") Eltype = magicEl::thunder;
            file >> tempT;
            if(tempT == "point") WpType = magicType::point;
            if(tempT == "field") WpType = magicType::field;
            file >> COST;
            file >> WeapTex;
            char* Tex = new char[WeapTex.length() + 1];
            for (int i = 0; i <= WeapTex.length(); i++)
            {
                Tex[i] = WeapTex[i];
            }
            file >> Name;
            file >> SpawnTex;
            loc SpawnLoc = returnLoc(SpawnTex);
            type ItemType = magic;
            ExistingItems[ItemNumber] = new magicWeapon(DMG, RNG, SPL, COST, ItemType, Eltype, WpType, Tex, Name, SpawnLoc);
        }
        if (Type == "armor")
        {
            file >> DEF;
            file >> COST;
            file >> WeapTex;
            char* Tex = new char[WeapTex.length() + 1];
            for (int i = 0; i <= WeapTex.length(); i++)
            {
                Tex[i] = WeapTex[i];
            }
            file >> Name;
            file >> SpawnTex;
            loc SpawnLoc = returnLoc(SpawnTex);
            type ItemType = armor;
            ExistingItems[ItemNumber] = new armorItem(DEF, COST, ItemType, Tex, Name, SpawnLoc);
        }
        if (Type == "potion")
        {
            file >> HEAL;
            file >> MpHEAL;
            file >> COST;
            file >> WeapTex;
            char* Tex = new char[WeapTex.length() + 1];
            for (int i = 0; i <= WeapTex.length(); i++)
            {
                Tex[i] = WeapTex[i];
            }
            file >> Name;
            file >> SpawnTex;
            loc SpawnLoc = returnLoc(SpawnTex);
            type ItemType = potion;
            ExistingItems[ItemNumber] = new Potion(HEAL, MpHEAL, COST, ItemType, Tex, Name, SpawnLoc);
        }
        if (Type == "artifact")
        {
            file >> STR;
            file >> DEX;
            file >> INT;
            file >> WSD;
            file >> PHS;
            file >> LCK;
            file >> COST;
            file >> WeapTex;
            char* Tex = new char[WeapTex.length() + 1];
            for (int i = 0; i <= WeapTex.length(); i++)
            {
                Tex[i] = WeapTex[i];
            }
            file >> Name;
            file >> SpawnTex;
            loc SpawnLoc = returnLoc(SpawnTex);
            type ItemType = artifact;
            ExistingItems[ItemNumber] = new Artifact(STR, DEX, INT, WSD, PHS, LCK, COST, ItemType, Tex, Name, SpawnLoc);
        }
        ItemNumber++;
    }
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        inventory[i] = -1;
    }
}

Inventory::~Inventory(){}

void Inventory::EquipItem(int i, int j) 
{
    //EquipedArmor = ExistingItems[i];
    //EquipedWeapon = ExistingItems[j];
}

int Inventory::InventoryCount()
{
    int count = 0;
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        if (inventory[i] != -1)
        {
            count++;
        }
    }
    return count;
}

void Inventory::AddItem(int id)
{
    int count = 0;
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        if (inventory[i] == -1)
        {
            inventory[i] = id;
            count = -1;
            break;
        }
        count++;
    }
}

void Inventory::AddPlaceItem(int id, int place)
{
    try {
        if (place >= TRADING_SIZE && place < 0)
            throw "place more or less than TRADING_SIZE";
    }  catch (const char* ex) {
        std::cerr << "Error in AddPlaceItem" << ex << std::endl;
    }
    assert(place < TRADING_SIZE);
    if (place < TRADING_SIZE)
        inventory[place] = id;
}

void Inventory::Update() 
{
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        inventoryFace[i] = inventory[i];
    }
}

void Inventory::traderUpdate()
{
    for (int j = 0; j < TRADING_SIZE; j++)
    {
        traderFace[j] = inventory[j];
    }
}

meleeWeapon* Inventory::GetRealMelee(int id) {
    return static_cast<meleeWeapon*>(ExistingItems[id]);
}

rangeWeapon* Inventory::GetRealRange(int id) {
    return static_cast<rangeWeapon*>(ExistingItems[id]);
}

armorItem* Inventory::GetRealArmor(int id) {
    return static_cast<armorItem*>(ExistingItems[id]);
}

magicWeapon* Inventory::GetRealMagic(int id) {
    return static_cast<magicWeapon*>(ExistingItems[id]);
}

Artifact* Inventory::GetRealArtifact(int id) {
    return static_cast<Artifact*>(ExistingItems[id]);
}

int InventoryItem::GetCost()
{
    return COST;
}

std::string InventoryItem::GetHoverText()
{
    return name;
}

loc Inventory::returnLoc(std::string Text) {
    if(Text == "cave") return loc::cave;
    if(Text == "jungle") return loc::jungle;
    if(Text == "castle") return loc::castle;
    if(Text == "hell") return loc::hell;
    if(Text == "arcane") return loc::arcane;
}

rangeWeapon::rangeWeapon(int Damage, int Range, int Chance, int deltaChanse, int Cost, type type, const char* WeapTex, std::string Name, loc SpawnLoc)
{
    DMG = Damage;
    RNG = Range;
    CHNS = Chance;
    DCHNS = deltaChanse;
    COST = Cost;
    ItemTexture = WeapTex;
    Type = type;
    name = Name;
    spawnLoc = SpawnLoc;
}
rangeWeapon::~rangeWeapon(){}

std::string rangeWeapon::GetHoverText()
{
    return "DMG:"+std::to_string(DMG);
}

meleeWeapon::meleeWeapon(int Damage, int range, int Cost, type type, const char* WeapTex, std::string Name, loc SpawnLoc)
{
    DMG = Damage;
    RNG = range;
    COST = Cost;
    ItemTexture = WeapTex;
    Type = type;
    name = Name;
    spawnLoc = SpawnLoc;
}
meleeWeapon::~meleeWeapon(){}

std::string meleeWeapon::GetHoverText()
{
    return "DMG:"+std::to_string(DMG);
}

magicWeapon::magicWeapon(int Damage, int range, int splash, int Cost, type type, magicEl weaponEl, magicType weaponType, const char* WeapTex, std::string Name, loc SpawnLoc)
{
    DMG = Damage;
    RNG = range;
    SPL = splash;
    COST = Cost;
    WeaponEl = weaponEl;
    WeaponType = weaponType;
    Type = type;
    ItemTexture = WeapTex;
    name = Name;
    spawnLoc = SpawnLoc;
}

std::string magicWeapon::GetHoverText()
{
    return "DMG:"+std::to_string(DMG);
}

Artifact::Artifact(int STR, int DEX, int INT, int WSD, int PHS, int LCK, int Cost, type type, const char* WeapTex, std::string Name, loc SpawnLoc)
{
    specs[0] = STR; specs[1] = DEX; specs[2] = INT; specs[3] = WSD; specs[4] = PHS; specs[5] = LCK;
    COST = Cost;
    Type = type;
    ItemTexture = WeapTex;
    name = Name;
    spawnLoc = SpawnLoc;
}

armorItem::armorItem(int Defence, int Cost, type type, const char* WeapTex, std::string Name, loc SpawnLoc)
{
    COST = Cost;
    DEF = Defence;
    ItemTexture = WeapTex;
    Type = type;
    name = Name;
    spawnLoc = SpawnLoc;
    COST = Cost;
}
armorItem::~armorItem(){}

std::string armorItem::GetHoverText()
{
    return "STR:"+std::to_string(DEF);
}

Potion::Potion(int Heal, int MpHeal, int Cost, type type, const char* WeapTex, std::string Name, loc SpawnLoc)
{
    COST = Cost;
    Type = type;
    ItemTexture = WeapTex;
    HEAL = Heal;
    MpHEAL = MpHeal;
    spawnLoc = SpawnLoc;
    name = Name;
    COST = Cost;
}

std::string Potion::GetHoverText()
{
    if(HEAL == 0)
        return "MP:"+std::to_string(MpHEAL);
    else
        return "HP:"+std::to_string(HEAL);
}
