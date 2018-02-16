Ethereum Future Core
=====================

Setup
---------------------
[Ethereum Future Core](https://www.ethereumfuture.net/) is the original Ethf client and it builds the backbone of the network. However, it downloads and stores the entire history of Ethf transactions; depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once.

Running
---------------------
The following are some helpful notes on how to run Ethf on your native platform.

### Unix

Unpack the files into a directory and run:

- bin/32/ethf-qt (GUI, 32-bit) or bin/32/ethfd (headless, 32-bit)
- bin/64/ethf-qt (GUI, 64-bit) or bin/64/ethfd (headless, 64-bit)

### Windows

Unpack the files into a directory, and then run ethf-qt.exe.

### OSX

Drag Ethf-Qt to your applications folder, and then run Ethf-Qt.

### Need Help?

* See the documentation at the [Ethf Wiki](https://github.com/ethereumfuture/ethf/wiki)
for help and more information.
* Ask for help on [BitcoinTalk](FIXME Add official BCT URL on ANN) or on the [Ethf Discord](https://discord.gg/a7vhegP).

Building
---------------------
The following are developer notes on how to build Ethf on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Ethf repo's [root README](https://github.com/ethereumfuture/ethf/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/bitcoin/doxygen/) ***TODO***
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT/X11 software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
