# Run in docker

Simple and fast setup of OAC.IO on Docker is also available.

## Install Dependencies

- [Docker](https://docs.docker.com) Docker 17.05 or higher is required
- [docker-compose](https://docs.docker.com/compose/) version >= 1.10.0

## Docker Requirement

- At least 7GB RAM (Docker -> Preferences -> Advanced -> Memory -> 7GB or above)
- If the build below fails, make sure you've adjusted Docker Memory settings and try again.

## Build oac image

```bash
git clone https://github.com/OACIO/oac.git --recursive  --depth 1
cd oac/Docker
docker build . -t oac/oac
```

The above will build off the most recent commit to the master branch by default. If you would like to target a specific branch/tag, you may use a build argument. For example, if you wished to generate a docker image based off of the v1.0.1 tag, you could do the following:

```bash
docker build -t oac/oac:v1.0.1 --build-arg branch=v1.0.1 .
```

By default, the symbol in oac.system is set to SYS. You can override this using the symbol argument while building the docker image.

```bash
docker build -t oac/oac --build-arg symbol=<symbol> .
```

## Start nodoac docker container only

```bash
docker run --name nodoac -p 8888:8888 -p 9876:9876 -t oac/oac nodoacd.sh -e arg1 arg2
```

By default, all data is persisted in a docker volume. It can be deleted if the data is outdated or corrupted:

```bash
$ docker inspect --format '{{ range .Mounts }}{{ .Name }} {{ end }}' nodoac
fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
$ docker volume rm fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
```

Alternately, you can directly mount host directory into the container

```bash
docker run --name nodoac -v /path-to-data-dir:/opt/oac/bin/data-dir -p 8888:8888 -p 9876:9876 -t oac/oac nodoacd.sh -e arg1 arg2
```

## Get chain info

```bash
curl http://127.0.0.1:8888/v1/chain/get_info
```

## Start both nodoac and koacd containers

```bash
docker volume create --name=nodoac-data-volume
docker volume create --name=koacd-data-volume
docker-compose up -d
```

After `docker-compose up -d`, two services named `nodoacd` and `koacd` will be started. nodoac service would expose ports 8888 and 9876 to the host. koacd service does not expose any port to the host, it is only accessible to cloac when running cloac is running inside the koacd container as described in "Execute cloac commands" section.

### Execute cloac commands

You can run the `cloac` commands via a bash alias.

```bash
alias cloac='docker-compose exec koacd /opt/oac/bin/cloac -u http://nodoacd:8888 --wallet-url http://localhost:8888'
cloac get info
cloac get account inita
```

Upload sample exchange contract

```bash
cloac set contract exchange contracts/exchange/
```

If you don't need koacd afterwards, you can stop the koacd service using

```bash
docker-compose stop koacd
```

### Develop/Build custom contracts

Due to the fact that the oac/oac image does not contain the required dependencies for contract development (this is by design, to keep the image size small), you will need to utilize the oac/oac-dev image. This image contains both the required binaries and dependencies to build contracts using oaccpp.

You can either use the image available on [Docker Hub](https://hub.docker.com/r/oac/oac-dev/) or navigate into the dev folder and build the image manually.

```bash
cd dev
docker build -t oac/oac-dev .
```

### Change default configuration

You can use docker compose override file to change the default configurations. For example, create an alternate config file `config2.ini` and a `docker-compose.override.yml` with the following content.

```yaml
version: "2"

services:
  nodoac:
    volumes:
      - nodoac-data-volume:/opt/oac/bin/data-dir
      - ./config2.ini:/opt/oac/bin/data-dir/config.ini
```

Then restart your docker containers as follows:

```bash
docker-compose down
docker-compose up
```

### Clear data-dir

The data volume created by docker-compose can be deleted as follows:

```bash
docker volume rm nodoac-data-volume
docker volume rm koacd-data-volume
```

### Docker Hub

Docker Hub image available from [docker hub](https://hub.docker.com/r/oac/oac/).
Create a new `docker-compose.yaml` file with the content below

```bash
version: "3"

services:
  nodoacd:
    image: oac/oac:latest
    command: /opt/oac/bin/nodoacd.sh -e
    hostname: nodoacd
    ports:
      - 8888:8888
      - 9876:9876
    expose:
      - "8888"
    volumes:
      - nodoac-data-volume:/opt/oac/bin/data-dir

  koacd:
    image: oac/oac:latest
    command: /opt/oac/bin/koacd
    hostname: koacd
    links:
      - nodoacd
    volumes:
      - koacd-data-volume:/opt/oac/bin/data-dir

volumes:
  nodoac-data-volume:
  koacd-data-volume:

```

*NOTE:* the default version is the latest, you can change it to what you want

run `docker pull oac/oac:latest`

run `docker-compose up`

### OACIO 1.0 Testnet

We can easily set up a OACIO 1.0 local testnet using docker images. Just run the following commands:

Note: if you want to use the mongo db plugin, you have to enable it in your `data-dir/config.ini` first.

```
# pull images
docker pull oac/oac:v1.0.1

# create volume
docker volume create --name=nodoac-data-volume
docker volume create --name=koacd-data-volume
# start containers
docker-compose -f docker-compose-oac1.0.yaml up -d
# get chain info
curl http://127.0.0.1:8888/v1/chain/get_info
# get logs
docker-compose logs -f nodoacd
# stop containers
docker-compose -f docker-compose-oac1.0.yaml down
```

The `blocks` data are stored under `--data-dir` by default, and the wallet files are stored under `--wallet-dir` by default, of course you can change these as you want.

### About MongoDB Plugin

Currently, the mongodb plugin is disabled in `config.ini` by default, you have to change it manually in `config.ini` or you can mount a `config.ini` file to `/opt/oac/bin/data-dir/config.ini` in the docker-compose file.
