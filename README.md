# R-Type - Epitech Project  
  
The repository for the R-Type project.  
  
<div id="pictureRType" style="display: flex;">  
  <img src="docs/readmePicture/pictureRType.jpg" alt="picture R-TYpe" width="300" height="150" style="margin-right: 50px;">  
  <img src="docs/readmePicture/pictureEpitech.png" alt="picture Epitech" width="150" height="150" style="margin-right: 50px;">  
</div>  

---  
  
## Table of contents  
  
[The purpose of the project 👽](#purpose_project)<br />
[The subjects of the project 📄](#subject_project)<br />
[Rules for conventional commit messages ➕](#conventionnal_commit)<br />
[Requirements 🔧](#requirements)<br />
[How to use R-Type 👨‍💻](#use_R-Type)<br />
[Contributors 👋](#contributors)<br />
[License 🔑](#license)<br />
  
---  
  
## <a id="purpose_project"></a> The purpose of the project 👽  
  
The purpose of the project is to implement a multithreaded server and a graphical client for a well-known legacy video game **called R-Type**, using a game engine of your own design.  
  
### <a id="subject_project"></a> The subjects of the project 📄  
  
[R-Type - A game engine that roars!](https://intra.epitech.eu/module/2023/B-CPP-500/PAR-5-2/acti-622530/project/file/B-CPP-500_rtype.pdf)  
  
### <a id="conventionnal_commit"></a> Rules for conventional commit messages ➕  
  
[The document rules for conventional commit messages](docs/COMMITS.md)  

If you would like to contribute to the project, see [CONTRIBUTING.md](CONTRIBUTING.md)  
  
---  
  
## <a id="requirements"></a> Requirements 🔧  
  
* The minimum cmake version required is 3.5.X  

You can use this setup command:
```
apt install -y zip curl unzip pip python3.11-venv libudev-dev libgl-dev libgl1-mesa-dev libx11-dev libx11-xcb-dev libfontenc-dev libice-dev libsm-dev libxau-dev libxaw7-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxfixes-dev libxi-dev libxinerama-dev libxkbfile-dev libxmuu-dev libxrandr-dev libxres-dev libxss-dev libxtst-dev libxv-dev libxvmc-dev libxxf86vm-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev libxcb-cursor-dev libxcb-util-dev libxcb-util0-dev libopenal-dev libvorbis-dev libflac-dev
```

## <a id="use_R-Type"></a> How to use R-Type 👨‍💻  
  
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
  
## <a id="contributors"></a> Contributors 👋  
  
| [<img src="https://github.com/Drindael.png?size=85" width=85><br><sub>Cyprien Nguyen-Van-Vien</sub>](https://github.com/Drindael) | [<img src="https://github.com/damienBC.png?size=85" width=85><br><sub>Damien Benais-Captal</sub>](https://github.com/damienBC) | [<img src="https://github.com/Pierrelouisleroy.png?size=85" width=85><br><sub>Pierre-Louis Leroy</sub>](https://github.com/Pierrelouisleroy) | [<img src="https://github.com/Hinivir.png?size=85" width=85><br><sub>Viktor Bruggeman</sub>](https://github.com/Hinivir) | [<img src="https://github.com/Lipatant.png?size=85" width=85><br><sub>Virgile Berrier</sub>](https://github.com/Lipatant)  
| :--: | :--: | :--: | :--: | :--: |  
  
cyprien.nguyen-van-vien@epitech.eu    
damien.benais-captal@epitech.eu    
pierre-louis.leroy@epitech.eu    
viktor.bruggeman@epitech.eu    
virgile.berrier@epitech.eu    

---  
  
## <a id="license"></a> License 🔑  

You can have a look at the [MIT license](LICENSE.md) of the project.
