# Moria-family races and classes

This note lists playable races and classes found in Moria-family source and documentation, and where a Jester class and a Sage Elf race do or do not appear. Nothing here was filled in from memory. If a tree was not opened, the gap is stated.

ImoriaPlus already implements the Imoria 4.85 set in `src/data_player.cpp`: ten races (Human, Half-Elf, Elf, Halfling, Gnome, Dwarf, Half-Orc, Half-Troll, Phraint, Dryad) and ten classes (Warrior, Mage, Priest, Rogue, Ranger, Paladin, Druid, Bard, Adventurer, Monk). No further race or class was added. Every additional set below that has real numbers sits in a license that cannot be combined with this tree's GPL-3.0-or-later terms, or it has a name without a stat block. Inventing replacement numbers was out of scope.

## Jester and Sage Elf

Both are in **Pmoria**, a modification of Umoria 5.5.0. They are not in Imoria, Umoria, VMS Moria 4.8, Moria UB 5.0, iCmoria, Morgul, BOSS, the colour Umoria 5.5 tree, or the current Angband race and class files.

Source archive: <http://www.nic.funet.fi/pub/unix/games/moria/unofficial/source/pmoria.tar.Z> (also mirrored at <http://ftp.zx.net.nz/pub/archive/ftp.funet.fi/pub/unix/games/moria/unofficial/source/pmoria.tar.Z>). Inside that archive:

- Race `Sage Elf` is the tenth entry of `race[]` in `pmoria/source/player.c` (the initializer begins `{"Sage Elf", -3,  1,  3,  0, -3, -1,`). `MAX_RACES` is 10 in `pmoria/source/constant.h`.
- Class `Jester` is an entry of `class[]` in the same `player.c` (`{"Jester", 4, 40, 25, 4, 24, 50, 55, 30, 1,-2, 2, 3, 1, 4, MAGE,25, 5, 15,12}`). Its spell realm is `MAGE`. `MAX_CLASS` is 13.
- `pmoria/pmoria.mod` ("PMoria 0.98 Modifications") describes Sage Elf as "Very wise Elf, makes GREAT Priests" and Jester as "very well-balanced character class. No strengths, no weaknesses. Fair magic."

`get_class()` in `pmoria/source/create.c` tests `race[].rtclass` from the least significant bit, and bit 0 is Warrior. With that order the Sage Elf mask `0x17CF` allows Warrior, Mage, Priest, Rogue, Demigod, Sage, Jester, Ninja, Healer, and Monk. It does not allow Ranger, Paladin, or Wizard.

The same `player.c` header is the James E. Wilson / Robert A. Koeneke grant: copy and distribute for educational, research, and not-for-profit purposes only, with that statement kept. That grant is not GPL-compatible, so the Pmoria rows were not copied into this tree.

Nearby strings that are not a Jester class or a Sage Elf race:

- Imoria and iCmoria bard rank titles include `Jester (1st)`, `Jester (2nd)`, and `Bardic Sage` (`imoria/src/values.inc`, `icmoria/values.h`). Those are titles on the Bard class.
- Both trees have a monster named Jester (`imoria/monsters.dat`, `icmoria/monsters.dat`) and a shopkeeper `Kelstor the Sage (Human)` (`imoria/src/values.inc`, `icmoria/values.h`).
- A web search for the phrase "Sage Elf" also hits HollowWiki, which uses it as another name for a wood elf. That is not a Moria-family game and was not used.

## Already in this game (Imoria 4.85)

Pascal source: <https://github.com/dungeons-of-moria/imoria>, `src/values.inc`, the `race` and `class` arrays. The C port <https://github.com/dungeons-of-moria/icmoria> repeats the same names in `values.h`. The GitHub metadata for the Pascal repository has no SPDX license, and the cloned tree has no `LICENSE` file. The rows already live in `src/data_player.cpp`; they were not copied again.

Class bit order, least significant bit first, is the comment in `values.inc`: Warrior, Mage, Priest, Rogue, Ranger, Paladin, Druid, Bard, Adventurer, Monk. Masks in that file, and the same masks in `src/data_player.cpp`:

| Race | Mask | Classes |
| --- | --- | --- |
| Human | `0x3FF` | all ten |
| Half-Elf | `0x3FF` | all ten |
| Elf | `0x1DF` | Warrior, Mage, Priest, Rogue, Ranger, Druid, Bard, Adventurer |
| Halfling | `0x2CA` | Mage, Rogue, Druid, Bard, Monk |
| Gnome | `0x04E` | Mage, Priest, Rogue, Druid |
| Dwarf | `0x045` | Warrior, Priest, Druid |
| Half-Orc | `0x20D` | Warrior, Priest, Rogue, Monk |
| Half-Troll | `0x005` | Warrior, Priest |
| Phraint | `0x39B` | Warrior, Mage, Rogue, Ranger, Bard, Adventurer, Monk |
| Dryad | `0x2D4` | Priest, Ranger, Druid, Bard, Monk |

Beyond stock Umoria, the additions are the races Phraint and Dryad and the classes Druid, Bard, Adventurer, and Monk.

## Stock Moria and Umoria (no additions)

Eight races: Human, Half-Elf, Elf, Halfling, Gnome, Dwarf, Half-Orc, Half-Troll. Six classes: Warrior, Mage, Priest, Rogue, Ranger, Paladin.

Checked sources:

- VMS Moria 4.8, <https://github.com/dungeons-of-moria/vms-moria>, `source/include/values.inc` (`race` and `class`).
- Umoria historical manual, <https://github.com/dungeons-of-moria/umoria/blob/master/historical/manual.md>, sections 3.4, 3.5, and 3.5.1. The same eight-by-six table is in the manual mirrored at <https://gmoria.nongnu.org/moria.html> and in the spoiler at <https://www.beej.us/moria/mmspoilers/character.html>.
- Colour Umoria, <http://www.nic.funet.fi/pub/unix/games/moria/unofficial/source/colour.umoria.tar.Z>, `umoria/source/player.c`: the same eight races. The rank-title blocks run Warrior through Paladin only.
- Umoria FAQ (Grabiner), <https://github.com/HunterZ/umoria/blob/master/doc/faq>. It describes PC-Moria, Amiga, Atari, and Mac builds as ports of Umoria, and XMoria as Moria for X Windows (`/pub/Games/Moria/XMoria/xm1.07.tar.Z`). That FAQ does not give any of those ports a different race or class list. The XMoria tarball and Amiga Moria 3.0 were not unpacked here; the FAQ's note on Amiga Moria 3.0 is about monsters, items, and bugs, not races or classes.

## Pmoria (the extra set that includes Jester and Sage Elf)

Archive and files cited above. `pmoria/source/player.c` replaces Gnome with Spectre. `pmoria/pmoria.mod` says so directly: "Spectre (replaces Gnome)".

Races, in `race[]` order: Human, Half-Elf, Elf, Halfling, Spectre, Dwarf, Half-Orc, Half-Troll, Avion, Sage Elf. There is no Gnome.

Classes, in `class[]` order: Warrior, Mage, Priest, Rogue, Ranger, Paladin, Demigod, Sage, Jester, Ninja, Healer, Wizard, Monk.

The rank-title block immediately before the Sage titles is commented `Merchants` (Sailor, Trader, Shopkeeper, and similar). The class record at that index is named Demigod, and `pmoria.mod` describes Demigod as a fighter with priest prayers. The title comment and the class name disagree; both are in the file.

Spell realms on the new classes, from the `class[]` initializers: Demigod `PRIEST`, Sage `SAGE`, Jester `MAGE`, Ninja `SAGE`, Healer `PRIEST`, Wizard `MAGE`, Monk `NONE`. `SAGE` is a separate realm (`#define SAGE 4` in `pmoria/source/constant.h`, books `TV_SAGE_BOOK`).

Allowed classes from the `rtclass` masks, using the least-significant-bit order in `create.c`:

| Race | Mask | Not allowed |
| --- | --- | --- |
| Human, Half-Elf | `0x1FFF` | none |
| Elf | `0x15CF` | Ranger, Paladin, Ninja, Wizard |
| Halfling | `0x07CB` | Priest, Ranger, Paladin, Wizard, Monk |
| Spectre | `0x088D` | Mage, Ranger, Paladin, Demigod, Jester, Ninja, Healer, Monk |
| Dwarf | `0x00C5` | Mage, Rogue, Ranger, Paladin, Jester, Ninja, Healer, Wizard, Monk |
| Half-Orc | `0x01CD` | Mage, Ranger, Paladin, Ninja, Healer, Wizard, Monk |
| Half-Troll | `0x0145` | Mage, Rogue, Ranger, Paladin, Sage, Ninja, Healer, Wizard, Monk |
| Avion | `0x044F` | Ranger, Paladin, Sage, Jester, Ninja, Wizard, Monk |
| Sage Elf | `0x17CF` | Ranger, Paladin, Wizard |

`pmoria.mod` also describes mechanics that are not just the stat row: armor weight limits, monk unarmed AC, warrior innate resists, and sage spells whose text it tells the player to discover in game. Those behaviors are not in ImoriaPlus, and the source license blocks copying them.

## Morgul

Archive: <http://www.nic.funet.fi/pub/unix/games/moria/unofficial/source/morgul05.tar.Z>. `morgul/source/player.c` has the stock eight races and six classes. Background text mentions Dark Elf, Green Elf, Grey Elf, and High Elf as ancestry, not as playable races. `morgul/source/main.c` carries the same not-for-profit Wilson/Koeneke statement. The Umoria FAQ calls Morgul an expansion of Umoria 5.5.0; the race and class tables themselves are not expanded.

## PC "druid" Umoria 5.5

Directory: <https://beej.us/moria/files/morialike/unofficial/pc/druid5.5/>. `version.hlp` is the Umoria 5.5 not-for-profit notice. `moria1.txt.gz` and `spells.doc` in that directory describe the stock eight races and six classes and do not mention a Druid class.

`druid.exe` from the same directory does. `strings` on that binary shows the class list Warrior, Mage, Priest, Rogue, Ranger, Paladin, Druid, and the race list Human, Half-Elf, Elf, Halfling, Gnome, Dwarf, Half-Orc, Half-Troll. Rank-title strings include `1st Circle` through `15th Circle`, Follower, Worshiper, Initiate, Planter, Celt, `Druid (1st)` through `Druid (8th)`, Arch-Druid, High Druid, Great Druid, and Grand Druid. Those titles are not the Imoria druid titles (Ovate, Cabal, Hierophant). No C or Pascal source for this executable was in the directory, so there is no stat block to port, and the accompanying license text is not GPL-compatible.

An old index, <https://ftp.funet.fi/index/files/index/unix/games/moria/mac/00index.txt>, describes MacMoria 5.5d and PXMoria 1.0d as UMoria 5.5 with druids added, and says non-druid play matches plain UMoria 5.5. Those source archives were not in the current Funet or Beej `unofficial/mac/` listings (those listings have JAMoria and MacMorgul only), so the druid stat rows were not read.

## Moria UB 5.0 (VMS Moria 5.0)

<https://github.com/dungeons-of-moria/moria-ub>. `source/include/values.inc` has the stock eight races. The `class` array adds two records after Paladin: `Consultant` and `Consultant2`. The comment above the race masks says the bits, from most significant to least significant, are Consultant2, Consultant, Paladin, Rogue, Priest, Mage, Rogue, Fighter. Every race mask in that file is `%B'00111111'`, so the two high bits are clear. `source/include/create.inc` offers a class only when `race[].tclass` intersects `bit_array`, and `bit_array[1]` is the least significant bit, which is Warrior. Consultant and Consultant2 are therefore not offered at character creation. Their rows in `source/include/spell_values.inc` are empty names at level 99. The repository has no SPDX license. These two records were not implemented.

## BOSS (Beyond Moria)

<https://github.com/dungeons-of-moria/boss-beyond-moria>. `boss.pas` says Moria may be copied and modified if the credits stay, and that nobody may sell or market the software without Robert Alan Koeneke's written consent. That no-sale term is not GPL-compatible. BOSS is also a different game: the README says it has no magic and uses skills, guns, and multiple cities. Porting a class would mean inventing a fantasy equivalent. Nothing from BOSS was implemented.

Playable `race[]` entries in `inc/variables.inc` are qualities, not the fantasy races. `inc/constants.inc` sets `max_races = 8` and `max_class = 9`. Qualities: Elite, Hefty, Mad, Wise, Lucky, Healthy, Sexy, Alien. Classes, in order: Wrestler, Scientist, Guru, Ninja, Soldier, Wanderer, Con-Artist, Thief, Journalist.

`inc/create.inc` tests `bit_array[i2]` with `bit_array[1] = $00000001`, so the least significant bit is class 1, Wrestler. The comment on `race[]` lists eight bits, most significant first: Thief, Con-Artist, Wanderer, Soldier, Ninja, Guru, Scientist, Wrestler. It does not mention Journalist. Elite through Sexy use `%11111111` (classes 1 through 8). Alien uses `%10111011`, which clears Guru and Con-Artist. None of the eight masks sets bit 9, so `get_class` does not offer Journalist even though `class[]` has a Journalist record.

The FAQ at <http://www.nic.funet.fi/pub/files/index/unix/games/moria/FAQ.BOSS.1.1.1992> describes three setting races: humans, Jarwangians, and Daysians. Those names are not `race[].trace` values. They show up in background text (for example `Jarwangian Thief`) and in monster help (`inc/help.inc` has "Alien Daysians" and "Jarwangian Molds"). RogueBasin's BOSS page (<https://roguebasin.com/index.php/BOSS>) repeats the FAQ's three races and lists the nine classes, including Journalist.

## JAMoria

<http://www.nic.funet.fi/pub/unix/games/moria/unofficial/mac/JAMORIA-README.txt> (John Magdaleno, `cooljohn@leland.stanford.edu`). The readme describes a pre-1.0 MacMoria 5.5 with outdoor adventures, rivers, multiple towns, and multiple dungeons. It does not mention races or classes. The companion file is `jamoria-pre-1.sea.hqx.gz`, a BinHex Mac archive. It was not decoded, so this note does not claim the binary has no extra race or class.

## Angband

Current data files on <https://github.com/angband/angband>:

- `lib/gamedata/p_race.txt`: Human, Half-Elf, Elf, Hobbit, Gnome, Dwarf, Half-Orc, Half-Troll, Dunadan, High-Elf, Kobold. Hobbit is the Angband name for the Moria halfling. Dunadan, High-Elf, and Kobold are the extra races.
- `lib/gamedata/class.txt`: Warrior, Mage, Druid, Priest, Necromancer, Paladin, Rogue, Ranger, Blackguard. Druid, Necromancer, and Blackguard are the extra classes relative to stock Moria. `lib/gamedata/old_class.txt` still lists only Mage, Priest, Rogue, Ranger, and Paladin.

`docs/copying.rst` dual-licenses Angband under GPLv2 (not "or later") or the not-for-profit Angband licence. Neither alternative can be combined with GPL-3.0-or-later, so those tables were not copied. Downstream Angband variants (ToME, PosChengband, and the rest) were not opened; this note does not list their races or classes.

## What was implemented

Nothing new. Phraint, Dryad, Druid, Bard, Adventurer, and Monk are already in `src/data_player.cpp`. Jester, Sage, Sage Elf, Spectre, Avion, Demigod, Ninja, Healer, Wizard, the Pmoria Monk, the PC druid binary's Druid, Consultant, Consultant2, and the BOSS qualities and classes all have a source, and each of those sources is either not GPL-compatible or, for the druid executable and JAMoria archive, not a readable stat table. Writing new numbers for them would be invention.
