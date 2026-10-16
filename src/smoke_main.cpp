// Copyright (c) 1981-86 Robert A. Koeneke
// Copyright (c) 1987-94 James E. Wilson
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Headless check: every legal race/class can be rolled, and the town plus
// the first dungeon level can be generated.

#include "headers.h"

static int fail(const char *message) {
    std::cerr << "smoke: " << message << "\n";
    return 1;
}

static bool spellRealmHasSpell(uint8_t class_id) {
    if (classes[class_id].class_to_use_mage_spells == config::spells::SPELL_TYPE_NONE) {
        return true;
    }
    for (int i = 0; i < PLAYER_MAX_SPELLS; i++) {
        if (magic_spells[class_id][i].level_required < 99 && magic_spells[class_id][i].name[0] != '\0') {
            return true;
        }
    }
    return false;
}

static int checkCharacters() {
    int legal = 0;
    for (uint8_t race = 0; race < PLAYER_MAX_RACES; race++) {
        int classes_for_race = 0;
        for (uint8_t klass = 0; klass < PLAYER_MAX_CLASSES; klass++) {
            bool allowed = (character_races[race].classes_bit_field & (uint16_t) (1u << klass)) != 0;
            bool rolled = characterRollRaceClass(race, klass);
            if (allowed != rolled) {
                std::cerr << "smoke: roll mismatch for " << character_races[race].name << " " << classes[klass].title << "\n";
                return 1;
            }
            if (!allowed) {
                continue;
            }
            classes_for_race++;
            legal++;
            if (py.misc.current_hp <= 0 || py.misc.history[0][0] == '\0') {
                std::cerr << "smoke: empty character " << character_races[race].name << " " << classes[klass].title << "\n";
                return 1;
            }
            if (py.misc.au < 80) {
                return fail("starting gold below the minimum");
            }
            for (int stat = 0; stat < 6; stat++) {
                if (py.stats.max[stat] < 3) {
                    return fail("stat below 3");
                }
            }
            if (!spellRealmHasSpell(klass)) {
                std::cerr << "smoke: " << classes[klass].title << " has no spells\n";
                return 1;
            }
        }
        if (classes_for_race == 0) {
            std::cerr << "smoke: " << character_races[race].name << " has no classes\n";
            return 1;
        }
    }
    if (legal < 40) {
        return fail("expected more legal race/class pairs");
    }
    std::cout << "smoke: rolled " << legal << " race/class pairs\n";
    return 0;
}

static int countFeature(uint8_t feature) {
    int count = 0;
    for (int y = 0; y < dg.height; y++) {
        for (int x = 0; x < dg.width; x++) {
            if (dg.floor[y][x].feature_id == feature) {
                count++;
            }
        }
    }
    return count;
}

static int countStoreDoors() {
    int count = 0;
    for (int y = 0; y < dg.height; y++) {
        for (int x = 0; x < dg.width; x++) {
            uint8_t treasure = dg.floor[y][x].treasure_id;
            if (treasure != 0 && game.treasure.list[treasure].category_id == TV_STORE_DOOR) {
                count++;
            }
        }
    }
    return count;
}

static bool playerOnMap() {
    if (py.pos.y < 0 || py.pos.x < 0 || py.pos.y >= dg.height || py.pos.x >= dg.width) {
        return false;
    }
    uint8_t feature = dg.floor[py.pos.y][py.pos.x].feature_id;
    return feature <= MAX_OPEN_SPACE || feature == TILE_WATER;
}

int main() {
    seedsInitialize(1);
    initializeMonsterLevels();
    initializeTreasureLevels();
    storeInitializeOwners();
    playerInitializeBaseExperienceLevels();

    if (checkCharacters() != 0) {
        return 1;
    }

    game.town_seed = 12345;
    dg.game_turn = 1000;
    dg.current_level = 0;
    generateCave();

    if (dg.height < 40 || dg.width < 120) {
        return fail("town is still the small Umoria map");
    }
    if (!playerOnMap()) {
        return fail("player is not standing in town");
    }
    if (countStoreDoors() < MAX_STORES) {
        std::cerr << "smoke: store doors " << countStoreDoors() << "\n";
        return fail("town is missing store doors");
    }
    if (countFeature(TILE_WATER) < 10) {
        return fail("town has no river");
    }
    std::cout << "smoke: town " << dg.width << "x" << dg.height << " stores " << countStoreDoors() << " water " << countFeature(TILE_WATER) << "\n";

    dg.current_level = 1;
    generateCave();
    if (dg.height != MAX_HEIGHT || dg.width != MAX_WIDTH) {
        return fail("dungeon level is the wrong size");
    }
    if (!playerOnMap()) {
        return fail("player is not standing in the dungeon");
    }
    std::cout << "smoke: dungeon level 1 ok\n";
    return 0;
}
