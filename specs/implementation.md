# Compass Cardinals: behavior and implementation

Describes the retained payload **0.2.0**. The behavior prose describes the retained payload; current candidate source and metadata are identified below. Gameplay qualification is a separate requirement.


<!-- source-only-sync -->
## Current source candidate

Source version **0.2.0** is saved from workshop revision `ca32bbf79ce0840d5166a232bdb3a9fdcd761254`. The retained installable payload remains **0.2.0** with its original bytes. This source update does not rebuild or requalify that payload. The current source and metadata define the candidate; gameplay, rendered behavior and co-op remain unqualified for rebuilt bytes.

The authored behavior and lifecycle descriptions below are retained from the published payload. They are not new qualification evidence for the source candidate. The integration table below follows the current candidate metadata.
<!-- /source-only-sync -->

## Behavior

Shop Framework sells a $100 passive compass upgrade. Once owned, a four-letter cardinal ribbon follows the native service-compass heading while on foot. Bearings wrap and letters outside the forward arc hide. It requires no held equipment slot or independent equip toggle; map/UI state suppresses the ribbon. Hints Framework supplies contextual controls through the normal legend.

## State and lifecycle

Ownership uses the checked per-world/player compass sidecar. Visibility and scene objects are temporary; world/player changes release rooted objects and reload the appropriate ownership. Purchase and persistent grants remain host-authoritative.

## Integration and configuration

Runtime dependencies: [shop-framework](https://github.com/swooping-mods/shop-framework), [hints-framework](https://github.com/swooping-mods/hints-framework).

The [module metadata](../source/mods/compass-cardinals/mod.json) owns the version and declared integration contract. Native modules start at `MoonLab_ModStart`. Game/Unity integrations target the pinned Steam Windows x64 IL2CPP build.

| Service | ABI | Table size |
|---|---:|---|
| Requires `shop-framework.shop` | 1 | at least 56 bytes |
| Requires `hints-framework.hints` | 1 | at least 24 bytes |

## Implementation sources

- [mod.c](../source/mods/compass-cardinals/mod.c)
- [framework.h](../source/mods/compass-cardinals/framework.h)
- [runtime.h](../source/mods/compass-cardinals/runtime.h)
- [store.h](../source/mods/compass-cardinals/store.h)

## Verification boundary

This is a compass presentation upgrade, not a navigation planner. Cardinal alignment, HUD layout and ownership reload need matching game-build checks.

`python3 build.py --check` verifies the exported source hashes. It does not execute the mod or qualify the behaviors above. Installation and independent build prerequisites are in the [README](../README.md).
