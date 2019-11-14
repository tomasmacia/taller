# taller
Yet another Beat 'em up game


### Build

Execute `./build.sh` in your terminal.

### Run

Run `./bin/game` which accepts the following arguments:
 1. `-c` or `--config` to specify a path to a XML config. Will use default file when not specified or error loading
 2. `-l` or `--logger` to specify a default logger level
 3. `-m` or `--mode` to specify a mode (CLIENT or SERVER)
 4. `-a` or `--address` to specify a server address (when mode is CLIENT)
 5. `-p` or `--port` to specify a port for the server/client
 6. `-u` or `--users` to specify a file with credentials for login. Will use default file when not specified or error loading
 
Example with two players

1) SERVER 

`./bin/game -c configs/2p.xml -l DEBUG -m SERVER -p 5000`

2) CLIENT  

`./bin/game -c configs/2p.xml -l DEBUG -m CLIENT -a 127.0.0.1 -p 5000`