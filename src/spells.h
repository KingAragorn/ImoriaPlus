// Copyright (c) 1981-86 Robert A. Koeneke
// Copyright (c) 1987-94 James E. Wilson
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

// spell types used by get_flags(), breathe(), fire_bolt() and fire_ball()
enum MagicSpellFlags {
    MagicMissile,
    Lightning,
    PoisonGas,
    Acid,
    Frost,
    Fire,
    HolyOrb,
};

// Spell effects shared by mage, prayer, song, druid, and monk lists.
enum SpellEffect {
    SE_NONE = 0,
    SE_GENERIC,
    SE_BOLT_MISSILE,
    SE_BOLT_LIGHTNING,
    SE_BOLT_FROST,
    SE_BOLT_FIRE,
    SE_BALL_POISON,
    SE_BALL_FROST,
    SE_BALL_FIRE,
    SE_BALL_LIGHTNING,
    SE_DETECT_MONSTERS,
    SE_DETECT_EVIL,
    SE_DETECT_TRAPS,
    SE_DETECT_DOORS,
    SE_DETECT_INVIS,
    SE_DETECT_TREASURE,
    SE_DETECT_OBJECTS,
    SE_DETECT_MAGIC,
    SE_PHASE_DOOR,
    SE_TELEPORT,
    SE_TELEPORT_AWAY,
    SE_TELEPORT_LEVEL,
    SE_LIGHT,
    SE_CURE_LIGHT,
    SE_CURE_MEDIUM,
    SE_CURE_SERIOUS,
    SE_CURE_CRITICAL,
    SE_HEAL,
    SE_CURE_POISON,
    SE_SLOW_POISON,
    SE_REMOVE_FEAR,
    SE_BLESS,
    SE_HERO,
    SE_CONFUSE,
    SE_SLEEP,
    SE_SLEEP_ALL,
    SE_DESTROY_TRAPS,
    SE_STONE_MUD,
    SE_CREATE_FOOD,
    SE_INFRA,
    SE_INVIS,
    SE_REMOVE_CURSE,
    SE_RECHARGE,
    SE_IDENTIFY,
    SE_POLYMORPH,
    SE_SLOW_MONSTER,
    SE_HOLD_MONSTER,
    SE_HASTE,
    SE_GENOCIDE,
    SE_TURN_UNDEAD,
    SE_DISPEL_UNDEAD,
    SE_DISPEL_EVIL,
    SE_DISPEL_MONSTER,
    SE_EARTHQUAKE,
    SE_PROTECT_EVIL,
    SE_WARDING,
    SE_MAP,
    SE_WORD_RECALL,
    SE_SUMMON,
    SE_RESIST,
    SE_STEALTH,
    SE_FREE_ACTION,
    SE_CHARM,
    SE_BLIND,
    SE_FOOD_FULL,
    SE_DESTRUCTION,
    SE_KILL,
    SE_FEAR_MONSTER,
};

// Spell_t is a base data object.
// Holds the base game data for a spell, including its Imoria name.
typedef struct {
    uint8_t level_required;
    uint8_t mana_required;
    uint8_t failure_chance;
    uint8_t exp_gain_for_learning; // 1/4 of exp gained for learning spell
    uint8_t effect;
    const char *name;
} Spell_t;

extern Spell_t magic_spells[PLAYER_MAX_CLASSES][PLAYER_MAX_SPELLS];
extern const char *spell_names[62];

// Realm helpers. class_id is the 0-based player class.
int classSpellStat(uint8_t class_id);
const char *classSpellNoun(uint8_t class_id);
const char *classSpellVerb(uint8_t class_id);
bool classChoosesSpells(uint8_t class_id);
bool classLearnsFromBook(uint8_t class_id);
uint8_t classBookCategory(uint8_t class_id);
uint64_t bookSpellMask(const Inventory_t &item);
uint64_t classKnownSpellMask();

int castSpellGetId(const char *prompt, int item_id, int &spell_id, int &spell_chance);
int castSpellChooseFromMask(const char *prompt, uint64_t spell_mask, int first_spell, int &spell_id, int &spell_chance);
void castSpellEffect(const Spell_t &spell);
void playerCastRealm(bool prayer_key);

bool spellDetectTreasureWithinVicinity();
bool spellDetectObjectsWithinVicinity();
bool spellDetectTrapsWithinVicinity();
bool spellDetectSecretDoorssWithinVicinity();
bool spellDetectInvisibleCreaturesWithinVicinity();
bool spellLightArea(Coord_t coord);
bool spellDarkenArea(Coord_t coord);
void spellMapCurrentArea();
bool spellIdentifyItem();
bool spellAggravateMonsters(int affect_distance);
bool spellSurroundPlayerWithTraps();
bool spellSurroundPlayerWithDoors();
bool spellDestroyAdjacentDoorsTraps();
bool spellDetectMonsters();
void spellLightLine(Coord_t coord, int direction);
void spellStarlite(Coord_t coord);
bool spellDisarmAllInDirection(Coord_t coord, int direction);
void spellFireBolt(Coord_t coord, int direction, int damage_hp, int spell_type, const std::string &spell_name);
void spellFireBall(Coord_t coord, int direction, int damage_hp, int spell_type, const std::string &spell_name);
void spellBreath(Coord_t coord, int monster_id, int damage_hp, int spell_type, const std::string &spell_name);
bool spellRechargeItem(int number_of_charges);
bool spellChangeMonsterHitPoints(Coord_t coord, int direction, int damage_hp);
bool spellDrainLifeFromMonster(Coord_t coord, int direction);
bool spellSpeedMonster(Coord_t coord, int direction, int speed);
bool spellConfuseMonster(Coord_t coord, int direction);
bool spellSleepMonster(Coord_t coord, int direction);
bool spellWallToMud(Coord_t coord, int direction);
bool spellDestroyDoorsTrapsInDirection(Coord_t coord, int direction);
bool spellPolymorphMonster(Coord_t coord, int direction);
bool spellBuildWall(Coord_t coord, int direction);
bool spellCloneMonster(Coord_t coord, int direction);
void spellTeleportAwayMonster(int monster_id, int distance_from_player);
void spellTeleportPlayerTo(Coord_t coord);
bool spellTeleportAwayMonsterInDirection(Coord_t coord, int direction);
bool spellMassGenocide();
bool spellGenocide();
bool spellSpeedAllMonsters(int speed);
bool spellSleepAllMonsters();
bool spellMassPolymorph();
bool spellDetectEvil();
bool spellChangePlayerHitPoints(int adjustment);
void spellEarthquake();
void spellCreateFood();
bool spellDispelCreature(int creature_defense, int damage);
bool spellTurnUndead();
void spellWardingGlyph();
void spellLoseSTR();
void spellLoseINT();
void spellLoseWIS();
void spellLoseDEX();
void spellLoseCON();
void spellLoseCHR();
void spellLoseEXP(int32_t adjustment);
bool spellSlowPoison();
void spellDestroyArea(Coord_t coord);
bool spellEnchantItem(int16_t &plusses, int16_t max_bonus_limit);
bool spellRemoveCurseFromAllWornItems();
bool spellRestorePlayerLevels();
