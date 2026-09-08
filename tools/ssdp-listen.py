import socket
import struct
import time

MCAST = "239.255.255.250"
PORT = 1900

# A) Loopback: TX+RX auf dieser Maschine
rx = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
rx.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
rx.bind(("0.0.0.0", 1901))
mreq = struct.pack("4s4s", socket.inet_aton(MCAST), socket.inet_aton("0.0.0.0"))
rx.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
rx.settimeout(5)
tx = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
tx.sendto(b"M-SEARCH-LOOPBACK-TEST", (MCAST, 1901))
try:
    d, a = rx.recvfrom(1024)
    print("[A] Loopback OK: %r von %s" % (d, a), flush=True)
except socket.timeout:
    print("[A] Loopback FEHLGESCHLAGEN (kein Empfang)", flush=True)
rx.close()
tx.close()

# B) 90s auf NOTIFY/beacon der Fritz!Box lauschen
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(("0.0.0.0", PORT))
s.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
s.settimeout(90)
print("[B] lausche 90s auf SSDP-Traffic ...", flush=True)
try:
    while True:
        d, a = s.recvfrom(4096)
        print("[B] Paket von %s:" % (a,), flush=True)
        print(d.decode("latin1")[:500])
        print("-----", flush=True)
except socket.timeout:
    print("[B] Ergebnis: nichts empfangen", flush=True)
