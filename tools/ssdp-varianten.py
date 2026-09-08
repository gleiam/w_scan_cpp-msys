import socket
import struct
import time

MCAST = "239.255.255.250"
PORT = 1900
LAN = "192.168.178.61"
VARIANTEN = {
    "plugin-identisch": ("M-SEARCH * HTTP/1.1\r\n"
                         "HOST: 239.255.255.250:1900\r\n"
                         'MAN: "ssdp:discover"\r\n'
                         "ST: urn:ses-com:device:SatIPServer:1\r\n"
                         "MX: 2\r\n\r\n"),
    "ssdp:all": ("M-SEARCH * HTTP/1.1\r\n"
                 "HOST: 239.255.255.250:1900\r\n"
                 'MAN: "ns=01"\r\n'
                 "MX: 3\r\n"
                 "ST: ssdp:all\r\n\r\n"),
    "upnp:rootdevice": ("M-SEARCH * HTTP/1.1\r\n"
                        "HOST: 239.255.255.250:1900\r\n"
                        'MAN: "ns=01"\r\n'
                        "MX: 3\r\n"
                        "ST: upnp:rootdevice\r\n\r\n"),
}

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_IF,
             socket.inet_aton(LAN))
s.bind(("0.0.0.0", 1900))
mreq = struct.pack("4s4s", socket.inet_aton(MCAST), socket.inet_aton(LAN))
s.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
s.settimeout(6)
for name, text in VARIANTEN.items():
    s.sendto(text.encode("latin1"), (MCAST, PORT))
    print("[%s] gesendet, warte ..." % name, flush=True)
    t = time.time()
    n = 0
    while time.time() - t < 5:
        try:
            d, a = s.recvfrom(4096)
        except socket.timeout:
            break
        # eigene Loopback-Pakete ignorieren
        if a[0] == LAN:
            continue
        n += 1
        print("[%s] ANTWORT von %s:" % (name, a))
        print(d.decode("latin1")[:700])
        print("-----", flush=True)
    print("[%s] Ergebnis: %d fremde Antwort(en)" % (name, n), flush=True)
