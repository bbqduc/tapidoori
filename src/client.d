module main;

import dsfml.network;
import std.stdio;

void main(string[] args)
{
    IpAddress server = "127.0.0.1";
    auto socket = new UdpSocket();

    const char msg[] = "Hey, I'm a client!";
    auto status = socket.send(msg, server, 53000);

    if(status != Socket.Status.Done)
    {
        writeln("Eipä onnistunut!");
    }
    else
    {
        writeln("Hörppyä!");
    }
}
