**Server wallet setup for further use jointly with other software** 
(pools, exchanges etc.)
To set up a separate Ethereum Future wallet on a remote Linux server
you will need a Linux system (VDS or server).
The following sever ports must be available for the ETHF demon to operate (if these are not available you can assign any other open ports instead)

    52545 is the primary port that needs to be open for remote access
    52544 is the port used by the RPC protocol for wallet control.

If one f these ports is unavailable your wallet will not start*; however, if these ports are already in use on your system you can setup your wallet on any other set of ports, provided their numbers are above 1000. Sample setups below demonstrate how to arrange this.
For your node to work properly wou will also need to ensure external access to port 52545* (or another port assigned by you for this purpose), but this is not prerequisite for receiving and sending ETHF. Optionally, you can ensure external access to this port with necessary exceptions made to the firewall on your system.
Port 52545* (or another port you plan to use instead) needs to be accessible from localhost or another IP you will set up for wallet administration with ethf-cli via RPC.
We also recommend creating a separate Linux user to operate the wallet. This is not mandatory but helps to increase security. In addition, we strongly advise against running your wallet under root on the server.

Here you can download archive with executable wallet files for linux
https://github.com/ethereumfuture/ethf/releases
Please, download the latest release.
You will need two files from the archive, ethfd and ethf-cli. Download the files into the folder, where you plan to execute them. Remember to assign these files rights to run in the system.
If you want to check source files for the wallet or make a build yourself, you can find the files here: https://github.com/ethereumfuture/ethf

Upon initiation, ethf demon by default creates all its system files in /home/user/.ethf, where it also looks for its configuration file that can be created in advance (see examples below) or generated automatically. If you prefer your EHTF wallet to use another folder you can create such folder at any convenient address and make sure the Linux user, under which you will run your wallet has full read and write access to the folder. After this you need to run your wallet assigning the following folder address:

    ./ethfd -datadir=/home/user/ethfdworkdir

If you plan to use other than default folder for your ETHF wallet data, we recommend to create a simple bash script that would contain a start-up command to prevent accidental start without the key referring to your operating folder, and use this script for start-up.

For automated wallet start-up as a demon, and for convenience of automated start-up from your app or upon your system start-up, you will need to create a config file named ethf.conf, and put it in your default operational folder or a folder you have set up using -datadir= command above. Below we provide several sample config files for different cases.

Here are config file lines for the simplest case where your demon can use all IP addresses on your servers and ports 52545 and 52544 are both available.

    daemon=1
    server=1
    listen=1
    rpcuser=ethf
    rpcpassword=yourpassword
    rpcallowip=127.0.0.1
    listenonion=0

If ports 52545 and/or 52544 are already in use on your system and you want your wallet to run only for certain IP's (e.g. if you have many IP's on one server), this is what the relevant config file lines will look like:

    daemon=1
    server=1
    listen=1
    bind=xxx.xxx.xxx.xxx:41000
    port=41000
    rpcuser=ethf
    rpcpassword=YourPassword
    rpcbind=xxx.xxx.xxx.xxx:41001
    rpcport=41001
    rpcallowip=127.0.0.1
    rpcallowip=xxx.xxx.xxx.xxx
    listenonion=0

Instead of port=41000 and rpcport=41001 use your preferred port ID's. Remember to give correct IP and port ID to ethf-cli for server access. You can also use a 

    -datadir=/home/user/ethfdworkdir key for ethf-cli start-up

, same as for demon start-ups. In this last case the utility program will take all data from the config file automatically. Another option is to run ethf-cli with the following keys:

    ./ethf-cli -rpcconnect=xxx.xxx.xxx.xxx -rpcport=41001 -rpcuser=ethf -rpcpassword=YourPassword

xxx.xxx.xxx.xxx, both in the config file example and in the example of ethf-cli start-up command is the IP address of your server where you want to run your ethf wallet.

After the config file is created according to your need, start your wallet using the following command

    ./ethfd

To check your wallet operation upon start-up, as well as its network connection and synchronization, you can run the following command

    ./ethf-cli -rpcconnect=xxx.xxx.xxx.xxx -rpcport=yurRPCport -rpcuser=ethf -rpcpassword=YourPassword getchaintips

or

    ./ethf-cli -datadir=/home/user/ethfdworkdir getchaintips

This will result in the following response

    [
	    {
		    "height" : 13085,
		    "hash" : "00000011b4dfeb395f374ebd09892578c01e91e97223e208c15e014c8324b49b",
		    "branchlen" : 0,
		    "status" : "active"
	    }
    ]

height (13085 in the example) is the number of the last synchronized block. Check http://explorer.ethereumfuture.net; if block number
in the response is the same as the last block number on the website it means your wallet successfully synchronized and is operating correctly.
Normally, this is not necessary; if everything was set up according to the instructions all you need to do is to wait a little while.

If any problems arise and your wallet is not running, you can check this file for details:

    /home/user/ethfdworkdir/debug.log

Here below are all port numbers that can be used by your wallet (in practice, you will only need the two listed above 52545 and 52544):

    Primary         52545
    testnet         42135
    regtestnet      51479
    unittest		51481
    nRPCPort        52544
    testnRPC        42131
