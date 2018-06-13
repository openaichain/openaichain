#!/bin/sh
cd /opt/oac/bin

if [ -f '/opt/oac/bin/data-dir/config.ini' ]; then
    echo
  else
    cp /config.ini /opt/oac/bin/data-dir
fi

if [ -d '/opt/oac/bin/data-dir/contracts' ]; then
    echo
  else
    cp -r /contracts /opt/oac/bin/data-dir
fi

while :; do
    case $1 in
        --config-dir=?*)
            CONFIG_DIR=${1#*=}
            ;;
        *)
            break
    esac
    shift
done

if [ ! "$CONFIG_DIR" ]; then
    CONFIG_DIR="--config-dir=/opt/oac/bin/data-dir"
else
    CONFIG_DIR=""
fi

exec /opt/oac/bin/nodoac $CONFIG_DIR "$@"
