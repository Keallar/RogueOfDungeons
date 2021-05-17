#include "Inventory.h"
#include "Managers.h"
#include <string>
#include <iostream>
#include <fstream>

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
            type ItemType = weapon;
            ExistingItems[ItemNumber] = new meleeWeapon(DMG, RNG, COST, ItemType, Tex, Name);
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
            type ItemType = rWeapon;
            ExistingItems[ItemNumber] = new rangeWeapon(DMG, RNG, CHS, dCHS, COST, ItemType, Tex, Name);
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
            type ItemType = magic;
            ExistingItems[ItemNumber] = new magicWeapon(DMG, RNG, SPL, COST, ItemType, Eltype, WpType, Tex, Name);
        }
        if (Type == "armor") {
            file >> DEF;
            file >> WeapTex;
            char* Tex = new char[WeapTex.length() + 1];
            for (int i = 0; i <= WeapTex.length(); i++)
            {
                Tex[i] = WeapTex[i];
            }
            file >> Name;
            type ItemType = armor;
            ExistingItems[ItemNumber] = new armorItem(DEF, ItemType, Tex, Name);
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
            type ItemType = potion;
            ExistingItems[ItemNumber] = new Potion(HEAL, MpHEAL, ItemType, Tex, Name);
        }
        if (Type == "artifact")
        {
            file >> STR;
            file >> DEX;
            file >> INT;
            file >> WSD;
            file >> PHS;
            file >> LCK;
            file >> WeapTex;
            char* Tex = new char[WeapTex.length() + 1];
            for (int i = 0; i <= WeapTex.length(); i++)
            {
                Tex[i] = WeapTex[i];
            }
            file >> Name;
            type ItemType = artifact;
            ExistingItems[ItemNumber] = new Artifact(STR, DEX, INT, WSD, PHS, LCK, ItemType, Tex, Name);
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

rangeWeapon::rangeWeapon(int Damage, int Range, int Chance, int deltaChanse, int Cost, type type, const char* WeapTex, std::string Name)
{
    DMG = Damage;
    RNG = Range;
    CHNS = Chance;
    DCHNS = deltaChanse;
    COST = Cost;
    ItemTexture = WeapTex;
    Type = type;
    name = Name;
}
rangeWeapon::~rangeWeapon(){}

meleeWeapon::meleeWeapon(int Damage, int range, int Cost, type type, const char* WeapTex, std::string Name)
{
    DMG = Damage;
    RNG = range;
    COST = Cost;
    ItemTexture = WeapTex;
    Type = type;
    name = Name;
}
meleeWeapon::~meleeWeapon(){}

magicWeapon::magicWeapon(int Damage, int range, int splash, int Cost, type type, magicEl weaponEl, magicType weaponType, const char* WeapTex, std::string Name)
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
}

Artifact::Artifact(int STR, int DEX, int INT, int WSD, int PHS, int LCK, type type, const char* WeapTex, std::string Name)
{
    specs[0] = STR; specs[1] = DEX; specs[2] = INT; specs[3] = WSD; specs[4] = PHS; specs[5] = LCK;
    Type = type;
    ItemTexture = WeapTex;
    name = Name;
}

armorItem::armorItem(int Defence, type type, const char* WeapTex, std::string Name)
{
    DEF = Defence;
    ItemTexture = WeapTex;
    Type = type;
    name = Name;
}
armorItem::~armorItem(){}

Potion::Potion(int Heal, int MpHeal, type type, const char* WeapTex, std::string Name)
{
    Type = type;
    ItemTexture = WeapTex;
    HEAL = Heal;
    MpHEAL = MpHeal;
    name = Name;
}
