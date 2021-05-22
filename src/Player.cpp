#include "Player.h"
#include "GameObject.h"
#include "Managers.h"
#include <iostream>
#include "EntityPosition.h"
#include "UiMain.h"
#include "Inventory.h"
#include "Enemy.h"
#include "Buttons.h"
#include "TextureBase.h"
#include <iostream>

Equiped Player::EqItems = { -1, nullptr, nullptr, nullptr, -1, nullptr, -1, nullptr};

int Player::HP[3] = {
    10, /*hp  now*/
    10, /*hp  previous*/
    10	 /*hp max*/
};

int Player::mana[3] = {
    50, /*mana  now*/
    0, /*mana  previous*/
    50 /*mana max */
};

int Player::exp[3] = {
    0,  /*exp  now*/
    0,  /*exp  previous*/
    100   /*exp max */
};

int Player::STR[2] = {
    1, /*STR  now*/
    1, /*STR  previous*/
};

int Player::DEX[2] = {
    1, /*DEX  now*/
    1, /*DEX  previous*/
};

int Player::INT[2] = {
    1, /*INT  now*/
    1, /*INT  previous*/
};

int Player::WSD[2] = {
    1, /*WSD  now*/
    1, /*WSD  previous*/
};

int Player::PHS[2] = {
    1, /*PHS  now*/
    1, /*PHS  previous*/
};

int Player::LCK[2] = {
    1, /*LCK  now*/
    1, /*LCK  previous*/
};

int Player::pointOfSpec[3] = {
    0, /*points now*/
    0, /*points previous*/
    10	 /*points max*/
};

int Player::levelOfPlayer[3] = {
    1, /*level now*/
    1, /*level previous*/
    100	 /*level max*/
};

int Player::quantityOfCoins[3] = {
    0, /*coins now*/
    0, /*coins previous*/
    100	 /*coins max*/
};

int Player::VIS = 10;

Player::Player( SDL_Renderer* renderer):
    GameObject( renderer)
{
    GameTextures = TextureBase::Instance();
    ren = renderer;
    PlayerTexture = GameTextures->GetTexture("Hero");
    playerAnimation = new Animation(ren, PlayerTexture);
    generate = -1;
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            Location[i][j] = 0;
        }
    }

    playerEscaping = false;
    inventory = new Inventory;
    inventory->Update();
    EqItems.WeaponId = 0;
    EqItems.equipedMeleeW = inventory->GetRealMelee(0);
    HP[0] = 10; HP[1] = 10; HP[2] = 10;
    mana[0] = 50; mana[1] = 0; mana[2] = 50;
    exp[0] = 0; exp[1] = 0; exp[2] = 100;
    STR[0] = 1; STR[1] = 1;
    DEX[0] = 1; DEX[1] = 1;
    INT[0] = 1; INT[1] = 1;
    WSD[0] = 1; WSD[1] = 1;
    PHS[0] = 1; PHS[1] = 1;
    LCK[0] = 1; LCK[1] = 1;
    pointOfSpec[0] = 0; pointOfSpec[1] = 0; pointOfSpec[2] = 10;
    levelOfPlayer[0] = 1; levelOfPlayer[1] = 1; levelOfPlayer[2] = 100;
    quantityOfCoins[0] = 0; quantityOfCoins[1] = 0; quantityOfCoins[2] = 100;
    EqItems = { -1, nullptr, nullptr, nullptr, -1, nullptr, -1, nullptr};
    EqItems.WeaponId = 0;
    EqItems.equipedMeleeW = inventory->GetRealMelee(0);
}

Player::~Player() {
    delete inventory;
    delete playerAnimation;
}

void Player::PushItemsToInventory(int kit)
{
    if (kit == 4)
    {
        for(int i = 1; i < Inventory::ExistingItems.size(); i++) {
            inventory->AddItem(i);
        }
    }
    if (kit == 1)
    {
        inventory->AddItem(1);
        inventory->AddItem(5);
        inventory->AddItem(8);
        inventory->AddItem(6);
        inventory->AddItem(9);
    }
    if (kit == 2)
    {
        inventory->AddItem(3);
        inventory->AddItem(5);
        inventory->AddItem(8);
        inventory->AddItem(7);
        inventory->AddItem(9);
    }
    if (kit == 3) {
        inventory->AddItem(4);
        inventory->AddItem(8);
        inventory->AddItem(7);
    }
}

//UNODNE
void Player::itemInInv(int num)
{
    if (num >= 1 && num <= 10)
    {
        inventory->AddItem(num);
    }
    else
    {
        try
        {
            if (num < 1 || num > 10)
                throw "Num in itemInInv is wrong\n";
        }  catch (const char* ex)
        {
            std::cerr << ex;
        }
    }
}

int Player::GetHP(int numOfArr) noexcept
{
    switch (numOfArr)
    {
    case 0:
        return HP[0];
    case 1:
        return HP[1];
    case 2:
        return HP[2];
    default:
        break;
    }
}

int Player::GetEXP(int numOfArr) noexcept
{
    switch (numOfArr)
    {
    case 0:
        return exp[0];
    case 1:
        return exp[1];
    case 2:
        return exp[2];
    default:
        break;
    }
}

int Player::GetMana(int numOfArr) noexcept
{
    switch (numOfArr)
    {
    case 0:
        return mana[0];
    case 1:
        return mana[1];
    case 2:
        return mana[2];
    default:
        break;
    }
}

//Получение значения характеристик (STR, DEX, INT, WSD, PHS, LCK)
int Player::GetSpecValue(int numSpec) noexcept
{
    switch (numSpec)
    {
    case 1:
        return STR[0];
    case 2:
        return DEX[0];
    case 3:
        return INT[0];
    case 4:
        return WSD[0];
    case 5:
        return PHS[0];
    case 6:
        return LCK[0];
    default:
        std::cout << "Error in GetSpecValue!" << std::endl;
        break;
    }
}

int Player::GetPointOfSpec(int numPoint) noexcept
{
    switch (numPoint)
    {
    case 0:
        return pointOfSpec[0];
    case 1:
        return pointOfSpec[1];
    case 2:
        return pointOfSpec[2];
    default:
        std::cout << "Error in GetPointSpec" << std::endl;
        break;
    }
}

int Player::GetLevelOfPlayer(int numLvl) noexcept
{
    switch (numLvl)
    {
    case 0:
        return levelOfPlayer[0];
    case 1:
        return levelOfPlayer[1];
    case 2:
        return levelOfPlayer[2];
    default:
        std::cout << "Error in GetPointSpec" << std::endl;
        break;
    }
}

int Player::GetCoinsOfPlayer(int numCoins) noexcept
{
    switch (numCoins)
    {
    case 0:
        return quantityOfCoins[0];
    case 1:
        return quantityOfCoins[1];
    case 2:
        return quantityOfCoins[2];
    default:
        std::cout << "Error in GetPointSpec" << std::endl;
        break;
    }
}

void Player::ChangePointOfSpec(int valueOfChanging)
{
    if (pointOfSpec[0] != 0)
        pointOfSpec[0] += valueOfChanging;
}

//Изменение значения характеристики (STR, DEX, INT, PHS, LCK) на +1
void Player::ChangeValueSpecs(int numOfSpec)
{
    if (pointOfSpec[0] != 0)
    {
        switch (numOfSpec)
        {
        case 1: //STR
            STR[0] += 1;
            Player::ChangePointOfSpec(-1);
            break;
        case 2: //DEX
            DEX[0] += 1;
            Player::ChangePointOfSpec(-1);
            break;
        case 3: //INT
            INT[0] += 1;
            Player::ChangePointOfSpec(-1);
            break;
        case 4:
            WSD[0] += 1;
            Player::ChangePointOfSpec(-1);
            break;
        case 5: //PHS
            PHS[0] += 1;
            Player::ChangePointOfSpec(-1);
            break;
        case 6: //LCK
            LCK[0] += 1;
            Player::ChangePointOfSpec(-1);
            break;
        default:
            std::cout << "Error in ChangeSpecValue!" << std::endl;
            break;
        }
    }
}

void Player::ChangeValueSpecsNoLvl(int numOfSpec, int Value)
{
    switch (numOfSpec)
    {
    case 1: //STR
        STR[0] += Value;
        break;
    case 2: //DEX
        DEX[0] += Value;
        break;
    case 3: //INT
        INT[0] += Value;
        break;
    case 4:
        WSD[0] += Value;
        break;
    case 5: //PHS
        PHS[0] += Value;
        break;
    case 6: //LCK
        LCK[0] += Value;
        break;
    default:
        std::cout << "Error in ChangeSpecValueNoLvl!" << std::endl;
        break;
    }
}

//Изменение текущего значения hp
void Player::ChangeHpValue(int valueOfChangingHp)
{
    if (valueOfChangingHp != 0)
        HP[0] += valueOfChangingHp;
    if (HP[0] > HP[2])
       HP[0] = HP[2];
}

//Изменение текущего значения mana
void Player::ChangeManaValue(int valueOfChangingMana)
{
    if (valueOfChangingMana != 0)
        mana[0] += valueOfChangingMana;
    if (mana[0] > mana[2])
        mana[0] = mana[2];
}

//Изменение текущего значения exp
void Player::ChangeExpValue(int valueOfChangingExp)
{
    exp[0] += valueOfChangingExp;
}

//Изменение максимального значения hp
void Player::ChangeMaxHpValue(int flag)
{
    int temp = HP[2];
    HP[2] = 10 +1*flag - 1;
    if(HP[2] != temp) HP[0] += HP[2] - temp;
    if(HP[0] < 1) HP[0] = 1;
}

//Изменение максимального значения маны
void Player::ChangeMaxManaValue(int flag)
{
    int temp = mana[2];
    mana[2] = 10 + 10*flag - 10;
    if(mana[2] != temp) mana[0] += mana[2] - temp;
    if(mana[0] < 0) mana[0] = 0;
}

//Изменение максимального значения exp
void Player::ChangeMaxExpValue()
{
    exp[2] += 100;
}

//Изменение кол-ва монет
void Player::ChangeCoins(int value)
{
    quantityOfCoins[0] += value;
}

//Проверка изменения HP
void Player::CheckHP()
{
    if (Player::HP[0] != Player::HP[1] && FlagManager::flagCheckHP == 0)
    {
        FlagManager::flagCheckHP = 1;
        Player::HP[1] = Player::HP[0];
    }
    else if (Player::HP[0] == Player::HP[1] && FlagManager::flagCheckHP == 1)
    {
        FlagManager::flagCheckHP = 0;
    }
}

//Проверка изменения MANA
void Player::CheckMANA()
{
    if (Player::mana[0] != Player::mana[1] && FlagManager::flagCheckMana == 0)
    {
        FlagManager::flagCheckMana = 1;
        Player::mana[1] = Player::mana[0];
    }
    else if (Player::mana[0] == Player::mana[1] && FlagManager::flagCheckMana == 1)
    {
        FlagManager::flagCheckMana = 0;
    }
}

//Проверка изменения EXP
void Player::CheckEXP()
{
    if (Player::exp[0] == Player::exp[2])
    {
        Player::exp[0] = 0;
        ChangeMaxExpValue();
        Player::levelOfPlayer[0] += 1;
        Player::pointOfSpec[0] += 1;
        FlagManager::flagCheckExp = 1;
    }
    else if (Player::exp[0] != Player::exp[1] && FlagManager::flagCheckExp == 0)
    {
        FlagManager::flagCheckExp = 1;
        Player::exp[1] = Player::exp[0];
    }
    else if (Player::exp[0] == Player::exp[1] && FlagManager::flagCheckExp == 1)
    {
        FlagManager::flagCheckExp = 0;
    }
}

void Player::CheckPointOfSpec()
{
    if (Player::pointOfSpec[0] != Player::pointOfSpec[1] && FlagManager::flagPointOfSpec == 0)
    {
        FlagManager::flagPointOfSpec = 1;
        Player::pointOfSpec[1] = Player::pointOfSpec[0];
    }
    else if (Player::pointOfSpec[0] != 0)
    {
        FlagManager::flagPointOfSpec = 1;
    }
    else
    {
        FlagManager::flagPointOfSpec = 0;
    }
}

void Player::CheckLevelOfPlayer()
{
    if (Player::levelOfPlayer[0] != Player::levelOfPlayer[1] && FlagManager::flagLevelOfPlayer == 0)
    {
        FlagManager::flagLevelOfPlayer = 1;
        Player::levelOfPlayer[1] = Player::levelOfPlayer[0];
    }
    else
    {
        FlagManager::flagLevelOfPlayer = 0;
    }
}

void Player::CheckCoinsOfPlayer()
{
    if (Player::quantityOfCoins[0] != Player::quantityOfCoins[1] && FlagManager::flagCoin == 0)
    {
        FlagManager::flagCoin = 1;
        Player::quantityOfCoins[1] = Player::quantityOfCoins[0];
    }
    else
    {
        FlagManager::flagCoin = 0;
    }
}

//Проверка изменения значений характеристик (STR, DEX, INT, PHS, LCK)
void Player::CheckSpecValue(int numSpec)
{
    switch (numSpec)
    {
    case 1://Check STR
        if (Player::STR[0] != Player::STR[1] && FlagManager::flagSTR == 0)
        {
            FlagManager::flagSTR = 1;
            Player::STR[1] = Player::STR[0];
        }
        else if (Player::STR[0] == Player::STR[1] && FlagManager::flagSTR == 1)
        {
            FlagManager::flagSTR = 0;
        }
        break;
    case 2://Check DEX
        if (Player::DEX[0] != Player::DEX[1] && FlagManager::flagDEX == 0)
        {
            FlagManager::flagDEX = 1;
            Player::DEX[1] = Player::DEX[0];
        }
        else if (Player::DEX[0] == Player::DEX[1] && FlagManager::flagDEX == 1)
        {
            FlagManager::flagDEX = 0;
        }
        break;
    case 3://Check INT
        if (Player::INT[0] != Player::INT[1] && FlagManager::flagINT == 0)
        {
            FlagManager::flagINT = 1;
            Player::INT[1] = Player::INT[0];
        }
        else if (Player::INT[0] == Player::INT[1] && FlagManager::flagINT == 1)
        {
            FlagManager::flagINT = 0;
        }
        break;
    case 4: //Check WSD
        if (Player::WSD[0] != Player::WSD[1] && FlagManager::flagWSD == 0)
        {
            FlagManager::flagWSD = 1;
            Player::WSD[1] = Player::WSD[0];
        }
        else if (Player::WSD[0] == Player::WSD[1] && FlagManager::flagWSD == 1)
        {
            FlagManager::flagWSD = 0;
        }
        break;
    case 5://Check PHS
        if (Player::PHS[0] != Player::PHS[1] && FlagManager::flagPHS == 0)
        {
            FlagManager::flagPHS = 1;
            Player::PHS[1] = Player::PHS[0];
        }
        else if (Player::PHS[0] == Player::PHS[1] && FlagManager::flagPHS == 1)
        {
            FlagManager::flagPHS = 0;
        }
        break;
    case 6://Check LCK
        if (Player::LCK[0] != Player::LCK[1] && FlagManager::flagLCK == 0)
        {
            FlagManager::flagLCK = 1;
            Player::LCK[1] = Player::LCK[0];
        }
        else if (Player::LCK[0] == Player::LCK[1] && FlagManager::flagLCK == 1)
        {
            FlagManager::flagLCK = 0;
        }
        break;
    default:
        std::cout << "Error in CheckSpecValue" << std::endl;
        break;
    }
}


void Player::GetLevel(int arr[22][32])
{
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            Location[i][j] = arr[i][j];
        }
    }
}

void Player::GetPlayerFirstCoords()
{
    EntityPosition::Coords[0] = (rand() % 3 + 1) * 32;
    EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
    if (generate != 4 && generate != 5 && generate != 7)
    {
        while ((Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32] == 1) ||
               ((Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32 - 1] != 0) &&
                (Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32 + 1] != 0) &&
                (Location[EntityPosition::Coords[1] / 32 - 1][EntityPosition::Coords[0] / 32] != 0) &&
                (Location[EntityPosition::Coords[1] / 32 + 1][EntityPosition::Coords[0] / 32] != 0)))
        {
            EntityPosition::Coords[0] = (rand() % 3 + 1) * 32;
            EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
        }
    }
    else
    {
       if (generate != 7)
       {
           while (Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32] == 1)
           {
               EntityPosition::Coords[0] = (rand() % 3 + 1) * 32;
               EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
           }
       }
       else
       {
           while (Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32] == 1)
           {
               EntityPosition::Coords[0] = (rand() % 16 + 1) * 32;
               EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
           }
       }
    }
}

void Player::GetItemDrop(int id)
{
    if (id != -1)
    {
        inventory->inventory[id] = -1;
    }
    FlagManager::flagDrop = -1;
}

void Player::GetItemEquip(int id)
{
	if (id != -1)
	{
		int ItemId = inventory->inventory[id];
		if (Inventory::ExistingItems[ItemId]->Type == weapon) 
		{
			if (EqItems.WeaponId > 0) 
			{
				inventory->inventory[id] = EqItems.WeaponId;
			}
			else
			{
				inventory->inventory[id] = -1;
			}
			EqItems.WeaponId = ItemId;
			EqItems.equipedMeleeW = inventory->GetRealMelee(ItemId);
			EqItems.equipedRangeW = nullptr;
            EqItems.equipedMagic = nullptr;
		}
		if (Inventory::ExistingItems[ItemId]->Type == rWeapon) 
		{
			if (EqItems.WeaponId > 0) 
			{
				inventory->inventory[id] = EqItems.WeaponId;
			}
			else 
			{
				inventory->inventory[id] = -1;
			}
			EqItems.WeaponId = ItemId;
			
			EqItems.equipedRangeW = inventory->GetRealRange(ItemId);
			EqItems.equipedMeleeW = nullptr;
            EqItems.equipedMagic = nullptr;
		}
        if (Inventory::ExistingItems[ItemId]->Type == magic)
        {
            if (EqItems.WeaponId > 0)
            {
                inventory->inventory[id] = EqItems.WeaponId;
            }
            else
            {
                inventory->inventory[id] = -1;
            }
            EqItems.WeaponId = ItemId;

            EqItems.equipedMagic = inventory->GetRealMagic(ItemId);
            EqItems.equipedMeleeW = nullptr;
            EqItems.equipedRangeW = nullptr;
        }
        if (Inventory::ExistingItems[ItemId]->Type == armor)
        {
            if (EqItems.ArmorId > 0)
            {
                inventory->inventory[id] = EqItems.ArmorId;
            }
            else
            {
                inventory->inventory[id] = -1;
            }
            EqItems.ArmorId = ItemId;

            EqItems.equipedArmor = inventory->GetRealArmor(ItemId);
            if (EqItems.equipedArmor->name == "LetherArmor")
            {
                PlayerTexture = 0;
                PlayerTexture = GameTextures->GetTexture("HeroLether");
                playerAnimation->UpdateTexture("HeroLether");
            }
        }
        if (Inventory::ExistingItems[ItemId]->Type == potion)
        {
            ChangeHpValue(static_cast<Potion*>(Inventory::ExistingItems[ItemId])->HEAL);
            ChangeManaValue(static_cast<Potion*>(Inventory::ExistingItems[ItemId])->MpHEAL);
            inventory->inventory[id] = -1;
        }
        if (Inventory::ExistingItems[ItemId]->Type == artifact)
        {
            if (EqItems.ArtId > 0)
            {
                for(int i = 1; i <= 6; i++) {
                    ChangeValueSpecsNoLvl(i, -(EqItems.equipedArtifact->specs[i-1]));
                }
                inventory->inventory[id] = EqItems.ArtId;
            }
            else
            {
                inventory->inventory[id] = -1;
            }
            EqItems.ArtId = ItemId;

            EqItems.equipedArtifact = inventory->GetRealArtifact(ItemId);

            for(int i = 1; i <= 6; i++)
            {
                ChangeValueSpecsNoLvl(i, EqItems.equipedArtifact->specs[i-1]);
            }
        }
    }
    FlagManager::flagEquip = -1;
}

void Player::GetItemUnEquip(int id)
{
    if (inventory->InventoryCount() != INVENTORY_SIZE)
    {
        if (id == 0)
        {
            inventory->AddItem(EqItems.WeaponId);
            EqItems.WeaponId = 0;
            EqItems.equipedMeleeW = inventory->GetRealMelee(0);
            EqItems.equipedRangeW = nullptr;
        }
        if (id == 1)
        {
            inventory->AddItem(EqItems.ArmorId);
            EqItems.ArmorId = -1;
            EqItems.equipedArmor = nullptr;
            PlayerTexture = 0;
            PlayerTexture = GameTextures->GetTexture("Hero");
            playerAnimation->UpdateTexture("Hero");
        }
        if (id == 2)
        {
            for(int i = 1; i <= 6; i++) {
                ChangeValueSpecsNoLvl(i, -(EqItems.equipedArtifact->specs[i-1]));
            }
            inventory->AddItem(EqItems.ArtId);
            EqItems.ArtId = -1;
            EqItems.equipedArtifact = nullptr;
        }

    }
    FlagManager::flagUnEquip = -1;
}

bool Player::InventoryBlock()
{
    int count = inventory->InventoryCount();
    if (count == INVENTORY_SIZE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Player::GetItemOnLvl(int id)
{
    inventory->AddItem(id);
}

void Player::Render()
{
    if (playerEscaping) RenderManager::CopyToRender(GameTextures->GetTexture("HeroEscape"), ren, EntityPosition::Coords[0], EntityPosition::Coords[1], 32, 32, 0, 0, 32, 32);
    if (!playerEscaping) playerAnimation->Render(EntityPosition::Coords[0], EntityPosition::Coords[1]);
}

void Player::Update()
{
    Player::GetItemDrop(FlagManager::flagDrop);
    Player::GetItemEquip(FlagManager::flagEquip);
    Player::GetItemUnEquip(FlagManager::flagUnEquip);
    inventory->Update();
    Player::CheckHP();
    Player::CheckMANA();
    Player::CheckEXP();
    Player::CheckLevelOfPlayer();
    Player::CheckPointOfSpec();
    Player::CheckCoinsOfPlayer();
    Player::CheckSpecValue(1); //STR
    Player::CheckSpecValue(2); //DEX
    Player::CheckSpecValue(3); //INT
    Player::CheckSpecValue(4); //WSD
    Player::CheckSpecValue(5); //PHS
    Player::CheckSpecValue(6); //LCK
}

int Player::damage = 0;

void Player::playerTurn()
{
    FlagManager::flagInAreaOfAnemy = 0;
    FlagManager::flagMeleeAttackPlayer = 1;
    FlagManager::flagRangeAttackPlayer = 1;
    FlagManager::flagTurn = 0;
    FlagManager::flagMeleeAttackEnemy = 0;
}

int	Player::MeleeAttack()
{
    if (Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == weapon)
    {
        std::cout << "Melee boy" << std::endl;
        damage = Player::EqItems.equipedMeleeW->DMG + Player::STR[0];
        std::cout << damage << std::endl;
    }
    return damage;
}

int Player::RangeAttack()
{
    if ((Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == rWeapon) &&
            FlagManager::flagRangeAttackPlayer == 1 &&
            Player::mana[0] != 0)
    {
        damage = Player::EqItems.equipedRangeW->DMG + Player::DEX[0];
        std::cout << damage << "!" << std::endl;
    }
    return damage;
}
int Player::MagicAttack()
{
    if ((Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == magic) &&
        Player::mana[0] != 0)
    {
        damage = Player::EqItems.equipedMagic->DMG + Player::WSD[0];
        std::cout << damage << "!" << std::endl;
    }
    return damage;
}

