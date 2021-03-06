HTTP-Over-Protocol (HOP)
========================

```
  _   _  ___  ____  
 | | | |/ _ \|  _ \ 
 | |_| | | | | |_) |
 |  _  | |_| |  __/ 
 |_| |_|\___/|_|    
```

# Introduction
A friend once told me that his university has an HTTP(S)-only proxy, and thus he is unable to SSH to hosts outside. 5 hours of intensive coding later using code borrowed from my course assignment, here's **HOP**.

**HOP** is a tool meant to tunnel any sort of traffic over a standard HTTP channel.

Useful for scenarios where there's a proxy filtering all traffic except standard HTTP(S) traffic. Unlike other tools which either require you to be behind a proxy which let's you pass arbitrary traffic (possibly after an initial CONNECT request), or tools which work only for SSH, this imposes no such restrictions.

# Working
Assuming you want to use SSH to connect to a remote machine where you don't have root privileges.

There will be 7 entities:

1. Client (Your computer, behind the proxy)
2. Proxy (Evil)
3. Target Server (The remote machine you want to SSH to, from Client)
4. Client HOP process
5. Target HOP process
6. Client SSH process
7. Target SSH process

If there was no proxy, the communication would be something like:
```
Client -> Client SSH process -> Target Server -> Target SSH process
```

In this scenario, here's the proposed method:
```
Client -> Client SSH process -> Client HOP process -> Proxy -> Target HOP process -> Target SSH process -> Target Server
```

**HOP** simply wraps all the data in HTTP packets, and buffers them accordingly.

Another even more complicated scenario would be if you have an external utility server, and need to access another server's
resources from behind a proxy. In this case, *hop* will still run on your external server, but instead of using `localhost`
in the second command (Usage section), use the hostname of the target machine which has the host.

# Usage
On the client machine:
```
./hop <client-hop-port> <server-host-name> <server-hop-port>
```

On the target machine:
```
./hop <server-hop-port> localhost <target-port> SERVER
```
(Note the keyword SERVER at the end)

In case of SSH, the target-port would be 22.
Now once these 2 are running, to SSH you would run the following:

```
ssh <target-machine-username>@localhost -p <client-hop-port>
```

*Note*: The keyword server tells *hop* which side of the connection has to be over HTTP.

# Contributing
Pull Requests are more than welcome! :smile:

I've put down a list of possible ideas if you would like to contribute.

# Bugs
* Currently uses a 100ms sleep after every send/receive cycle to allow for synchonizations.
* HTTP Responses may come before HTTP Requests. Let me know if you know of some proxy which blocks such responses.
* Some SSH connections break after a while, with a noticed extra connection being opened by SSH itself (on the client side). Suspected SSH attempting to create a replacement connection and killing the original connection. See issue #1

# Planned features
* Better and adaptive buffering
* Better CLI flags interface
* Parsing of .ssh/config file for hosts
* Web interface for remote server admin
* Web interface for local host
* Daemon mode for certain configs
