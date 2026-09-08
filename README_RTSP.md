# SAT>IP RTSP Tune-Tests (FRITZ!Box 6591 / Vodafone Kabel)

Stand: 2026-09-08. Werkzeug: `tools/rtsp-tune-test.py`
(`OPTIONS → SETUP → PLAY → RTP/RTCP zählen → TEARDOWN`, optional `--dump-ts`).

## URL-Format (so baut es auch das Plugin, `vdr-plugin-satip/tuner.c`)

```text
rtsp://192.168.1.1/?src=1&freq=330&msys=dvbc&mtype=256qam&sr=6900&specinv=0&pids=all
```

| Param | Bedeutung |
|---|---|
| `src` | Tuner-Index der Box (0–3) |
| `freq` | MHz |
| `msys` / `mtype` / `sr` / `specinv` | DVB-C, Modulation, Symbolrate, Inversion |
| `pids=all` | Full-TS (alle PIDs) |

## Ergebnisse

| Transponder | RTSP-Antworten | Stream | TS-Dump | Fazit |
|---|---|---|---|---|
| 330 MHz / 256QAM / SR 6900 | `200 OK` überall | RTP fließt, aber **0 Byte Nutzdaten** (leere Header) | `logs/330-ts.bin` = 0 Bytes | **unbelegt** (passt zu [Vodafone-Belegung](https://helpdesk.vodafonekabelforum.de/sendb/belegung-188.html)); Box meldet Session/Lock, liefert aber kein TS |
| 610 MHz / 64QAM / SR 6900 | `200 OK` überall | RTP + RTCP fließen | `logs/610-ts.bin` ≈ 39 KB, Sync-Offset 0 (8/8), echte PIDs | **belegt** (Das Erste HD & Co.) |

Konsequenz für Scans: Auf leeren TPs wie 330 MHz steppt `w_scan_cpp` nach ~1 s
weiter (`tuning to …` ohne `lock.`, keine Services) – kein Fehler, kein Inhalt.

## Voraussetzungen / Stolpersteine

1. **Firewall (Privat-Profil):** RTSP (TCP 554 raus) geht immer, aber RTP/RTCP
   (inbound UDP auf ephemeren Ports) fällt ins Default-Block. Jeweils einmalig
   als Admin freischalten – Regel muss **programmbezogen ohne Port-Einschränkung**
   sein (Port-1900-Regel allein reicht nicht):
   ```powershell
   netsh advfirewall firewall add rule name="Python RTP-RTCP (UDP)" dir=in action=allow program="C:\ProgramData\Python\python.exe" protocol=UDP profile=private
   ```
   Analog existieren Regeln für `w_scan_cpp` (dist + build, TCP/UDP,
   Privat + Öffentlich) in `tools/firewall-rules.ps1`.
2. **Interface:** Unicast-Routing ist sauber (`192.168.1.0/24 → WLAN`,
   Hyper-V Default Switch isoliert auf `172.22.80.0/20`). Das Skript loggt die
   lokale Quell-IP (`RTSP via lokal …`) – bei Multihoming dort prüfen.
   `destination=` im SETUP-Transport ist **nicht** nötig (Plugin schickt plain
   `RTP/AVP;unicast;client_port=`).
3. **Box-Eigenheiten:** `OPTIONS *` wird ignoriert (Timeout) – immer
   `OPTIONS <volle URI>` senden (wie libcurl im Plugin, `rtsp.c`). `client_port`
   muss ein echtes Paar `N/N+1` sein (Skript bindet 50000–50001 ff.).
4. **SSDP-Auto-Discovery:** Die Box beantwortet kein M-SEARCH (nur RTSP +
   `satipdesc.xml` leben) → Scans brauchen `--satip-server "IP|MODEL|DESC"`.

## Reproduktion

```powershell
python tools/rtsp-tune-test.py --freq 610 --mtype 64qam --duration 12 --dump-ts logs/610-ts.bin
python tools/rtsp-tune-test.py --freq 330 --mtype 256qam --duration 10
```
