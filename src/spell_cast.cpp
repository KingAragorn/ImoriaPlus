// Copyright (c) 1981-86 Robert A. Koeneke
// Copyright (c) 1987-94 James E. Wilson
// Copyright (c) 1985-1994 Kenneth Case, Mary Conner, Robert DeLoura,
//           Dan Flye, Todd Gardiner, Dave Jungck, Andy Walker, Dean Yasuda
//
// SPDX-License-Identifier: GPL-3.0-or-later

// One caster for mage spells, prayers, songs, druid magic, and monk disciplines.
// Effects are the Umoria primitives closest to the Imoria spell of the same name.

#include "headers.h"

static bool aimSpell(int &direction) {
    if (!getDirectionWithMemory(CNIL, direction)) {
        game.player_free_turn = true;
        return false;
    }
    return true;
}

static void boltSpell(const Spell_t &spell, int damage, int kind) {
    int direction;
    if (!aimSpell(direction)) {
        return;
    }
    spellFireBolt(py.pos, direction, damage, kind, spell.name);
}

static void ballSpell(const Spell_t &spell, int damage, int kind) {
    int direction;
    if (!aimSpell(direction)) {
        return;
    }
    spellFireBall(py.pos, direction, damage, kind, spell.name);
}

static void aimedMonsterSpell(bool (*effect)(Coord_t, int)) {
    int direction;
    if (!aimSpell(direction)) {
        return;
    }
    (void) effect(py.pos, direction);
}

void castSpellEffect(const Spell_t &spell) {
    int direction;

    switch (spell.effect) {
        case SE_BOLT_MISSILE:
            boltSpell(spell, diceRoll(Dice_t{2, 6}), MagicSpellFlags::MagicMissile);
            break;
        case SE_BOLT_LIGHTNING:
            boltSpell(spell, diceRoll(Dice_t{4, 8}), MagicSpellFlags::Lightning);
            break;
        case SE_BOLT_FROST:
            boltSpell(spell, diceRoll(Dice_t{6, 8}), MagicSpellFlags::Frost);
            break;
        case SE_BOLT_FIRE:
            boltSpell(spell, diceRoll(Dice_t{9, 8}), MagicSpellFlags::Fire);
            break;
        case SE_BALL_POISON:
            ballSpell(spell, 12, MagicSpellFlags::PoisonGas);
            break;
        case SE_BALL_FROST:
            ballSpell(spell, 48, MagicSpellFlags::Frost);
            break;
        case SE_BALL_FIRE:
            ballSpell(spell, 72, MagicSpellFlags::Fire);
            break;
        case SE_BALL_LIGHTNING:
            ballSpell(spell, 64, MagicSpellFlags::Lightning);
            break;
        case SE_KILL:
            boltSpell(spell, diceRoll(Dice_t{8, 8}) + py.misc.level * 3, MagicSpellFlags::MagicMissile);
            break;
        case SE_DETECT_MONSTERS:
        case SE_DETECT_MAGIC:
            (void) spellDetectMonsters();
            break;
        case SE_DETECT_EVIL:
            (void) spellDetectEvil();
            break;
        case SE_DETECT_TRAPS:
            (void) spellDetectTrapsWithinVicinity();
            (void) spellDetectSecretDoorssWithinVicinity();
            break;
        case SE_DETECT_DOORS:
            (void) spellDetectSecretDoorssWithinVicinity();
            break;
        case SE_DETECT_INVIS:
            (void) spellDetectInvisibleCreaturesWithinVicinity();
            playerDetectInvisible(py.misc.level + 10);
            break;
        case SE_DETECT_TREASURE:
            (void) spellDetectTreasureWithinVicinity();
            break;
        case SE_DETECT_OBJECTS:
            (void) spellDetectObjectsWithinVicinity();
            break;
        case SE_PHASE_DOOR:
            playerTeleport(10);
            break;
        case SE_TELEPORT:
            playerTeleport(py.misc.level * 5);
            break;
        case SE_TELEPORT_AWAY:
            if (aimSpell(direction)) {
                (void) spellTeleportAwayMonsterInDirection(py.pos, direction);
            }
            break;
        case SE_TELEPORT_LEVEL:
        case SE_WORD_RECALL:
            py.flags.word_of_recall = (int16_t) (15 + randomNumber(20));
            printMessage("The air about you becomes charged...");
            break;
        case SE_LIGHT:
            (void) spellLightArea(py.pos);
            break;
        case SE_CURE_LIGHT:
            (void) spellChangePlayerHitPoints(diceRoll(Dice_t{2, 8}));
            break;
        case SE_CURE_MEDIUM:
            (void) spellChangePlayerHitPoints(diceRoll(Dice_t{4, 8}));
            break;
        case SE_CURE_SERIOUS:
            (void) spellChangePlayerHitPoints(diceRoll(Dice_t{8, 8}));
            break;
        case SE_CURE_CRITICAL:
            (void) spellChangePlayerHitPoints(diceRoll(Dice_t{16, 8}));
            break;
        case SE_HEAL:
            (void) spellChangePlayerHitPoints(200);
            break;
        case SE_CURE_POISON:
            (void) playerCurePoison();
            break;
        case SE_SLOW_POISON:
            (void) spellSlowPoison();
            break;
        case SE_REMOVE_FEAR:
            (void) playerRemoveFear();
            break;
        case SE_BLESS:
            playerBless(py.misc.level + 12);
            printMessage("You feel righteous!");
            break;
        case SE_HERO:
            py.flags.heroism += (int16_t) (10 + randomNumber(py.misc.level));
            (void) playerRemoveFear();
            printMessage("You feel like a hero!");
            break;
        case SE_CONFUSE:
        case SE_BLIND:
            aimedMonsterSpell(spellConfuseMonster);
            break;
        case SE_SLEEP:
        case SE_HOLD_MONSTER:
        case SE_CHARM:
        case SE_FEAR_MONSTER:
            aimedMonsterSpell(spellSleepMonster);
            break;
        case SE_SLEEP_ALL:
            (void) spellSleepAllMonsters();
            break;
        case SE_DESTROY_TRAPS:
            (void) spellDestroyAdjacentDoorsTraps();
            break;
        case SE_STONE_MUD:
            if (aimSpell(direction)) {
                (void) spellWallToMud(py.pos, direction);
            }
            break;
        case SE_CREATE_FOOD:
            spellCreateFood();
            break;
        case SE_FOOD_FULL:
            py.flags.food = (int16_t) config::player::PLAYER_FOOD_FULL;
            printMessage("You are full.");
            printCharacterHungerStatus();
            break;
        case SE_INFRA:
            py.flags.timed_infra += (int16_t) (100 + py.misc.level);
            printMessage("Your eyes begin to tingle.");
            break;
        case SE_INVIS:
        case SE_STEALTH:
            if (py.misc.stealth_factor < 18) {
                py.misc.stealth_factor += 5;
            }
            printMessage("You move silently.");
            break;
        case SE_REMOVE_CURSE:
            (void) spellRemoveCurseFromAllWornItems();
            break;
        case SE_RECHARGE:
            (void) spellRechargeItem(spell.effect == SE_RECHARGE ? 20 : 60);
            break;
        case SE_IDENTIFY:
            (void) spellIdentifyItem();
            break;
        case SE_POLYMORPH:
            if (aimSpell(direction)) {
                (void) spellPolymorphMonster(py.pos, direction);
            }
            break;
        case SE_SLOW_MONSTER:
            if (aimSpell(direction)) {
                (void) spellSpeedMonster(py.pos, direction, -1);
            }
            break;
        case SE_HASTE:
            if (py.flags.fast == 0) {
                py.flags.fast += (int16_t) (randomNumber(20) + py.misc.level);
            } else {
                py.flags.fast++;
            }
            printMessage("You feel yourself moving faster.");
            break;
        case SE_GENOCIDE:
            (void) spellGenocide();
            break;
        case SE_TURN_UNDEAD:
            (void) spellTurnUndead();
            break;
        case SE_DISPEL_UNDEAD:
            (void) spellDispelCreature(config::monsters::defense::CD_UNDEAD, diceRoll(Dice_t{4, 8}) + py.misc.level);
            break;
        case SE_DISPEL_EVIL:
            (void) spellDispelCreature(config::monsters::defense::CD_EVIL, diceRoll(Dice_t{4, 8}) + py.misc.level);
            break;
        case SE_DISPEL_MONSTER:
            (void) spellDispelCreature(0xFFFF, diceRoll(Dice_t{4, 6}) + py.misc.level);
            break;
        case SE_EARTHQUAKE:
            spellEarthquake();
            break;
        case SE_PROTECT_EVIL:
            (void) playerProtectEvil();
            break;
        case SE_WARDING:
            spellWardingGlyph();
            break;
        case SE_MAP:
            spellMapCurrentArea();
            break;
        case SE_SUMMON:
            printMessage("You call something from nearby.");
            monsterPlaceNewWithinDistance(randomNumber(3) + 1, 2, false);
            break;
        case SE_RESIST:
            py.flags.heat_resistance += (int16_t) (20 + py.misc.level);
            py.flags.cold_resistance += (int16_t) (20 + py.misc.level);
            printMessage("You feel resistant.");
            break;
        case SE_FREE_ACTION:
            py.flags.free_action = true;
            py.flags.paralysis = 0;
            printMessage("You feel free to move.");
            break;
        case SE_DESTRUCTION:
            spellDestroyArea(py.pos);
            break;
        case SE_GENERIC:
        case SE_NONE:
        default:
            vtype_t invoked = {'\0'};
            (void) snprintf(invoked, MORIA_MESSAGE_SIZE, "You invoke %s.", spell.name);
            printMessage(invoked);
            (void) spellChangePlayerHitPoints(spell.mana_required);
            break;
    }
}

static void spellFailureMessage() {
    switch (classes[py.misc.class_id].class_to_use_mage_spells) {
        case config::spells::SPELL_TYPE_SONG:
            printMessage("*Squak*");
            break;
        case config::spells::SPELL_TYPE_DRUID:
            printMessage("*Twang*");
            break;
        case config::spells::SPELL_TYPE_MONK:
            printMessage("You lose your concentration!");
            break;
        case config::spells::SPELL_TYPE_PRIEST:
            printMessage("You lost your concentration!");
            break;
        default:
            printMessage("You failed to get the spell off!");
            break;
    }
}

static void spendSpellMana(const Spell_t &spell) {
    if (spell.mana_required > py.misc.current_mana) {
        printMessage("You faint from the effort!");
        py.flags.paralysis = (int16_t) randomNumber((5 * (spell.mana_required - py.misc.current_mana)));
        py.misc.current_mana = 0;
        py.misc.current_mana_fraction = 0;
        if (randomNumber(3) == 1) {
            printMessage("You have damaged your health!");
            (void) playerStatRandomDecrease(PlayerAttr::A_CON);
        }
    } else {
        py.misc.current_mana -= spell.mana_required;
    }
    printCharacterCurrentMana();
}

void playerCastRealm(bool prayer_key) {
    game.player_free_turn = true;

    uint8_t realm = classes[py.misc.class_id].class_to_use_mage_spells;
    bool on_prayer_key = realm == config::spells::SPELL_TYPE_PRIEST || realm == config::spells::SPELL_TYPE_DRUID;
    bool on_magic_key = realm == config::spells::SPELL_TYPE_MAGE || realm == config::spells::SPELL_TYPE_SONG || realm == config::spells::SPELL_TYPE_MONK;

    if (prayer_key && !on_prayer_key) {
        printMessage("Pray hard enough and your prayers may be answered.");
        return;
    }
    if (!prayer_key && !on_magic_key) {
        printMessage("You don't know any magic.");
        return;
    }
    if (py.flags.confused > 0) {
        printMessage("You are too confused.");
        return;
    }

    int choice = 0;
    int chance = 0;
    int result;

    if (realm == config::spells::SPELL_TYPE_MONK) {
        uint64_t known = py.flags.spells_learnt & classKnownSpellMask();
        result = castSpellChooseFromMask("Use which discipline?", known, 0, choice, chance);
    } else {
        if (py.flags.blind > 0) {
            printMessage("You can't see to read.");
            return;
        }
        if (playerNoLight()) {
            printMessage("You have no light to read by.");
            return;
        }

        uint8_t book = classBookCategory(py.misc.class_id);
        int begin, end;
        if (!inventoryFindRange(book, TV_NEVER, begin, end)) {
            printMessage("You are not carrying the right book.");
            return;
        }

        int item_val;
        const char *ask = realm == config::spells::SPELL_TYPE_DRUID ? "Play which instrument?" : "Use which book?";
        if (!inventoryGetInputForItemId(item_val, ask, begin, end, CNIL, CNIL)) {
            return;
        }

        const char *prompt = "Cast which spell?";
        if (realm == config::spells::SPELL_TYPE_PRIEST) {
            prompt = "Recite which prayer?";
        } else if (realm == config::spells::SPELL_TYPE_SONG) {
            prompt = "Sing which song?";
        } else if (realm == config::spells::SPELL_TYPE_DRUID) {
            prompt = "Play which song?";
        }
        result = castSpellGetId(prompt, item_val, choice, chance);
    }

    if (result < 0) {
        printMessage("You don't know any of those.");
        return;
    }
    if (result == 0) {
        return;
    }

    game.player_free_turn = false;
    Spell_t const &spell = magic_spells[py.misc.class_id][choice];

    if (randomNumber(100) < chance) {
        spellFailureMessage();
    } else {
        castSpellEffect(spell);
        if (!game.player_free_turn && (py.flags.spells_worked & (1ULL << choice)) == 0) {
            py.misc.exp += spell.exp_gain_for_learning << 2;
            py.flags.spells_worked |= 1ULL << choice;
            displayCharacterExperience();
        }
    }

    if (game.player_free_turn) {
        return;
    }

    spendSpellMana(spell);
}
