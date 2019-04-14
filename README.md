
**Tute** <= **mytetra_webengine** <= **MyTetra** -- Thanks to MyTetra

Tute aims to provide some basic components of personal knowledge management in a free/libre, open source and decentralized way.

Currently,

It has a note component working on topics.

It has an embedded and customized web browser, which provides an easy way to combine tabs, bookmarks and history management together (the browser currently derived from Qt::WebEngine (Chromium-based)).

Local and internet search functions come out from the note and the browser.

It has a client. You can manage your remote service via XML-RPC.

If someday,

It can listen to some local screen capture or other content queries triggered by the user, that should not be a surprise.

Same as the real-time collaborative editing functions, should it?

Should you expect more novel features? feel free to contact me: hughvonyoung[at]gmail.com.

Welcome to fork and give back :)

Please note that Tute is distributed under the GPL v3.

## How to remote synchronize Tute
_______________________________________________________________________

Currently I chose Dropbox

Move files to Dropbox:
```
	rsync -n -avhSDHAX  --progress --delete --ignore-errors --force --stats "./bin/" "~/dropbox/knowledge\ management/."
```
After that, change settings from contextmenu of Record View on the left side: Main Menu: Tools: Main Preferences: "Main" tag: "Root directory". Point it to the parent folder where you want "data" and "trash" to locate (E.g.: "~/dropbox/knowledge\ management/bin". Leave the "Data directory" and the "Trash directory" as "./data" and "./trash" are OK).

## How to build Tute
_______________________________________________________________________

### 1 Build on Linux

Let's say the directory of your current project is named "working":
```
	working
            |____verdigris (created by or synchronized with git) (does not needed from Qt 5.7 and later versions)
	    |       |____src
	    |
	    |____knowledge management (name is whatever)
		    |____tute (created by or synchronized with git)
```
#### 1.1 Install C++ Boost library (for boost::intrusive_ptr, boost::MPL, and some others. I installed it from package manager)

#### 1.2 Install verdigris (only needed by remove qt::moc in Qt 5.6. Two header-only files.)
```
	git clone https://github.com/woboq/verdigris.git
```
#### 1.3 Download and install Qt packages (May 18, 2017: qt-unified-linux-x64-2.0.5-2-online.run)
```
        wget http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
        chmod a+x ./qt-unified-linux-x64-online.run
        ./qt-unified-linux-x64-online.run
```
* Run the installation. Default location for administrator installation (hereafter called "path-to-qt-installation"):
<<<<<<< HEAD
```
        /opt
```
But it's not a must. Current support Qt version: 5.10.0.
=======
>>>>>>> tuple

* Environment in ~/.profile (~/.bash_profile or ~/.bashrc) for command line build and installation
```
	QT5DIR=/path-to-qt-installation/gcc_64

	export QT5DIR

	if ! echo ${PATH} | /bin/grep -q $QT5DIR/bin ; then

	    PATH=$QT5DIR/bin:${PATH}

	    PKG_CONFIG_PATH=$QT5DIR/lib/pkgconfig:${PKG_CONFIG_PATH}

	fi

	QT5INC="$QT5DIR/include"

	QT5LIB="$QT5DIR/lib"

	QT5LIB=$QT5DIR/plugins/platforms:${QT5LIB}

	PATH=$QT5INC:${PATH}

	PATH=$QT5LIB:${PATH}

	export QT5DIR QT5INC QT5LIB PATH
```
* After modified the above file, use
```
.  ~/.bashrc
```
* to export it.

* Do not recommend to mix it up with system installation of Qt
* If you compile and debug the project by qt-creator, environment variable could be overrided by qt-creeator. So you can skip the shell settings and just check them in qt-creator's "Projects" mode => "Build Environment" settings as following:
```
Set QT5DIR to /path-to-qt-installation
Set PATH to ${QT5DIR}/bin:${QT5LIB}:${QT5INC}:/path-to-compiler-installation/bin:/path-to-compiler-installation/include:/path-to-compiler-installation/lib:...
Set QT5INC to ${QT5DIR}/include
Set QT5LIB to ${QT5DIR}/plugins/platforms:${QT5DIR}/lib

```
<<<<<<< HEAD
* If you want to switch qt lib version manually, I usually change the environment variable like this:
```
export PATH=/path-to-qt-installation/bin:/path-to-qt-installation/plugins/platforms:/path-to-qt-installation/lib:/path-to-qt-installation/include:/path-to-compiler-installation/bin:/path-to-compiler-installation/include:/path-to-compiler-installation/lib:$PATH
env |grep QT
then export corresponding variables to current version.

```
####1.4 Clone the repo to your workbench
=======
#### 1.4 Clone the repo to your workbench
>>>>>>> tuple
```
	git clone https://github.com/beimprovised/tute.git
```
#### 1.5 Compile
```
	/path-to-qt-installation/gcc_64/bin/qmake tute.pro
        make -j$(nproc) all
	sudo make install
```
* Or via GUI (Compile the Qt project file with Qt-Creator which comes with Qt 5.7 or more recent version):
        Open "tute.pro" under tute in qtcreator
        "Configure" the project in qtcreator (append "-j*" with prefer progress number * to "make" options might be better)
        Build it.

#### 1.6 Input methods (for non-English users)
```
                // Suppose we chose Fcitx:
                // On Ubuntu:
        sudo apt-get install fcitx-frontend-qt5
                // libfcitxplatforminputcontextplugin.so should be under /usr/lib/x86_64-linux-gnu/qt5/plugins/platforminputcontexts/ or somewhere from:
        locate libfcitxplatforminputcontextplugin.so
                // Then copy it to $${PROJECT_QT_VERSION}/plugins/platforminputcontexts:
        cp /path/to/libfcitxplatforminputcontextplugin.so /path/to/$${PROJECT_QT_VERSION}/plugins/platforminputcontexts/.
                // Or modify tute.pro with:
        LIBS            += /path/to/libfcitxplatforminputcontextplugin.so
                // Then put following lines in your ~/.bashrc
        export GTK_IM_MODULE=fcitx
        export QT_IM_MODULE=fcitx
        export XMODIFIERS="@im=fcitx"
                // Or at least put this variable in your Qt-Creator::Projects settings::Build Environment:
        QT_IM_MODULE=fcitx
                // When build from command line, make sure
        echo $QT5DIR
                // The output should not be empty. If it is, try to do
        export QT5DIR=/path-to-qt-installation/gcc_64

```

_______________________________________________________________________

## Thanks to MyTetra: Tute is forked from mytetra_webengine and mytetra_webengine is forked from MyTetra
_______________________________________________________________________

ENG: Central source repository for MyTetra development.
MyTetra official english page: [http://webhamster.ru/site/page/index/articles/projectcode/138](http://webhamster.ru/site/page/index/articles/projectcode/138)

RUS: Основной репозитарий исходников для разработки MyTetra.
Официальная русскоязычная страница программы MyTetra: [http://webhamster.ru/site/page/index/articles/projectcode/105](http://webhamster.ru/site/page/index/articles/projectcode/105)

Agreement on the coding (registration code)

_______________________________________________________________________

###When writing code to be guided by the following agreements:



* If a staitc polymorphism is feasible, escape dynamic one.
* Keep class abstraction as possible as you could.
* If a function you used it just once, use a lambda;


* The name of the file with the implementation of the class is based on the principle ClassName.cpp/classname.cxx (prefer: class_name.cxx);
* The name of the file with the title of class is based on the principle ClassName.hxx/classname.hxx/classname.h (prefer: class_name.hxx);
* The name of the class is based on the principle ClassName;
* The name of the method is based on the principle method_name (underscore);
* The name of the member variables is based on the principle _parameter_name (underscore), and get set name is parameter_name(...);


* Function name begin with the aspect which it belongs to. If the name is not enough, newly created method should contain a comment that describes what the method does. So it is desirable to describe the purpose of the method parameters;
* The header class, after the section is necessary in #include class assignment to write comments.
* Each header file must have the following structure:
```
	\#ifndef _CLIPBBRANCH_H_

	\#define _CLIPBBRANCH_H_

	...

	\#endif // _CLIPBBRANCH_H_
```
* The program is designed as a cross-platform Qt-only application. Program should not depend on third-party libraries that are not part of Qt unless you could provide its source code to the project under free/libre and open source licenses.
* Source file encoding: UTF-8;
* Comment the code in English languages;


* Tab prohibited padding spaces are made (use folling code beautifiers);
* Margin - 0 spaces (use style sheet);
* Comments must have the same indentation that of the code (use folling code beautifiers);



Branches at GIT
_______________________________________________________________________

The system Git created two main branches.

For mytetra_webengine

* origin       - the main branch with the latest stable release;
* develop      - branch to develop.

For Tute:

* master            - the main branch with the latest stable release;
* develop           - branch to develop.
* code beautifier   - uncrustify (deprecated)
```
        find . -iname "*.h" -or -iname "*.cpp" -or -iname "*.cxx" > files.txt
        uncrustify -c src/uncrustify.cfg  -l CPP --replace --no-backup -F ./files.txt
```
* code beautifier   - clang-format::WebKit (to save time)
```
        find . -iname "*.h" -or -iname "*.hxx" -or -iname "*.inl" -or -iname "*.cpp" -or -iname "*.cxx" | xargs clang-format -i -style=WebKit
        // if you have a .clang-format under currrent directory (clang-format -style=webkit -dump-config > .clang-format), then:
        find . -iname "*.h" -or -iname "*.hxx" -or -iname "*.inl" -or -iname "*.cpp" -or -iname "*.cxx" | xargs clang-format -i -style=file
```

Besides these two branches have been established in other branches for the implementation of a functional. Upon completion of the changes flow into the branch experimental. After stabilization of the changes in the experimental, the changes flow into the master and release is issued.

Deciding to connect to the development Tute, please use the develop branch for the current code.
