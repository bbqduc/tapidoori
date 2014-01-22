module main;

import dsfml.network;
import std.stdio;

void main(string[] args)
{
    auto socket = new UdpSocket();
    auto status = socket.bind(53000);
    writeln("Server is listening!");

    char inmsg[128];

    IpAddress sender;
    ushort  senderport;

    status = socket.receive(inmsg, sender, senderport);

    if(status != Socket.Status.Done)
    {
        writeln("Eipä onnistunut!");
    }
    else
    {
        writeln(inmsg);
    }
}
