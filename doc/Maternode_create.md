## Masternode Setup

To create a masternode, you need at least 1k ETHF on your account.
Note: If you want to set up several masternodes, you will need to have at least 1000 ETHF * masternode number and set up these consecutively, starting on the next masternode after the previous one was initiated. This needs to be consecutive; each new masternode must always be set up only after the previous one is done. Please make sure to comply with times stated in the instructions to avoid potential masternode activation problems and complete activation rapidly and smoothly.
We also strongly recommend using wallet debug console for all wallet manipulations related to masternode setup. This is not mandatory but helps prevent possible mix-ups and errors. The instructions describe initial preparation and masternode start-up as performed via debug console, except for the start-up itself, performed via GUI for convenience.
To run debug console, open Tools menu and choose Debug Console.
For your convenience and to avoid errors, we also recommend using text editor to prepare text lines with commands you will enter during setup, and use the same editor to write down all codes appearing in the debug console in course of the setup. To make sure you have all the data, save the file in a secure location preventing unauthorized access (e.g. to a memory stick).
For the masternode itself, you will need a VDS or a Linux server (Windows is also acceptable although less desirable than Linux). If you want to run several masternodes on one VDS, you can do it, provided your VDS has several external static IPV4.

## Preliminary.

For those new to Linux I recommend to install Midnight Commander. It allows convenient operations with files, access management (executable files control) and config files editing even if you are not familiar with Unix-specific VI.
If you have Debian or Ubuntu:

    apt-get update
    apt-get install mc

If you have Centos or Fedora:

    yum install mc 

OR 

    dnf install mc

After that you can start your mc by simply entering 

    mc<enter> 

in the console; 

    F10 or esc + 0 for exit

If your VDS is firewall-protected, you need to open access to the ports used by ETHF before starting the process.

    52545 - primary port required for wallet operation.
    52544* - wallet administration port*

The port marked with * should be open for external access only if you fully understand what you are doing. Generally, it needs to be accessible from localhost only, making your masternode more secure.
If you use iptables you can open the above ports with the following command (under root only):

    /sbin/iptables -A INPUT -i eth0  -p tcp --dport 52545 -j ACCEPT
    /sbin/iptables -A INPUT -i eth0  -p tcp --dport 52544 -j ACCEPT

To ensure the ports are open after system reboot, enter the commands into rc.local; or enter the ports into your VDS system configuration; or create, for example, /usr/local/sbin/iptables_init.sh and assign execution rights to it (the simplest way is via mc), with the following content:

    #!/bin/sh
    /sbin/iptables -A INPUT -m state --state RELATED,ESTABLISHED -j ACCEPT
    /sbin/iptables -A INPUT -i eth0  -p tcp --dport 22 -j ACCEPT
    /sbin/iptables -A INPUT -i eth0  -p tcp --dport 52545 -j ACCEPT
    /sbin/iptables -A INPUT -i eth0  -p tcp --dport 52544 -j ACCEPT
    /sbin/iptables -A INPUT -i eth0  -j DROP

Note: The first line ensures the masternode-initiated connections are not blocked.
The second line serves to ensure you do not lose SSH access to the VDS. Add other ports if you use the VDS for other purposes since the above rules will not only provide better security but also block all functions except for masternode and wallet operation.
Then add the following line to the file /etc/crontab :
@reboot ethfnd  /home/ethfnd/ethfd
to make sure the rules are initiated upon VDS restart.
Please write down IP address of your masternode (or IP addresses, if you have several and you plan to run several masternodes on the same VDS). To see the IP's you can use hoster panel or this command:

    root@yourvds:/usr/local/sbin# ip addr li

run under root.
You will need the IP's for masternode setup.

## Now we can start creating a masternode.

1 First of all, you need to set up the wallet and let it synchronize.
a) Create in the system a separate user under which to run the wallet (we strongly advise against running it under root).

    adduser ethf

*the name is optional, you can put in whatever you like instead of ethf. Depending on the installation package, the system will ask you for a password; make sure to remember it. If you use an RH package (e.g. CentOs or Fedora), after creating a user you will need to use a special command:

    passwd ethf

to enter password for the user.
If you plan to run several masternodes on your VDS (provided you have several external IP's), the simplest way is to create a special user (with a unique name) for each masternode
b) Upload the wallet and the wallet administration utility to the user home directory(ies) via command line.
This is the command for Linux (run from the folder where you have put binary files of the coin)

    scp ./ethfd  ethf@YourServerAddress:/home/ethf
    scp ./ethf-cli  ethf@YourServerAddress:/home/ethf

For Windows. First you need to install PuTTY freeware (https://www.putty.org/)
Then run the following command (https://www.ssh.com/ssh/putty/putty-manuals/0.68/Chapter5.html)

    pscp c:\ethf\ethfd  ethf@YourServerAddress:/home/ethf
    pscp c:\ethf\ethf-cli  ethf@YourServerAddress:/home/ethf

c) Log in to VDS via ssh under the relevant user (ethf in our case); or, if you are already logged in under root, enter

    su - ethf

To avoid creating the folder and config files manually, initiate the wallet using `./ethfd`
, wait 30 seconds while it generates the folders, and stop it with ctrl+c
d) Open the newly created folder .ethf (cd ./ethf or, more conveniently, vc), where you need just one file
Open it for editing (F4 in mc). Enter the following:

    daemon=1
    server=1
    #listen=1
    masternode=1
    bind=xxx.xxx.xxx.xxx
    rpcuser=ethf
    rpcpassword=YourPassword
    rpcallowip=yyy.yyy.yyy.yyy
    rpcallowip=127.0.0.1
    rpcallowip=xxx.xxx.xxx.xxx
    listenonion=0
    #masternodeprivkey=
    externalip=xxx.xxx.xxx.xxx

Where xxx.xxx.xxx.xxx is the IP address of your VDS or the masternode, if there are several masternodes on the VDS.
To prevent rejected access, if you have more than one IP on your, add the appropriate number or rpcallowip= lines, according to the number of addresses you have on your VDS. In most cases, this is not required, except for some VDS configurations that may on occasion give you 403 error when trying to access an active demon via ethf-cli.
yyy.yyy.yyy.yyy is your home Internet static IP, if you decide to give yourself direct access for remote administration of the masternode wallet. Otherwise simply delete the line and log in to the VDS via SSH for administration
ethf is the username to be used by the administration utility ethf-cli for access; you can assign any other name
YourPassword is your password for any operations with ethf-cli
e) Exit from directory .ethf, run wallet demon using this command: 

    ./ethfd

To make sure it is running use this command:

    ps ax | grep ethfd | grep -v grep

This will result in the following line:
10036         SLsl 906:03 ./ethfd
Exact numbers do not matter; as long as the line is there everything is fine; if not, you can look for causes in ./ethf/debug.log
If you have several masternodes, you can repeat the first step for each of them without waiting for the synchronization to complete. All further steps must always be done consecutively, as mentioned above.
Wait 15-30 minutes for full synchronization of the new node (not a masternode yet) with the network.
To make sure synchronization is complete use this command:

    ./ethf-cli -rpcconnect=xxx.xxx.xxx.xxx -rpcuser=ethf -rpcpassword=YourPassword getchaintips

This will result in the following response

    [
	    {
	    "height" : 13085,
	    "hash" : "00000011b4dfeb395f374ebd09892578c01e91e97223e208c15e014c8324b49b",
	    "branchlen" : 0,
	    "status" : "active"
	    }
    ]

height (13085 in the example) is the number of the last synchronized block. Check http://explorer.ethereumfuture.net; if block number in the response is the same as the last block number on the website it means your wallet has synchronized successfully and is operating correctly.
Normally, this is not necessary; if everything was set up according to the instructions all you need to do is to wait a little while.
Now you can begin to set up the masternode itself.

2 Create a separate address in your wallet (local, on your PC) for the new masternode (via Debug Console; see above for instructions on how to open it)
Enter the following command:

    getnewaddress MasterNode1

The response will look like the following address (yours will be different but also starting with f)
fZdXkYr53bzFDDwKNTNACeWFsVhPYSRaBh
Write the address down and enter the next command

    sendtoaddress fZdXkYr53bzFDDwKNTNACeWFsVhPYSRaBh 1000

You will get a long transaction number, write it down too (copy/paste to notepad); it will come up later more than once:
bd7003525b6fe43e8f099cbb9ef2f59924c47a6475b60dd6fdd9fef43c11f7d3
3) Take a break for a cigarette, coffee, or gym: the transaction needs to get a minimum of 16 confirmations (at least 30 mins).
Now check the number of confirmations received by the transaction at the wallet main page: upon mouse over, a pop-up window will show the number. If the number has not reached 16 yet, go have another coffee. If more than 16, go to step 4.
4) Via debug console again, send the following command:

    createmasternodekey

The response will be the masternode key, write it down:
7qfViUz8Xs9anFkCjxCChruMFw6FftpWpQGoFojNB23B6Gz2YUc
Enter the next command:

    masternode outputs

The response will look like the line below for one masternode, or a set of lines for several masternodes; look for the line where transaction number (long number) is the same as received in response to sendtoaddress.

    {
    "bd7003525b6fe43e8f099cbb9ef2f59924c47a6475b60dd6fdd9fef43c11f7d3": "0"
    }

The character after the colon ("0" in this case) will be numeric; write it down too.
Now you have all you need to start your masternode.
5) Enter your new masternode data into the wallet configuration (at your local system).
If you use Linux, all config files will be in the following folder:

    /home/yourname/.ethf

In Windows 7, the folder you need is:

    C:\Users\username\AppData\Roaming\ethf\

In Mac:

    /Users/username/Library/Application Support/ethf/

In this folder, we need masternode.conf. Add the following line to the file (single line):

    mn1 xxx.xxx.xxx.xxx:52545 7qfViUz8Xs9anFkCjxCChruMFw6FftpWpQGoFojNB23B6Gz2YUc bd7003525b6fe43e8f099cbb9ef2f59924c47a6475b60dd6fdd9fef43c11f7d3 0

Where mn1 is masternode ID, anything you like; first long number is the masternode key you got earlier; second long number is the transaction number above; the last number is your response after running masternode outputs; and xxx.xxx.xxx.xxx is your new masternode IP address.
IMPORTANT In case of several masternodes, make sure to check you do not simply copy and paste but change names and addresses correctly and enter new relevant data for each masternode added. If you make a mistake, you will have to wait for a while before the correction is processed. Please be mindful.
6) Restart the wallet, go to "masternodes". If everything is OK, the masternode description line must appear.
Left-click on the masternode to choose it, right-click to open menu, find "start alias" and click it. The masternode Status must display ENABLE now.
7) Go to the server where your masternode will be hosted (under the masternode user, not under root!). In the config file created earlier (see above) delete initial # in the line #listen=1; delete initial # in the line masternodeprivkey=, and insert the masternode key you got earlier in the same line after =. The resulting lines will look like this:

    listen=1
    masternodeprivkey=7qfViUz8Xs9anFkCjxCChruMFw6FftpWpQGoFojNB23B6Gz2YUc

8 Restart the demon.
Stop it.

    ./ethf-cli -rpcconnect=xxx.xxx.xxx.xxx -rpcuser=ethf -rpcpassword=YourPassword stop
    Enter
    ps ax | grep ethfd | grep -v grep

This must result in an empty line response; wait for it.
After that restart the daemon, using

    ./ethfd

Run this command:

    ps ax | grep ethfd | grep -v grep

to make sure the demon is running. If not, see the first part of this guide for reference on the errors.
Wait for at least one block (2-3 minutes)
If everything is OK, your masternode should have started already. Run this command to check it:

    ./ethf-cli -rpcconnect=xxx.xxx.xxx.xxx -rpcuser=ethf -rpcpassword=YourPassword masternode status

If you followed the instructions and complied with the wait time above, you will see this:

    {
	    "txhash" : "bd7003525b6fe43e8f099cbb9ef2f59924c47a6475b60dd6fdd9fef43c11f7d3",
	    "outputidx" : 0,
	    "netaddr" : "xxx.xxx.xxx.xxx:52545",
	    "addr" : "fZdXkYr53bzFDDwKNTNACeWFsVhPYSRaBh",
	    "status" : 4,
	    "message" : "Masternode successfully started"
    }

The main line here is "message": "Masternode successfully started"
If you see something else you must have skipped some wait time (did not allow the minimum of 16 blocks after running sendtoaddress). Wait for about 5 minutes and try to initiate the system manually entering:

    ./ethf-cli -rpcconnect=xxx.xxx.xxx.xxx -rpcuser=ethf -rpcpassword=YourPassword masternode start all

Run this command to check:

    ./ethf-cli -rpcconnect=xxx.xxx.xxx.xxx -rpcuser=ethf -rpcpassword=YourPassword masternode status

If the system is still not active, try manual startup again. This can take time and patience; it is always better to comply with the instructions to the letter and go have a coffee if it says so :-)
9) Finally, you need to set up your masternode to start automatically upon restart of your VDS. To do this log in under root and add the following line into 

    /etc/crontab
    @reboot ethfn  /home/yourmasternodehome/ethfd

10) Celebrate successful completion of masternode setup and startup and your new source of stable passive income, accept congratulations from your friends and family. Congratulations from our Ethereum Future team! Glad you joined us!

