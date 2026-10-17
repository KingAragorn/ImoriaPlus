// Copyright (c) 1981-86 Robert A. Koeneke
// Copyright (c) 1987-94 James E. Wilson
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Player character data

// clang-format off
#include "headers.h"

// Class rank titles for different levels
ClassRankTitle_t class_rank_titles[PLAYER_MAX_CLASSES][PLAYER_MAX_LEVEL] = {
    // Warrior
    {"Rookie",       "Private",      "Soldier",      "Mercenary",
     "Veteran(1st)", "Veteran(2nd)", "Veteran(3rd)", "Warrior(1st)",
     "Warrior(2nd)", "Warrior(3rd)", "Warrior(4th)", "Swordsman-1",
     "Swordsman-2",  "Swordsman-3",  "Hero",         "Swashbuckler",
     "Myrmidon",     "Champion-1",   "Champion-2",   "Champion-3",
     "Superhero",    "Knight",       "Superior Knt", "Gallant Knt",
     "Knt Errant",   "Guardian Knt", "Baron",        "Duke",
     "Lord (1st)",   "Lord (2nd)",   "Lord (3rd)",   "Lord (4th)",
     "Lord (5th)",   "Lord (6th)",   "Lord (7th)",   "Lord (8th)",
     "Lord (9th)",   "Lord Gallant", "Lord Keeper",  "Lord Noble"},
    // Mage
    {"Novice",       "Apprentice",   "Trickster-1",  "Trickster-2",
     "Trickster-3",  "Cabalist-1",   "Cabalist-2",   "Cabalist-3",
     "Visionist",    "Phantasmist",  "Shadowist",    "Spellbinder",
     "Illusionist",  "Evoker (1st)", "Evoker (2nd)", "Evoker (3rd)",
     "Evoker (4th)", "Conjurer",     "Theurgist",    "Thaumaturge",
     "Magician",     "Enchanter",    "Warlock",      "Sorcerer",
     "Necromancer",  "Mage (1st)",   "Mage (2nd)",   "Mage (3rd)",
     "Mage (4th)",   "Mage (5th)",   "Wizard (1st)", "Wizard (2nd)",
     "Wizard (3rd)", "Wizard (4th)", "Wizard (5th)", "Wizard (6th)",
     "Wizard (7th)", "Wizard (8th)", "Wizard (9th)", "Wizard Lord"},
    // Priests
    {"Believer",     "Acolyte(1st)", "Acolyte(2nd)", "Acolyte(3rd)",
     "Adept (1st)",  "Adept (2nd)",  "Adept (3rd)",  "Priest (1st)",
     "Priest (2nd)", "Priest (3rd)", "Priest (4th)", "Priest (5th)",
     "Priest (6th)", "Priest (7th)", "Priest (8th)", "Priest (9th)",
     "Curate (1st)", "Curate (2nd)", "Curate (3rd)", "Curate (4th)",
     "Curate (5th)", "Curate (6th)", "Curate (7th)", "Curate (8th)",
     "Curate (9th)", "Canon (1st)",  "Canon (2nd)",  "Canon (3rd)",
     "Canon (4th)",  "Canon (5th)",  "Low Lama",     "Lama-1",
     "Lama-2",       "Lama-3",       "High Lama",    "Great Lama",
     "Patriarch",    "High Priest",  "Great Priest", "Noble Priest"},
    // Rogues
    {"Vagabond",     "Footpad",     "Cutpurse",      "Robber",
     "Burglar",      "Filcher",     "Sharper",       "Magsman",
     "Common Rogue", "Rogue (1st)", "Rogue (2nd)",   "Rogue (3rd)",
     "Rogue (4th)",  "Rogue (5th)", "Rogue (6th)",   "Rogue (7th)",
     "Rogue (8th)",  "Rogue (9th)", "Master Rogue",  "Expert Rogue",
     "Senior Rogue", "Chief Rogue", "Prime Rogue",   "Low Thief",
     "Thief (1st)",  "Thief (2nd)", "Thief (3rd)",   "Thief (4th)",
     "Thief (5th)",  "Thief (6th)", "Thief (7th)",   "Thief (8th)",
     "Thief (9th)",  "High Thief",  "Master Thief",  "Executioner",
     "Low Assassin", "Assassin",    "High Assassin", "Guildsmaster"},
    // Rangers
    {"Runner (1st)",  "Runner (2nd)",  "Runner (3rd)",  "Strider (1st)",
     "Strider (2nd)", "Strider (3rd)", "Scout (1st)",   "Scout (2nd)",
     "Scout (3rd)",   "Scout (4th)",   "Scout (5th)",   "Courser (1st)",
     "Courser (2nd)", "Courser (3rd)", "Courser (4th)", "Courser (5th)",
     "Tracker (1st)", "Tracker (2nd)", "Tracker (3rd)", "Tracker (4th)",
     "Tracker (5th)", "Tracker (6th)", "Tracker (7th)", "Tracker (8th)",
     "Tracker (9th)", "Guide (1st)",   "Guide (2nd)",   "Guide (3rd)",
     "Guide (4th)",   "Guide (5th)",   "Guide (6th)",   "Guide (7th)",
     "Guide (8th)",   "Guide (9th)",   "Pathfinder-1",  "Pathfinder-2",
     "Pathfinder-3",  "Ranger",        "High Ranger",   "Ranger Lord"},
    // Paladins
    {"Gallant",      "Keeper (1st)", "Keeper (2nd)", "Keeper (3rd)",
     "Keeper (4th)", "Keeper (5th)", "Keeper (6th)", "Keeper (7th)",
     "Keeper (8th)", "Keeper (9th)", "Protector-1",  "Protector-2",
     "Protector-3",  "Protector-4",  "Protector-5",  "Protector-6",
     "Protector-7",  "Protector-8",  "Defender-1",   "Defender-2",
     "Defender-3",   "Defender-4",   "Defender-5",   "Defender-6",
     "Defender-7",   "Defender-8",   "Warder (1st)", "Warder (2nd)",
     "Warder (3rd)", "Warder (4th)", "Warder (5th)", "Warder (6th)",
     "Warder (7th)", "Warder (8th)", "Warder (9th)", "Guardian",
     "Chevalier",    "Justiciar",    "Paladin",      "High Lord"},
    // Druids. Imoria's "Ovate(3th)" and "LowHierophant" are spelled out.
    {"Aspirant-1",    "Aspirant-2",    "Ovate (1st)",   "Ovate (2nd)",
     "Ovate (3rd)",   "Initiate-1",    "Initiate-2",    "1st Cabal",
     "2nd Cabal",     "3rd Cabal",     "4th Cabal",     "5th Cabal",
     "6th Cabal",     "7th Cabal",     "8th Cabal",     "9th Cabal",
     "10th Cabal",    "11th Cabal",    "12th Cabal",    "13th Cabal",
     "Low Druid",     "Druid (1st)",   "Druid (2nd)",   "Druid (3rd)",
     "Druid (4th)",   "Druid (5th)",   "Druid (6th)",   "Adept Druid",
     "Arch Druid",    "Great Druid",   "Master Druid",  "Grand Druid",
     "Lord Druid",    "Low Hierophant","Hierophant-1",  "Hierophant-2",
     "Hierophant-3",  "Hierophant-4",  "Hierophant-5",  "Forest Master"},
    // Bards
    {"Singer",        "Rhymer",        "Joker",         "Lyrist (1st)",
     "Lyrist (2nd)",  "Lyrist (3rd)",  "Jester (1st)",  "Jester (2nd)",
     "Sonnateer-1",   "Sonnateer-2",   "Sonnateer-3",   "Skald (1st)",
     "Skald (2nd)",   "Skald (3rd)",   "Comic (1st)",   "Comic (2nd)",
     "Comic (3rd)",   "Racaraide-1",   "Racaraide-2",   "Racaraide-3",
     "Joungleur-1",   "Joungleur-2",   "Joungleur-3",   "Minstrel-1",
     "Minstrel-2",    "Minstrel-3",    "Muse (1st)",    "Muse (2nd)",
     "Muse (3rd)",    "Lorist (1st)",  "Lorist (2nd)",  "Lorist (3rd)",
     "Initiate Bard", "Bard (1st)",    "Bard (2nd)",    "Bard (3rd)",
     "Master Bard-1", "Master Bard-2", "Master Bard-3", "Bardic Sage"},
    // Adventurers. Packed Imoria titles are given spaces.
    {"Dimwit",        "Beginner",      "Amateur",       "Flathead",
     "Pile of Leaves","Novice",        "Brass Bell",    "Orange Cake",
     "White Unicorn", "Charlatan",     "Clove of Garlic","Nasty Knife",
     "Parlor Magician","Gaudy Crown",  "Loaf of Bread", "Lurking Grue",
     "Noisome Stew",  "Broken Timber", "Granite Wall",  "FCD #3",
     "Adventurer-1",  "Adventurer-2",  "Adventurer-3",  "AIMFIZ Scroll",
     "VILSTU Potion", "Sr Adventurer", "Master Advnt",  "Wiz of Frobozz",
     "Enchanter",     "Sorcerer",      "Wizard (1st)",  "Wizard (2nd)",
     "Wizard (3rd)",  "Wizard (4th)",  "Wizard (5th)",  "Wizard (6th)",
     "Wizard (7th)",  "Zorkmid Coin",  "Dungeon Master","Implementer"},
    // Monks
    {"Disciple",      "Acolyte (1st)", "Acolyte (2nd)", "Acolyte (3rd)",
     "Neophyte (1st)","Neophyte (2nd)","Neophyte (3rd)","Neophyte (4th)",
     "Adept (1st)",   "Adept (2nd)",   "Adept (3rd)",   "Hermit (1st)",
     "Hermit (2nd)",  "Hermit (3rd)",  "Hermit (4th)",  "Hermit (5th)",
     "Curate (1st)",  "Curate (2nd)",  "Curate (3rd)",  "Curate (4th)",
     "Curate (5th)",  "Curate (6th)",  "Curate (7th)",  "Curate (8th)",
     "Curate (9th)",  "Master (1st)",  "Master (2nd)",  "Master (3rd)",
     "Master (4th)",  "Master (5th)",  "Superior Master","Low Lama",
     "High Lama",     "Great Lama",    "Dancing Llama", "Holy Man",
     "Hi-YA Man",     "Baby Buddha",   "Budding Buddha","Buddha"},
};

// Race, STR, INT, WIS, DEX, CON, CHR,
//   ages, heights, and weights (male then female)
// Racial Bases for:
//   dis, chance_in_search, stealth_factor, fos, bth, bth_with_bows, saving_throw_base,
//   hit_die, infra, exp base, choice-classes
// Imoria values.inc race records. Infra for Elf and Half-Elf is 0 there;
// infravision is a spell. Class bits are Imoria's 10-wide mask, LSB = Warrior.
//   Monk Adventurer Bard Druid Paladin Ranger Rogue Priest Mage Warrior
Race_t character_races[PLAYER_MAX_RACES] = {
    {
        "Human", 0,  0,  0,  0,  0,  0,
        14,  6, 72,  6,180, 25, 66,  4,120, 20,
        0,  0,  0,  0,  0,  0,  0, 10,  0, 100, 0x3FF,
    },
    {
        "Half-Elf", -1,  1,  0,  1, -1,  1,
        24, 16, 66,  6,130, 15, 62,  6,100, 10,
        2,  6,  1, -1,  0,  5,  3,  9,  0, 110, 0x3FF,
    },
    {
        "Elf", -1,  2,  1,  1, -2,  1,
        75, 75, 60,  4,100,  6, 54,  4, 80,  6,
        5,  8,  1, -2, -5, 15,  6,  8,  0, 120, 0x1DF,
    },
    {
        "Halfling", -2,  2,  1,  3,  1,  1,
        21, 12, 36,  3, 60,  3, 33,  3, 50,  3,
        15, 12,  4, -5,-10, 20, 18,  6,  4, 110, 0x2CA,
    },
    {
        "Gnome", -1,  2,  0,  2,  1, -2,
        50, 40, 42,  3, 90,  6, 39,  3, 75,  3,
        10,  6,  3, -3, -8, 12, 12,  7,  3, 125, 0x04E,
    },
    {
        "Dwarf", 2, -3,  1, -2,  2, -3,
        35, 15, 48,  3,150, 10, 46,  3,120, 10,
        2,  7,   0,  0, 15,  0,  9,  9,  5, 120, 0x045,
    },
    {
        "Half-Orc", 2, -1,  0,  0,  1, -4,
        11,  4, 66,  1,150,  5, 62,  1,120,  5,
        -3,  0, -1,  3, 12, -5, -3, 10,  3, 110, 0x20D,
    },
    {
        "Half-Troll", 4, -4, -3, -4,  4, -6,
        20, 10, 96, 10,300, 50, 84,  8,260, 40,
        -5, -1, -2,  5, 20,-10, -9, 12,  3, 120, 0x005,
    },
    {
        "Phraint", 0,  0, -4,  5,  0, -3,
        15, 10, 96, 24,100, 20, 84, 12, 95, 16,
        15, 10,  5,  4,  3,  5, -3,  8,  5, 120, 0x39B,
    },
    {
        "Dryad", -1,  0,  3,  0, -2,  3,
        75, 75, 60,  4, 85,  6, 40,  4, 70,  6,
        2,  6,  1, -1,  0,  5,  3,  7,  3, 120, 0x2D4,
    },
};

// Background information
Background_t character_backgrounds[PLAYER_MAX_BACKGROUNDS] = {
    {"You are the illegitimate and unacknowledged child ",   10,  1,  2,  25},
    {"You are the illegitimate but acknowledged child ",     20,  1,  2,  35},
    {"You are one of several children ",                     95,  1,  2,  45},
    {"You are the first child ",                            100,  1,  2,  50},
    {"of a Serf.  ",                                         40,  2,  3,  65},
    {"of a Yeoman.  ",                                       65,  2,  3,  80},
    {"of a Townsman.  ",                                     80,  2,  3,  90},
    {"of a Guildsman.  ",                                    90,  2,  3, 105},
    {"of a Landed Knight.  ",                                96,  2,  3, 120},
    {"of a Titled Noble.  ",                                 99,  2,  3, 130},
    {"of a Royal Blood Line.  ",                            100,  2,  3, 140},
    {"You are the black sheep of the family.  ",             20,  3, 50,  20},
    {"You are a credit to the family.  ",                    80,  3, 50,  55},
    {"You are a well liked child.  ",                       100,  3, 50,  60},
    {"Your mother was a Green-Elf.  ",                       40,  4,  1,  50},
    {"Your father was a Green-Elf.  ",                       75,  4,  1,  55},
    {"Your mother was a Grey-Elf.  ",                        90,  4,  1,  55},
    {"Your father was a Grey-Elf.  ",                        95,  4,  1,  60},
    {"Your mother was a High-Elf.  ",                        98,  4,  1,  65},
    {"Your father was a High-Elf.  ",                       100,  4,  1,  70},
    {"You are one of several children ",                     60,  7,  8,  50},
    {"You are the only child ",                             100,  7,  8,  55},
    {"of a Green-Elf ",                                      75,  8,  9,  50},
    {"of a Grey-Elf ",                                       95,  8,  9,  55},
    {"of a High-Elf ",                                      100,  8,  9,  60},
    {"Ranger.  ",                                            40,  9, 54,  80},
    {"Archer.  ",                                            70,  9, 54,  90},
    {"Warrior.  ",                                           87,  9, 54, 110},
    {"Mage.  ",                                              95,  9, 54, 125},
    {"Prince.  ",                                            99,  9, 54, 140},
    {"King.  ",                                             100,  9, 54, 145},
    {"You are one of several children of a Halfling ",       85, 10, 11,  45},
    {"You are the only child of a Halfling ",               100, 10, 11,  55},
    {"Bum.  ",                                               20, 11,  3,  55},
    {"Tavern Owner.  ",                                      30, 11,  3,  80},
    {"Miller.  ",                                            40, 11,  3,  90},
    {"Home Owner.  ",                                        50, 11,  3, 100},
    {"Burglar.  ",                                           80, 11,  3, 110},
    {"Warrior.  ",                                           95, 11,  3, 115},
    {"Mage.  ",                                              99, 11,  3, 125},
    {"Clan Elder.  ",                                       100, 11,  3, 140},
    {"You are one of several children of a Gnome ",          85, 13, 14,  45},
    {"You are the only child of a Gnome ",                  100, 13, 14,  55},
    {"Beggar.  ",                                            20, 14,  3,  55},
    {"Braggart.  ",                                          50, 14,  3,  70},
    {"Prankster.  ",                                         75, 14,  3,  85},
    {"Warrior.  ",                                           95, 14,  3, 100},
    {"Mage.  ",                                             100, 14,  3, 125},
    {"You are one of two children of a Dwarven ",            25, 16, 17,  40},
    {"You are the only child of a Dwarven ",                100, 16, 17,  50},
    {"Thief.  ",                                             10, 17, 18,  60},
    {"Prison Guard.  ",                                      25, 17, 18,  75},
    {"Miner.  ",                                             75, 17, 18,  90},
    {"Warrior.  ",                                           90, 17, 18, 110},
    {"Priest.  ",                                            99, 17, 18, 130},
    {"King.  ",                                             100, 17, 18, 150},
    {"You are the black sheep of the family.  ",             15, 18, 57,  10},
    {"You are a credit to the family.  ",                    85, 18, 57,  50},
    {"You are a well liked child.  ",                       100, 18, 57,  55},
    {"Your mother was an Orc, but it is unacknowledged.  ",  25, 19, 20,  25},
    {"Your father was an Orc, but it is unacknowledged.  ", 100, 19, 20,  25},
    {"You are the adopted child ",                          100, 20,  2,  50},
    {"Your mother was a Cave-Troll ",                        30, 22, 23,  20},
    {"Your father was a Cave-Troll ",                        60, 22, 23,  25},
    {"Your mother was a Hill-Troll ",                        75, 22, 23,  30},
    {"Your father was a Hill-Troll ",                        90, 22, 23,  35},
    {"Your mother was a Water-Troll ",                       95, 22, 23,  40},
    {"Your father was a Water-Troll ",                      100, 22, 23,  45},
    {"Cook.  ",                                               5, 23, 62,  60},
    {"Warrior.  ",                                           95, 23, 62,  55},
    {"Shaman.  ",                                            99, 23, 62,  65},
    {"Clan Chief.  ",                                       100, 23, 62,  80},
    {"You have dark brown eyes, ",                           20, 50, 51,  50},
    {"You have brown eyes, ",                                60, 50, 51,  50},
    {"You have hazel eyes, ",                                70, 50, 51,  50},
    {"You have green eyes, ",                                80, 50, 51,  50},
    {"You have blue eyes, ",                                 90, 50, 51,  50},
    {"You have blue-gray eyes, ",                           100, 50, 51,  50},
    {"straight ",                                            70, 51, 52,  50},
    {"wavy ",                                                90, 51, 52,  50},
    {"curly ",                                              100, 51, 52,  50},
    {"black hair, ",                                         30, 52, 53,  50},
    {"brown hair, ",                                         70, 52, 53,  50},
    {"auburn hair, ",                                        80, 52, 53,  50},
    {"red hair, ",                                           90, 52, 53,  50},
    {"blond hair, ",                                        100, 52, 53,  50},
    {"and a very dark complexion.",                          10, 53,  0,  50},
    {"and a dark complexion.",                               30, 53,  0,  50},
    {"and an average complexion.",                           80, 53,  0,  50},
    {"and a fair complexion.",                               90, 53,  0,  50},
    {"and a very fair complexion.",                         100, 53,  0,  50},
    {"You have light grey eyes, ",                           85, 54, 55,  50},
    {"You have light blue eyes, ",                           95, 54, 55,  50},
    {"You have light green eyes, ",                         100, 54, 55,  50},
    {"straight ",                                            75, 55, 56,  50},
    {"wavy ",                                               100, 55, 56,  50},
    {"black hair, and a fair complexion.",                   75, 56,  0,  50},
    {"brown hair, and a fair complexion.",                   85, 56,  0,  50},
    {"blond hair, and a fair complexion.",                   95, 56,  0,  50},
    {"silver hair, and a fair complexion.",                 100, 56,  0,  50},
    {"You have dark brown eyes, ",                           99, 57, 58,  50},
    {"You have glowing red eyes, ",                         100, 57, 58,  60},
    {"straight ",                                            90, 58, 59,  50},
    {"wavy ",                                               100, 58, 59,  50},
    {"black hair, ",                                         75, 59, 60,  50},
    {"brown hair, ",                                        100, 59, 60,  50},
    {"a one foot beard, ",                                   25, 60, 61,  50},
    {"a two foot beard, ",                                   60, 60, 61,  51},
    {"a three foot beard, ",                                 90, 60, 61,  53},
    {"a four foot beard, ",                                 100, 60, 61,  55},
    {"and a dark complexion.",                              100, 61,  0,  50},
    {"You have slime green eyes, ",                          60, 62, 63,  50},
    {"You have puke yellow eyes, ",                          85, 62, 63,  50},
    {"You have blue-bloodshot eyes, ",                       99, 62, 63,  50},
    {"You have glowing red eyes, ",                         100, 62, 63,  55},
    {"dirty ",                                               33, 63, 64,  50},
    {"mangy ",                                               66, 63, 64,  50},
    {"oily ",                                               100, 63, 64,  50},
    {"sea-weed green hair, ",                                33, 64, 65,  50},
    {"bright red hair, ",                                    66, 64, 65,  50},
    {"dark purple hair, ",                                  100, 64, 65,  50},
    {"and green ",                                           25, 65, 66,  50},
    {"and blue ",                                            50, 65, 66,  50},
    {"and white ",                                           75, 65, 66,  50},
    {"and black ",                                          100, 65, 66,  50},
    {"ulcerous skin.",                                       33, 66,  0,  50},
    {"scabby skin.",                                         66, 66,  0,  50},
    {"leprous skin.",                                       100, 66,  0,  50},
    // Phraint. Chart numbers match values.inc. Bonus is the Imoria value plus 50.
    {"You are one of many illegitimate children ",            5, 25, 26,  20},
    {"You are one of several illegitimate children ",        10, 25, 26,  25},
    {"You are one of many children ",                        50, 25, 26,  40},
    {"You are one of several children ",                     75, 25, 26,  45},
    {"You are the 2nd child ",                               95, 25, 26,  50},
    {"You are the only child ",                             100, 25, 26,  55},
    {"of a Worker.  ",                                       50, 26, 27,  65},
    {"of a Warrior.  ",                                      75, 26, 27,  80},
    {"of an Elite Warrior.  ",                               90, 26, 27, 100},
    {"of the Hive Mother.  ",                               100, 26, 27, 150},
    {"You are the outcast of the hive.  ",                    5, 27, 38,   0},
    {"You are the black sheep of the hive.  ",               20, 27, 38,  20},
    {"You are a credit to the hive.  ",                      80, 27, 38,  55},
    {"You are a well liked child.  ",                       100, 27, 38,  60},
    // Dryad. The stump and forest lines jump to chart 54, so that chart is
    // repeated after this block. The earlier chart 54 still serves elves.
    {"You are the Dryad of a sickly ",                       15, 28, 29,  30},
    {"You are the Dryad of a large ",                        40, 28, 29,  50},
    {"You are the Dryad of a rich, green ",                  60, 28, 29,  50},
    {"You are the Dryad of a magnificent ",                  90, 28, 29,  60},
    {"You are the Dryad of a stump! ",                      100, 28, 54,  20},
    {"pine tree",                                            30, 29, 30,  55},
    {"birch tree",                                           40, 29, 30,  65},
    {"ash tree",                                             50, 29, 30,  80},
    {"cedar tree",                                           70, 29, 30, 100},
    {"willow tree",                                          90, 29, 30, 120},
    {"oak tree",                                            100, 29, 30, 140},
    {", but the elven community avoids your forest.  ",      10, 30, 54,  20},
    {" in a small glade.  ",                                 40, 30, 54,  45},
    {" and you are a fine upholder of the woodlands.  ",     60, 30, 54,  55},
    {" and Humans and Half-Elves hold your tree sacred.  ",  88, 30, 54,  70},
    {" where the Elves hold yearly ceremonies.  ",           90, 30, 54,  75},
    {" that all races hold in reverence.  ",                100, 30, 54,  80},
    {"You have small ",                                      40, 38, 39,  50},
    {"You have large ",                                      70, 38, 39,  50},
    {"You have very large ",                                100, 38, 39,  50},
    {"buggy green eyes, ",                                   10, 39, 40,  50},
    {"buggy silver eyes, ",                                  30, 39, 40,  50},
    {"iridescent eyes, ",                                    70, 39, 40,  50},
    {"glowing eyes, ",                                      100, 39, 40,  50},
    {"straight feelers, ",                                   10, 40, 41,  50},
    {"curved feelers, ",                                     30, 40, 41,  50},
    {"bent feelers, ",                                       80, 40, 41,  50},
    {"very long feelers, ",                                 100, 40, 41,  50},
    {"and dull brown chiton.",                               10, 41,  0,  50},
    {"and shiny brown chiton.",                              60, 41,  0,  50},
    {"and shiny black chiton.",                              90, 41,  0,  50},
    {"and polished silver chiton.",                         100, 41,  0,  50},
    {"You have light grey eyes, ",                           85, 54, 55,  50},
    {"You have light violet eyes, ",                         90, 54, 55,  50},
    {"You have light blue eyes, ",                           95, 54, 55,  50},
    {"You have light green eyes, ",                          98, 54, 55,  52},
    {"You have light golden colored eyes, ",                100, 54, 55,  55},
    {"straight ",                                            75, 55, 56,  50},
    {"wavey ",                                              100, 55, 56,  50},
    {"jet black hair, and a fair complexion.",               75, 56,  0,  50},
    {"light brown hair, and a fair complexion.",             85, 56,  0,  50},
    {"blonde hair, and a fair complexion.",                  95, 56,  0,  50},
    {"silver hair, and a fair complexion.",                  98, 56,  0,  51},
    {"hair the color of spun gold and pale skin.",          100, 56,  0,  55},
};

// Classes.
// Combat to-hit stays on Umoria's scale for the original six classes.
// New classes use that same scale (about eight times Imoria's mbth).
// Rogues sing and rangers play druid magic, matching Imoria's realms.
Class_t classes[PLAYER_MAX_CLASSES] = {
    // class      hp dis src stl fos bth btb sve  s   i   w   d  co  ch  spell                          exp  spl
    {"Warrior",    10, 25, 14, 1, 38, 70, 55, 18,  5, -2, -2,  2,  2, -1, config::spells::SPELL_TYPE_NONE,    0, 0},
    {"Mage",        0, 30, 16, 2, 36, 34, 20, 36, -5,  3,  0,  0, -2,  0, config::spells::SPELL_TYPE_MAGE,   30, 1},
    {"Priest",      3, 25, 16, 2, 32, 48, 35, 30,  0, -3,  3, -1,  1,  2, config::spells::SPELL_TYPE_PRIEST, 20, 1},
    {"Rogue",       6, 45, 32, 4, 16, 60, 66, 30,  2,  0, -2,  3,  1,  1, config::spells::SPELL_TYPE_SONG,   10, 3},
    {"Ranger",      4, 30, 24, 3, 24, 56, 72, 30,  2,  0,  1,  1,  1,  2, config::spells::SPELL_TYPE_DRUID, 30, 1},
    {"Paladin",     6, 20, 12, 1, 38, 68, 40, 24,  3, -3,  1,  0,  2,  2, config::spells::SPELL_TYPE_PRIEST, 35, 1},
    {"Druid",       3, 25, 16, 1, 32, 42, 49, 30, -1, -1,  2,  0,  0,  3, config::spells::SPELL_TYPE_DRUID,  20, 1},
    {"Bard",        4, 30, 22, 2, 28, 50, 42, 30,  2,  1, -1,  2,  0,  3, config::spells::SPELL_TYPE_SONG,   30, 1},
    {"Adventurer",  4, 30, 24, 3, 24, 54, 42, 28,  2,  2, -1,  1,  1,  0, config::spells::SPELL_TYPE_MAGE,   40, 3},
    {"Monk",        4, 45, 24, 3, 24, 68, 40, 36,  2,  0,  2,  3,  1,  1, config::spells::SPELL_TYPE_MONK,   10, 3},
};

// making it 16 bits wastes a little space, but saves much signed/unsigned
// headaches in its use.
// CLASS_MISC_HIT is identical to py_class_level_adj::CLASS_SAVE, which takes advantage of
// the fact that the save values are independent of the class.
// Columns: bth, bth_with_bows, device, disarm, save/misc hit
int16_t class_level_adj[PLAYER_MAX_CLASSES][CLASS_MAX_LEVEL_ADJUST] = {
    { 4, 4, 2, 2, 3 }, // Warrior
    { 2, 2, 4, 3, 3 }, // Mage
    { 2, 2, 4, 3, 3 }, // Priest
    { 3, 4, 3, 4, 3 }, // Rogue
    { 3, 4, 3, 3, 3 }, // Ranger
    { 3, 3, 3, 2, 3 }, // Paladin
    { 2, 3, 4, 3, 3 }, // Druid
    { 3, 3, 3, 3, 3 }, // Bard
    { 3, 3, 3, 3, 3 }, // Adventurer
    { 4, 2, 2, 4, 3 }, // Monk
};

// Spell tables for every class, including Warrior (all level 99).
// Generated from Imoria 4.85 values.inc. Indexed by class_id.
#include "data_spells.inc"

const char *spell_names[62] = {
    // Mage Spells
    "Magic Missile", "Detect Monsters", "Phase Door", "Light Area",
    "Cure Light Wounds", "Find Hidden Traps/Doors", "Stinking Cloud",
    "Confusion", "Lightning Bolt", "Trap/Door Destruction", "Sleep I",
    "Cure Poison", "Teleport Self", "Remove Curse", "Frost Bolt",
    "Turn Stone to Mud", "Create Food", "Recharge Item I", "Sleep II",
    "Polymorph Other", "Identify", "Sleep III", "Fire Bolt", "Slow Monster",
    "Frost Ball", "Recharge Item II", "Teleport Other", "Haste Self",
    "Fire Ball", "Word of Destruction", "Genocide",

    // Priest Spells, start at index 31
    "Detect Evil", "Cure Light Wounds", "Bless", "Remove Fear", "Call Light",
    "Find Traps", "Detect Doors/Stairs", "Slow Poison", "Blind Creature",
    "Portal", "Cure Medium Wounds", "Chant", "Sanctuary", "Create Food",
    "Remove Curse", "Resist Heat and Cold", "Neutralize Poison",
    "Orb of Draining", "Cure Serious Wounds", "Sense Invisible",
    "Protection from Evil", "Earthquake", "Sense Surroundings",
    "Cure Critical Wounds", "Turn Undead", "Prayer", "Dispel Undead", "Heal",
    "Dispel Evil", "Glyph of Warding", "Holy Word",
};

// Each type of character starts out with a few provisions.
//
// Note that the entries refer to elements of the game_objects[] array.
//      344 = Food Ration
//      365 = Wooden Torch
//      123 = Cloak
//      318 = Beginners-Magick
//      103 = Soft Leather Armor
//       30 = Stiletto
//      322 = Beginners Handbook
uint16_t class_base_provisions[PLAYER_MAX_CLASSES][5] = {
    {344, 365, 123,  30, 103}, // Warrior
    {344, 365, 123,  30, 318}, // Mage
    {344, 365, 123,  30, 322}, // Priest
    {344, 365, 123,  30, 427}, // Rogue, beginners songbook
    {344, 365, 123,  30, 431}, // Ranger, beginners instrument
    {344, 365, 123,  30, 322}, // Paladin
    {344, 365, 123,  30, 431}, // Druid
    {344, 365, 123,  30, 427}, // Bard
    {344, 365, 123,  30, 318}, // Adventurer
    {344, 365, 123, 344, 344}, // Monk, no weapon
};
