#!/usr/bin/env python3
"""SAT>IP RTSP Tune-Test: OPTIONS -> SETUP -> PLAY -> RTP/RTCP zaehlen -> TEARDOWN."""
import argparse, socket, sys, time


def rtsp_exchange(sock, req):
    """Roh-Socket statt makefile (kein Poisoning nach Timeout)."""
    sock.sendall(req.encode())
    buf = b""
    try:
        while b"\r\n\r\n" not in buf:
            chunk = sock.recv(4096)
            if not chunk:
                break
            buf += chunk
    except (socket.timeout, TimeoutError):
        pass
    text = buf.decode("latin1")
    head = text.split("\r\n\r\n", 1)[0]
    return head.split("\r\n")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--server", default="192.168.178.1")
    ap.add_argument("--port", type=int, default=554)
    ap.add_argument("--src", default="1")
    ap.add_argument("--freq", required=True)
    ap.add_argument("--msys", default="dvbc")
    ap.add_argument("--mtype", required=True)
    ap.add_argument("--sr", default="6900")
    ap.add_argument("--specinv", default="0")
    ap.add_argument("--duration", type=float, default=10.0)
    ap.add_argument("--dump-ts", default="",
                    help="TS-Nutzdaten (ohne RTP-Header) in Datei schreiben")
    a = ap.parse_args()

    uri = (f"rtsp://{a.server}/?src={a.src}&freq={a.freq}&msys={a.msys}"
           f"&mtype={a.mtype}&sr={a.sr}&specinv={a.specinv}&pids=all")

    rtp = rtcp = None
    for base in range(50000, 51000, 2):
        try:
            t1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            t1.bind(("0.0.0.0", base))
            t2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            try:
                t2.bind(("0.0.0.0", base + 1))
            except OSError:
                t1.close()
                t2.close()
                continue
            rtp, rtcp = t1, t2
            break
        except OSError:
            continue
    if rtp is None:
        print("FEHLER: keine freien Port-Paare", flush=True)
        return 2
    p_rtp, p_rtcp = rtp.getsockname()[1], rtcp.getsockname()[1]
    print(f"client_port={p_rtp}-{p_rtcp}", flush=True)
    rtp.settimeout(0.5)
    rtcp.settimeout(0.5)

    s = socket.create_connection((a.server, a.port), timeout=10)
    s.settimeout(8)
    print(f"RTSP via lokal {s.getsockname()[0]} -> {a.server}", flush=True)

    cseq = 0

    def cmd(method, target, extra=""):
        nonlocal cseq
        cseq += 1
        req = f"{method} {target} RTSP/1.0\r\nCSeq: {cseq}\r\n{extra}\r\n"
        return rtsp_exchange(s, req)

    print(f"URI: {uri}", flush=True)
    # Plugin fragt OPTIONS mit voller URI (rtsp.c), NICHT "OPTIONS *"
    r = cmd("OPTIONS", uri)
    print(f"OPTIONS uri -> {r[0] if r else 'TIMEOUT'}", flush=True)
    if not r:
        print("KEINE RTSP-ANTWORT (Firewall/Server?)", flush=True)
        return 2

    r = cmd("SETUP", uri,
            f"Transport: RTP/AVP;unicast;client_port={p_rtp}-{p_rtcp}\r\n")
    print(f"SETUP -> {r[0] if r else 'KEINE ANTWORT'}", flush=True)
    if not r:
        return 2
    session = ""
    for line in r:
        if line.lower().startswith("session:"):
            session = line.split(":", 1)[1].split(";")[0].strip()
    print(f"Session: {session or 'FEHLT'}", flush=True)
    if not session:
        return 2

    r = cmd("PLAY", uri, f"Session: {session}\r\n")
    print(f"PLAY -> {r[0] if r else 'KEINE ANTWORT'}", flush=True)

    n_rtp, n_rtcp, first_rtcp = 0, 0, b""
    ts_f = open(a.dump_ts, "wb") if a.dump_ts else None
    t_end = time.time() + a.duration
    while time.time() < t_end:
        for sock, kind in ((rtp, "rtp"), (rtcp, "rtcp")):
            try:
                data, _ = sock.recvfrom(65536)
            except socket.timeout:
                continue
            if kind == "rtp":
                n_rtp += 1
                if ts_f and len(data) > 12:
                    ts_f.write(data[12:])
            else:
                n_rtcp += 1
                if not first_rtcp:
                    first_rtcp = data[:64]
    if ts_f:
        ts_f.close()
    print(f"ERGEBNIS freq={a.freq} {a.mtype}: RTP-Pakete={n_rtp} "
          f"RTCP-Pakete={n_rtcp}", flush=True)
    if first_rtcp:
        print(f"RTCP-Head: {first_rtcp.hex()}", flush=True)
    print("LOCK=" + ("JA (RTP fliesst)" if n_rtp > 0 else "NEIN (kein RTP)"),
          flush=True)

    r = cmd("TEARDOWN", uri, f"Session: {session}\r\n")
    print(f"TEARDOWN -> {r[0] if r else 'KEINE ANTWORT'}", flush=True)
    return 0 if n_rtp > 0 else 1


if __name__ == "__main__":
    sys.exit(main())
