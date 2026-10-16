# ImoriaPlus roadmap

ImoriaPlus 5.8 plays from the Umoria 5.7 engine and takes its extra content
from Imoria 4.85 (`values.inc`, `monsters.dat`, and the Pascal sources).
This is what that pass covers, and what is still open.

## In this version

- Ten races: Human, Half-Elf, Elf, Halfling, Gnome, Dwarf, Half-Orc,
  Half-Troll, Phraint, and Dryad, with Imoria stat adjustments, hit dice,
  infravision, experience, class masks, and backgrounds.
- Ten classes: Warrior, Mage, Priest, Rogue, Ranger, Paladin, Druid, Bard,
  Adventurer, and Monk, with Imoria hit dice, skills, titles, and realms.
- Spell realms: mage books (Mage, Adventurer), prayer books (Priest, Paladin),
  song books (Rogue, Bard), druid instruments (Ranger, Druid), and unarmed
  monk disciplines. Each realm has the 40 Imoria spells for that class.
  Spells 31-39 are stored in the book's `misc_use` field because bit 31 of
  `flags` means cursed.
- 133 Imoria creatures that were not already in Umoria, inserted ahead of
  Evil Iggy and the Balrog. Movement, spell, and defense bits are remapped
  onto Umoria's flags. Levels above 40 are clamped to 40.
- Eleven haggling shops on a 44 by 132 town: the original six, plus an Inn,
  Library, Music Shop, Gem Store, and Deli. A river and two fountains use a
  walkable water tile. Wading costs a little food.
- The curses screen is isolated in `src/ui_io.cpp`. `imoriaplus_smoke` links
  a headless stand-in instead, which is the same seam a later Emscripten
  build would use.

## Still open

- Trading Post, Bank, Insurance, Casino, Money Exchange, and private houses.
- Several coin metals. Gold is still one `au` pile. Imoria's coin rates
  (iron through mithril) are not applied.
- Quests, mugging, the day/night hour clock (`cur_age.hour`, Imoria's
  9600-turn day), and the full drown/swim model. Water is wadeable and
  costs food. Creatures do not swim, and the player does not drown.
- Monster magic resistance (`mr`). Imoria attack types above 24 (charisma
  drain, petrify) are ordinary hits. Attack descriptions that Umoria leaves
  compiled out (kick, embrace) read as a normal hit.
- A full retune of the 400-plus objects Umoria already had. New books and
  shop doors were appended. The imported creatures are the ones whose names
  were not already in Umoria, not a replacement of every shared monster's
  statistics.
- Summon-only creatures (the "will not normally appear" bit, and a level
  above 0). There is no summon-by-name yet, so those entries were left out.
- Per-spell effects that Imoria implements and Umoria does not. Unmapped
  spells heal for their mana cost and print the spell name. Charm, fear,
  and blindness are approximated with the existing sleep and confuse timers.
- Hoarse-voice checks for songs. The caster still has to be free of fear,
  confusion, and blindness.
- The Emscripten / browser front end. Do not start it until the engine seam
  above is the only display dependency.
