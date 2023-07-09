# Clip Share
### Copy on one device. Paste on another device

<br>
This is the server that runs in the background.
<br>
<br>

## Building
This needs,
* gcc
* make

### Dependencies
#### Linux
The following development libraries are required.
* libx11
* libxmu
* libpng
* libssl

They can be installed with the following command:

* on Debian or Ubuntu based distros,
```bash
sudo apt-get install libx11-dev libxmu-dev libpng-dev libssl-dev
```

* on Redhat or Fedora based distros,
```bash
sudo yum install libX11-devel libXmu-devel libpng-devel openssl-devel
```

* on Arch based distros,
```bash
sudo pacman -S libx11 libxmu libpng openssl
```

#### Windows
The following development libraries are required.
* libz
* libpng16
* libssl (provided by openssl)

### SSL/TLS certificate and key files
**Note** : This section is optional if you do not need the TLS encrypted mode and the web mode.
<br>
The following files should be created and placed in the `cert_keys/` directory and specified in the configuration file `clipshare.conf`. You may use different file names and paths to store the keys and certificates.
* ``server.key`` &ensp; : &nbsp; SSL/TLS key file for the server
* ``server.crt`` &ensp; : &nbsp; SSL/TLS certificate file of the server
* ``ca.crt`` &emsp;&emsp;&ensp; : &nbsp; SSL/TLS certificate of the CA which signed the server.crt

### Compiling
Run the following command to make the executable file.
```bash
make
```
This will generate the executable which is named clip_share (or clip_share.exe on Windows).

To compile with the web server enabled, (Currently, this is supported only on Linux)
```bash
make web
```
This will generate the web server enabled executable which is named clip_share_web.

<br>

## Allow through firewall
This server listens on the following ports (unless different ports are assigned from the configuration),

* ``4337`` &nbsp;&nbsp; ``TCP`` &nbsp;&nbsp; : &nbsp;&nbsp; For application traffic (not encrypted)
* ``4337`` &nbsp;&nbsp; ``UDP`` &nbsp;&nbsp; : &nbsp;&nbsp; For network scanning
* ``4338`` &nbsp;&nbsp; ``TCP`` &nbsp;&nbsp; : &nbsp;&nbsp; For application traffic over TLS (encrypted)
* ``4339`` &nbsp;&nbsp; ``TCP`` &nbsp;&nbsp; : &nbsp;&nbsp; For the web server (if the web server is available)

You may need to allow incoming connections to the above ports for the client to connect to the server.

<br>

## How to use
### Run the server

When the server is started, it will not open any window. Instead, it will run in the background.
If the program is started from the terminal, it should return immediately (server will continue to run in the background).
If something goes wrong, a server_err.log file will be created and it will contain what went wrong.

### Connect the client application

Open the client application on any other device on the same network.
If the client supports network scanning, the server can be easily found. Otherwise, enter the server's IPv4 address to the client.
Now the client should be able to share clipboard data, files, and get images from the server.
Note that the client should be allowed through the firewall as mentioned in the above section.

<br>

## Configuration
Create a file named &nbsp; ``clipshare.conf`` &nbsp; and add the following lines into that configuration file

```properties
app_port=4337
app_port_secure=4338
web_port=4339
insecure_mode_enabled=true
secure_mode_enabled=true
web_mode_enabled=true
server_key=cert_keys/server.key
server_cert=cert_keys/server.crt
ca_cert=cert_keys/ca.crt
allowed_clients=allowed_clients.txt
working_dir=./path/to/work_dir
```

Note that all the lines in the configuration file are optional. You may omit some lines if they need to get their default values.

* `insecure_mode_enabled`: Whether or not the application listens for unencrypted connections. The values `true` or `1` will enable it, while `false` or `0` will disable it. The default value is `1`.
* `app_port`: The port on which the application listens for unencrypted TCP connections. The application listens on the same port for UDP for network scanning. The default value is `4337`
* `secure_mode_enabled`: Whether or not the application listens for TLS-encrypted connections. The values `true` or `1` will enable it, while `false` or `0` will disable it. The default value is `1`.
* `app_port_secure`: The TCP port on which the application listens for TLS-encrypted connections. The default value is `4338`
* `web_mode_enabled`: Whether or not the application listens for TLS-encrypted connections from web clients if the web mode is available. The values `true` or `1` will enable it, while `false` or `0` will disable it. The default value is `1`.
* `web_port`: The TCP port on which the application listens for TLS-encrypted connections for web clients. This setting is used only if web mode is available. The default value is `4339`
* `server_key`: The TLS private key file of the server. If this is not specified, secure mode will be disabled.
* `server_cert`: The TLS certificate file of the server. If this is not specified, secure mode will be disabled.
* `ca_cert`: The TLS certificate file of the CA that signed the TLS certificate of the server. If this is not specified, secure mode will be disabled.
* `allowed_clients`: The text file containing a list of allowed clients (Common Name of client certificate), one name per each line. If this is not specified, secure mode will be disabled.
* `working_dir`: The working directory where the application should run. All the files, that are sent from a client, will be saved in this directory. This path can be an absolute or a relative path to an existing directory. It will follow symlinks. The default value is the current directory.

You may change those values. But it is recommended to keep the port numbers unchanged. If the port numbers are changed, client application configurations may also need to be changed as appropriate to connect to the server.
