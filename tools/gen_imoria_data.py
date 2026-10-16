#!/usr/bin/env python3
"""Generate Imoria spell and monster tables for ImoriaPlus.

Reads the University of Washington Imoria 4.85 sources (values.inc and
monsters.dat) and emits C++ fragments. Flag layouts are remapped onto
Umoria's bit fields; they are not copied raw.
"""

import re
import sys
from pathlib import Path

IMORIA = Path("/tmp/imoria")
OUT = Path("/workspace/src")

EFFECTS = {
    "magic missile": "SE_BOLT_MISSILE",
    "detect monsters": "SE_DETECT_MONSTERS",
    "detect monster": "SE_DETECT_MONSTERS",
    "phase door": "SE_PHASE_DOOR",
    "blink": "SE_PHASE_DOOR",
    "light area": "SE_LIGHT",
    "light": "SE_LIGHT",
    "call light": "SE_LIGHT",
    "starlight": "SE_LIGHT",
    "sunray": "SE_LIGHT",
    "cure light wounds": "SE_CURE_LIGHT",
    "minor cure": "SE_CURE_LIGHT",
    "self-healing": "SE_CURE_LIGHT",
    "find hidden traps/doors": "SE_DETECT_TRAPS",
    "find hidden doors/traps": "SE_DETECT_TRAPS",
    "detect hidden doors/traps": "SE_DETECT_TRAPS",
    "find traps": "SE_DETECT_TRAPS",
    "find safe path": "SE_DETECT_TRAPS",
    "stinking cloud": "SE_BALL_POISON",
    "confusion": "SE_CONFUSE",
    "lightning bolt": "SE_BOLT_LIGHTNING",
    "call lightning": "SE_BOLT_LIGHTNING",
    "trap/door destruction": "SE_DESTROY_TRAPS",
    "sleep i": "SE_SLEEP",
    "sleep ii": "SE_SLEEP",
    "sleep iii": "SE_SLEEP_ALL",
    "cure poison": "SE_CURE_POISON",
    "neutralize poison": "SE_CURE_POISON",
    "poison immunity": "SE_CURE_POISON",
    "shadow door": "SE_TELEPORT",
    "shadow gate": "SE_TELEPORT",
    "portal": "SE_TELEPORT",
    "teleport self": "SE_TELEPORT",
    "remove curse": "SE_REMOVE_CURSE",
    "frost bolt": "SE_BOLT_FROST",
    "create food": "SE_CREATE_FOOD",
    "create food and drink": "SE_CREATE_FOOD",
    "goodberry": "SE_FOOD_FULL",
    "negate hunger": "SE_FOOD_FULL",
    "hero's feast": "SE_FOOD_FULL",
    "infravision": "SE_INFRA",
    "night vision": "SE_INFRA",
    "invisibility": "SE_INVIS",
    "turn stone to mud": "SE_STONE_MUD",
    "stone to mud": "SE_STONE_MUD",
    "recharge item i": "SE_RECHARGE",
    "recharge item ii": "SE_RECHARGE",
    "recharge item": "SE_RECHARGE",
    "polymorph other": "SE_POLYMORPH",
    "identify": "SE_IDENTIFY",
    "legend lore": "SE_IDENTIFY",
    "item lore": "SE_IDENTIFY",
    "detect magic": "SE_DETECT_MAGIC",
    "detect curse": "SE_IDENTIFY",
    "fire bolt": "SE_BOLT_FIRE",
    "fire stream": "SE_BOLT_FIRE",
    "pillar of fire": "SE_BOLT_FIRE",
    "slow creature": "SE_SLOW_MONSTER",
    "slow monster": "SE_SLOW_MONSTER",
    "frost ball": "SE_BALL_FROST",
    "ring of frost": "SE_BALL_FROST",
    "fire ball": "SE_BALL_FIRE",
    "ring of fire": "SE_BALL_FIRE",
    "lightning ball": "SE_BALL_LIGHTNING",
    "teleport other": "SE_TELEPORT_AWAY",
    "haste self": "SE_HASTE",
    "improved speed": "SE_HASTE",
    "genocide": "SE_GENOCIDE",
    "detect evil": "SE_DETECT_EVIL",
    "bless": "SE_BLESS",
    "remove fear": "SE_REMOVE_FEAR",
    "courage": "SE_REMOVE_FEAR",
    "detect doors/stairs": "SE_DETECT_DOORS",
    "slow poison": "SE_SLOW_POISON",
    "blind creature": "SE_BLIND",
    "word of blindness": "SE_BLIND",
    "cure medium wounds": "SE_CURE_MEDIUM",
    "self-healing ii": "SE_CURE_SERIOUS",
    "heroism": "SE_HERO",
    "battle song": "SE_HERO",
    "battle dance": "SE_HERO",
    "sanctuary": "SE_SLEEP_ALL",
    "resist heat and cold": "SE_RESIST",
    "silence": "SE_SLEEP",
    "earthquake": "SE_EARTHQUAKE",
    "sense invisible": "SE_DETECT_INVIS",
    "see invisible": "SE_DETECT_INVIS",
    "detect invisible": "SE_DETECT_INVIS",
    "protection from evil": "SE_PROTECT_EVIL",
    "sense surroundings": "SE_MAP",
    "magic mapping": "SE_MAP",
    "clairvoyance": "SE_MAP",
    "cure serious wounds": "SE_CURE_SERIOUS",
    "major cure": "SE_CURE_SERIOUS",
    "cure critical wounds": "SE_CURE_CRITICAL",
    "advanced self-healing": "SE_HEAL",
    "turn undead": "SE_TURN_UNDEAD",
    "dispel undead": "SE_DISPEL_UNDEAD",
    "dispell undead": "SE_DISPEL_UNDEAD",
    "heal": "SE_HEAL",
    "dispel evil": "SE_DISPEL_EVIL",
    "dispell evil": "SE_DISPEL_EVIL",
    "glyph of warding": "SE_WARDING",
    "holy word": "SE_HEAL",
    "word of recall": "SE_WORD_RECALL",
    "teleport level": "SE_TELEPORT_LEVEL",
    "detect treasure": "SE_DETECT_TREASURE",
    "detect object": "SE_DETECT_OBJECTS",
    "charm monsters": "SE_CHARM",
    "charm": "SE_CHARM",
    "mass charm": "SE_CHARM",
    "magical jig": "SE_SLEEP",
    "battle frenzy": "SE_HASTE",
    "moon beam": "SE_BOLT_MISSILE",
    "phantasmal force": "SE_BOLT_MISSILE",
    "orb of draining": "SE_BOLT_MISSILE",
    "hold monster": "SE_HOLD_MONSTER",
    "death spell": "SE_KILL",
    "power word: destruction": "SE_DESTRUCTION",
    "power word: kill": "SE_KILL",
    "note of destruction": "SE_DESTRUCTION",
    "song of power": "SE_DESTRUCTION",
    "protection from magic": "SE_RESIST",
    "protection from nature": "SE_RESIST",
    "protection from monsters": "SE_RESIST",
    "song of protection": "SE_RESIST",
    "resist magic": "SE_RESIST",
    "magic resistance": "SE_RESIST",
    "resist petrification": "SE_RESIST",
    "resist charm": "SE_RESIST",
    "resist paralysis": "SE_RESIST",
    "control temperature": "SE_RESIST",
    "summon insects": "SE_SUMMON",
    "creeping doom": "SE_SUMMON",
    "stealth": "SE_STEALTH",
    "free action": "SE_FREE_ACTION",
    "sense enemies": "SE_DETECT_MONSTERS",
    "holy prayer": "SE_BLESS",
    "chant": "SE_BLESS",
    "ray of sanctification": "SE_DISPEL_UNDEAD",
    "blade barrier": "SE_DISPEL_MONSTER",
    "dispel monster": "SE_DISPEL_MONSTER",
    "holy of thunder": "SE_BALL_LIGHTNING",
    "holy thunder": "SE_BALL_LIGHTNING",
    "joke of death": "SE_FEAR_MONSTER",
    "physical humor": "SE_CONFUSE",
    "last laugh": "SE_BALL_POISON",
    "panic": "SE_FEAR_MONSTER",
    "dispel magic": "SE_SLOW_MONSTER",
    "dispell magic": "SE_SLOW_MONSTER",
    "warp wood": "SE_DESTROY_TRAPS",
    "transplant": "SE_TELEPORT",
}


def c_string(text):
    return text.replace("\\", "\\\\").replace('"', '\\"')


def parse_spells():
    text = (IMORIA / "src" / "values.inc").read_text(errors="replace")
    start = text.find("magic_spell")
    end = text.find("monk_book", start)
    chunk = text[start:end]
    # Pascal doubles quotes inside strings.
    spells = []
    for match in re.finditer(
        r"\('((?:[^']|'')*)'\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)",
        chunk,
    ):
        name = match.group(1).replace("''", "'")
        level, mana, exp, fail = (int(match.group(i)) for i in range(2, 6))
        spells.append((name, level, mana, exp, fail))
    if len(spells) != 400:
        raise SystemExit(f"expected 400 spells, got {len(spells)}")
    return spells


def emit_spells(spells):
    lines = []
    lines.append("// Generated from Imoria 4.85 values.inc magic_spell.")
    lines.append("// exp_gain_for_learning is Imoria sexp/4 (minimum 1 when sexp > 0).")
    lines.append("Spell_t magic_spells[PLAYER_MAX_CLASSES][PLAYER_MAX_SPELLS] = {")
    class_names = [
        "Warrior",
        "Mage",
        "Priest",
        "Rogue",
        "Ranger",
        "Paladin",
        "Druid",
        "Bard",
        "Adventurer",
        "Monk",
    ]
    for class_id, name in enumerate(class_names):
        lines.append(f"    {{ // {name}")
        block = spells[class_id * 40 : (class_id + 1) * 40]
        for spell_name, level, mana, exp, fail in block:
            if level >= 99 or spell_name == "":
                lines.append('        {99, 99, 0, 0, SE_NONE, ""},')
                continue
            gain = max(1, exp // 4) if exp > 0 else 0
            if gain > 255:
                gain = 255
            effect = EFFECTS.get(spell_name.lower(), "SE_GENERIC")
            lines.append(
                f'        {{{level:3d}, {mana:3d}, {fail:3d}, {gain:3d}, {effect}, "{c_string(spell_name)}"}},'
            )
        lines.append("    },")
    lines.append("};")
    (OUT / "data_spells.inc").write_text("\n".join(lines) + "\n")


def norm_name(name):
    return re.sub(r"[^a-z0-9]", "", name.lower())


def parse_existing_names():
    text = (OUT / "data_creatures.cpp").read_text()
    names = set()
    for match in re.finditer(r'^\s*\{"([^"]+)"', text, re.M):
        names.add(norm_name(match.group(1)))
    return names


def parse_existing_attacks():
    text = (OUT / "data_creatures.cpp").read_text()
    attacks = {}
    # {type, desc, {dice, sides}},
    for index, match in enumerate(
        re.finditer(r"\{(\d+),\s*(\d+),\s*\{(\d+),\s*(\d+)\}\}", text)
    ):
        key = tuple(int(match.group(i)) for i in range(1, 5))
        attacks.setdefault(key, index)
    return attacks


def remap_move(cmove):
    um = 0
    CM_ATTACK_ONLY = 0x00000001
    CM_MOVE_NORMAL = 0x00000002
    CM_20 = 0x00000008
    CM_40 = 0x00000010
    CM_75 = 0x00000020
    CM_WATER = 0x00000040
    CM_INVISIBLE = 0x00010000
    CM_OPEN_DOOR = 0x00020000
    CM_PHASE = 0x00040000
    CM_PICKS_UP = 0x00100000
    CM_MULTIPLY = 0x00200000
    CM_CARRY_OBJ = 0x01000000
    CM_CARRY_GOLD = 0x02000000
    CM_60 = 0x04000000
    CM_90 = 0x08000000
    CM_1D2 = 0x10000000
    CM_2D2 = 0x20000000
    CM_4D2 = 0x40000000
    if cmove & 0x1:
        um |= CM_ATTACK_ONLY
    if cmove & 0x2:
        um |= CM_20
    if cmove & 0x4:
        um |= CM_40
    if cmove & 0x8:
        um |= CM_75
    if (cmove & 0x1) == 0 and (cmove & 0xE) == 0:
        um |= CM_MOVE_NORMAL
    if cmove & 0x10:
        um |= CM_WATER
    if cmove & 0x10000:
        um |= CM_INVISIBLE
    if cmove & 0x20000:
        um |= CM_OPEN_DOOR
    if cmove & 0x40000:
        um |= CM_PHASE
    if cmove & 0x100000:
        um |= CM_PICKS_UP
    if cmove & 0x200000:
        um |= CM_MULTIPLY
    if cmove & 0x1000000:
        um |= CM_CARRY_OBJ
    if cmove & 0x2000000:
        um |= CM_CARRY_GOLD
    if cmove & 0x4000000:
        um |= CM_60
    if cmove & 0x8000000:
        um |= CM_90
    if cmove & 0x10000000:
        um |= CM_1D2
    if cmove & 0x20000000:
        um |= CM_2D2
    if cmove & 0x40000000:
        um |= CM_4D2
    return um


def remap_defense(cdef):
    # Drop slay-monster (0x0002), demon (0x0400) and regen (0x8000).
    return cdef & ~0x8402


def remap_spells(spells):
    if spells & 0x80000000:
        spells &= ~0xF
    # Breaths and the spell bits Umoria already understands.
    return spells & 0x00F9FFFF


def parse_attacks(text):
    attacks = []
    for part in text.split("|"):
        part = part.strip()
        if not part:
            continue
        match = re.match(r"(\d+)\s+(\d+)\s+(?:(\d+)-)?(\d+)d(\d+)", part)
        if not match:
            continue
        kind = int(match.group(1))
        desc = int(match.group(2))
        count = int(match.group(3) or 1)
        dice = int(match.group(4))
        sides = int(match.group(5))
        if kind == 99 or desc == 99:
            continue
        if kind > 24:
            kind = 1
        if desc > 19 or desc in (6, 11):
            desc = 1
        dice = min(255, dice)
        sides = min(255, sides)
        count = max(1, min(4, count))
        for _ in range(count):
            if len(attacks) >= 4:
                break
            attacks.append((kind, desc, dice, sides))
    while len(attacks) < 4:
        attacks.append(None)
    return attacks[:4]


def emit_monsters():
    existing = parse_existing_names()
    attack_index = parse_existing_attacks()
    next_attack = (max(attack_index.values()) + 1) if attack_index else 1
    new_attacks = []

    raw = (IMORIA / "monsters.dat").read_text(errors="replace")
    blocks = re.split(r"---\s*\d+\s*---\n", raw)[1:]
    creatures = []
    skipped = {"dup": 0, "wimp": 0, "win": 0, "hidden": 0, "bad": 0}

    for block in blocks:
        lines = [line.rstrip() for line in block.strip().splitlines()]
        if len(lines) < 13:
            skipped["bad"] += 1
            continue
        try:
            aaf = int(lines[0])
            ac = int(lines[1])
            name = lines[2].strip()
            cmove = int(lines[3], 16)
            spells = int(lines[4], 16)
            cdef = int(lines[5], 16)
            # monsters.dat follows creature_type: sleep, then experience.
            sleep = int(lines[6])
            exp = int(lines[7])
            speed = int(lines[8])
            sprite = lines[9].strip() or "m"
            hd = lines[10].strip()
            attack_line = lines[11].strip()
            level = int(lines[-1].split()[0])
        except ValueError:
            skipped["bad"] += 1
            continue

        if name.lower().startswith("wimp"):
            skipped["wimp"] += 1
            continue
        if cmove & 0x80000000:
            skipped["win"] += 1
            continue
        # Summon-only creatures (will-not-normally-appear) above town level.
        if (cmove & 0x8000) and level > 0:
            skipped["hidden"] += 1
            continue
        if norm_name(name) in existing:
            skipped["dup"] += 1
            continue

        hd_match = re.match(r"(\d+)d(\d+)", hd)
        if not hd_match:
            skipped["bad"] += 1
            continue
        hd_dice = int(hd_match.group(1))
        hd_sides = int(hd_match.group(2))
        if hd_dice == 0 or hd_sides == 0:
            hd_dice, hd_sides = 1, 1
        hd_dice = min(255, hd_dice)
        hd_sides = min(255, hd_sides)

        if level < 0:
            level = 0
        if level > 40:
            level = 40

        speed = max(0, min(245, speed)) + 10
        sleep = max(0, min(255, sleep))
        aaf = max(0, min(255, aaf))
        ac = max(0, min(255, ac))
        exp = max(0, min(65535, exp))
        sprite = sprite[0]
        if sprite == "'":
            sprite_src = "'\\''"
        elif sprite == "\\":
            sprite_src = "'\\\\'"
        else:
            sprite_src = f"'{sprite}'"

        slots = []
        for attack in parse_attacks(attack_line):
            if attack is None:
                slots.append(0)
                continue
            if attack not in attack_index:
                if next_attack > 65535:
                    attack_index[attack] = 1
                else:
                    attack_index[attack] = next_attack
                    new_attacks.append(attack)
                    next_attack += 1
            slots.append(attack_index[attack])

        move = remap_move(cmove)
        defense = remap_defense(cdef) & 0xFFFF
        spell_bits = remap_spells(spells)
        creatures.append(
            f'    {{"{c_string(name)}", 0x{move:08X}L, 0x{spell_bits:08X}L, 0x{defense:04X}, '
            f"{exp:5d}, {sleep:3d}, {aaf:3d}, {ac:3d}, {speed:3d}, {sprite_src}, "
            f"{{{hd_dice:3d}, {hd_sides:3d}}}, {{{slots[0]:3d}, {slots[1]:3d}, {slots[2]:3d}, {slots[3]:3d}}}, {level:3d}}},"
        )
        existing.add(norm_name(name))

    monster_text = [
        "// Imoria creatures appended ahead of the end-game pair.",
        "// Movement, spell, and defense bits are remapped onto Umoria.",
        *creatures,
    ]
    (OUT / "data_imoria_monsters.inc").write_text("\n".join(monster_text) + "\n")

    attack_lines = ["    // Attacks introduced by Imoria creatures."]
    for kind, desc, dice, sides in new_attacks:
        attack_lines.append(f"    {{{kind}, {desc}, {{{dice}, {sides}}}}},")
    (OUT / "data_imoria_attacks.inc").write_text("\n".join(attack_lines) + "\n")

    total_creatures = 279 + len(creatures)
    total_attacks = next_attack
    print(f"creatures_added {len(creatures)}")
    print(f"MON_MAX_CREATURES {total_creatures}")
    print(f"attacks_added {len(new_attacks)}")
    print(f"MON_ATTACK_TYPES {total_attacks}")
    print(f"skipped {skipped}")
    print(f"attack_index_max {max(slots_max(creatures), default=0)}")


def slots_max(creatures):
    vals = []
    for line in creatures:
        match = re.search(r"\{(\s*\d+,\s*\d+,\s*\d+,\s*\d+)\},", line)
        if match:
            vals.extend(int(x) for x in match.group(1).split(","))
    return vals


def main():
    emit_spells(parse_spells())
    emit_monsters()


if __name__ == "__main__":
    main()
