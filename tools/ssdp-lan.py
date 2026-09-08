import socket
import struct
import time

MCAST = "239.255.255.250"
PORT = 1900
LAN = "192.168.178.61"
MSG = ("M-SEARCH * HTTP/1.1\r\n"
       "HOST: 239.255.255.250:1900\r\n"
       'MAN: "ns=01"\r\n'
       "MX: 3\r\n"
       "ST: urn:ses-com:device:SatIPServer:1\r\n\r\n").encode()


def run(label, bind_port):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    # Senden ueber LAN-Interface (wie DVBViewer: Interface zur Fritz!Box)
    s.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_IF,
                 socket.inet_aton(LAN))
    # Gruppe auf LAN-Interface joinen (Empfang)
    s.bind(("0.0.0.0", bind_port))
    mreq = struct.pack("4s4s", socket.inet_aton(MCAST),
                       socket.inet_aton(LAN))
    s.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
    s.settimeout(8)
    s.sendto(MSG, (MCAST, PORT))
    print("[%s] M-SEARCH via %s (bind :%d) gesendet" % (label, LAN, bind_port),
          flush=True)
    n = 0
    t = time.time()
    while time.time() - t < 7:
        try:
            d, a = s.recvfrom(4096)
        except socket.timeout:
            break
        n += 1
        print("[%s] ANTWORT von %s:" % (label, a))
        print(d.decode("latin1")[:700])
        print("-----", flush=True)
    print("[%s] Ergebnis: %d Antwort(en)" % (label, n), flush=True)
    s.close()


run("LAN-IF ephemeral", 0)
run("LAN-IF :1900 (plugin-identisch)", 1900)
