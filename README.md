# gRPC_chat
A simple gRPC based chat application in C++.


1) To build the project, run the following.

    `git clone https://github.com/jitpaul/gRPC_chat.git`
    `cd gRPC_chat`
    `mkdir build`
    `cd build`
    `cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..`
    `make`

2) Now, to run the client, run the following.
    `src/chat_client`

3) To run the server, run the following.
    `src/chat_server`