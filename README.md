# w_scan_cpp (SAT>IP-only) – MSYS2-Build

Baut `w_scan_cpp` unter Windows mit MSYS2 (msys-Toolchain, kein MinGW):
SAT>IP-Tuning via vendored VDR + vdr-plugin-satip, Linux-DVB-Header als Shim.

## Herkunft, Dank, Lizenz

Dieses Repo ist ein Fork von
[wirbel-at-vdr-portal/w_scan_cpp](https://github.com/wirbel-at-vdr-portal/w_scan_cpp)
und enthält ausschließlich Ergänzungen für den MSYS2-Build (Patches, Skripte, CI);
die Upstream-Quellen liegen unverändert in `w-scan-cpp-20260515+dfsg/`, Änderungen
dazu als `patches/101-*` … `patches/112-*`.

- Original-Autor: **Winfried Koehler („wirbel“)**, Projektseite:
  <https://www.gen2vdr.de/wirbel/w_scan_cpp/index2.html>
- Mitwirkende siehe Upstream-Datei `CONTRIBUTORS`.
- `w_scan_cpp` basiert auf [VDR](https://www.tvdr.de) von Klaus Schmidinger,
  [vdr-plugin-satip](https://github.com/rofafor/vdr-plugin-satip) von Rolf Ahrenberg
  sowie dem VDR-Plugin wirbelscan – Dank an alle Beteiligten.
- Lizenz: **GNU General Public License v2** (siehe `COPYING`, Upstream-Original).
  Alle Dateien dieses Forks, die Upstream-Code enthalten oder davon abgeleitet sind,
  stehen ebenfalls unter GPL-2.0.

## Schnellstart

```cmd
build.cmd
```

Das nutzt MSYS unter `C:\msys64`. Anderer Pfad, Priorität aufsteigend:

1. `C:\msys64` (Standard)
2. Session-Env `MSYS_ROOT`
3. `local-env.cmd` neben `build.cmd` (**lokal, nicht einchecken** – siehe `.git/info/exclude`)
4. `build.cmd --msys-root <Pfad>`

Beispiel `local-env.cmd` (nur lokal anlegen, Vorlage im Kopf behalten):

```cmd
set "MSYS_ROOT=D:\Tools\msys64"
set "SATIP_SERVER=192.168.1.1|DVBC-4|FRITZBox"
```

## Pipeline-Stufen (`tools/build.sh`)

| # | Stufe | Skript |
|---|-------|--------|
| 1 | MSYS-Pakete installieren (`pacman`) | `tools/01-install.sh` |
| 2 | Patches 101–112 auf pristine Tree | `tools/00-apply-patches.sh` |
| 3 | Vendor-/Hygiene-Checks | `tools/02-prepare.sh` |
| 4 | librepfunc (statisch) | `tools/03-librepfunc.sh` |
| 5 | Build + `--help`-Gate | `tools/04-build.sh` |
| 6 | Paket `dist/w_scan_cpp-msys-x86_64/` | `tools/05-package.sh` |
| 7 | Smoke-Test: dist-`--help` + DLL-Herkunft (ohne Netz) | inline |

Optionen: `--skip-install` (MSYS schon eingerichtet).

Hinweise:

- Stufe 1 macht ein volles `pacman -Syu`; beim allerersten Lauf auf frischem
  MSYS ggf. zweimal laufen lassen („restart required“).
- Stufe 2 läuft bewusst nur auf pristine Quellen (kein `--forward`) – danach
  ist der Tree gepatcht, das ist normaler Pipeline-Zustand.
- Logs landen in `logs/` (ausgeblendet, siehe unten).

## Verify (separat, nicht Teil der Pipeline)

`bash tools/verify-femon.sh` stimmt per `-F` genau einen Transponder ab
(Endlosschleife, wird per `timeout` beendet, RC 124 erwartet) und verlangt
`lock 1`. Braucht `SATIP_SERVER` (Env oder `--satip-server`
`"IP|MODEL|DESC"`); optional `--verify-channel`, `--exe`, `--timeout`.
Läuft später als eigener GitHub-Job, lokal nur zum Testen.
Beispiel-Referenz: `scan.txt`.

## Repo-Hygiene

- `.gitignore` (eingecheckt): generische Build-Artefakte – `*.o`, `*.d`,
  `*.a`, `*.exe`, `*.dll`, `dist/`, `logs/`, `*.log`, `*.bin`, `local/`.
- `.git/info/exclude` (nur lokal, wird nie committet): unsere
  maschinenspezifischen Dateien – `local-env.cmd`, `local/`.
- Zeilenenden: `.gitattributes` erzwingt LF für `*.sh`/`Makefile.msys`/
  `patches/`; `core.autocrlf=input` (CI setzt das vor dem Checkout).

## CI

`.github/workflows/msys-build.yml` richtet MSYS2 ein (MSYS, Update + Pakete)
und ruft danach dieselbe Pipeline auf (`tools/build.sh --skip-install
--skip-verify`), inkl. `--help`-Gate und Artifact-Upload aus `dist/`.

## Werkzeuge (nicht Teil der Pipeline)

- `tools/rtsp-tune-test.py` – reiner RTSP-Tune-Test eines Transponders.
- `tools/verify-femon.sh` – separater Lock-Test eines Transponders (s. Verify).
- `tools/ssdp-*.py` – SSDP-/M-SEARCH-Diagnose.
- `tools/06-patches.sh` – Patches aus Diffs regenerieren (Dev).
- `tools/firewall-rules.ps1` – Windows-Firewallregeln (als Admin).
- `scan.txt` – Referenz-Kanalliste eines Verifikationslaufs (327 Kanäle).
