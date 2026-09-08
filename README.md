# w_scan_cpp (SAT>IP-only) – MSYS2-Build

Baut `w_scan_cpp` unter Windows mit MSYS2 (msys-Toolchain, kein MinGW):
SAT>IP-Tuning via vendored VDR + vdr-plugin-satip, Linux-DVB-Header als Shim.

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
| 7 | femon-Verify (ein Transponder, ~40 s) | inline |

Optionen: `--skip-install` (MSYS schon eingerichtet),
`--skip-verify`, `--satip-server "IP|MODEL|DESC"`,
`--verify-channel "VDR-Zeile"`, Env `SATIP_SERVER`/`VERIFY_CHANNEL`.

Hinweise:

- Stufe 1 macht ein volles `pacman -Syu`; beim allerersten Lauf auf frischem
  MSYS ggf. zweimal laufen lassen („restart required“).
- Stufe 2 läuft bewusst nur auf pristine Quellen (kein `--forward`) – danach
  ist der Tree gepatcht, das ist normaler Pipeline-Zustand.
- Stufe 7 stimmt per `-F` genau einen Transponder ab (Endlosschleife, wird per
  `timeout` beendet, RC 124 erwartet) und verlangt `lock 1`. Ohne
  `SATIP_SERVER` wird sie übersprungen. Beispiel-Referenz: `scan.txt`.
- Logs landen in `logs/` (ausgeblendet, siehe unten).

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
- `tools/ssdp-*.py` – SSDP-/M-SEARCH-Diagnose.
- `tools/06-patches.sh` – Patches aus Diffs regenerieren (Dev).
- `tools/firewall-rules.ps1` – Windows-Firewallregeln (als Admin).
- `scan.txt` – Referenz-Kanalliste eines Verifikationslaufs (327 Kanäle).
