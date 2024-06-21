#include "Condition.h"
#include "Utils.h"
#include "Globals.h"
#include <algorithm>

bool CodeCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(GetItemsTxt(pItem)->dwCode);
	return m_Expression->Evaluate(pItem);
}

void CodeCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool TypeCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(GetItemsTxt(pItem)->dwCode);
	return m_Expression->Evaluate(pItem);
}

void TypeCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool PlayerClassCondition::Evaluate(Unit* pItem) {
	Unit* pUnit = D2CLIENT_GetPlayerUnit();
	m_Left.SetValue(static_cast<int32_t>(pUnit->dwClassId));
	return m_Expression->Evaluate(pItem);
}

void PlayerClassCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool ClassCondition::Evaluate(Unit* pItem) {
	return m_Expression->Evaluate(pItem);
}

void ClassCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::ParseCall(m_Value.c_str(), Token::CLASS);
	m_Expression->SetVariables(variables);
};

bool RarityCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(static_cast<int32_t>(pItem->pItemData->dwRarity));
	return m_Expression->Evaluate(pItem);
}

void RarityCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool EtherealCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue((pItem->pItemData->dwItemFlags & ItemFlags::ETHEREAL) == ItemFlags::ETHEREAL);
	return m_Expression->Evaluate(pItem);
}

void EtherealCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool RunewordCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue((pItem->pItemData->dwItemFlags & ItemFlags::RUNEWORD) == ItemFlags::RUNEWORD);
	return m_Expression->Evaluate(pItem);
}

void RunewordCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool PrefixCondition::Evaluate(Unit* pItem) {
	uint8_t isIdentified = (pItem->pItemData->dwItemFlags & ItemFlags::IDENTIFIED) == ItemFlags::IDENTIFIED;
	if (!isIdentified) {
		return false;
	}
	for (auto& prefix : pItem->pItemData->wMagicPrefix) {
		m_Left.SetValue(prefix);
		if (m_Expression->Evaluate(pItem)) {
			return true;
		}
	}
	return false;
}

void PrefixCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool SuffixCondition::Evaluate(Unit* pItem) {
	uint8_t isIdentified = (pItem->pItemData->dwItemFlags & ItemFlags::IDENTIFIED) == ItemFlags::IDENTIFIED;
	if (!isIdentified) {
		return false;
	}
	for (auto& prefix : pItem->pItemData->wMagicSuffix) {
		m_Left.SetValue(prefix);
		if (m_Expression->Evaluate(pItem)) {
			return true;
		}
	}
	return false;
}

void SuffixCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool ItemLevelCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(pItem->pItemData->dwItemLevel);
	return m_Expression->Evaluate(pItem);
}

void ItemLevelCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool QualityCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(GetQualityLevel(pItem));
	return m_Expression->Evaluate(pItem);
}

void QualityCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool AreaLevelCondition::Evaluate(Unit* pItem) {
	return false;
}

void AreaLevelCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool CharacterLevelCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(D2COMMON_STATLIST_GetUnitStatUnsigned(D2CLIENT_GetPlayerUnit(), Stat::LEVEL, 0));
	return m_Expression->Evaluate(pItem);
}

void CharacterLevelCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool DifficultyCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(D2CLIENT_GetDifficulty());
	return m_Expression->Evaluate(pItem);
}

void DifficultyCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool RuneCondition::Evaluate(Unit* pItem) {
	if (!D2COMMON_ITEMS_CheckItemTypeId(pItem, ItemType::RUNE)) {
		return false;
	}
	int nRuneNumber = std::stoi(std::string(&GetItemsTxt(pItem)->szCode[1], 3));
	m_Left.SetValue(nRuneNumber);
	return m_Expression->Evaluate(pItem);
}

void RuneCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool IdCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(pItem->dwLineId);
	return m_Expression->Evaluate(pItem);
}

void IdCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool GoldCondition::Evaluate(Unit* pItem) {
	if (!D2COMMON_ITEMS_CheckItemTypeId(pItem, ItemType::GOLD)) {
		return false;
	}
	m_Left.SetValue(D2COMMON_STATLIST_GetUnitStatUnsigned(pItem, Stat::GOLD, 0));
	return m_Expression->Evaluate(pItem);
}

void GoldCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool StatsCondition::Evaluate(Unit* pItem) {
	return m_Expression->Evaluate(pItem);
}

void StatsCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	for (const auto& stat : CustomStats) {
		replace(m_Value, stat.first, stat.second);
	}
	m_Expression = Parser::Parse(m_Value.c_str());
	m_Expression->SetVariables(variables);
};

bool DefenseCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(D2COMMON_STATLIST_GetUnitStatUnsigned(pItem, Stat::ARMORCLASS, 0));
	return m_Expression->Evaluate(pItem);
}

void DefenseCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool ArmorCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(D2COMMON_ITEMS_CheckItemTypeId(pItem, ItemType::ANY_ARMOR));
	return m_Expression->Evaluate(pItem);
}

void ArmorCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool WeaponCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(D2COMMON_ITEMS_CheckItemTypeId(pItem, ItemType::WEAPON));
	return m_Expression->Evaluate(pItem);
}

void WeaponCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool PriceCondition::Evaluate(Unit* pItem) {
	Unit* pPlayer = D2CLIENT_GetPlayerUnit();
	if (pItem != NULL && pPlayer != NULL) {
		int nPrice = D2COMMON_ITEMS_GetTransactionCost(pPlayer, pItem, D2CLIENT_GetDifficulty(), D2CLIENT_GetQuestFlags(), 0x201, 1);
		m_Left.SetValue(nPrice);
		return m_Expression->Evaluate(pItem);
	}
	return false;
}

void PriceCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool ModeCondition::Evaluate(Unit* pItem) {
	return false;
}

void ModeCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool IdentifiedCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue((pItem->pItemData->dwItemFlags & ItemFlags::IDENTIFIED) == ItemFlags::IDENTIFIED);
	return m_Expression->Evaluate(pItem);
}

void IdentifiedCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool SocketsCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(D2COMMON_STATLIST_GetUnitStatUnsigned(pItem, Stat::ITEM_NUMSOCKETS, 0));
	return m_Expression->Evaluate(pItem);
}

void SocketsCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool WidthCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(GetItemsTxt(pItem)->nInvWidth);
	return m_Expression->Evaluate(pItem);
}

void WidthCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool HeightCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(GetItemsTxt(pItem)->nInvHeight);
	return m_Expression->Evaluate(pItem);
}

void HeightCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool RandomCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(rand() % 100);	//random between 0-99
	return m_Expression->Evaluate(pItem);
}

void RandomCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool OwnedCondition::Evaluate(Unit* pItem) {
	//only check set/unique items for duplicates
	if (pItem->pItemData->dwRarity != ItemRarity::SET
		&& pItem->pItemData->dwRarity != ItemRarity::UNIQUE) {
		return false;
	}

	Unit* pPlayer = D2CLIENT_GetPlayerUnit();
	if (!pPlayer || !pPlayer->pInventory) {
		return false;
	}

	int32_t unitId = pItem->dwUnitId;
	int32_t fileIndex = pItem->pItemData->dwFileIndex;
	ItemRarity rarity = pItem->pItemData->dwRarity;
	int value = 0;
	
	for (int i = 0; i < 128; i++) {
		Unit* pOtherItem = FindUnitFromTable(i, UnitType::ITEM);
		while (pOtherItem) {
			if (pOtherItem->pItemData->dwRarity != ItemRarity::SET
				&& pOtherItem->pItemData->dwRarity != ItemRarity::UNIQUE) {
				pOtherItem = pOtherItem->pRoomNext;
				continue;
			}
			if (fileIndex == pOtherItem->pItemData->dwFileIndex
				&& pItem->pItemData->dwRarity == pOtherItem->pItemData->dwRarity
				&& unitId != pOtherItem->dwUnitId) {
				value = 1;
				break;
			}
			pOtherItem = pOtherItem->pRoomNext;
		}
		if (value == 1) {
			break;
		}
	}

	m_Left.SetValue(value);
	return m_Expression->Evaluate(pItem);
}

void OwnedCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
};

bool HasWeightCondition::Evaluate(Unit* pItem) {
	m_Left.SetValue(ITEM_ACTIONS[pItem->dwUnitId].nWeight);
	return m_Expression->Evaluate(pItem);
}

void HasWeightCondition::Initialize(const utility::string_umap<std::wstring, int32_t>& variables) {
	m_Expression = Parser::Parse(m_Value.c_str(), &m_Left);
	m_Expression->SetVariables(variables);
}
