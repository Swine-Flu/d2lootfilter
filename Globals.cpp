#include "Globals.h"
#include <fmt/format.h>
#include <fmt/core.h>
#include "Action.h"

GameVersion GAME_VERSION = GameVersion::NONE;

bool TXT_DATA_LOADED = false;

std::map<std::wstring, std::vector<Action*>> STYLES;
std::map<std::wstring, uint32_t> ITEM_NAME_LOOKUP_TABLE;
std::map<std::wstring, uint32_t> ITEM_CODE_LOOKUP_TABLE;
std::map<std::wstring, uint32_t> RUNE_NAME_LOOKUP_TABLE;
std::map<std::wstring, std::wstring> SKILL_LOOKUP_TABLE;

std::map<std::wstring, uint16_t> ITEM_TYPE_LOOKUP_TABLE = {
{ L"None", static_cast<std::underlying_type_t<ItemType>>(ItemType::NONE_1) },
{ L"None", static_cast<std::underlying_type_t<ItemType>>(ItemType::NONE_2) },
{ L"Shield", static_cast<std::underlying_type_t<ItemType>>(ItemType::SHIELD) },
{ L"Armor", static_cast<std::underlying_type_t<ItemType>>(ItemType::ARMOR) },
{ L"Gold", static_cast<std::underlying_type_t<ItemType>>(ItemType::GOLD) },
{ L"Bow Quiver", static_cast<std::underlying_type_t<ItemType>>(ItemType::BOW_QUIVER) },
{ L"Crossbow Quiver", static_cast<std::underlying_type_t<ItemType>>(ItemType::CROSSBOW_QUIVER) },
{ L"Player Body Part", static_cast<std::underlying_type_t<ItemType>>(ItemType::PLAYER_BODY_PART) },
{ L"Herb", static_cast<std::underlying_type_t<ItemType>>(ItemType::HERB) },
{ L"Potion", static_cast<std::underlying_type_t<ItemType>>(ItemType::POTION) },
{ L"Ring", static_cast<std::underlying_type_t<ItemType>>(ItemType::RING) },
{ L"Elixir", static_cast<std::underlying_type_t<ItemType>>(ItemType::ELIXIR) },
{ L"Amulet", static_cast<std::underlying_type_t<ItemType>>(ItemType::AMULET) },
{ L"Charm", static_cast<std::underlying_type_t<ItemType>>(ItemType::CHARM) },
{ L"Not Used", static_cast<std::underlying_type_t<ItemType>>(ItemType::NONE_3) },
{ L"Boots", static_cast<std::underlying_type_t<ItemType>>(ItemType::BOOTS) },
{ L"Gloves", static_cast<std::underlying_type_t<ItemType>>(ItemType::GLOVES) },
{ L"Not Used", static_cast<std::underlying_type_t<ItemType>>(ItemType::NONE_4) },
{ L"Book", static_cast<std::underlying_type_t<ItemType>>(ItemType::BOOK) },
{ L"Belt", static_cast<std::underlying_type_t<ItemType>>(ItemType::BELT) },
{ L"Gem", static_cast<std::underlying_type_t<ItemType>>(ItemType::GEM) },
{ L"Torch", static_cast<std::underlying_type_t<ItemType>>(ItemType::TORCH) },
{ L"Scroll", static_cast<std::underlying_type_t<ItemType>>(ItemType::SCROLL) },
{ L"Not Used", static_cast<std::underlying_type_t<ItemType>>(ItemType::NONE_5) },
{ L"Scepter", static_cast<std::underlying_type_t<ItemType>>(ItemType::SCEPTER) },
{ L"Wand", static_cast<std::underlying_type_t<ItemType>>(ItemType::WAND) },
{ L"Staff", static_cast<std::underlying_type_t<ItemType>>(ItemType::STAFF) },
{ L"Bow", static_cast<std::underlying_type_t<ItemType>>(ItemType::BOW) },
{ L"Axe", static_cast<std::underlying_type_t<ItemType>>(ItemType::AXE) },
{ L"Club", static_cast<std::underlying_type_t<ItemType>>(ItemType::CLUB) },
{ L"Sword", static_cast<std::underlying_type_t<ItemType>>(ItemType::SWORD) },
{ L"Hammer", static_cast<std::underlying_type_t<ItemType>>(ItemType::HAMMER) },
{ L"Knife", static_cast<std::underlying_type_t<ItemType>>(ItemType::KNIFE) },
{ L"Spear", static_cast<std::underlying_type_t<ItemType>>(ItemType::SPEAR) },
{ L"Polearm", static_cast<std::underlying_type_t<ItemType>>(ItemType::POLEARM) },
{ L"Crossbow", static_cast<std::underlying_type_t<ItemType>>(ItemType::CROSSBOW) },
{ L"Mace", static_cast<std::underlying_type_t<ItemType>>(ItemType::MACE) },
{ L"Helm", static_cast<std::underlying_type_t<ItemType>>(ItemType::HELM) },
{ L"Missile Potion", static_cast<std::underlying_type_t<ItemType>>(ItemType::MISSILE_POTION) },
{ L"Quest", static_cast<std::underlying_type_t<ItemType>>(ItemType::QUEST) },
{ L"Body Part", static_cast<std::underlying_type_t<ItemType>>(ItemType::BODY_PART) },
{ L"Key", static_cast<std::underlying_type_t<ItemType>>(ItemType::KEY) },
{ L"Throwing Knife", static_cast<std::underlying_type_t<ItemType>>(ItemType::THROWING_KNIFE) },
{ L"Throwing Axe", static_cast<std::underlying_type_t<ItemType>>(ItemType::THROWING_AXE) },
{ L"Javelin", static_cast<std::underlying_type_t<ItemType>>(ItemType::JAVELIN) },
{ L"Weapon", static_cast<std::underlying_type_t<ItemType>>(ItemType::WEAPON) },
{ L"Melee Weapon", static_cast<std::underlying_type_t<ItemType>>(ItemType::MELEE_WEAPON) },
{ L"Missile Weapon", static_cast<std::underlying_type_t<ItemType>>(ItemType::MISSILE_WEAPON) },
{ L"Thrown Weapon", static_cast<std::underlying_type_t<ItemType>>(ItemType::THROWN_WEAPON) },
{ L"Combo Weapon", static_cast<std::underlying_type_t<ItemType>>(ItemType::COMBO_WEAPON) },
{ L"Any Armor", static_cast<std::underlying_type_t<ItemType>>(ItemType::ANY_ARMOR) },
{ L"Any Shield", static_cast<std::underlying_type_t<ItemType>>(ItemType::ANY_SHIELD) },
{ L"Miscellaneous", static_cast<std::underlying_type_t<ItemType>>(ItemType::MISCELLANEOUS) },
{ L"Socket Filler", static_cast<std::underlying_type_t<ItemType>>(ItemType::SOCKET_FILLER) },
{ L"Second Hand", static_cast<std::underlying_type_t<ItemType>>(ItemType::SECOND_HAND) },
{ L"Staves And Rods", static_cast<std::underlying_type_t<ItemType>>(ItemType::STAVES_AND_RODS) },
{ L"Missile", static_cast<std::underlying_type_t<ItemType>>(ItemType::MISSILE) },
{ L"Blunt", static_cast<std::underlying_type_t<ItemType>>(ItemType::BLUNT) },
{ L"Jewel", static_cast<std::underlying_type_t<ItemType>>(ItemType::JEWEL) },
{ L"Class Specific", static_cast<std::underlying_type_t<ItemType>>(ItemType::CLASS_SPECIFIC) },
{ L"Amazon Item", static_cast<std::underlying_type_t<ItemType>>(ItemType::AMAZON_ITEM) },
{ L"Barbarian Item", static_cast<std::underlying_type_t<ItemType>>(ItemType::BARBARIAN_ITEM) },
{ L"Necromancer Item", static_cast<std::underlying_type_t<ItemType>>(ItemType::NECROMANCER_ITEM) },
{ L"Paladin Item", static_cast<std::underlying_type_t<ItemType>>(ItemType::PALADIN_ITEM) },
{ L"Sorceress Item", static_cast<std::underlying_type_t<ItemType>>(ItemType::SORCERESS_ITEM) },
{ L"Assassin Item", static_cast<std::underlying_type_t<ItemType>>(ItemType::ASSASSIN_ITEM) },
{ L"Druid Item", static_cast<std::underlying_type_t<ItemType>>(ItemType::DRUID_ITEM) },
{ L"Hand to Hand", static_cast<std::underlying_type_t<ItemType>>(ItemType::HAND_TO_HAND) },
{ L"Orb", static_cast<std::underlying_type_t<ItemType>>(ItemType::ORB) },
{ L"Voodoo Heads", static_cast<std::underlying_type_t<ItemType>>(ItemType::VOODOO_HEADS) },
{ L"Auric Shields", static_cast<std::underlying_type_t<ItemType>>(ItemType::AURIC_SHIELDS) },
{ L"Primal Helm", static_cast<std::underlying_type_t<ItemType>>(ItemType::PRIMAL_HELM) },
{ L"Pelt", static_cast<std::underlying_type_t<ItemType>>(ItemType::PELT) },
{ L"Cloak", static_cast<std::underlying_type_t<ItemType>>(ItemType::CLOAK) },
{ L"Rune", static_cast<std::underlying_type_t<ItemType>>(ItemType::RUNE) },
{ L"Circlet", static_cast<std::underlying_type_t<ItemType>>(ItemType::CIRCLET) },
{ L"Healing Potion", static_cast<std::underlying_type_t<ItemType>>(ItemType::HEALING_POTION) },
{ L"Mana Potion", static_cast<std::underlying_type_t<ItemType>>(ItemType::MANA_POTION) },
{ L"Rejuv Potion", static_cast<std::underlying_type_t<ItemType>>(ItemType::REJUV_POTION) },
{ L"Stamina Potion", static_cast<std::underlying_type_t<ItemType>>(ItemType::STAMINA_POTION) },
{ L"Antidote Potion", static_cast<std::underlying_type_t<ItemType>>(ItemType::ANTIDOTE_POTION) },
{ L"Thawing Potion", static_cast<std::underlying_type_t<ItemType>>(ItemType::THAWING_POTION) },
{ L"Small Charm", static_cast<std::underlying_type_t<ItemType>>(ItemType::SMALL_CHARM) },
{ L"Medium Charm", static_cast<std::underlying_type_t<ItemType>>(ItemType::MEDIUM_CHARM) },
{ L"Large Charm", static_cast<std::underlying_type_t<ItemType>>(ItemType::LARGE_CHARM) },
{ L"Amazon Bow", static_cast<std::underlying_type_t<ItemType>>(ItemType::AMAZON_BOW) },
{ L"Amazon Spear", static_cast<std::underlying_type_t<ItemType>>(ItemType::AMAZON_SPEAR) },
{ L"Amazon Javelin", static_cast<std::underlying_type_t<ItemType>>(ItemType::AMAZON_JAVELIN) },
{ L"Hand to Hand 2", static_cast<std::underlying_type_t<ItemType>>(ItemType::HAND_TO_HAND_2) },
{ L"Magic Bow Quiv", static_cast<std::underlying_type_t<ItemType>>(ItemType::MAGIC_BOW_QUIV) },
{ L"Magic Xbow Quiv", static_cast<std::underlying_type_t<ItemType>>(ItemType::UNK) },
{ L"Chipped Gem", static_cast<std::underlying_type_t<ItemType>>(ItemType::CHIPPED_GEM) },
{ L"Flawed Gem", static_cast<std::underlying_type_t<ItemType>>(ItemType::FLAWED_GEM) },
{ L"Standard Gem", static_cast<std::underlying_type_t<ItemType>>(ItemType::STANDARD_GEM) },
{ L"Flawless Gem", static_cast<std::underlying_type_t<ItemType>>(ItemType::FLAWLESS_GEM) },
{ L"Perfect Gem", static_cast<std::underlying_type_t<ItemType>>(ItemType::PERFECT_GEM) },
{ L"Amethyst", static_cast<std::underlying_type_t<ItemType>>(ItemType::AMETHYST) },
{ L"Diamond", static_cast<std::underlying_type_t<ItemType>>(ItemType::DIAMOND) },
{ L"Emerald", static_cast<std::underlying_type_t<ItemType>>(ItemType::EMERALD) },
{ L"Ruby", static_cast<std::underlying_type_t<ItemType>>(ItemType::RUBY) },
{ L"Sapphire", static_cast<std::underlying_type_t<ItemType>>(ItemType::SAPPHIRE) },
{ L"Topaz", static_cast<std::underlying_type_t<ItemType>>(ItemType::TOPAZ) },
{ L"Skull", static_cast<std::underlying_type_t<ItemType>>(ItemType::SKULL) },
};

//pretty name for stats...
std::map<std::wstring, std::wstring> STAT_LOOKUP_TABLE = {
	{ L"\"Defense\"", fmt::format(L"Stat({})", Stat::ARMORCLASS) },
	{ L"\"Enhanced Damage\"", fmt::format(L"Stat({})", Stat::ITEM_MAXDAMAGE_PERCENT) },
	{ L"\"Enhanced Defense\"", fmt::format(L"Stat({})", Stat::ITEM_ARMOR_PERCENT) },
	{ L"\"Durability\"", fmt::format(L"Stat({})", Stat::ITEM_MAXDURABILITY_PERCENT) },
	{ L"\"Fire Resist\"", fmt::format(L"Stat({})", Stat::FIRERESIST) },
	{ L"\"Cold Resist\"", fmt::format(L"Stat({})", Stat::COLDRESIST) },
	{ L"\"Lightning Resist\"", fmt::format(L"Stat({})", Stat::LIGHTRESIST) },
	{ L"\"Poison Resist\"", fmt::format(L"Stat({})", Stat::POISONRESIST) },
	{ L"\"Increased Attack Speed\"", fmt::format(L"Stat({})", Stat::ITEM_FASTERATTACKRATE) },
	{ L"\"Faster Cast Rate\"", fmt::format(L"Stat({})", Stat::ITEM_FASTERCASTRATE) },
	{ L"\"Faster Hit Recovery\"", fmt::format(L"Stat({})", Stat::ITEM_FASTERGETHITRATE) },
	{ L"\"Faster Run Walk\"", fmt::format(L"Stat({})", Stat::ITEM_FASTERMOVEVELOCITY) },
	{ L"\"Life\"", fmt::format(L"Stat({})", Stat::MAXHP) },
	{ L"\"Mana\"", fmt::format(L"Stat({})", Stat::MAXMANA) },
	{ L"\"Required Level\"", fmt::format(L"Stat({})", Stat::ITEM_LEVELREQ) },
	{ L"\"Magic Find\"", fmt::format(L"Stat({})", Stat::ITEM_MAGICBONUS) },
	{ L"\"Gold Find\"", fmt::format(L"Stat({})", Stat::ITEM_GOLDBONUS) },
	{ L"\"Strength\"", fmt::format(L"Stat({})", Stat::STRENGTH) },
	{ L"\"Dexterity\"", fmt::format(L"Stat({})", Stat::DEXTERITY) },
	{ L"\"Vitality\"", fmt::format(L"Stat({})", Stat::VITALITY) },
	{ L"\"Energy\"", fmt::format(L"Stat({})", Stat::ENERGY) },
	{ L"\"Mana After Each Kill\"", fmt::format(L"Stat({})", Stat::ITEM_MANAAFTERKILL) },
	{ L"\"Attack Rating\"", fmt::format(L"Stat({})", Stat::TOHIT) },
	{ L"\"Minimum Damage\"", fmt::format(L"Stat({})", Stat::MINDAMAGE) },
	{ L"\"Maximum Damage\"", fmt::format(L"Stat({})", Stat::MAXDAMAGE) },
	{ L"\"Repairs Durability\"", fmt::format(L"Stat({})", Stat::ITEM_REPLENISH_DURABILITY) },
	{ L"\"All Resist\"", fmt::format(L"MinIn(Stat({}),Stat({}),Stat({}),Stat({}))", Stat::FIRERESIST, Stat::COLDRESIST, Stat::LIGHTRESIST, Stat::POISONRESIST) },
	{ L"\"Any Resist\"", fmt::format(L"Max(Stat({}),Stat({}),Stat({}),Stat({}))", Stat::FIRERESIST, Stat::COLDRESIST, Stat::LIGHTRESIST, Stat::POISONRESIST) }
};