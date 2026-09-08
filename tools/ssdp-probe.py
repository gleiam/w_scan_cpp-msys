import socket
import time

MCAST = "239.255.255.250"
PORT = 1900
WLAN = "192.168.178.61"
MSG = ("M-SEARCH * HTTP/1.1\r\n"
       "HOST: 239.255.255.250:1900\r\n"
       'MAN: "ns=01"\r\n'
       "MX: 3\r\n"
       "ST: urn:ses-com:device:SatIPServer:1\r\n\r\n").encode()


def probe(label, mcast_if=None):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    if mcast_if:
        s.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_IF,
                     socket.inet_aton(mcast_if))
    s.settimeout(6)
    s.sendto(MSG, (MCAST, PORT))
    print("[%s] M-SEARCH gesendet" % label, flush=True)
    n = 0
    t = time.time()
    while time.time() - t < 5:
        try:
            d, a = s.recvfrom(4096)
        except socket.timeout:
            break
        n += 1
        print("[%s] ANTWORT von %s:" % (label, a))
        print(d.decode("latin1")[:600])
    print("[%s] Ergebnis: %d Antwort(en)" % (label, n), flush=True)
    s.close()


print("IP_MULTICAST_IF=%s" % socket.IP_MULTICAST_IF, flush=True)
probe("ohne IF-Option")
probe("mit IF=WLAN", mcast_if=WLAN)
