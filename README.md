# R-Type - Epitech Project  
  
The repository for the R-Type project.  
  
---  
  
## Table of contents  
  
[1. The purpose of the project](#titre1)<br />  
[A) The subjects of the project 📄](#titre11)<br />  
[B) Rules for conventional commit messages 📄](#titre12)<br />  
  
[2. How to use R-Type](#titre2)<br />  
  
[3. People on the project](#titre3)<br />  
  
---  
  
## <a id="titre1"></a>1. The purpose of the project  
  
The purpose of the project is to implement a multithreaded server and a graphical client for a well-known legacy video game **called R-Type**, using a game engine of your own design.  
  
### <a id="titre11"></a>A) The subjects of the project 📄  
  
[R-Type - A game engine that roars!](https://intra.epitech.eu/module/2023/B-CPP-500/PAR-5-2/acti-622530/project/file/B-CPP-500_rtype.pdf)  
  
### <a id="titre12"></a>B) Rules for conventional commit messages 📄  
  
[The document rules for conventional commit messages](docs/COMMITS.md)  
  
---  
  
## <a id="titre2"></a>2. How to use R-Type  
  
### Build and setup

First, you need to build the project to do so, create, or go to, a file name **build** then executes the following commands:

```bash
cd build/
cmake ..
```

The binaries will be generated and the necessary dependancies will be installed.

### Launch the server

The binary of the server can be found in **/app/Server/**.<br />
You can launch the server by running this command:

```bash
./L-Type-Server [ip] [port]
```

where **ip** is the ip you want the other users to connect, and **port** is the port where the server will be running.

### Connect a client

The binary of the client can be found in **/app/Client/**.<br />
You can launch a client by running this command:

```bash
./L-Type-Client [ip] [port]
```

where **ip** is the ip where the server is running, and **port** is the port where the server runs.<br />
You can connect as many clients as you want.

---  
  
## <a id="titre3"></a>3. Contributors  
  
| [<img src="https://github.com/Drindael.png?size=85" width=85><br><sub>Cyprien Nguyen-Van-Vien</sub>](https://github.com/Drindael) | [<img src="https://github.com/damienBC.png?size=85" width=85><br><sub>Damien Benais-Captal</sub>](https://github.com/damienBC) | [<img src="https://github.com/Pierrelouisleroy.png?size=85" width=85><br><sub>Pierre-Louis Leroy</sub>](https://github.com/Pierrelouisleroy) | [<img src="https://github.com/Hinivir.png?size=85" width=85><br><sub>Viktor Bruggeman</sub>](https://github.com/Hinivir) | [<img src="https://github.com/Lipatant.png?size=85" width=85><br><sub>Virgile Berrier</sub>](https://github.com/Lipatant)  
| :--: | :--: | :--: | :--: | :--: |  
  
cyprien.nguyen-van-vien@epitech.eu    
damien.benais-captal@epitech.eu    
pierre-louis.leroy@epitech.eu    
viktor.bruggeman@epitech.eu    
virgile.berrier@epitech.eu    
